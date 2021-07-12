//
// Created by Karyn Cedra on 4/5/21.
//

#include "methods.h"

void 	*returnError(RequestHeaders request, int statusC, std::string reason, ConnectionClass &connection) {
	ResponseHeaders				response;
	std::stringstream			strstream;
	std::fstream 				fin;
	std::string 				body;
	std::string 				statusCode;
	std::string 				contentLength;
	std::string 				file;
	std::string 				ret;
	char 						*line;
	char 						*charbuffer;
	void 						*buffer;
	void 						*retline;
	int 						length;
	bool 						errorexist = 0;
	std::map<int, std::string>	errors;
	std::string 				errorfile;


	if ((request.getResponseFlags() & CUSTOM_ERRORS) == CUSTOM_ERRORS) {
		if (request.getLocation() == -1) {
			errors = connection.getServer().getErrorPages();
		}
		else {
			errors = (*connection.getServer().getLocations())[request.getLocation()]->getErrorPages();
		}
		for (std::map<int, std::string>::iterator it = errors.begin(); it != errors.end() ; ++it) {
			if (it->first == statusC) {
				errorexist = 1;
				file = it->second;
				break;;
			}
		}
		if (errorexist) {
			fin.open(file);
			fin.seekg(0, fin.end);
			length = fin.tellg();
			fin.seekg(0, fin.beg);
			charbuffer = new char[length];
			fin.read(charbuffer, length);
			buffer = static_cast<void *>(charbuffer);
			response.setBinaryPage(buffer, length);
			fin.close();
			response.setContentType(mimeDetect(file));
		}
	}
	if (!errorexist) {
		body += "<html>\n"
				"<head><title>";
		body += std::to_string(statusC);
		body += " " + reason;
		body += "</title></head>\n"
				"<body>\n"
				"<center><h1>";
		body += std::to_string(statusC);
		body += " " + reason;
		body += "</h1></center>\n"
				"<hr><center>webserver</center>\n"
				"</body>\n"
				"</html>";
		response.setPage(body);
		response.setContentType("text/html");
	}
	response.setVersion();
	response.setStatusCode(statusC);
	response.setReasonPhrase(reason);
	if (statusC == 308) {
		response.setLocation((*connection.getServer().getLocations())[request.getLocation()]->getRedirection());
	}
	if (statusC == 405 || statusC == 501)
		response.setAllow(connection, request);
	response.setConnection("keep-alive");
	if (errorexist)
		response.setContentLength(response.getBinaryPageLen());
	else
		response.setContentLength(response.getPage().length());
	response.setDate(request);
	response.setServer();
	statusCode = std::to_string(response.getStatusCode());
	contentLength = std::to_string(response.getContentLength());
	ret = response.getVersion() + " " + statusCode + " " + response.getReasonPhrase();
	if (statusC == 501 || statusC == 405)
		ret += "\r\nAllow: " + response.getAllow();
	ret += "\r\nConnection: " + response.getConnection() + "\r\nContent-Length: " + contentLength;
	ret += "\r\nContent-Type: " + response.getContentType() + "\r\nServer: " + response.getServer();
	if (statusC == 308)
		ret += "\r\nLocation: " + response.getLocation();
	ret += "\r\n\r\n" + response.getPage();
	if (errorexist) {
		line = ft_strdup(ret.c_str());
		retline = newbuffer(line, response.getBinaryPage(), (int)(response.getBinaryPageLen()));
		connection.setAnswerSize(ret.size() + response.getBinaryPageLen());
		return (retline);
	}
	else {
		ret += response.getPage();
		line = ft_strdup(ret.c_str());
		response.setBinaryPage(nullptr, 0);
		connection.setAnswerSize(ret.size() + response.getPage().size());
		return (line);
	}
}

void 	*GET(RequestHeaders request, ConfigClass server, ConnectionClass &connection) {
	ResponseHeaders response;
	std::string body;
	std::string ret;
	std::string statusCode;
	std::string contentLength;
	std::string file;
	std::string directory;
	std::string uri = request.get_uri();
	std::string::iterator it;
	std::string::iterator ite;
	std::fstream fin;
	std::stringstream strstream;
	struct stat buf;
	struct dirent *entry;
	std::string seekfilename;
	char *line;
	void *retline;
	DIR *dir;
	int length;
	void *buffer;
	char *charbuffer;
	size_t pos;
	size_t result;
	std::string index = "";
	bool 		flag = 0;

	if (*(--uri.end()) == '/') {
		if ((request.getResponseFlags() & LISTING) == LISTING) {
			if ((request.getResponseFlags() & LISTING_RESULT_YES) != LISTING_RESULT_YES) {
				return (returnError(request, 403, "Forbidden", connection));
			}
			flag = 1;
		}
		else {
			if ((request.getResponseFlags() & INDEX) == INDEX) {
				//Выбираю индекс из локейшена
				file = (*server.getLocations())[request.getLocation()]->getIndex();
			}
		}
	}
	else {
		if ((pos = uri.find("?")) != std::string::npos)
			uri.erase(pos, uri.length() - 1);
		it = uri.end();
		ite = uri.end();
		while (*it != '/') {
			it--;
		}
		directory = (std::string(uri.begin(), it++)) + '/';
		if ((result = directory.find("//")) != std::string::npos) {
			directory.replace(result, 2, std::string("/"));
		}
		dir = opendir(directory.c_str());
		it--;
		while (++it != ite) {
			file += *(it);
		}
		while (dir != NULL && (entry = readdir(dir)) != NULL) {
			seekfilename = entry->d_name;
			stat(file.c_str(), &buf);
			if (seekfilename == file) {
				if (S_ISDIR(buf.st_mode)) {
					file = uri + "/" + index;
				}
				closedir(dir);
				break;
			}
		}
		if (dir == NULL || entry == NULL) {
			if (dir != NULL) {
				closedir(dir);
			}
			return (returnError(request, 404, "Not Found", connection));
		}
		file = directory + file;
	}
	response.setBinaryPage(nullptr, 0);
	if ((request.getResponseFlags() & LISTING) == LISTING && flag == 1) {
		if ((request.getResponseFlags() & LISTING_RESULT_YES) == LISTING_RESULT_YES) {
			directory = uri;
			response.setPage(listing(directory));
		}
	}
	else {
		if (mimeDetect(file) == "image/png" || mimeDetect(file) == "image/jpeg"
			|| mimeDetect(file).find("font") != std::string::npos) {
			fin.open(file, std::ios::binary | std::ios::in);
		}
		else {
			fin.open(file, std::ios::in);
		}
		if (!fin.is_open())
			return (returnError(request, 404, "Not Found", connection));
		else {
			if (mimeDetect(file) == "image/png" || mimeDetect(file) == "image/jpeg"
				|| mimeDetect(file).find("font") != std::string::npos) {
				fin.seekg(0, fin.end);
				length = fin.tellg();
				fin.seekg(0, fin.beg);
				charbuffer = new char[length];
				ft_bzero(charbuffer, sizeof(char));
				fin.read(charbuffer, length);
				buffer = static_cast<void*>(charbuffer);
				response.setBinaryPage(buffer, length);
				fin.close();
			}
			else {
				strstream << fin.rdbuf();
				body = strstream.str();
				response.setPage(body);
				fin.close();
			}
		}
	}
	response.setVersion();
	response.setStatusCode(200);
	response.setReasonPhrase("OK");
	if (request.get_connection() == "close") {
		response.setConnection("close");
	}
	else {
		response.setConnection("keep-alive");
	}
	if (response.getBinaryPage() != nullptr) {
		response.setContentLength(response.getBinaryPageLen());
	}
	else {
		response.setContentLength(response.getPage().length());
	}
	if ((request.getResponseFlags() & LISTING) == LISTING && flag == 1)
		response.setContentType("text/html");
	else
		response.setContentType(mimeDetect(file));
	response.setServer();
	statusCode = std::to_string(response.getStatusCode());
	contentLength = std::to_string(response.getContentLength());
	ret = response.getVersion() + " " + statusCode + " " + response.getReasonPhrase();
	ret += "\r\nConnection: " + response.getConnection() + "\r\nContent-Length: " + contentLength;
	ret += "\r\nContent-Type: " + response.getContentType();
	ret += "\r\nServer: " + response.getServer();
	ret += "\r\n\r\n";
	if (mimeDetect(file) == "image/png" || mimeDetect(file) == "image/jpeg"
	|| mimeDetect(file).find("font") != std::string::npos) {
		line = ft_strdup(ret.c_str());
		retline = newbuffer(line, response.getBinaryPage(), (int)(response.getBinaryPageLen()));
		//delete line;
		connection.setAnswerSize(ret.size() + response.getBinaryPageLen());
		//delete charbuffer; //static_cast<char*>(response.getBinaryPage());
		response.setBinaryPage(nullptr, 0);
		return (retline);
	}
	else {
		ret += response.getPage();
		line = ft_strdup(ret.c_str());
		connection.setAnswerSize(ret.size() + response.getPage().size());
		return (line);
	}
}

void 	*POST(RequestHeaders request, ConfigClass server, ConnectionClass &connection) {
	ResponseHeaders			response;
	std::fstream			file;
	std::string 			openfile;
	std::string 			ret;
	std::string 			body;
	size_t 					result;
	std::string 			statucCode;
	char 					*line;

	if (request.getBody().length() == 0) {
		response.setVersion();
		openfile = server.getRoot() + "/" + request.get_uri();
		if ((result = openfile.find("//")) != std::string::npos) {
			openfile.replace(result, 2, std::string("/"));
		}
		file.open(openfile, std::fstream::out);
		if (file.is_open())
			file.close();
		response.setReasonPhrase("No Content");
		response.setConnection("keep-alive");
		response.setServer();
		ret = response.getVersion() + " 204 " + response.getReasonPhrase();
		ret += "\r\nConnection: " + response.getConnection();
		ret += "\r\nServer: " + response.getServer() + "\r\n";
		connection.setAnswerSize(ret.size());
		return (ft_strdup(ret.c_str()));
	}
	else {
		response.setVersion();
		response.setServer();
		if ((request.getResponseFlags() & CLIENT_BODY_SIZE_EXIST) == CLIENT_BODY_SIZE_EXIST) {
			if (request.getLocation() < 0) {
				if (static_cast<int>(request.getBody().size()) > server.getClientBodySize())
					return (returnError(request, 413, "Payload Too Large", connection));
			}
			else {
				if (static_cast<int>(request.getBody().size()) >
				(*server.getLocations())[request.getLocation()]->getClientBodySize()) {
					return (returnError(request, 413, "Payload Too Large", connection));
				}
			}
		}
		openfile = request.get_uri();
		if ((result = openfile.find("//")) != std::string::npos) {
			openfile.replace(result, 2, std::string("/"));
		}
		if ((request.getResponseFlags() & CGI_FLAG) == CGI_FLAG) {
			CGI	cgi(request, *(*server.getLocations())[request.getCGILocation()], connection, request.get_uri());

			statucCode = cgi.run(body);
			if (statucCode == "500")
				return (returnError(request, 500, "Server Error", connection));
			else {
				response.setStatusCode(200);
				response.setReasonPhrase("OK");
				if (request.get_connection() == "close") {
					response.setConnection("close");
				}
				else {
					response.setConnection("keep-alive");
				}
				response.setContentType("text/html");
				response.setContentLength(body.size());
				ret = response.getVersion() + " " + "200" + " " + response.getReasonPhrase();
				ret += "\r\nConnection: " + response.getConnection();
				ret += "\r\nContent-Length: " + std::to_string(response.getContentLength());
				ret += "\r\nContent-Type: " + response.getContentType();
				ret += "\r\nServer: " + response.getServer();
				ret += "\r\n\r\n";
				ret += body;
				line = ft_strdup(ret.c_str());
				connection.setAnswerSize(ret.size() + ft_strlen(line));
				return (line);
			}
		}
		else {
			file.open(openfile, std::fstream::out);
			if (file.is_open()) {
				file << request.getBody();
				response.setReasonPhrase("Created");
				response.setConnection("keep-alive");
				response.setServer();
				ret = response.getVersion() + " 201 " + response.getReasonPhrase();
				ret += "\r\nConnection: " + response.getConnection();
				ret += "\r\nServer: " + response.getServer() + "\r\n";
				connection.setAnswerSize(ret.size());
				return (ft_strdup(ret.c_str()));
			} else {
				return (returnError(request, 404, "Found", connection));
			}
		}
	}
}

void 	*DELETE(RequestHeaders request, ConfigClass server, ConnectionClass &connection) {
	ResponseHeaders response;
	std::string file;
	std::string ret;
	size_t 		result;

	file = server.getRoot() + "/" + request.get_uri();
	if ((result = file.find("//")) != std::string::npos) {
		file.replace(result, 2, std::string("/"));
	}
	if (std::remove(file.c_str()) == 0) {
		response.setVersion();
		response.setReasonPhrase("OK");
		response.setConnection("keep-alive");
		response.setServer();
		ret = response.getVersion() + " 200 " + response.getReasonPhrase();
		ret += "\r\nConnection: " + response.getConnection();
		ret += "\r\nServer: " + response.getServer() + "\r\n";
		connection.setAnswerSize(ret.size());
		return (ft_strdup(ret.c_str()));
	}
	else {
		return (returnError(request, 400, "Bad Request", connection));
	}
}

void 		*methodNotAllowed(RequestHeaders request, ConnectionClass &connection) {
	return (returnError(request, 405, "Method Not Allowed", connection));
}

void 		*noSuchMethod(RequestHeaders request, ConnectionClass &connection) {
	return (returnError(request, 501, "Not Implemented", connection));
}

static bool	checkServer(RequestHeaders &request, std::vector<ConfigClass*> config, ConnectionClass &connection) {
	uint32_t	ip;
	uint16_t	port;
	std::string serverName;
	bool 		firstServerFlag = 0;
	size_t 		firstServer = 0;
	bool 		flag = 0;

	request.clearResponesFlag();
	if (request.get_host() != "") {
		for (size_t i = 0; i < config.size(); ++i) {
			ip = config[i]->getIp();
			port = config[i]->getPort();
			serverName = config[i]->getServer_name();
			if (firstServerFlag == 0 && port == connection.getListenPort()) {
				firstServer = i;
				firstServerFlag = 1;
			}
			if (serverName == request.get_host() && ip == connection.getListenIp() && port == connection.getListenPort()) {
				connection.setServer(*config[i]);
				request.setResponseFlag(SERVER_NAME);
				flag = 1;
				break;
			}
		}
		if (firstServerFlag && !flag) {
			connection.setServer(*config[firstServer]);
			request.setResponseFlag(SERVER_NAME);
			flag = 1;
		}
	}
	else {
		for (size_t i = 0; i < config.size(); ++i) {
			ip = config[i]->getIp();
			port = config[i]->getPort();
			if (ip == connection.getListenIp() && port == connection.getListenPort()) {
				connection.setServer(*config[i]);
				request.setResponseFlag(SERVER_NAME);
				flag = 1;
				break;
			}
		}
	}
	return (flag);
}

void		setFlags(RequestHeaders &request, ConfigClass server) {
	std::string 							fileExtension;
	std::string								uri = request.get_uri();
	std::string 							locationRoot;
	std::string 							location;
	std::pair<std::string, std::string>		root;
	std::vector<LocationClass*>::iterator	allowIter;
	bool 									flag = 0;
	size_t 									result;
	size_t 									locationNumber = 0;
	size_t 									locationSize = 0;

	fileExtension = extensionDetect(uri);
	for (std::vector<LocationClass*>::iterator it = server.getLocations()->begin(); it != server.getLocations()->end(); ++it) {
		locationRoot = (*it)->getRoot();
		location = (*it)->getLocation();
		if (fileExtension != "none" && location == fileExtension) {
			request.setResponseFlag(CGI_FLAG);
			request.setCGILocation(locationNumber);
		}
		else if ((request.get_uri().find(location) == 0 || request.get_uri() == location) \
		&& ((flag == 1 && location.size() > locationSize) || flag == 0)) {
			locationSize = location.size();
			request.setLocation(locationNumber);
			allowIter = it;
			flag = 1;
		}
		locationNumber++;
	}
	if (flag == 1) {
		if ((*allowIter)->getRoot() != "") {
			request.setResponseFlag(ROOT_EXISTS);
			uri.replace(0, (*allowIter)->getLocation().size(), (*allowIter)->getRoot());
			if (uri.find("./") != std::string::npos) {
				uri = server.getRoot() + "/" + uri;
			}
			else {
				uri = locationRoot + "/" + uri;
			}
			if ((result = uri.find("./")) != std::string::npos || locationRoot == "./")
				uri.replace(result, 2, "/");
		}
		else {
			uri = server.getRoot() + request.get_uri();
		}
		if (uri != request.get_uri()) {
			if ((result = uri.find("?")) != std::string::npos) {
				uri.erase(result, uri.length() - 1);
			}
			if ((result = uri.find(".map")) != std::string::npos) {
				uri.erase(result, uri.length() - 1);
			}
			if ((result = uri.find("//")) != std::string::npos)
				uri.replace(result, 2,std::string("/"));
			request.setUri(uri);
		}
		if ((*allowIter)->getListing() != -1) {
			request.setResponseFlag(LISTING);
			if ((*allowIter)->getListing() == 1) {
				request.setResponseFlag(LISTING_RESULT_YES);
			}
		}
		if ((*allowIter)->getMethods()->size() > 0)
			request.setResponseFlag(ALLOW_METHODS);
		if ((*allowIter)->getClientBodySize() > 0)
			request.setResponseFlag(CLIENT_BODY_SIZE_EXIST);
		if ((*allowIter)->getIndex() != "")
			request.setResponseFlag(INDEX);
		if ((*allowIter)->getRedirection() != "")
			request.setResponseFlag(REDIRECTION);
		if ((*allowIter)->getErrorPages().size() > 0) {
			request.setResponseFlag(CUSTOM_ERRORS);
		}
	}
	else {
		request.setLocation(-1);
		if (server.getClientBodySize() > 0)
			request.setResponseFlag(CLIENT_BODY_SIZE_EXIST);
		if ((*allowIter)->getErrorPages().size() > 0) {
			request.setResponseFlag(CUSTOM_ERRORS);
		}
	}
}

static bool checkAllow(RequestHeaders &request, std::string method, ConfigClass server) {
	size_t 	locationNumber;

	if ((request.getResponseFlags() & ALLOW_METHODS) == ALLOW_METHODS) {
		locationNumber = request.getLocation();
		// Создаю объект локации из той, что получил при парсе флагов
		LocationClass	*location((*server.getLocations())[locationNumber]);

		// Создаю вектор доступных методов из полученного location
		std::vector<std::string>	allow((*location->getMethods()));

		if (allow.size() > 0 && (std::find(allow.begin(), allow.end(), method) == allow.end())) {
			return (0);
		}
	}
	return (1);
}

static bool	chUriDir(RequestHeaders &request, ConfigClass server, std::string GetRoot) {
	std::string	root;
	std::string locationRoot;
	size_t 		locationNumber;
	size_t 		result;

	if ((request.getResponseFlags() & ROOT_EXISTS) == ROOT_EXISTS) {
		locationNumber = request.getLocation();
		// Создаю объект локации из той, что получил при парсе флагов
		LocationClass	*location((*server.getLocations())[locationNumber]);

		locationRoot = location->getRoot();
		if (locationRoot.find("./") == 0 || locationRoot == "./") {
			locationRoot.replace(0, 2, "/");
			root = server.getRoot() + "/" + locationRoot;
			if ((result = root.find("//")) != std::string::npos)
				root.replace(result, 2,"/");
		}
		else {
			root = location->getRoot();
		}
		if (chdir(root.c_str()) == -1)
			return (0);
	}
	else {
		if (chdir(GetRoot.c_str()) == -1)
			return (0);
	}
	return (1);
}

static bool checkRedirect(RequestHeaders &request) {
	if ((request.getResponseFlags() & REDIRECTION) == REDIRECTION) {
		return (0);
	}
	return (1);
}

void 		*generateAnswer(RequestHeaders &request, std::vector<ConfigClass*> config, ConnectionClass &connection) {
	std::string root;
	std::string method;
	std::string index;
	void 		*ret;

	if (!checkServer(request, config, connection))
		return (returnError(request, 400, "Bad Request", connection));
	method = request.get_method();
	root = connection.getServer().getRoot();
	if (method != "GET" && method != "POST" && method != "DELETE")
		return (noSuchMethod(request, connection));
	setFlags(request, connection.getServer());
	if (!checkAllow(request, method, connection.getServer()))
		return (methodNotAllowed(request, connection));
	if (!checkRedirect(request))
		return (returnError(request, 308, "Permanent Redirect", connection));
	if (!chUriDir(request, connection.getServer(), root))
		return (returnError(request, 404, "Not Found", connection));
	if (method == "GET") {
		ret = GET(request,  connection.getServer(), connection);
	}
	else if (method == "POST") {
		ret = POST(request, connection.getServer(), connection);
	}
	else {
		ret = DELETE(request, connection.getServer(), connection);
	}
	return (ret);
}
