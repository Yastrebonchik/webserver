//
// Created by Alexandr Yastrebow on 4/25/21.
//

#ifndef WEBSERVER_REQUESTHEADERS_HPP
# define WEBSERVER_REQUESTHEADERS_HPP


# include <string>
# include <list>
# include <map>
# include <cstring>
# include "libft.h"

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
	std::list<char*> 				_tokens;
public:
	RequestHeaders();
	RequestHeaders(char *source);
	~RequestHeaders();
	void							getSource(char *source);
	std::string 					get_method() const;
	std::string 					get_uri() const;
	std::string 					get_version() const;
	std::map<std::string, float>	get_accept() const;
	std::list<std::string>			get_acceptCharset() const;
	std::list<std::string>			get_acceptLanguage() const;
	std::list<std::string>			get_authorization() const;
	std::string 					get_connection() const;
	std::list<std::string>			get_contentLanguage() const;
	size_t 							get_contentLength() const;
	std::string 					get_contentLocation() const;
	std::list<std::string>			get_contentType() const;
	std::string 					get_date() const;
	std::string 					get_host() const;
	std::string 					get_lastModified() const;
	std::string 					get_referer() const;
	std::list<std::string>			get_transferEncoding() const;
	std::list<std::string>			get_userAgent() const;
	std::string						getSourceHeader();
	void 							detectHeader(std::string header);
	void 							setInfo();
	void 							setStartLine();
	void							setAccept();
	void 							setAcceptCharset();
	void 							setAcceptLanguage();
	void 							setAuthorization();
	void					 		setConnection();
	void 							setContentLanguage();
	void 							setContentLength();
	void 							setContentLocation();
	void 							setContentType();
	void 							setDate();
	void 							setHost();
	void 							setLastModified();
	void 							setReferer();
	void 							setTransferEncoding();
	void 							setUserAgent();
	void 							clear();
};

#endif //WEBSERVER_REQUESTHEADERS_HPP
