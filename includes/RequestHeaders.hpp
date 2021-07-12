//
// Created by Alexandr Yastrebow on 4/25/21.
//

#ifndef WEBSERVER_REQUESTHEADERS_HPP
# define WEBSERVER_REQUESTHEADERS_HPP


# include <string>
# include <list>
# include <map>
# include <vector>
# include <cstring>
# include <algorithm>
# include <iostream>
# include "utils.hpp"

class RequestHeaders {
private:
	std::string 								_method;
	std::string 								_uri;
	std::string 								_version;
	std::vector<std::pair<std::string, float> >	_accept;
	std::vector<std::pair<std::string, float> >	_acceptCharset;
	std::vector<std::pair<std::string, float> >	_acceptLanguage;
	std::list<std::string>						_authorization;
	std::string 								_connection;
	std::list<std::string>						_contentLanguage;
	size_t 										_contentLength;
	std::string 								_contentLocation;
	std::string									_contentType;
	std::string 								_date;
	std::string 								_host;
	std::string 								_lastModified;
	std::string 								_referer;
	std::list<std::string>						_transferEncoding;
	std::string									_userAgent;
	std::string 								_body;
	char										*_source;
	std::list<char*> 							_tokens;
	unsigned int								_responseFlags;
	int 										_location;
	int 										_CGILocation;

	/* Методы для извлечения данных */
	void										setAccept();
	void 										setAcceptCharset();
	void 										setAcceptLanguage();
	void 										setAuthorization();
	void					 					setConnection();
	void 										setContentLanguage();
	void 										setContentLength();
	void 										setContentLocation();
	void 										setContentType();
	void 										setDate();
	void 										setHost();
	void 										setLastModified();
	void 										setReferer();
	void 										setTransferEncoding();
	void 										setUserAgent();
	void 										setPostBody();
public:
	RequestHeaders();
	RequestHeaders(char *source);
	~RequestHeaders();
	std::string 								get_method() const;
	std::string 								get_uri() const;
	std::string 								get_version() const;
	std::vector<std::pair<std::string, float> >	get_accept() const;
	std::vector<std::pair<std::string, float> >	get_acceptCharset() const;
	std::vector<std::pair<std::string, float> >	get_acceptLanguage() const;
	std::list<std::string>						get_authorization() const;
	std::string 								get_connection() const;
	std::list<std::string>						get_contentLanguage() const;
	size_t 										get_contentLength() const;
	std::string 								get_contentLocation() const;
	std::string									get_contentType() const;
	std::string 								get_date() const;
	std::string 								get_host() const;
	std::string 								get_lastModified() const;
	std::string 								get_referer() const;
	std::list<std::string>						get_transferEncoding() const;
	std::string									get_userAgent() const;
	std::string									getSourceHeader();
	std::string 								getBody();
	unsigned int								getResponseFlags();
	int 										getLocation();
	int 										getCGILocation();
	void 										setUri(std::string);
	void 										detectHeader(std::string header);
	void										setSource(char *source);
	void 										setInfo();
	void 										setStartLine();
	void 										clear();
	void 										setResponseFlag(unsigned int flag);
	void 										clearResponesFlag();
	void 										setLocation(int location);
	void 										setCGILocation(size_t CGILocation);
};

#endif //WEBSERVER_REQUESTHEADERS_HPP
