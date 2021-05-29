//
// Created by Karyn Cedra on 4/5/21.
//

#include "methods.h"

char 	*returnError(RequestHeaders request, size_t statusC, std::string reason) {
	ResponseHeaders	response;
	std::string 	statusCode;
	std::string 	contentLength;
	std::string 	fileline;
	std::string 	ret;
	char 			*line;
	int 			fd;

	fd = open(std::string("error" + std::to_string(statusC) + ".html").c_str(), O_RDONLY);
	while (get_next_line(fd, &line) > 0){
		fileline = line;
		free(line);
		line = nullptr;
		response.pageAdd(fileline + "\n");
	}
	close(fd);
	response.setVersion();
	response.setStatusCode(statusC);
	response.setReasonPhrase(reason);
	if (statusC == 405 || statusC == 501)
		response.setAllow();
	response.setConnection("close");
	response.setContentLength(response.getPage().length());
	response.setContentType("text/html");
	response.setDate(request);
	response.setServer();
	statusCode = std::to_string(response.getStatusCode()); //Добавить сюда свой итоа
	contentLength = std::to_string(response.getContentLength()); //Добавить сюда свой итоа
	ret = response.getVersion() + " " + statusCode + " " + response.getReasonPhrase();
	if (statusC == 501 || statusC == 405)
		ret += "\r\nAllow: " + response.getAllow();
	ret += "\r\nConnection: " + response.getConnection() + "\r\nContent-Length: " + contentLength;
	ret += "\r\nContent-Type: " + response.getContentType() + "\r\nServer: " + response.getServer();
	ret += "\r\n\r\n" + response.getPage();
	line = ft_strdup(ret.c_str());
	return (line);
}

char 	*GET(RequestHeaders request, ConfigClass server) {
	ResponseHeaders	response;
	std::string 			ret;
	std::string 			statusCode;
	std::string				contentLength;
	std::string 			fileline;
	std::string 			file;
	std::string 			directory;
	std::string     		uri = request.get_uri();
	std::string::iterator	it = uri.end();
	std::string::iterator	ite = uri.end();
	struct stat 			*buf = (struct stat*)malloc(sizeof(struct stat));
	struct dirent			*entry;
	std::string     		seekfilename;
	char 					*line;
	DIR 					*dir;
	int 					fd;

	if (request.get_uri() == "/") {
		if (request.get_uri() == "/")
			file = server.getIndex();
		else
			file = request.get_uri(); // Нужно будет сделать выбор файла с опциям, по приоритету и т.п.
	}
	else {
		while (*it != '/') {
			it--;
		}
		directory = (server.getRoot() + std::string(uri.begin(), it++)) + '/';
		dir = opendir(directory.c_str());
		it--;
		while (++it != ite) {
			file += *(it);
		}
		while (dir != NULL && (entry = readdir(dir)) != NULL) {
		    seekfilename = entry->d_name;
			stat(file.c_str(), buf);
		    if (seekfilename == file && !S_ISDIR(buf->st_mode)) {
				closedir(dir);
				break;
			}
		}
		if (dir == NULL || entry == NULL) {
			return (returnError(request, 404, "Not Found"));
		}
	}
	fd = open(file.c_str(), O_RDONLY);
	while (get_next_line(fd, &line) > 0){
		fileline = line;
		free(line);
		line = nullptr;
		response.pageAdd(fileline + "\n");
	}
	close(fd);
	response.setVersion();
	response.setStatusCode(200);
	response.setReasonPhrase("OK");
	response.setConnection("keep-alive");
	response.setContentLength(response.getPage().length());
	if (file == "aboba.jpg")
		response.setContentType("image/jpeg");
	else
		response.setContentType("text/html; charset=UTF-8");
	response.setDate(request);
	response.setServer();
	statusCode = std::to_string(response.getStatusCode()); //Добавить сюда свой итоа
	contentLength = std::to_string(response.getContentLength());
	ret = response.getVersion() + " " + statusCode + " " + response.getReasonPhrase();// + "\nAllow: " + response.getAllow();
	ret += "\nConnection: " + response.getConnection() + "\nContent-Length: " + contentLength + "\nContent-Type: " + response.getContentType();
	ret += "\nServer: " + response.getServer();
	ret += "\r\n\r\n" + response.getPage();
	line = ft_strdup(ret.c_str());
	return (line);
}

char 	*POST(RequestHeaders request, ConfigClass server) {
	return nullptr;
}

char 	*noSuchMethod(RequestHeaders request) {
	return (returnError(request, 501, "Not Implemented"));
}

char 	*generateAnswer(RequestHeaders request, ConfigClass config) {
	//ConfigClass					server;
	std::string 				method;
	char 						*ret;

//	server.server_name = "default_server";
//	server.ip = "127.0.0.1";
//	server.port = 80;
//	server.root = "/Users/kcedra/webserver/directory_for_tests";
	chdir(config.getRoot().c_str());
	//config.push_back(server);
	method = request.get_method();
	if (method == "GET") {
		ret = GET(request, config);
	}
	else if (method == "POST") {
		ret = POST(request, config);
	}
	else {
		ret = noSuchMethod(request);
	}
	return (ret);
}
