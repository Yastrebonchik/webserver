//
// Created by Karyn Cedra on 5/4/21.
//

#ifndef WEBSERVER_CONFIGCLASS_HPP
#define WEBSERVER_CONFIGCLASS_HPP
# include <string>
# include <vector>

//class LocationClass;

class ConfigClass {
public:
	std::string server_name;
	std::string ip;
	std::string port;
	std::string root;
	std::vector<std::string> index;
	std::vector<std::string> methods;
	//std::vector<LocationClass> locations;

public:
	ConfigClass();
	ConfigClass(std::string server, std::string ip, std::string port, std::string root);
	~ConfigClass();

	std::string getServer_name() const;
	std::string getIp() const;
	std::string getPort() const;
	std::string getRoot() const;
	std::vector<std::string> &getIndex() const;
	std::vector<std::string> &getMethods() const;
	//std::vector<LocationClass> &getLocations() const;
};

#endif //WEBSERVER_CONFIGCLASS_HPP
