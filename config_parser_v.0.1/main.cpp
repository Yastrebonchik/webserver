#include "includes/config_parser.hpp"
#include <iostream>

int main (int argc, char **argv)
{
	std::vector<ConfigClass> conf;

	int i;
	int size;

	config_parser(argv[1], conf);
	i = 0;
	size = conf.size();
	while (i < size)
	{
		std::cout << conf[i].getServer_name() << std::endl;
		std::cout << conf[i].getIp() << std::endl;
		std::cout << conf[i].getPort() << std::endl;
		std::cout << conf[i].getRoot() << std::endl;
		std::cout << conf[i].getIndex() << std::endl;
		std::cout << conf[i].getErrorPage() << std::endl;
		std::cout << conf[i].getClientBodySize() << std::endl;
		std::cout << "-----------------------------------\n";
		i++;
	}
	return (1);
}
