#include "config.hpp"

int ft_strerror (std::string str)
{
	std::cerr << "Error: " << str << std::endl;
	return (1);
}
