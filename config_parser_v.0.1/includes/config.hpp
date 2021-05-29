#ifndef CONFIG_HPP
#define CONFIG_HPP
#include <vector>
#include <iostream>
#include <fcntl.h>
#include <errno.h>
#include <string>
#include <cstring>
#include <unistd.h>
#include <list>
#include <map>
#include <arpa/inet.h>
#include "libft.h"
#include "ConfigClass.hpp"

int config_check(std::list<std::list<std::string> > lines);
int ft_strerror(std::string str);
int get_next_line(int fd, char **line);

#endif
