#include "config.hpp"

int ft_strerror (std::string str)
{
	std::cerr << "Error: " << str << std::endl;
	return (1);
}

void free_conf(std::vector<ConfigClass *> &conf)
{
	for (size_t i = 0; i < conf.size(); i++)
		delete conf[i];
}
