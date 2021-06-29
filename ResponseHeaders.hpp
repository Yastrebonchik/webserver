//
// Created by Alexandr Yastrebow on 4/25/21.
//

#ifndef WEBSERVER_RESPONSEHEADERS_HPP
# define WEBSERVER_RESPONSEHEADERS_HPP

# include <string>
# include <list>
# include "RequestHeaders.hpp"
# include "utils.hpp"
# include <time.h>
# include <sys/time.h>

class ResponseHeaders {
private:
	std::string 			_version;
	size_t 					_statusCode;
	std::string 			_reasonPhrase;
	std::list<std::string>	_allow;
	std::string 			_connection;
	std::list<std::string>	_contentLanguage;
	size_t 					_contentLength;
	std::string 			_contentLocation;
	std::string				_contentType;
	std::string 			_date;
	std::string 			_lastModified;
	std::string 			_location;
	std::string 			_retryAfter;
	std::list<std::string>	_server;
	std::list<std::string>	_WWWAuthenticate;
	std::string 			_page;
	char 					*_binaryPage;
	bool 					sendFlag;

public:
	ResponseHeaders();
	~ResponseHeaders();

	std::string 			getVersion() const;
	size_t 					getStatusCode() const;
	std::string 			getReasonPhrase() const;
	std::string				getAllow() const;
	std::string 			getConnection() const;
	std::list<std::string>	getContentLanguage() const;
	size_t 					getContentLength() const;
	std::string 			getContentLocation() const;
	std::string				getContentType() const;
	std::string 			getDate() const;
	std::string 			getLastModified() const;
	std::string 			getLocation() const;
	std::string 			getRetryAfter() const;
	std::string				getServer() const;
	std::list<std::string>	getWWWAuthenticate() const;
	std::string 			getPage();
	char* 					getBinaryPage();
	void 					setVersion();
	void 					setStatusCode(size_t code);
	void 					setReasonPhrase(std::string phrase);
	void					setAllow();
	void 					setConnection(std::string phrase);
	void 					setContentLength(size_t length);
	void 					setContentType(std::string type);
	void 					setDate(RequestHeaders request);
	void 					setServer();
	void 					pageAdd(std::string line);
	void 					binaryPageAdd(char *line);
};


#endif //WEBSERVER_RESPONSEHEADERS_HPP
