//
// Created by Alexandr Yastrebow on 4/25/21.
//

#ifndef WEBSERVER_RESPONSEHEADERS_HPP
# define WEBSERVER_RESPONSEHEADERS_HPP

# include <string>
# include <list>

class ResponseHeaders {
private:
	std::list<std::string>	_allow;
	std::list<std::string>	_contentLanguage;
	size_t 					_contentLength;
	std::string 			_contentLocation;
	std::list<std::string>	_contentType;
	std::string 			_date;
	std::string 			_lastModified;
	std::string 			_location;
	std::string 			_retryAfter;
	std::list<std::string>	_server;
	std::list<std::string>	_wwwAuthenticate;
};


#endif //WEBSERVER_RESPONSEHEADERS_HPP
