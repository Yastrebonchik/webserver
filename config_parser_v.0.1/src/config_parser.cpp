#include "../includes/config_parser.hpp"

int class_add(std::map<std::string, std::string> &attributes, std::vector<ConfigClass> &conf, std::list<LocationClass> *locations)
{
	ConfigClass *server;
	int			ip[4];
	int			port;
	char		*nbrs;
	char		*ip_str;
	int			ip_len;
	int			i;
	uint32_t	x;
	int			cbs;

	server = new ConfigClass();
	ip_len = (attributes.find("listen")->second).length();
	ip_str = (char*)malloc(ip_len);
	ip_str[ip_len] = 0;
	strcpy(ip_str, (attributes.find("listen")->second).c_str());
	nbrs = strtok(ip_str, ".:");
	i = 0;
	while (nbrs)
	{
		if (i < 4)
			ip[i] = atoi(nbrs);
		else
			port = atoi(nbrs);
		nbrs = strtok(NULL, ".:");
		i++;
	}
	cbs = atoi((char*)(attributes.find("client_body_size")->second).c_str());
	x = (uint32_t)ip[3] << 24;
	x += (uint32_t)ip[2] << 16;
	x += (uint32_t)ip[1] << 8;
	x += (uint32_t)ip[0];
	server->setServer_name(attributes.find("server_name")->second);
	server->setIp(htonl(x));
	server->setPort(htons(port));
	server->setRoot(attributes.find("root")->second);
	server->setIndex(attributes.find("index")->second);
	server->setErrorPage(attributes.find("error_page")->second);
	server->setClientBodySize(cbs);
	server->setLocations(locations);
	conf.push_back(*server);
	return (0);
}

static LocationClass *location_class_create(std::map<std::string, std::string> &attributes)
{
	LocationClass *location = new LocationClass();
	std::list<std::string> *words = new std::list<std::string>();
	std::stringstream ss;
	std::string word;

	if (attributes.find("listing")->second == "yes")
		location->setListing(1);
	else
		location->setListing(0);
	location->setClientBodySize(atoi((char *)(attributes.find("client_body_size")->second).c_str()));
	location->setRoot(attributes.find("root")->second);
	location->setIndex(attributes.find("index")->second);
	location->setErrorPage(attributes.find("error_page")->second);
	location->setLocation(attributes.find("location")->second);
	location->setRedirection(attributes.find("redirection")->second);
	location->setCgi_dir(attributes.find("cgi_dir")->second);
	ss << attributes.find("allow_methods")->second;
	while ((std::getline(ss, word, ' ')))
	{
		if (word.length())
			words->push_back(word);
	}
	location->setMethods(words);
	return (location);
}

LocationClass *location_add(std::list<std::list<std::string> > &lines, std::list<std::list<std::string> >::iterator &it)
{
	std::map<std::string, std::string>::iterator it_map;
	std::map<std::string, std::string> attributes;
	std::list<std::string>::iterator it_str;

	attributes["listen"] = DEFAULT_LISTEN;
	attributes["error_page"] = DEFAULT_ERROR_PAGE;
	attributes["client_body_size"] = DEFAULT_CLIENT_BODY_SIZE;
	attributes["root"] = DEFAULT_ROOT;
	attributes["index"] = DEFAULT_INDEX;
	attributes["location"] = "";
	attributes["redirection"] = "";
	attributes["listing"] = "";
	attributes["cgi_dir"] = "";
	attributes["allow_methods"] = "";

	while (it != lines.end() && *(((*it).begin())) != "}")
	{
		if ((it_map = attributes.find(*((*it).begin()))) != attributes.end())
		{
			if (*((*it).begin()) == "allow_methods")
			{
				it_str = (*it).begin();
				it_str++;
				while (it_str != (*it).end())
				{
					attributes["allow_methods"] = attributes["allow_methods"] + " " + *it_str;
					it_str++;
				}
			}
			else if (++((*it).begin()) != (*it).end())
				it_map->second = *(++((*it).begin()));
		}
		it++;
	}
	return (location_class_create(attributes));
}

int server_add(std::list<std::list<std::string> > &lines, std::list<std::list<std::string> >::iterator &it, std::vector<ConfigClass> &conf)
{
	std::map<std::string, std::string> attributes;
	attributes["server_name"] = DEFAULT_SERVER_NAME;
	attributes["listen"] = DEFAULT_LISTEN;
	attributes["error_page"] = DEFAULT_ERROR_PAGE;
	attributes["client_body_size"] = DEFAULT_CLIENT_BODY_SIZE;
	attributes["root"] = DEFAULT_ROOT;
	attributes["index"] = DEFAULT_INDEX;
	std::map<std::string, std::string>::iterator it_map;
	std::list<LocationClass> *locations = new std::list<LocationClass>();
	while (it != lines.end())
	{
		if (*((*it).begin()) == "location")
		{
			locations->push_back(*location_add(lines, it));
			if (it == lines.end() || *((*it).begin()) == "server")
				break;
		}
		if ((it_map = attributes.find(*((*it).begin()))) != attributes.end())
			{
				if (++((*it).begin()) != (*it).end())
					it_map->second = *(++((*it).begin()));
		}
		it++;
		if (it != lines.end() && *((*it).begin()) == "server")
			break;
	}
	it_map = attributes.begin();
	if (class_add(attributes, conf, locations))
		return (1);
	return (0);
}

int static server_fuller(std::list<std::list<std::string> > lines, std::vector<ConfigClass> &conf)
{
	std::list<std::list<std::string> >::iterator it;

	it = lines.begin();
	while (it != lines.end())
	{
		if (*((*it).begin()) == "server" && *(++(*it).begin()) == "{")
		{
			if (server_add(lines, it, conf))
				return (1);
			if (it == lines.end())
				break;
			continue;
		}
		it++;
	}
	return (0);
}

static void list_word_fuller(std::string line, std::list<std::list<std::string> > *config)
{
	std::list<std::string> words;
	std::stringstream ss;
    std::string word;

	std::replace( line.begin(), line.end(), '	', ' ');
	ss << line;
	while ((std::getline(ss, word, ' ')))
	{
		if (word.length())
			words.push_back(word);
	config->push_back(words);
}

static int open_read(char *file, std::list<std::list<std::string> > *config)
{
	std::string line;
	std::fstream fd;

	fd.open(file, std::fstream::in);
	if (!fd.is_open())
		return (1);
	while ((std::getline(fd, line)))
		list_word_fuller(line, config);
	return (0);
}

int config_parser(char *file, std::vector<ConfigClass> &conf)
{
	std::list<std::list<std::string> > lines;

	if (open_read(file, &lines))
		return (ft_strerror("Configuration file openning or reading error"));
	if (config_check(lines))
		return (1);
	if (server_fuller(lines, conf))
		return (1);
	return (0);
}
