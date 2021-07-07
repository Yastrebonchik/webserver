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

//char 	*HEAD(RequestHeaders request, std::string root, std::string index) {
//	return (nullptr)
//}

char 	*GET(RequestHeaders request, std::string root, std::string index) {
	ResponseHeaders response;
	std::string body;
	std::string ret;
	std::string statusCode;
	std::string contentLength;
	std::string fileline;
	std::string file;
	std::string directory;
	std::string uri = request.get_uri();
	std::string::iterator it;
	std::string::iterator ite;
	std::fstream fin;
	std::stringstream strstream;
	struct stat *buf = (struct stat *) operator new(sizeof(struct stat));
	struct dirent *entry;
	std::string seekfilename;
	char *line;
	DIR *dir;
	int length;
	char *buffer;
	size_t pos;
	size_t result;

	if (*(--uri.end()) == '/') {
		file = index; // Нужно будет сделать выбор файла с опциям, по приоритету и т.п.
		directory = root + uri;
	}
	else {
		if ((pos = uri.find("?")) != std::string::npos)
			uri.erase(pos, uri.length() - 1);
		it = uri.end();
		ite = uri.end();
		while (*it != '/') {
			it--;
		}
		directory = (root + std::string(uri.begin(), it++)) + '/';
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
			stat(file.c_str(), buf);
			if (seekfilename == file) {
				if (S_ISDIR(buf->st_mode)) {
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
	if (index == "" && directory == uri) {
		response.setPage(listing(directory));
		response.setBinaryPage(nullptr);
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
			return (returnError(request, 404, "Not Found"));
		else {
			if (mimeDetect(file) == "image/png" || mimeDetect(file) == "image/jpeg"
				|| mimeDetect(file).find("font") != std::string::npos) {
				fin.seekg(0, fin.end);
				length = fin.tellg();
				fin.seekg(0, fin.beg);
				buffer = new char[length];
				fin.read(buffer, length);
				response.setBinaryPage(buffer);
				fin.close();
			} else {
				strstream << fin.rdbuf();
				body = strstream.str();
				response.setPage(std::string(body.begin(), body.end()));
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
	if (index == "")
		response.setContentType("text/html");
	else
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

char 	*POST(RequestHeaders request, ConfigClass server) {
	ResponseHeaders			response;
	std::fstream			file;
	std::string 			ret;

	if (request.getBody().length() == 0) {
		response.setVersion();
		file.open(server.getRoot() + request.get_uri(), std::fstream::out);
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
	return nullptr;
}

char 	*methodNotAllowed(RequestHeaders request) {
	return (returnError(request, 405, "Method Not Allowed"));
}

char 	*noSuchMethod(RequestHeaders request) {
	return (returnError(request, 501, "Not Implemented"));
}

std::pair<std::string, std::string>	chooseRootgetIndexFindAllowed(RequestHeaders &request, ConfigClass config, \
	std::string method) {

	std::string							uri = request.get_uri();
	std::string 						locationRoot;
	std::string 						location;
	std::pair<std::string, std::string>	root;
	std::list<LocationClass>::iterator	allowIter;
	std::list<std::string>				*allow;
	bool 								flag = 0;
	size_t 								result;

	root = std::make_pair("", "");
	for (std::list<LocationClass>::iterator it = config.getLocations()->begin(); it != config.getLocations()->end(); ++it) {
		locationRoot = it->getRoot();
		location = it->getLocation();
		if ((request.get_uri().find(location) != std::string::npos || request.get_uri() == location\
		) && locationRoot.size() >= root.first.size()) {
			uri	= request.get_uri();
			uri.replace(0, location.size(), locationRoot);
			flag = 1;
			allowIter = it;
		}
	}
	if (flag == 1) {
		root = std::make_pair(config.getRoot() + locationRoot, allowIter->getIndex());
		if (allowIter->getListing()) {
			root.second = "";
		}
	}
	if (root == std::pair<std::string, std::string>("", "")) {
		root = std::make_pair(config.getRoot(), config.getIndex());
	}
	if (flag == 1 && (method == "GET" || method == "POST" || method == "DELETE" || method == "HEAD")) {
		allow = allowIter->getMethods();
		if (std::find(allow->begin(), allow->end(), method) == allow->end())
			root = std::make_pair("", "");
	}
	if (uri != request.get_uri()) {
		if ((result = uri.find("//")) != std::string::npos)
			uri.replace(result, 2,std::string("/"));
		request.setUri(uri);
	}
	return (root);
}

char 	*generateAnswer(RequestHeaders request, ConfigClass config) {
	std::pair<std::string, std::string> 				root;
	std::string 										method;
	std::string 										index;
	char 												*ret;

	method = request.get_method();
	root = chooseRootgetIndexFindAllowed(request, config, method);
	if (root.first == "" && root.second == "")
		return (methodNotAllowed(request));
	chdir(root.first.c_str());
	if (method == "GET") {
		ret = GET(request,  root.first, root.second);
	}
	else if (method == "POST") {
		ret = POST(request, config);
	}
//	else if (method == "HEAD") {
//		ret = HEAD(GET(request,  root.first, root.second));
//	}
	else {
		ret = noSuchMethod(request);
	}
	return (ret);
}
