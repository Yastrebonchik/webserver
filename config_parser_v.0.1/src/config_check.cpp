#include "../includes/config.hpp"

int static bracket_check(std::list<std::list<std::string> > lines)
{
	std::list<std::list<std::string> >::iterator it;
	std::list<std::string>::iterator itw;
	int br;

	br = 0;
	it = lines.begin();
	while (it != lines.end())
	{
		itw = (*it).begin();
		while (itw != (*it).end())
		{
			if (*itw == "{")
				br++;
			if (*itw == "}")
				br--;
			if (br < 0)
				return (1);
			itw++;
		}
		it++;
	}
	if (br != 0)
		return (1);
	return (0);
}

int config_check(std::list<std::list<std::string> > lines)
{
	if (!lines.size())
		return (ft_strerror("Configuration file is empty"));
	if (bracket_check(lines))
		return (ft_strerror("Configuration file has unpair brackets"));
	return (0);
}
