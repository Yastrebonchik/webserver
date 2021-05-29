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

char	*generateAnswer(RequestHeaders request, ConfigClass config);
char 	*GET(RequestHeaders request, ConfigClass server);
char 	*POST(RequestHeaders request, ConfigClass server);
char 	*noSuchMethod(RequestHeaders request);
char	*returnError(RequestHeaders request);

#endif //WEBSERVER_METHODS_H
