#include "includes/config_parser.hpp"
#include <iostream>


void free_conf(std::vector<ConfigClass> &conf) {

}

int main (int argc, char **argv)
{
	std::vector<ConfigClass> conf;

	int i;
	int m;

	int size;
	std::vector<LocationClass>::iterator it;
	std::vector<std::string>::iterator it_str;

	config_parser(argv[1], conf);
	i = 0;
	size = conf.size();
	while (i < size)
	{
		std::cout << "server name:      " << conf[i].getServer_name() << std::endl;
		std::cout << "IP:               " << conf[i].getIp() << std::endl;
		std::cout << "Port:             " << conf[i].getPort() << std::endl;
		std::cout << "Root:             " << conf[i].getRoot() << std::endl;
		std::cout << "Index:            " << conf[i].getIndex() << std::endl;
		//std::cout << "Error page:       " << conf[i].getErrorPage() << std::endl;
		std::cout << "Client body size: " << conf[i].getClientBodySize() << std::endl;
		std::cout << "Location number:  " << conf[i].getLocNum() << std::endl;
		m = 1;
		if (!(conf[i].getLocations())->empty())
		{
			it = (conf[i].getLocations())->begin();
			while (it != (conf[i].getLocations())->end())
			{
				std::cout << "" << "Location " << m << ":\n";
				std::cout << "	Location:			" << (*it).getLocation() << std::endl;
				std::cout << "	Root:				" << (*it).getRoot() << std::endl;
				std::cout << "	Index:				" << (*it).getIndex() << std::endl;
				//std::cout << "	Error page:			" << (*it).getErrorPage() << std::endl;
				std::cout << "	Client body size:		" << (*it).getClientBodySize() << std::endl;
				std::cout << "	Listing:			" << (*it).getListing() << std::endl;
				std::cout << "	Redirection:			" << (*it).getRedirection() << std::endl;
				std::cout << "	Cgi directory:			" << (*it).getCgi_dir() << std::endl;

				if (!(*it).getMethods()->empty())
				{
					it_str = (*it).getMethods()->begin();
					std::cout << "		Allow methods: ";
					while (it_str != (*it).getMethods()->end())
					{
						std::cout << *it_str << " ";
						it_str++;
					}
					std::cout << std::endl;
				}
				m++;
				it++;
			}
		}
		std::cout << "-----------------------------------\n";
		i++;
	}
	free_conf(conf);
	return (1);
}
