#ifndef CGI_HPP
#define CGI_HPP

#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstdlib>
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

#define DEFAULT_PATH "./configs"
#define DEFAULT_CONF "./configs/config_file"
//#define WEBSERV_NAME "webserv/1.0.0"
//#define WEBSERV_HTTP "HTTP/1.1"
//#define WEBSERV_AUTH "Basic"
#define RECV_BUFFER 16 * 1024
#define SEND_BUFFER 10000000
#define TIMEOUT_SEC 10
#define BUFFER_SIZE 32

#include "RequestHeaders.hpp"
//#include "ResponseHeaders.hpp"
#include "LocationClass.hpp"
#include "ConnectionClass.hpp"
#include "methods.h"
//#include "base64.hpp"   ENCODE / DECODE for Encryption and Safety 

class RequestHeaders;

class CGI
{
private:
	RequestHeaders client_;
	LocationClass location_;
	ConnectionClass connection_;
	std::string *ptrFile;
	std::string *ptrCgiFile;
	char *args_[4];
	char **env_;

	std::map<std::string, std::string> envMap_;
	std::string envir_;                             //ENVIRONMENT VARIABLES
	std::string body_;

public:
	CGI(RequestHeaders const &client, LocationClass location, ConnectionClass connection, std::string const &path);
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
