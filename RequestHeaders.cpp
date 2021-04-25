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

std::string	RequestHeaders::getHeader(){
	int 		i = this->_index;

	while (this->_source[i] != ':')
		i++;
	std::string	ret(&(this->_source[this->_index]), i - this->_index);
	this->_index = i + 2;
	return (ret);
}

void 	RequestHeaders::getSource(char *source){
	this->_source = source;
}

void	RequestHeaders::detectHeader(std::string header){
	if (header == "Accept")
		this->getAccept();
	else if (header == "Accept-Charset")
		this->getAcceptCharset();
	else if (header == "Accept-Language")
		this->getAcceptLanguage();
	else if (header == "Authorization")
		this->getAuthorization();
	else if (header == "Connection")
		this->getConnection();
	else if (header == "Content-language")
		this->getContentLanguage();
	else if (header == "Content-Length")
		this->getContentLength();
	else if (header == "Content-Location")
		this->getContentLocation();
	else if (header == "Content-Type")
		this->getContentType();
	else if (header == "Date")
		this->getDate();
	else if (header == "Host")
		this->getHost();
	else if (header == "Last-Modified")
		this->getLastModified();
	else if (header == "Referer")
		this->getReferer();
	else if (header == "Transfer-Encoding")
		this->getTransferEncoding();
	else if (header == "User-Agent")
		this->getUserAgent();
	else{
		while (this->_source[_index] != '\r')
			this->_index++;
		this->_index += 2;
	}
}

void 	RequestHeaders::getMethod(){
	int 		i = this->_index;

	while (this->_source[i] != ' ')
		i++;
	std::string	buf(this->_source, i - this->_index);
	this->_method = buf;
	this->_index = i + 1;
}

void 	RequestHeaders::getUri(){
	int 		i = this->_index;

	while (this->_source[i] != ' ')
		i++;
	std::string	buf(&(this->_source[this->_index]), i - this->_index);
	this->_uri = buf;
	this->_index = i + 1;
}

void 	RequestHeaders::getVersion() {
	int 		i = this->_index;

	while (this->_source[i] != '\r')
		i++;
	std::string	buf(&(this->_source[this->_index]), i - this->_index);
	this->_version = buf;
	this->_index = i + 2;
}

void 	RequestHeaders::getAccept(){

}

void 	RequestHeaders::getAcceptLanguage(){

}

void 	RequestHeaders::getAcceptCharset(){

}

void 	RequestHeaders::getAuthorization(){

}

void 	RequestHeaders::getConnection(){

}

void 	RequestHeaders::getContentLanguage(){

}

void 	RequestHeaders::getContentLength(){

}

void 	RequestHeaders::getContentLocation(){

}

void 	RequestHeaders::getContentType(){

}

void 	RequestHeaders::getDate(){

}

void 	RequestHeaders::getHost(){
	int 		i = this->_index;

	while (this->_source[i] != '\r')
		i++;
	std::string	buf(&(this->_source[this->_index]), i - this->_index);
	this->_host = buf;
	this->_index = i + 2;
}

void 	RequestHeaders::getLastModified(){

}

void 	RequestHeaders::getReferer(){

}

void 	RequestHeaders::getTransferEncoding(){

}

void 	RequestHeaders::getUserAgent(){

}

void 	RequestHeaders::getInfo(){
	std::string header;
	
	this->getMethod();
	this->getUri();
	this->getVersion();
	while(this->_source[this->_index] != '\0')
	{
		header = this->getHeader();
		detectHeader(header);
	}
}
