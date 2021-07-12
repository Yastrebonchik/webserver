#include "includes/config_parser.hpp"
#include <iostream>

int main (int argc, char **argv)
{
	std::vector<ConfigClass*> conf;

	int i;
	int m;

	int size;
	std::vector<LocationClass*>::iterator it;
	std::vector<std::string>::iterator it_str;

	if (config_parser(argv[1], conf))
		return(1);
	i = 0;
	size = conf.size();
	while (i < size)
	{
		std::cout << "server name:      " << conf[i]->getServer_name() << std::endl;
		std::cout << "IP:               " << conf[i]->getIp() << std::endl;
		std::cout << "Port:             " << conf[i]->getPort() << std::endl;
		std::cout << "Root:             " << conf[i]->getRoot() << std::endl;
		std::cout << "Index:            " << conf[i]->getIndex() << std::endl;
		//std::cout << "Error page:       " << conf[i].getErrorPage() << std::endl;
		std::cout << "Client body size: " << conf[i]->getClientBodySize() << std::endl;
		std::cout << "Location number:  " << conf[i]->getLocNum() << std::endl;
		m = 1;
		std::map<int, std::string> error_map(conf[i]->getErrorPages());
		if (!(error_map.empty()))
		{
			std::cout << "Error_pages:\n";
			for(std::map<int, std::string>::const_iterator it = error_map.begin(); it != error_map.end(); it++)
			{
				std::cout << "    {" << it->first << ": " << it->second << "}\n";
			}
		}
		if (!(conf[i]->getLocations())->empty())
		{
			it = (conf[i]->getLocations())->begin();
			while (it != (conf[i]->getLocations())->end())
			{
				std::cout << "" << "Location " << m << ":\n";
				std::cout << "	Location:			" << (*it)->getLocation() << std::endl;
				std::cout << "	Root:				" << (*it)->getRoot() << std::endl;
				std::cout << "	Index:				" << (*it)->getIndex() << std::endl;
				//std::cout << "	Error page:			" << (*it).getErrorPage() << std::endl;
				std::cout << "	Client body size:		" << (*it)->getClientBodySize() << std::endl;
				std::cout << "	Listing:			" << (*it)->getListing() << std::endl;
				std::cout << "	Redirection:			" << (*it)->getRedirection() << std::endl;
				std::cout << "	Cgi directory:			" << (*it)->getCgi_dir() << std::endl;

				if (!(*it)->getMethods()->empty())
				{
					it_str = (*it)->getMethods()->begin();
					std::cout << "	Allow methods: ";
					while (it_str != (*it)->getMethods()->end())
					{
						std::cout << *it_str << " ";
						it_str++;
					}
					std::cout << std::endl;
				}
				m++;
				std::map<int, std::string> error_map((*it)->getErrorPages());
				if (!(error_map.empty()))
				{
					std::cout << "	Error_pages:\n";
					for(std::map<int, std::string>::const_iterator it = error_map.begin(); it != error_map.end(); it++)
					{
						std::cout << "	    {" << it->first << ": " << it->second << "}\n";
					}
				}
				it++;
			}
		}
		std::cout << "-----------------------------------\n";
		i++;
	}
	free_conf(conf);
	return (1);
}
