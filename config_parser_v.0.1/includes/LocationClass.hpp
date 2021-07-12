#ifndef LOCATIONCLASS_HPP
# define LOCATIONCLASS_HPP
# include "ConfigClass.hpp"
#include <vector>
#include <string>

class ConfigClass;

class LocationClass : public ConfigClass
{
	private:
		std::string location;
		std::string redirection;
		int listing;
		std::string cgi_dir;
		std::vector<std::string> *allow_methods;
	
	public:
		LocationClass();
		~LocationClass();

		void setLocation(std::string);
		void setRedirection(std::string);
		void setListing(int);
		void setCgi_dir(std::string);
		void setMethods(std::vector<std::string>*);

		std::string getLocation();
		std::string getRedirection();
		int getListing();
		std::string getCgi_dir();
		std::vector<std::string> *getMethods();
};

#endif
