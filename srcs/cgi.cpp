#include "cgi.hpp"

std::string NumToString(size_t num)
{
	std::string s = std::to_string(num);
	return s;
}

CGI::CGI(RequestHeaders const &client, LocationClass location, ConnectionClass connection, std::string const &path) :
client_(client), location_(location), connection_(connection), ptrFile(NULL), ptrCgiFile(NULL), env_(NULL)  //Конструктор для СиЖиаИ ЗДЕСЬ!!!
{
	char cwd[PATH_MAX + 1];
	getcwd(cwd, sizeof(cwd));
	std::string	scrypt;

	ptrFile = new std::string(cwd + path.substr(1));
	ptrCgiFile = new std::string(path);    //Директория для СиЖиАй

	scrypt = location.getCgi_dir() + "/" + location.getIndex();
	args_[0] = ft_strdup(scrypt.c_str());        //FOR EXECVE,  - int execve(char *name, char *arv[], char *envp[])  - первый аргумент имя
	args_[1] = ft_strdup((*ptrFile).c_str());
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
	envMap_["PATH_INFO"] = scrypt;   //Путь к запрошенному файлу - Директория СЖИ + Имя файла
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
	//if (env_ == NULL)
		//ошибка
	for (it = envMap_.begin(); it != envMap_.end(); it++)
	{
		envir_ = (it->first + "=" + it->second);
		//if (!(env_[i] = ft_strdup(envir_.c_str())))
			//ошибка
		i++;
	}
	env_[i] = NULL;
}

std::string CGI::run(std::string &data)            // ЗАПУСК СиДЖиАй здесь!!!!! С Аргументом ДАТА! ДАТА и получит результат выполнения программы!
{
	this->createMetaVariables();
	this->createCgiEnv();

	int fd_cgiFile = open((*ptrCgiFile).c_str(), O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd_cgiFile < 0)
	{
		write(1, "CGI: fail to open file\n", 23);
		return "500";
	}
	pid_t pid;
	int fd[2];

	if (pipe(fd) != 0)
	{
		write(1, "CGI: Pipe error\n", 12);
		close(fd_cgiFile);
		return "500";
	}

	pid = fork();
	if (pid < 0)
	{
		write(1, "CGI: Fork error\n", 12);
		close(fd_cgiFile);
		return "500";
	}

	int status = 0;

	if (pid == 0)
	{
		close(fd[1]);
		dup2(fd_cgiFile, 1);
		dup2(fd[0], 0);
		close(fd_cgiFile);
		close(fd[0]);

		int exec_res = execve(args_[0], args_, env_);      //например выполняется файл result.php а там просто идет замена и-мейл адреса клиента, или же можно возраст имя итд, Я Дима, Мне 55 лет итд.

		write(1, "CGI: Execve error\n", 14);
		exit(exec_res);
	}
	else
	{
		close(fd[0]);
		if (client_.getBody().length() > 0)
			if (write(fd[1], client_.getBody().c_str(), client_.getBody().length()) == -1)
			{
				write(1, "CGI: Write error\n", 13);
				kill(pid, SIGKILL);
				close(fd[1]);
				return "500";
			}
		close(fd[1]);

		if (waitpid(pid, &status, 0) == -1)
		{
			write(1, "CGI: Waitpid error\n", 15);
			return "500";
		}
		if (WIFEXITED(status) && WIFSIGNALED(status) != 0)
		{
			write(1, "CGI: return\n", 12);
			return "500";
		}
	}

	if (!this->readFile(*ptrCgiFile, this->body_))    //прочитать результат выполнения ЕХЕСВЕ
		return "500";                                 //500 если неудачно

//	size_t pos = body_.find("\r\n\r\n");
//	if (pos == std::string::npos)        //не нашел если
//		return "500";                    //500 если неудачно
//
//	body_.erase(0, pos + 4);             //вырезать эти символы
	data = this->body_;                  //В ДАТА уже лежит финальная версия для отправки обратно клиенту через сервер
	return "200";                        //200 если все удачно
}

bool CGI::readFile(std::string const &file, std::string &body)
{
	char buffer[BUFFER_SIZE + 1] = {0};
	int fd;
	int ret;

	fd = open(file.c_str(), O_RDONLY);
	if (fd < -1)
	{
		write(1, "CGI: File not open\n", 15);
		return false;
	}

	body = "";
	while ((ret = read(fd, buffer, BUFFER_SIZE)) > 0)
		body.append(buffer, ret);                   //В БОДИ перезаписывается видоизмененый файл

	if (ret == -1)
	{
		body = "";
		write(1, "CGI: Error in file reading\n", 23);
		return false;
	}
	return true;
}

/*void CGI::createHttpMetaVariables()
{
	std::map<std::string, std::string>::const_iterator it = client_.getHeaders().begin();
	std::string httpKey;

	while (it != client_.getHeaders().end())
	{
		httpKey = it->first;
		std::transform(httpKey.begin(), httpKey.end(), httpKey.begin(), ::toupper);
		std::replace(httpKey.begin(), httpKey.end(), '-', '_');

		envMap_["HTTP_" + httpKey] = it->second;    //[HTTP_ACCEPT], [HTTP_USER_AGENT], [HTTP_HOST], [HTTP_DNT], [HTTP_ORIGIN], etc,...
		++it;
	}
}*/