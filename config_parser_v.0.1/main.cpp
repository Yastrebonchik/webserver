#include "includes/config_parser.hpp"
#include <iostream>

int main (int argc, char **argv)
{
	std::vector<ConfigClass> conf;

	int i;
	int m;
	int size;
	std::list<LocationClass>::iterator it;

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
		m = 1;
		if (!(conf[i].getLocations())->empty())
		{
			it = (conf[i].getLocations())->begin();
			while (it != (conf[i].getLocations())->end())
			{
				std::cout << "Location " << m << ":\n";
				std::cout << (*it).getLocation() << std::endl;
				std::cout << (*it).getRoot() << std::endl;
				std::cout << (*it).getIndex() << std::endl;
				std::cout << (*it).getErrorPage() << std::endl;
				std::cout << (*it).getClientBodySize() << std::endl;
				std::cout << (*it).getListing() << std::endl;
				std::cout << (*it).getRedirection() << std::endl;
				std::cout << (*it).getCgi_dir() << std::endl;
				it++;
				m++;
			}
		}
		std::cout << "-----------------------------------\n";
		i++;
	}
	return (1);
}
