//
// Created by Karyn Cedra on 4/5/21.
//

#include "methods.h"

char 	*returnError(RequestHeaders request, size_t statusC, std::string reason) {
	ResponseHeaders		response;
	std::stringstream	strstream;
	std::fstream 		fin;
	std::string 		body;
	std::string 		statusCode;
	std::string 		contentLength;
	std::string 		fileline;
	std::string 		ret;
	char 				*line;


	fin.open(std::string("/Users/kcedra/webserver/default_errors/error" +
						 std::to_string(statusC) + ".html"), std::ios::in); // Убрать косталь с моим абсоютным путем
	strstream << fin.rdbuf();
	body = strstream.str();
	response.setPage(std::string(body.begin(), body.end()));
	fin.close();
	response.setVersion();
	response.setStatusCode(statusC);
	response.setReasonPhrase(reason);
	if (statusC == 405 || statusC == 501)
		response.setAllow();
	response.setConnection("keep-alive");
	response.setContentLength(response.getPage().length());
	response.setContentType("text/html");
	response.setDate(request);
	response.setServer();
	statusCode = std::to_string(response.getStatusCode());
	contentLength = std::to_string(response.getContentLength());
	ret = response.getVersion() + " " + statusCode + " " + response.getReasonPhrase();
	if (statusC == 501 || statusC == 405)
		ret += "\r\nAllow: " + response.getAllow();
	ret += "\r\nConnection: " + response.getConnection() + "\r\nContent-Length: " + contentLength;
	ret += "\r\nContent-Type: " + response.getContentType() + "\r\nServer: " + response.getServer();
	ret += "\r\n\r\n" + response.getPage();
	line = ft_strdup(ret.c_str());
	return (line);
}

char 	*GET(RequestHeaders request, ConfigClass server, std::string root) {
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
	DIR *dir;
//	int length;
	char *buffer;
	size_t pos;
	size_t result;
	std::string index = "";

	if (*(--uri.end()) == '/') {
		if ((request.getResponseFlags() & INDEX) == INDEX) {
			//Выбираю индекс из локейшена
			file = (*server.getLocations())[request.getLocation()].getIndex();
		}
		else {
			if ((request.getResponseFlags() & LISTING) == LISTING) {
				if ((request.getResponseFlags() & LISTING_RESULT_YES) != LISTING_RESULT_YES) {
					return (returnError(request, 403, "Forbidden"));
				}
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
//		if (directory.find("./") == 0 || directory == "./") {
//			directory.replace(0, 2, "/");
//		}
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
			return (returnError(request, 404, "Not Found"));
		}
		file = directory + file;
	}
	if ((pos = file.find("?")) != std::string::npos) {
		file.erase(pos, file.length() - 1);
	}
	if ((request.getResponseFlags() & LISTING) == LISTING) {
		if ((request.getResponseFlags() & LISTING_RESULT_YES) == LISTING_RESULT_YES) {
			directory = root + uri;
			if ((result = directory.find("//")) != std::string::npos) {
				directory.replace(result, 2, std::string("/"));
			}
			response.setPage(listing(directory));
			response.setBinaryPage(nullptr);
		}
	}
	else {
		if (mimeDetect(file) == "image/png" || mimeDetect(file) == "image/jpeg"
			|| mimeDetect(file).find("font") != std::string::npos) {
			fin.open(file, std::fstream::binary | std::fstream::in);
		}
		else {
			fin.open(file, std::fstream::in);
		}
		if (!fin.is_open())
			return (returnError(request, 404, "Not Found"));
		else {
			if (mimeDetect(file) == "image/png" || mimeDetect(file) == "image/jpeg"
				|| mimeDetect(file).find("font") != std::string::npos) {
//				fin.seekg(0, fin.end);
//				length = fin.tellg();
//				fin.seekg(0, fin.beg);
//				buffer = new char[length];
//				fin.read(buffer, length);
//				response.setBinaryPage(buffer);
//				fin.close();
				std::filebuf* pbuf = fin.rdbuf();

				// get file size using buffer's members
				std::size_t size = pbuf->pubseekoff (0,fin.end,fin.in);
				pbuf->pubseekpos (0,fin.in);

				// allocate memory to contain file data
				buffer = (char*)ft_calloc(size, sizeof (char));

				// get file data
				pbuf->sgetn (buffer,size);

				response.setBinaryPage(buffer);
				fin.close();
			} else {
				strstream << fin.rdbuf();
				body = strstream.str();
				response.setPage(body);
				fin.close();
				response.setBinaryPage(nullptr);
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
		response.setContentLength(ft_strlen(response.getBinaryPage()));
	}
	else {
		response.setContentLength(response.getPage().length());
	}
	response.setContentType(mimeDetect(file));
	response.setDate(request);
	response.setServer();
	statusCode = std::to_string(response.getStatusCode()); //Добавить сюда свой итоа
	contentLength = std::to_string(response.getContentLength());
	ret = response.getVersion() + " " + statusCode + " " + response.getReasonPhrase();
	ret += "\r\nConnection: " + response.getConnection() + "\r\nContent-Length: " + contentLength;
	ret += "\r\nContent-Type: " + response.getContentType();
	ret += "\r\nServer: " + response.getServer();
	ret += "\r\n\r\n";
	if (mimeDetect(file) == "image/png" || mimeDetect(file) == "image/jpeg"
	|| mimeDetect(file).find("font") != std::string::npos) {
		line = ft_strjoin(ret.c_str(), response.getBinaryPage());
	}
	else {
		ret += response.getPage();
		line = ft_strdup(ret.c_str());
	}
	response.setBinaryPage(nullptr);
	return (line);
}

char 	*POST(RequestHeaders request, ConfigClass server, ConnectionClass connection) {
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
		return (ft_strdup(ret.c_str()));
	}
	else {
		response.setVersion();
		response.setServer();
		openfile = server.getRoot() + "/" + request.get_uri();
		if ((result = openfile.find("//")) != std::string::npos) {
			openfile.replace(result, 2, std::string("/"));
		}
		if ((request.getResponseFlags() & CGI_FLAG) == CGI_FLAG) {
			CGI	cgi(request, (*server.getLocations())[request.getCGILocation()], connection, request.get_uri());

			statucCode = cgi.run(body);
			if (statucCode == "500")
				return (returnError(request, 500, "Server Error"));
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
				line = ft_strdup(ret.c_str());
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
				return (ft_strdup(ret.c_str()));
			} else {
				return (returnError(request, 500, "Server Error"));
			}
		}
	}
}

char 	*DELETE(RequestHeaders request, ConfigClass server) {
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
		return (ft_strdup(ret.c_str()));
	}
	else {
		return (returnError(request, 400, "Bad Request"));
	}
}

char 		*methodNotAllowed(RequestHeaders request) {
	return (returnError(request, 405, "Method Not Allowed"));
}

char 		*noSuchMethod(RequestHeaders request) {
	return (returnError(request, 501, "Not Implemented"));
}

static		std::string	extensionDetect(std::string file) {
	if (file.rfind(".") != std::string::npos)
		return (std::string(file.begin() + file.find("."), file.end()));
	else
		return ("none");
}

static bool	checkServer(RequestHeaders &request, std::vector<ConfigClass> config, ConnectionClass &connection) {
	uint32_t	ip;
	uint16_t	port;
	std::string serverName;
	bool 		flag = 0;

	if (request.get_host() != "") {
		for (size_t i = 0; i < config.size(); ++i) {
			ip = config[i].getIp();
			port = config[i].getPort();
			serverName = config[i].getServer_name();
			if (serverName == request.get_host() && ip == connection.getListenIp() && port == connection.getListenPort()) {
				connection.setServer(config[i]);
				request.setResponseFlag(SERVER_NAME);
				flag = 1;
				break;
			}
		}
	}
	else {
		for (size_t i = 0; i < config.size(); ++i) {
			ip = config[i].getIp();
			port = config[i].getPort();
			if (ip == connection.getListenIp() && port == connection.getListenPort()) {
				connection.setServer(config[i]);
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
	std::vector<LocationClass>::iterator	allowIter;
	bool 									flag = 0;
	size_t 									result;
	size_t 									locationNumber = 0;
	size_t 									locationSize = 0;

	fileExtension = extensionDetect(uri);
	for (std::vector<LocationClass>::iterator it = server.getLocations()->begin(); it != server.getLocations()->end(); ++it) {
		locationRoot = it->getRoot();
		location = it->getLocation();
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
		uri	= request.get_uri();
		if (allowIter->getRoot() != "") {
			request.setResponseFlag(ROOT_EXISTS);
			uri = server.getRoot() + locationRoot + request.get_uri();
			//uri.replace(0, location.size(), locationRoot);
			//uri =  request.get_uri();
			if ((result = uri.find("./")) == 0 || locationRoot == "./")
				uri.replace(result, 2, "/");
		}
		else {
			uri = server.getRoot() + request.get_uri();
			//uri.replace(0, location.size(), server.getRoot());
			//uri += request.get_uri();
		}
		if (uri != request.get_uri()) {
			if ((result = uri.find("//")) != std::string::npos)
				uri.replace(result, 2,std::string("/"));
			request.setUri(uri);
		}
		if (allowIter->getListing() != -1) {
			request.setResponseFlag(LISTING);
			if (allowIter->getListing() == 1) {
				request.setResponseFlag(LISTING_RESULT_YES);
			}
		}
		if (allowIter->getMethods()->size() > 0)
			request.setResponseFlag(ALLOW_METHODS);
		if (allowIter->getClientBodySize() != -1)
			request.setResponseFlag(CLIENT_BODY_SIZE_EXIST);
		if (allowIter->getIndex() != "")
			request.setResponseFlag(INDEX);
		if (allowIter->getRedirection() != "")
			request.setResponseFlag(REDIRECTION);
//		if (allowIter->getErrorPage()) Добавить error page когда Серега завезет
	}
	else {
		request.setLocation(-1);
		if (server.getClientBodySize() != -1)
			request.setResponseFlag(CLIENT_BODY_SIZE_EXIST);
//		if (allowIter->getErrorPage()) Добавить error page когда Серега завезет
	}
}

static bool checkAllow(RequestHeaders &request, std::string method, ConfigClass server) {
	size_t 	locationNumber;

	if ((request.getResponseFlags() & ALLOW_METHODS) == ALLOW_METHODS) {
		locationNumber = request.getLocation();
		// Создаю объект локации из той, что получил при парсе флагов
		LocationClass	location((*server.getLocations())[locationNumber]);

		// Создаю вектор доступных методов из полученного location
		std::vector<std::string>	allow((*location.getMethods()));

		if (std::find(allow.begin(), allow.end(), method) == allow.end()) {
			return (0);
		}
	}
	return (1);
}

static bool	chUriDir(RequestHeaders &request, ConfigClass server, std::string &GetRoot) {
	std::string	root;
	std::string locationRoot;
	size_t 		locationNumber;
	size_t 		result;

	if ((request.getResponseFlags() & ROOT_EXISTS) == ROOT_EXISTS) {
		locationNumber = request.getLocation();
		// Создаю объект локации из той, что получил при парсе флагов
		LocationClass	location((*server.getLocations())[locationNumber]);

		locationRoot = location.getRoot();
		if (locationRoot.find("./") == 0 || locationRoot == "./") {
			locationRoot.replace(0, 2, "/");
			root = server.getRoot() + "/" + locationRoot;
			if ((result = root.find("//")) != std::string::npos)
				root.replace(result, 2,"/");
		}
		else {
			root = location.getRoot();
		}
		GetRoot = root;
		if (chdir(root.c_str()) == -1)
			return (0);
	}
	else {
		if (chdir(GetRoot.c_str()) == -1)
			return (0);
	}
	return (1);
}

char 		*generateAnswer(RequestHeaders &request, std::vector<ConfigClass> config, ConnectionClass &connection) {
	std::string root;
	std::string method;
	std::string index;
	char 		*ret;

	if (!checkServer(request, config, connection))
		return (returnError(request, 400, "Bad Request"));
	method = request.get_method();
	root = connection.getServer().getRoot();
	if (method != "GET" && method != "POST" && method != "DELETE")
		return (noSuchMethod(request));
	setFlags(request, connection.getServer());
	if (!checkAllow(request, method, connection.getServer()))
		return (methodNotAllowed(request));
	if (!chUriDir(request, connection.getServer(), root))
		return (returnError(request, 500, "Server Error"));
	if (method == "GET") {
		ret = GET(request,  connection.getServer(), root);
	}
	else if (method == "POST") {
		ret = POST(request, connection.getServer(), connection);
	}
	else {
		ret = DELETE(request, connection.getServer());
	}
	return (ret);
}
