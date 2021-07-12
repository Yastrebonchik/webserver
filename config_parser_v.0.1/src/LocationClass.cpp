#include "../includes/LocationClass.hpp"
# include <iostream>

LocationClass::LocationClass(){
	this->allow_methods = NULL;
};

LocationClass::~LocationClass(){
	if(this->allow_methods)
		delete this->allow_methods;
};

void LocationClass::setLocation(std::string str) {
	this->location = str;
}
void LocationClass::setRedirection(std::string str) {
	this->redirection = str;
}
void LocationClass::setListing(int lis){
	this->listing = lis;
}
void LocationClass::setCgi_dir(std::string str) {
	this->cgi_dir = str;
}
void LocationClass::setMethods(std::vector<std::string> *methods){

	this->allow_methods = methods;
}

std::string LocationClass::getLocation() {
	return this->location;
}
std::string LocationClass::getRedirection() {
	return this->redirection;
}
int LocationClass::getListing(){
	return this->listing;
} 
std::string LocationClass::getCgi_dir(){
	return this->cgi_dir;
}
std::vector<std::string> *LocationClass::getMethods() {
	return this->allow_methods;
}
