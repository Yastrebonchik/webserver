#include "CGI.hpp"

CGI::CGI(Client const &client, ConfigLocation location, std::string const &path) : client_(client), location_(location), ptrFile(NULL), ptrCgiFile(NULL), env_(NULL)
{
	char cwd[PATH_MAX + 1];
	getcwd(cwd, sizeof(cwd));

	ptrFile = new std::string(cwd + path.substr(1));
	ptrCgiFile = new std::string(std::string(cwd) + "/test/cgi");

	args_[0] = ft_strdup(location_.getScrypt().c_str());
	args_[1] = ft_strdup((*ptrFile).c_str());
	args_[2] = NULL;
}

CGI::~CGI()
{
	int i = 0;
	std::map<std::string, std::string>::iterator it;

	for(it = envMap_.begin(); it != envMap_.end(); it++)
		free(env_[i++]);
	free(env_);
	unlink((*ptrCgiFile).c_str());
	free(args_[0]);
	free(args_[1]);
	delete ptrFile;
	delete ptrCgiFile;
}

void CGI::createMetaVariables()
{
	if (client_.getHeaderAuthorization().size() > 0)
	{
		std::string decoded = Base64::decode(client_.getHeaderAuthorization().at(WEBSERV_AUTH));
		size_t pos = decoded.find(":");

		envMap_["AUTH_TYPE"] = WEBSERV_AUTH;
		envMap_["REMOTE_USER"] = decoded.substr(0, pos);
		envMap_["REMOTE_IDENT"] = envMap_["REMOTE_USER"];
	}
	if (client_.getBody().length() > 0)
	{
		envMap_["CONTENT_LENGTH"] = positiveNumberToString(client_.getBody().length());

		if (client_.getHeaderContentType().length() > 0)
			envMap_["CONTENT_TYPE"] = client_.getHeaderContentType();
	}
	envMap_["GATEWAY_INTERFACE"] = "CGI/1.1";
	envMap_["PATH_INFO"] = client_.getPath() + client_.getFileName();
	envMap_["PATH_TRANSLATED"] = *ptrFile;

	if (client_.getQueryString().length() > 0)
		envMap_["QUERY_STRING"] = client_.getQueryString();

	sockaddr_in addrCl;
	socklen_t lenCl = sizeof(addrCl);
	if (getsockname(client_.getSocketClient(), (struct sockaddr *)&addrCl, &lenCl) == 0)
	{
		envMap_["REMOTE_ADDR"] = std::string(inet_ntoa(addrCl.sin_addr));
		envMap_["REMOTE_PORT"] = positiveNumberToString(ntohs(addrCl.sin_port));
	}
	envMap_["REQUEST_METHOD"] = client_.getMethod();
	envMap_["REQUEST_URI"] = client_.getPath() + client_.getFileName();
	envMap_["SCRIPT_NAME"] = location_.getScrypt();
	envMap_["SERVER_NAME"] = client_.getServer().getServerName();
	envMap_["SERVER_PORT"] = positiveNumberToString(size_t(client_.getServer(),getPort()));
	envMap_["SERVER_PROTOCOL"] = WEBSERV_HTTP;
	envMap_["SERVER_SOFTWARE"] = WEBSERV_NAME;

	if (location_.getExtensions() == ".php")
		envMap_["REDIRECT_STATUS"] = "200";
	this->createHttpMetaVariables();
}

void CGI::createHttpMetaVariables()
{
	std::map<std::string, std::string>::const_iterator it = client_.getHeaders().begin();
	std::string httpKey;

	while (it != client_.getHeaders().end())
	{
		httpKey = it->first;
		std::transform(httpKey.begin(), httpKey.end(), httpKey.begin(), ::toupper);
		std::replace(httpKey.begin(), httpKey.end(), '-', '_');

		envMap_["HTTP_" + httpKey] = it->second;
		++it;
	}
}

void CGI::printMetaVariables()
{
	std::cout << UNDERLINE_W << "PRINT MetaVariables" << RESET_C << std::endl;

	std::map<std::string, std::string>::iterator it = envMap_.begin();
	while (it != envMap_.end())
	{
		std::cout << it->first << ": " << it->second << std::endl;
		++it;
	}
}

void CGI::createCgiEnv()
{
	int i = 0;
	std::map<std::string, std::string>::iterator it;

	env_ = (char **)malloc(sizeof(char *) * (envMap_.size() + 1));
	if (env_ == NULL)
		throw(std::runtime_error(strerror(errno)));
	for (it = envMap_.begin(); it != envMap_.end(); it++)
	{
		envir_ = (it->first + "=" + it->second);
		if (!(env_[i] = ft_strdup(envir_.c_str())))
			throw(std::runtime_error(strerror(errno)));
		i++;
	}
	env_[i] = NULL;
}

std::string CGI::run(std::string &data)
{
	this->createMetaVariables();
	this->createCgiEnv();

	int fd_cgiFile = open((*ptrCgiFile).c_str(), O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd_cgiFile < 0)
	{
		//g_log.printErrorMassage("CGI fail to open file: " + *ptrCgiFile);
		return "500";
	}
	pid_t pid;
	int fd[2];

	if (pipe(fd) != 0)
	{
		//g_log.printErrorMassage("Pipe error: " + std::string(strerror(errno)));
		close(fd_cgiFile);
		return "500";
	}

	pid = fork();
	if (pid < 0)
	{
		//g_log.printErrorMassage("Fork error: " + std::string(strerror(errno)));
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

		int exec_res = execve(args_[0], args_, env_);

		//g_log.printErrorMassage("Execve error '" + std::string(args_[0]) + "': " + std::string(strerror(errno)));
		exit(exec_res);
	}
	else
	{
		close(fd[0]);
		if (client_.getBody().length() > 0)
			if (write(fd[1], client_.getBody().c_str(), client_.getBody().length()) == -1)
			{
				//g_log.printErrorMassage("Write error: " + std::string(strerror(errno)));
				kill(pid, SIGKILL);
				close(fd[1]);
				return "500";
			}
		close(fd[1]);

		if (waitpid(pid, &status, 0) == -1)
		{
			//g_log.printErrorMassage("Waitpid error: " + std::string(strerror(errno)));
			return "500";
		}
		if (WIFEXITED(status) && WIFSIGNALED(status) != 0)
		{
			//g_log.printErrorMassage("CGI return: " + positiveNumberToString(WIFSIGNALED(status)));
			return "500";
		}
	}

	if (!this->readFile(*ptrCgiFile, this->body_))
		return "500";

	size_t pos = body_.find("\r\n\r\n");
	if (pos == std::string::npos)
		return "500";
	
	body_.erase(0, pos + 4);
	data = this->body_;
	return "200";
}

bool CGI::readFile(std::string const &file, std::string &body)
{
	char buffer[BUFFER_SIZE + 1] = {0};
	int fd;
	int ret;

	fd = open(file.c_str(), O_RDONLY);
	if (fd < -1)
	{
		//g_log.printErrorMassage("File not open! " + std::string(strerror(errno)));
		return false;
	}

	body = "";
	while ((ret = read(fd, buffer, BUFFER_SIZE)) > 0)
		body.append(buffer, ret);

	if (ret == -1)
	{
		body = "";
		//g_log.printErrorMassage("Error in file reading: " + std::string(strerror(errno)));
		return false;
	}
	return true;
}
