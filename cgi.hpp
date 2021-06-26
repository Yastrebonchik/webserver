#ifndef CGI_HPP
#define CGI_HPP

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <map>
#include <algorithm>
#include <ctime>
#include <cstring>
#include <exception>
#include <stack>
#include <signal.h>
#include "utils.hpp"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define DEFAULT_PATH "./config"
#define DEFAULT_CONF "./config/default.conf"
#define WEBSERV_NAME "webserv/1.0.0"
#define WEBSERV_HTTP "HTTP/1.1"
#define WEBSERV_AUTH "Basic"
#define RECV_BUFFER 16 * 1024
#define SEND_BUFFER 10000000
#define TIMEOUT_SEC 10

#include "RequestHeaders.hpp"
#include "ResponseHeaders.hpp"
//#include "base64.hpp"     тут хз что

class Client;      //config location tut must be "RequestHeaders.hpp" or "ResponseHeaders.hpp"

class CGI
{
private:
	Client client_;
	ConfigLocation location_;    //config
	std::string *ptrFile;
	std::string *ptrCgiFile;
	char *args_[4];
	char **env_;            //закинуть енв сюда

	std::map<std::string, std::string> envMap_;
	std::string envir;

	std::string body_;

public:
	CGI(Client const &client, ConfigLocation location, std::string const &path);
	~CGI();

	std::string const &getHeaders() const;

	void createMetaVariables();
	void createHttpMetaVariables();
	void printMetaVariables();
	void createCgiEnv();
	std::string run(std::string &data);
	bool readFile(std::string const &file, std::string &body);
};

#endif
