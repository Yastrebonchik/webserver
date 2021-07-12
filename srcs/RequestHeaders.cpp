//
// Created by Alexandr Yastrebow on 4/25/21.
//

#include "RequestHeaders.hpp"

bool sortbyvalue(std::pair<std::string, float> &a, std::pair<std::string, float>& b){
	return a.second > b.second;
}

RequestHeaders::RequestHeaders() {
}

RequestHeaders::~RequestHeaders() {
}

RequestHeaders::RequestHeaders(char *source) : _source(source), _responseFlags(0), _location(-1), _CGILocation(-1) {
}

std::string	RequestHeaders::getSourceHeader(){
	char 		*header;
	int 		i = 0;
	std::string	ret;

	while (this->_tokens.front()[i] != ':' && this->_tokens.front()[i] != '\0')
		i++;
	header = ft_substr(this->_tokens.front(), 0, i);
	if (header != NULL) {
		ret = header;
		delete (header);
		header = NULL;
	}
	return (ret);
}

void 	RequestHeaders::setSource(char *source){
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
	else if (header == "POST_BODY")
		this->setPostBody();
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
	char 		*token;
	char 		**values;
	std::string format;
	float 		q;

	token = strtok(ft_strchr(this->_tokens.front(), ' ') + 1, ",");
	while (token != NULL){
		values = ft_split(token, ';');
		format = values[0];
		q  = 1;
		if (values[1] != NULL)
			q = atof(ft_strchr(values[1], '=') + 1);
		this->_accept.push_back(std::pair<std::string, float>(format, q));
		delete (values[0]);
		values[0] = NULL;
		if (values[1] != NULL)
			delete(values[1]);
		values[1] = NULL;
		delete(values);
		values = NULL;
		token = strtok(NULL, ",");
	}
	std::sort(this->_accept.begin(), this->_accept.end(), sortbyvalue);
}

void 	RequestHeaders::setAcceptLanguage(){
	char 		*token;
	char 		**values;
	std::string language;
	float 		q;

	token = strtok(ft_strchr(this->_tokens.front(), ' ') + 1, ",");
	while (token != NULL){
		values = ft_split(token, ';');
		language = values[0];
		q = 1;
		if (values[1] != NULL)
			q = atof(ft_strchr(values[1], '=') + 1);
		this->_acceptLanguage.push_back(std::pair<std::string, float>(language, q));
		delete(values[0]);
		values[0] = NULL;
		if (values[1] != NULL)
			delete(values[1]);
		values[1] = NULL;
		delete(values);
		values = NULL;
		token = strtok(NULL, ",");
	}
	std::sort(this->_acceptLanguage.begin(), this->_acceptLanguage.end(), sortbyvalue);
}

void 	RequestHeaders::setAcceptCharset(){
	char 		*token;
	char 		**values;
	std::string charset;
	float 		q;

	token = strtok(ft_strchr(this->_tokens.front(), ' ') + 1, ",");
	while (token != NULL){
		values = ft_split(token, ';');
		charset = values[0];
		q  = 1;
		if (values[1] != NULL)
			q = atof(ft_strchr(values[1], '=') + 1);
		this->_acceptCharset.push_back(std::pair<std::string, float>(charset, q));
		delete(values[0]);
		values[0] = NULL;
		if (values[1] != NULL)
			delete(values[1]);
		values[1] = NULL;
		delete(values);
		values = NULL;
		token = strtok(NULL, ",");
	}
	std::sort(this->_acceptCharset.begin(), this->_acceptCharset.end(), sortbyvalue);
}

void 	RequestHeaders::setAuthorization(){
	char	*token;

	token = ft_strchr(this->_tokens.front(), ' ');
	this->_connection = ++token;
}

void 	RequestHeaders::setConnection(){
	char	*token;

	token = ft_strchr(this->_tokens.front(), ' ') + 1;
	this->_connection = token;
}

void 	RequestHeaders::setContentLanguage(){
	char		*token;
	std::string language;

	token = strtok(ft_strchr(this->_tokens.front(), ' ') + 1, ",");
	while (token != NULL){
		language = token;
		this->_contentLanguage.push_back(language);
		token = strtok(NULL, ",");
	}
}

void 	RequestHeaders::setContentLength(){
	char		*token;

	token = ft_strchr(this->_tokens.front(), ' ') + 1;
	this->_contentLength = ft_atoi(token);
}

void 	RequestHeaders::setContentLocation(){
	char	*token;

	token = ft_strchr(this->_tokens.front(), ' ') + 1;
	this->_contentLocation = token;
}

void 	RequestHeaders::setContentType(){
	char	*token;

	token = ft_strchr(this->_tokens.front(), ' ') + 1;
	this->_contentType = token;
}

void 	RequestHeaders::setDate(){
	char	*token;

	token = ft_strchr(this->_tokens.front(), ' ') + 1;
	this->_date = token;
}

void 	RequestHeaders::setHost(){
	char	*token;

	token = ft_strchr(this->_tokens.front(), ' ') + 1;
	this->_host = token;
}

void 	RequestHeaders::setLastModified(){
	char	*token;

	token = ft_strchr(this->_tokens.front(), ' ') + 1;
	this->_lastModified = token;
}

void 	RequestHeaders::setReferer(){
	char	*token;

	token = ft_strchr(this->_tokens.front(), ' ') + 1;
	this->_referer = token;
}

void 	RequestHeaders::setTransferEncoding(){
	char		*token;
	std::string encoding;

	token = strtok(ft_strchr(this->_tokens.front(), ' ') + 1, ",");
	while (token != NULL){
		encoding = token;
		this->_transferEncoding.push_back(encoding);
		token = strtok(NULL, ",");
	}
}

void 	RequestHeaders::setUserAgent(){
	char	*token;

	token = ft_strchr(this->_tokens.front(), ' ') + 1;
	this->_userAgent = token;
}

void 	RequestHeaders::setPostBody() {
	char 	*postBody;

	postBody = this->_tokens.front();
	this->_body = postBody;
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
		if (!(this->_method == "POST" && this->_tokens.size() == 1))
			this->_tokens.pop_front();
		else
			break;
	}
	if (this->_method == "POST" && this->_tokens.size() != 0) {
		if (!(this->_tokens.front()[0] == '0' && ft_strlen(this->_tokens.front()) == 1)) {
			detectHeader("POST_BODY");
		}
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

std::vector<std::pair<std::string, float> >	RequestHeaders::get_accept() const{
	return (this->_accept);
}

std::vector<std::pair<std::string, float> >	RequestHeaders::get_acceptCharset() const{
	return (this->_acceptCharset);
}

std::vector<std::pair<std::string, float> >	RequestHeaders::get_acceptLanguage() const{
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

std::string						RequestHeaders::get_contentType() const{
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

std::string						RequestHeaders::get_userAgent() const{
	return (this->_userAgent);
}

std::string 					RequestHeaders::getBody() {
	return (this->_body);
}

unsigned int					RequestHeaders::getResponseFlags() {
	return (this->_responseFlags);
};

int 							RequestHeaders::getLocation() {
	return (this->_location);
};

int 							RequestHeaders::getCGILocation() {
	return (this->_CGILocation);
};

void 							RequestHeaders::setUri(std::string uri) {
	this->_uri = uri;
}

void 							RequestHeaders::clear() {
	try {
		this->_method.clear();
		this->_uri.clear();
		this->_version.clear();
		this->_accept.clear();
		this->_acceptCharset.clear();
		this->_acceptLanguage.clear();
		this->_authorization.clear();
		this->_connection.clear();
		this->_contentLanguage.clear();
		this->_contentLength = 0;
		this->_contentLocation.clear();
		this->_contentType.clear();
		this->_date.clear();
		this->_host.clear();
		this->_lastModified.clear();
		this->_referer.clear();
		this->_transferEncoding.clear();
		this->_userAgent.clear();
		this->_tokens.clear();
	}
	catch (std::exception) {
		std::cout << "Something went wrong while clearing request headers" << std::endl;
	}
}

void 							RequestHeaders::setResponseFlag(unsigned int flag) {
	if ((this->_responseFlags & flag) != flag)
		this->_responseFlags += flag;
};

void 							RequestHeaders::clearResponesFlag() {
	this->_responseFlags = 0;
}

void 							RequestHeaders::setLocation(int location) {
	this->_location = location;
};

void 							RequestHeaders::setCGILocation(size_t CGILocation) {
	this->_CGILocation = CGILocation;
};