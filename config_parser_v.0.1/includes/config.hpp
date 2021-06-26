#ifndef CONFIG_HPP
#define CONFIG_HPP
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <fcntl.h>
#include <errno.h>
#include <string>
#include <cstring>
#include <unistd.h>
#include <list>
#include <map>
#include <arpa/inet.h>
#include "ConfigClass.hpp"
#include "LocationClass.hpp"

int config_check(std::list<std::list<std::string> > lines);
int ft_strerror(std::string str);

#endif
