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

#include "RequestHeaders.hpp"
#include "LocationClass.hpp"
#include "ConnectionClass.hpp"
#include "methods.h"

class RequestHeaders;

class CGI
{
private:
	RequestHeaders client_;
	LocationClass location_;
	ConnectionClass connection_;
	std::string *EXEC;
	std::string *Scrypt;
	std::string php_copy;

	char **env_;
	std::map<std::string, std::string> envMap_;
	std::string temp_;                             //CREATE ENVIRONMENT VARIABLES
	std::string body_;

	char *args_[4];
public:
	CGI(RequestHeaders const &client, LocationClass location, ConnectionClass connection, std::string const &path);
	~CGI();

	void createEnvVar();
	void createEnv();
	std::string run(std::string &data);
};

#endif
