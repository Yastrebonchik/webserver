#include "../includes/ConfigClass.hpp"
#include "LocationClass.hpp"

ConfigClass::ConfigClass(){
	std::list<LocationClass> locations;
	this->locations = &locations;
};

ConfigClass::~ConfigClass() {};

void ConfigClass::setServer_name(std::string &x)
{
	this->server_name = x;
};
void ConfigClass::setIp(uint32_t x)
{
	this->ip = x;
};
void ConfigClass::setPort(uint16_t x)
{
	this->port = x;
};
void ConfigClass::setRoot(std::string &x)
{
	this->root = x;
};
void ConfigClass::setIndex(std::string &x)
{
	this->index = x;
};
void ConfigClass::setErrorPage(std::string &x)
{
	this->error_page = x;
};
void ConfigClass::setClientBodySize(int x)
{
	this->client_body_size = x;
};
void ConfigClass::setLocations(std::list<LocationClass> locations)
{
	this->locations = &locations;
}

std::string ConfigClass::getServer_name() const
{
	return this->server_name;
};
uint32_t ConfigClass::getIp() const
{
	return this->ip;
};
uint16_t ConfigClass::getPort() const
{
	return this->port;
};
std::string ConfigClass::getRoot() const
{
	return this->root;
};
std::string ConfigClass::getIndex() const
{
	return this->index;
};
std::string ConfigClass::getErrorPage() const
{
	return this->error_page;
};
int ConfigClass::getClientBodySize() const
{
	return this->client_body_size;
};

std::list<LocationClass> *ConfigClass::getLocations() const{
	return this->locations;
}
