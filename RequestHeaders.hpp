//
// Created by Alexandr Yastrebow on 4/25/21.
//

#ifndef WEBSERVER_REQUESTHEADERS_HPP
# define WEBSERVER_REQUESTHEADERS_HPP


#include <string>
#include <list>
#include <map>

class RequestHeaders {
private:
	std::string 					_method;
	std::string 					_uri;
	std::string 					_version;
	std::map<std::string, float>	_accept;
	std::list<std::string>			_acceptCharset;
	std::list<std::string>			_acceptLanguage;
	std::list<std::string>			_authorization;
	std::string 					_connection;
	std::list<std::string>			_contentLanguage;
	size_t 							_contentLength;
	std::string 					_contentLocation;
	std::list<std::string>			_contentType;
	std::string 					_date;
	std::string 					_host;
	std::string 					_lastModified;
	std::string 					_referer;
	std::list<std::string>			_transferEncoding;
	std::list<std::string>			_userAgent;
	char							*_source;
	size_t 							_index;
public:
	RequestHeaders();
	RequestHeaders(char *source);
	~RequestHeaders();
	void		getSource(char *source);
	std::string	getHeader();
	void 		detectHeader(std::string header);
	void 		getInfo();
	void		getMethod();
	void 		getUri();
	void 		getVersion();
	void		getAccept();
	void 		getAcceptCharset();
	void 		getAcceptLanguage();
	void 		getAuthorization();
	void 		getConnection();
	void 		getContentLanguage();
	void 		getContentLength();
	void 		getContentLocation();
	void 		getContentType();
	void 		getDate();
	void 		getHost();
	void 		getLastModified();
	void 		getReferer();
	void 		getTransferEncoding();
	void 		getUserAgent();
};


#endif //WEBSERVER_REQUESTHEADERS_HPP
