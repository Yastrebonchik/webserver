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

char 			*generateAnswer(RequestHeaders request);
char 			*GET(RequestHeaders request);
char 			*POST(RequestHeaders request);
char 			*noSuchMethod(RequestHeaders request);

#endif //WEBSERVER_METHODS_H
