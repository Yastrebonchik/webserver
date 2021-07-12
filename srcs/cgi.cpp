#include "cgi.hpp"

std::string NumToString(size_t num)
{
	std::string s = std::to_string(num);
	return s;
}

CGI::CGI(RequestHeaders const &client, LocationClass location, ConnectionClass connection, std::string const &path) :
client_(client), location_(location), connection_(connection), EXEC(NULL), Scrypt(NULL), env_(NULL)  //Конструктор для СиЖиаИ ЗДЕСЬ!!!
{
	std::string executable; // php

	executable = location.getCgi_dir() + "/" + location.getIndex();
	EXEC = new std::string(executable); // php
	Scrypt = new std::string(path);    //path = result.php

	args_[0] = ft_strdup(executable.c_str());
	args_[1] = ft_strdup(path.c_str());
	args_[2] = NULL;
	///////////////////////////////////////////////////////////////////////////////////
	std::ifstream myfile;
	std::string line;
	std::string php_copy;

	myfile.open(path.c_str());
	if (myfile.is_open())
	{
		while(getline(myfile, line))
		{
			php_copy.append(line, line.length());
			php_copy.append("\n", 1);
		}
		myfile.close();
		this->copyptr = ft_strdup(php_copy.c_str());
	}
	else
		write(1, "File not found to open\n", 24);
	///////////////////////////////////////////////////////////////////////////////////
}

CGI::~CGI()
{
	int i = 0;
	std::map<std::string, std::string>::iterator it;

	for(it = envMap_.begin(); it != envMap_.end(); it++)
		delete(env_[i++]);
	delete(env_);
	delete(args_[0]);
	delete(args_[1]);
	delete EXEC;
	delete Scrypt;
	delete copyptr; ////
}

void CGI::createEnvVar()
{
	std::string	scrypt_;

	if (client_.getBody().length() > 0)
	{
		envMap_["CONTENT_LENGTH"] = NumToString(client_.getBody().length());
		if (client_.get_contentType().length() > 0)
			envMap_["CONTENT_TYPE"] = client_.get_contentType();
	}
	scrypt_ = this->location_.getCgi_dir() + "/" + this->location_.getIndex();
	envMap_["GATEWAY_INTERFACE"] = "CGI/1.0";
	envMap_["PATH_INFO"] = *Scrypt;   //Путь к запрошенному файлу - Директория СЖИ + Имя файла
	envMap_["PATH_TRANSLATED"] = *EXEC;
	if (client_.getBody().length() > 0)
		envMap_["QUERY_STRING"] = client_.getBody();    //Собственно информация, которую нужно подставить и динамически изменить в запросе ".php" etc... Строка запроса
	envMap_["REQUEST_METHOD"] = client_.get_method();
	envMap_["REQUEST_URI"] = client_.get_uri();    //Путь к запрошенному файлу - Директория + Имя файла
	envMap_["SCRIPT_NAME"] = scrypt_;
	envMap_["SERVER_NAME"] = connection_.getServer().getServer_name();       //Имя сервера
	envMap_["SERVER_PORT"] = NumToString(size_t(ntohs(connection_.getServer().getPort())));    //Порт сервера
	envMap_["SERVER_PROTOCOL"] = "HTTP/1.1";
	envMap_["SERVER_SOFTWARE"] = "Webserv/1.0";
}

void CGI::createEnv()
{
	int i = 0;
	std::map<std::string, std::string>::iterator it;

	env_ = (char **)operator new(sizeof(char *) * (envMap_.size() + 1));
	if (env_ == NULL)
	{
		write(1, "ENV: Malloc error\n", 19);
		return ;
	}
	for (it = envMap_.begin(); it != envMap_.end(); it++)
	{
		temp_ = (it->first + "=" + it->second);
		if (!(env_[i] = ft_strdup(temp_.c_str())))
		{
			write(1, "ENV: Malloc error\n", 19);
			return ;
		}
		i++;
	}
	env_[i] = NULL;
}

std::string CGI::run(std::string &body)            // ЗАПУСК СиДЖиАй здесь!!!!! С Аргументом BODY! BODY и получит результат выполнения программы!
{
	this->createEnvVar();
	this->createEnv();

	pid_t pid;
	int stdin_pipe[2];
	int stdout_pipe[2];
	int status = 0;

	if (pipe(stdin_pipe) != 0)
	{
		write(1, "CGI: Pipe IN error\n", 17);
		return "500";
	}
	if (pipe(stdout_pipe) != 0)
	{
		write(1, "CGI: Pipe 2 OUT error\n", 19);
		return "500";
	}

	pid = fork();
	if (pid < 0)
	{
		write(1, "CGI: Fork error\n", 17);
		return "500";
	}

	if (pid == 0)
	{
		close(stdin_pipe[1]);
		close(stdout_pipe[0]);
		dup2(stdin_pipe[0], 0);
		dup2(stdout_pipe[1], 1);
		
		int ret = execve(args_[0], args_, env_);      //например выполняется файл result.php а там просто идет замена и-мейл адреса клиента, или же можно возраст имя итд, Я Дима, Мне 55 лет итд.

		write(1, "CGI: Execve error\n", 19);
		exit(ret);
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
	int ret2;
	while ((ret2 = read(stdout_pipe[0], buffer, 1024)) > 0)
		body.append(buffer, ret2); 
	if (ret2 == -1)
	{
		body = "";
		write(1, "CGI: Error in file reading\n", 28);
		return "500";
	}
	//////////////////////////////////////////////////////////////////////////////////////
	std::ofstream newfile;
	newfile.open(args_[1]);
	newfile << this->copyptr;
	newfile.close();
	//////////////////////////////////////////////////////////////////////////////////////
	return "200";
}
