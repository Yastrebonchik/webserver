#include "cgi.hpp"

std::string NumToString(size_t num)
{
	std::string s = std::to_string(num);
	return s;
}

CGI::CGI(RequestHeaders const &client, LocationClass location, ConnectionClass connection, std::string const &path) :
client_(client), location_(location), connection_(connection), ptrFile(NULL), ptrCgiFile(NULL), env_(NULL)  //Конструктор для СиЖиаИ ЗДЕСЬ!!!
{
	//char cwd[PATH_MAX + 1];
	//getcwd(cwd, sizeof(cwd));
	// path = result.php
	std::string executable; // php

	executable = location.getCgi_dir() + "/" + location.getIndex();
	ptrFile = new std::string(executable); // php
	ptrCgiFile = new std::string(path);    //path = result.php

	args_[0] = ft_strdup(executable.c_str());        //FOR EXECVE,  - int execve(char *name, char *arv[], char *envp[])  - первый аргумент имя
	args_[1] = ft_strdup(path.c_str());
	args_[2] = NULL;
}

CGI::~CGI()
{
	int i = 0;
	std::map<std::string, std::string>::iterator it;

	for(it = envMap_.begin(); it != envMap_.end(); it++)
		delete(env_[i++]);
	delete(env_);
	unlink((*ptrCgiFile).c_str());
	delete(args_[0]);
	delete(args_[1]);
	delete ptrFile;
	delete ptrCgiFile;
}

void CGI::createMetaVariables()
{
	std::string	scrypt;
	//if (client_.getHeaderAuthorization().size() > 0)
	//{
		//std::string decoded = decode(client_.getHeaderAuthorization().at(WEBSERV_AUTH));     //ENCODING & DECODING
		//size_t pos = decoded.find(":");

		//envMap_["AUTH_TYPE"] = WEBSERV_AUTH;
		//envMap_["REMOTE_USER"] = decoded.substr(0, pos);   //shifrovanie for auth user
		//envMap_["REMOTE_IDENT"] = envMap_["REMOTE_USER"];
	//}
	if (client_.getBody().length() > 0)
	{
		envMap_["CONTENT_LENGTH"] = NumToString(client_.getBody().length());

		if (client_.get_contentType().length() > 0)
			envMap_["CONTENT_TYPE"] = client_.get_contentType();
	}
	scrypt = this->location_.getCgi_dir() + "/" + this->location_.getIndex();
	envMap_["GATEWAY_INTERFACE"] = "CGI/1.0";
	envMap_["PATH_INFO"] = *ptrCgiFile;   //Путь к запрошенному файлу - Директория СЖИ + Имя файла
	envMap_["PATH_TRANSLATED"] = *ptrFile;

	if (client_.getBody().length() > 0)
		envMap_["QUERY_STRING"] = client_.getBody();    //Собственно информация, которую нужно подставить и динамически изменить в запросе ".php" etc... Строка запроса

//	sockaddr_in addrCl;
//	socklen_t lenCl = sizeof(addrCl);
	//if (getsockname(client_.getWHAT(), (struct sockaddr *)&addrCl, &lenCl) == 0)
	//{
//	envMap_["REMOTE_ADDR"] = std::string(inet_ntoa(addrCl.sin_addr));
//	envMap_["REMOTE_PORT"] = NumToString(ntohs(addrCl.sin_port));
	//}
	envMap_["REQUEST_METHOD"] = client_.get_method();
	envMap_["REQUEST_URI"] = client_.get_uri();    //Путь к запрошенному файлу - Директория + Имя файла
	envMap_["SCRIPT_NAME"] = scrypt;
	envMap_["SERVER_NAME"] = connection_.getServer().getServer_name();       //Имя сервера
	envMap_["SERVER_PORT"] = NumToString(size_t(ntohs(connection_.getServer().getPort())));    //Порт сервера
	envMap_["SERVER_PROTOCOL"] = "HTTP/1.1";
	envMap_["SERVER_SOFTWARE"] = "Webserv/1.0";

	//this->createHttpMetaVariables();    //Надо ли вообще создавать переменные окружения НТТР 
}

void CGI::createCgiEnv()
{
	int i = 0;
	std::map<std::string, std::string>::iterator it;

	env_ = (char **)operator new(sizeof(char *) * (envMap_.size() + 1));
	if (env_ == NULL)
		;//ошибка
	for (it = envMap_.begin(); it != envMap_.end(); it++)
	{
		envir_ = (it->first + "=" + it->second);
		if (!(env_[i] = ft_strdup(envir_.c_str())))
			;//ошибка
		i++;
	}
	env_[i] = NULL;
}

std::string CGI::run(std::string &body)            // ЗАПУСК СиДЖиАй здесь!!!!! С Аргументом ДАТА! ДАТА и получит результат выполнения программы!
{
	this->createMetaVariables();
	this->createCgiEnv();

	//int fd_cgiFile = open((*ptrCgiFile).c_str(), O_RDONLY);
	//if (fd_cgiFile < 0)
	//{
	//	write(1, "CGI: fail to open file\n", 24);
	//	return "500";
	//}
	pid_t pid;
	int stdin_pipe[2];
	int stdout_pipe[2];

	if (pipe(stdin_pipe) != 0)
	{
		write(1, "CGI: Pipe error\n", 17);
		//close(fd_cgiFile);
		return "500";
	}
	if (pipe(stdout_pipe) != 0)
	{
		write(1, "CGI: Pipe 2 error\n", 19);
		//close(fd_cgiFile);
		return "500";
	}

	pid = fork();
	if (pid < 0)
	{
		write(1, "CGI: Fork error\n", 17);
		//close(fd_cgiFile);
		return "500";
	}

	int status = 0;

	if (pid == 0)
	{
		close(stdin_pipe[1]);
		close(stdout_pipe[0]);
		dup2(stdin_pipe[0], 0);
		dup2(stdout_pipe[1], 1);
		
		int exec_res = execve(args_[0], args_, env_);      //например выполняется файл result.php а там просто идет замена и-мейл адреса клиента, или же можно возраст имя итд, Я Дима, Мне 55 лет итд.

		write(1, "CGI: Execve error\n", 19);
		exit(exec_res);
	}
	else
	{
		close(stdin_pipe[0]);
		close(stdout_pipe[1]);
		if (client_.getBody().length() > 0)
			if (write(stdin_pipe[1], client_.getBody().c_str(), client_.getBody().length()) == -1)
			{
				write(1, "CGI: Write error\n", 18);
				kill(pid, SIGKILL);
				close(stdin_pipe[1]);
				return "500";
			}
		close(stdin_pipe[1]);

		if (waitpid(pid, &status, 0) == -1)
		{
			write(1, "CGI: Waitpid error\n", 20);
			return "500";
		}
		if (WIFEXITED(status) && WIFSIGNALED(status) != 0)
		{
			write(1, "CGI: return\n", 13);
			return "500";
		}
	}
	char buffer[1024 + 1] = {0};
	int ret;
	//body = "";
	while ((ret = read(stdout_pipe[0], buffer, 1024)) > 0)
		body.append(buffer, ret); 
	if (ret == -1)
	{
		body = "";
		write(1, "CGI: Error in file reading\n", 28);
		return "500";
	}

//	size_t pos = body_.find("\r\n\r\n");
//	if (pos == std::string::npos)        //не нашел если
//		return "500";                    //500 если неудачно
//
//	body_.erase(0, pos + 4);             //вырезать эти символы
	return "200";
}

//bool CGI::readFile(std::string const &file, std::string &body)
//{
//	char buffer[1024 + 1] = {0};
//	int fd;
//	int ret;
//
//	fd = open(file.c_str(), O_RDONLY);
//	if (fd < -1)
//	{
//		write(1, "CGI: File not open secondly\n", 29);
//		return false;
//	}
//
//	body = "";     //oblulenie
//	while ((ret = read(fd, buffer, 1024)) > 0)
//		body.append(buffer, ret);                   //В БОДИ перезаписывается видоизмененый файл after EXECVE
//
//	if (ret == -1)
//	{
//		body = "";
//		write(1, "CGI: Error in file reading\n", 28);
//		return false;
//	}
//	return true;
//}
