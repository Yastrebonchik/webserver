//
// Created by Alexandr Yastrebow on 4/25/21.
//

#include "ResponseHeaders.hpp"

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
	return ("GET, POST");
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

void 					ResponseHeaders::setVersion(){
	this->_version = "HTTP/1.1";
}

void 					ResponseHeaders::setStatusCode(size_t code){
	this->_statusCode = code;
}

void 					ResponseHeaders::setReasonPhrase(std::string phrase){
	this->_reasonPhrase = phrase;
}

void					ResponseHeaders::setAllow(){
	this->_allow.push_back("GET");
	this->_allow.push_back("POST");
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
//	struct timeval	gmt;
//	struct tm 		*m_time;
//	char str_t[128];
//
//	//Нужно добавить костыль в виде считывания даты при поступлении реквеста и вычислении новой после выполнения запроса.
//	ft_bzero(str_t, 128);
//	localtime()
//	//Считываем системное время
//	gettimeofday(&gmt, NULL);
//	//Преобразуем локальное время в текстовую строку
//	strftime(str_t, 128, "Date: %x %A %X %Z", gmt);
	this->_date = request.get_date();
}

void 					ResponseHeaders::setServer(){
	this->_server.push_back("Webserver/1.0");
}

void 					ResponseHeaders::pageAdd(std::string line) {
	this->_page += line;
}