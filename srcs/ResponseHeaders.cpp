//
// Created by Alexandr Yastrebow on 4/25/21.
//

#include "../includes/ResponseHeaders.hpp"

ResponseHeaders::ResponseHeaders() {

}

ResponseHeaders::~ResponseHeaders() {

}

std::string 			ResponseHeaders::getVersion() const{
	return (this->_version);
}

size_t 					ResponseHeaders::getStatusCode() const{
	return (this->_statusCode);
}

std::string 			ResponseHeaders::getReasonPhrase() const{
	return (this->_reasonPhrase);
}

std::string				ResponseHeaders::getAllow() const{
	return (this->_allow);
}

std::string 			ResponseHeaders::getConnection() const{
	return (this->_connection);
}

std::list<std::string>	ResponseHeaders::getContentLanguage() const{
	return (this->_contentLanguage);
}
size_t 					ResponseHeaders::getContentLength() const{
	return (this->_contentLength);
}
std::string 			ResponseHeaders::getContentLocation() const{
	return (this->_contentLocation);
}

std::string				ResponseHeaders::getContentType() const{
	return (this->_contentType);
}
std::string 			ResponseHeaders::getDate() const{
	return (this->_date);
}
std::string 			ResponseHeaders::getLastModified() const{
	return (this->_lastModified);
}

std::string 			ResponseHeaders::getLocation() const{
	return (this->_location);
}

std::string 			ResponseHeaders::getRetryAfter() const{
	return (this->_retryAfter);
}

std::string				ResponseHeaders::getServer() const{
	return (*(this->_server.begin()));
}

std::list<std::string>	ResponseHeaders::getWWWAuthenticate() const{
	return (this->_WWWAuthenticate);
}

std::string 			ResponseHeaders::getPage(){
	return (this->_page);
}

void* 					ResponseHeaders::getBinaryPage() {
	return (this->_binaryPage);
};

size_t 					ResponseHeaders::getBinaryPageLen() {
	return (this->_binaryPageLen);
};

void 					ResponseHeaders::setVersion(){
	this->_version = "HTTP/1.1";
}

void 					ResponseHeaders::setStatusCode(size_t code){
	this->_statusCode = code;
}

void 					ResponseHeaders::setReasonPhrase(std::string phrase){
	this->_reasonPhrase = phrase;
}

void					ResponseHeaders::setAllow(ConnectionClass connection, RequestHeaders request){
	ConfigClass	server;
	std::vector<std::string>	allow;

	server = connection.getServer();
	allow = (*(*server.getLocations())[request.getLocation()]->getMethods());
	if (allow.size() > 0) {
		for (size_t i = 0; i < allow.size(); ++i) {
			this->_allow += allow[i];
			this->_allow += " ";
		}
		this->_allow.pop_back();
	}
	else {
		this->_allow = "GET, POST, DELETE";
	}
}

void 					ResponseHeaders::setConnection(std::string phrase){
	this->_connection = phrase;
}

void 					ResponseHeaders::setContentLength(size_t length) {
	this->_contentLength = length;
}

void 					ResponseHeaders::setContentType(std::string type){
	this->_contentType = type;
}

void 					ResponseHeaders::setDate(RequestHeaders request) {
	this->_date = request.get_date();
}

void 					ResponseHeaders::setLocation(std::string location) {
	this->_location = location;
}

void 					ResponseHeaders::setServer(){
	this->_server.push_back("Webserver/1.0");
}

void 					ResponseHeaders::setPage(std::string page) {
	this->_page = page;
}

void 					ResponseHeaders::setBinaryPage(void *buffer, size_t len) {
	this->_binaryPage = buffer;
	this->_binaryPageLen = len;
}
