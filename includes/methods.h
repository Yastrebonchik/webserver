//
// Created by Karyn Cedra on 5/4/21.
//

#ifndef WEBSERVER_METHODS_H
# define WEBSERVER_METHODS_H

# include "ResponseHeaders.hpp"
# include "RequestHeaders.hpp"
# include "ConfigClass.hpp"
# include <unistd.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/stat.h>
# include <time.h>
# include "config_parser.hpp"
# include "utils.hpp"
# include <fstream>
# include "ConnectionClass.hpp"

# define SERVER_NAME 1
# define REDIRECTION 2
# define DEFAULT_ERRORS 4
# define ALLOW_METHODS 8
# define ROOT_EXISTS 16
# define LISTING 32
# define LISTING_RESULT_YES 64
# define INDEX 128
# define CLIENT_BODY_SIZE_EXIST 256
# define CGI_FLAG 512

char	*generateAnswer(RequestHeaders &request, std::vector<ConfigClass> config, ConnectionClass &connection);
char 	*GET(RequestHeaders request, ConfigClass server, std::string root);
char 	*POST(RequestHeaders request, ConfigClass server);
char 	*DELETE(RequestHeaders request, ConfigClass server);
char 	*noSuchMethod(RequestHeaders request);
char	*returnError(RequestHeaders request);

#endif //WEBSERVER_METHODS_H
