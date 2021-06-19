#include "../includes/config_parser.hpp"

int class_add(std::map<std::string, std::string> &attributes, std::vector<ConfigClass> &conf)
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
	conf.push_back(*server);
	return (0);
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

	while (it != lines.end())
	{
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
	if (class_add(attributes, conf))
		return (1);
	return (0);
}

int static server_fuller(std::list<std::list<std::string> > lines, std::vector<ConfigClass> &conf)
{
	std::list<std::list<std::string> >::iterator it;
	int br;

	br = 0;
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
		{
			std::cout << word << "- after second getline" << std::endl;
			words.push_back(word);
		}
	}
	config->push_back(words);
}

static int open_read(char *file, std::list<std::list<std::string> > *config)
{
	//int fd;
	int gnl_res;
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
