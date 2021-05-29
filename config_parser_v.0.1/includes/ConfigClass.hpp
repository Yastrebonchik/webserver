#ifndef CONFIGCLASS_HPP
#define CONFIGCLASS_HPP
# include "config.hpp"

//class LocationClass;

//test comment

class ConfigClass {
	private:
		std::string	server_name;
		uint32_t	ip;
		uint16_t	port;
		std::string	root;
		std::string	index;
		std::string	error_page;
		int			client_body_size;
		//std::vector<LocationClass> locations;

	public : ConfigClass();
		~ConfigClass();

		void setServer_name(std::string &x);
		void setIp(uint32_t x);
		void setPort(uint16_t x);
		void setRoot(std::string &x);
		void setIndex(std::string &x);
		void setErrorPage(std::string &x);
		void setClientBodySize(int x);
		//void addLocation(std::string &x);

		std::string	getServer_name() const;
		uint32_t	getIp() const;
		uint16_t	getPort() const;
		std::string	getRoot() const;
		std::string	getIndex() const;
		std::string	getErrorPage() const;
		int			getClientBodySize() const;
		//std::vector<LocationClass> &getLocations() const;
};

#endif
