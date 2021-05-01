//
// Created by Alexandr Yastrebow on 4/25/21.
//

#include "RequestHeaders.hpp"

RequestHeaders::RequestHeaders(){
}

RequestHeaders::~RequestHeaders(){
}

RequestHeaders::RequestHeaders(char *source) : _source(source){
}

std::string	RequestHeaders::getSourceHeader(){
	char 		*header;
	int 		i = 0;
	std::string	ret;

	while (this->_tokens.front()[i] != ':')
		i++;
	header = ft_substr(this->_tokens.front(), 0, i);
	if (header != NULL) {
		ret = header;
		free(header);
		header = NULL;
	}
	return (ret);
}

void 	RequestHeaders::getSource(char *source){
	this->_source = source;
}

void	RequestHeaders::detectHeader(std::string header){
	if (header == "Accept")
		this->setAccept();
	else if (header == "Accept-Charset")
		this->setAcceptCharset();
	else if (header == "Accept-Language")
		this->setAcceptLanguage();
	else if (header == "Authorization")
		this->setAuthorization();
	else if (header == "Connection")
		this->setConnection();
	else if (header == "Content-language")
		this->setContentLanguage();
	else if (header == "Content-Length")
		this->setContentLength();
	else if (header == "Content-Location")
		this->setContentLocation();
	else if (header == "Content-Type")
		this->setContentType();
	else if (header == "Date")
		this->setDate();
	else if (header == "Host")
		this->setHost();
	else if (header == "Last-Modified")
		this->setLastModified();
	else if (header == "Referer")
		this->setReferer();
	else if (header == "Transfer-Encoding")
		this->setTransferEncoding();
	else if (header == "User-Agent")
		this->setUserAgent();
}

void 	RequestHeaders::setStartLine() {
	char	*tokens;
	int 	i = 0;

	tokens = strtok(this->_tokens.front(), " ");
	while (tokens != NULL){
		switch (i) {
			case 0: this->_method = tokens;
			case 1: this->_uri = tokens;
			case 2: this->_version = tokens;
		}
		tokens = strtok(NULL, " ");
		i++;
	}
	this->_tokens.pop_front();
}

void 	RequestHeaders::setAccept(){

}

void 	RequestHeaders::setAcceptLanguage(){

}

void 	RequestHeaders::setAcceptCharset(){

}

void 	RequestHeaders::setAuthorization(){

}

void 	RequestHeaders::setConnection(){
	char	*token;

	token = ft_strchr(this->_tokens.front(), ' ');
	this->_connection = ++token;
}

void 	RequestHeaders::setContentLanguage(){

}

void 	RequestHeaders::setContentLength(){

}

void 	RequestHeaders::setContentLocation(){
	char	*token;

	token = ft_strchr(this->_tokens.front(), ' ');
	this->_contentLocation = ++token;
}

void 	RequestHeaders::setContentType(){

}

void 	RequestHeaders::setDate(){
	char	*token;

	token = ft_strchr(this->_tokens.front(), ' ');
	this->_date = ++token;
}

void 	RequestHeaders::setHost(){
	char	*token;

	token = ft_strchr(this->_tokens.front(), ' ');
	this->_host = ++token;
}

void 	RequestHeaders::setLastModified(){
	char	*token;

	token = ft_strchr(this->_tokens.front(), ' ');
	this->_lastModified = ++token;
}

void 	RequestHeaders::setReferer(){
	char	*token;

	token = ft_strchr(this->_tokens.front(), ' ');
	this->_referer = ++token;
}

void 	RequestHeaders::setTransferEncoding(){

}

void 	RequestHeaders::setUserAgent(){

}

void 	RequestHeaders::setInfo(){
	std::string header;
	char 		*token;

	token = strtok(this->_source, "\r\n");
	this->_tokens.push_back(token);
	while ((token = strtok(NULL, "\r\n")) != NULL){
		this->_tokens.push_back(token);
	}
	this->setStartLine();
	while(this->_tokens.size() != 0){
		header = this->getSourceHeader();
		detectHeader(header);
		this->_tokens.pop_front();
	}
}

std::string 					RequestHeaders::get_method() const{
	return (this->_method);
}

std::string 					RequestHeaders::get_uri() const{
	return (this->_uri);
}

std::string 					RequestHeaders::get_version() const{
	return (this->_version);
}

std::map<std::string, float>	RequestHeaders::get_accept() const{
	return (this->_accept);
}

std::list<std::string>			RequestHeaders::get_acceptCharset() const{
	return (this->_acceptCharset);
}

std::list<std::string>			RequestHeaders::get_acceptLanguage() const{
	return (this->_acceptLanguage);
}

std::list<std::string>			RequestHeaders::get_authorization() const{
	return (this->_authorization);
}

std::string 					RequestHeaders::get_connection() const{
	return (this->_connection);
}

std::list<std::string>			RequestHeaders::get_contentLanguage() const{
	return (this->_contentLanguage);
}

size_t 							RequestHeaders::get_contentLength() const{
	return (this->_contentLength);
}

std::string 					RequestHeaders::get_contentLocation() const{
	return (this->_contentLocation);
}

std::list<std::string>			RequestHeaders::get_contentType() const{
	return	(this->_contentType);
}

std::string 					RequestHeaders::get_date() const{
	return (this->_date);
}

std::string 					RequestHeaders::get_host() const{
	return (this->_host);
}

std::string 					RequestHeaders::get_lastModified() const{
	return (this->_lastModified);
}

std::string 					RequestHeaders::get_referer() const{
	return (this->_referer);
}

std::list<std::string>			RequestHeaders::get_transferEncoding() const{
	return (this->_transferEncoding);
}

std::list<std::string>			RequestHeaders::get_userAgent() const{
	return (this->_userAgent);
}

void 							RequestHeaders::clear() {
	this->_method = "";
	this->_uri = "";
	this->_version = "";
}