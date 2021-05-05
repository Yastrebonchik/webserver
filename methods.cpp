//
// Created by Karyn Cedra on 4/5/21.
//

#include "methods.h"

char 	*GET(RequestHeaders request, ConfigClass server) {
	ResponseHeaders	response;
	std::string 	ret;
	std::string 	statusCode;
	std::string 	contentLength;
	std::string 	fileline;
	std::string 	file;
	std::string 	directory;
	std::string     uri = request.get_uri();
	struct dirent	*entry;
	std::string     seekfilename;
	char 			*line;
	DIR 			*dir;
	int 			fd;
	std::string::iterator it = uri.end();
	std::string::iterator ite = uri.end();

	if (*(--it) == '/') {
//		dir = opendir((server.root + request.get_uri()).c_str());
//		if (!dir) {
//			perror("diropen");
//			exit(5);
//		}
		file = "index.html"; // Нужно будет сделать выбор файла с опциям, по приоритету и т.п.
	}
	else {
		while (*it != '/') {
			it--;
		}
		directory = (server.root + std::string(uri.begin(), it++)) + '/';
		dir = opendir(directory.c_str());
//		if (!dir) {
//			perror("diropen");
//			exit(5);
//		}
		it--;
		while (++it != ite) {
			file += *(it);
		}
		while (dir != NULL && (entry = readdir(dir)) != NULL) {
		    seekfilename = entry->d_name;
			if (seekfilename == file) {
				closedir(dir);
				break;
			}
		}
		if (dir == NULL || entry == NULL) {
			fd = open("error404.html", O_RDONLY);
			while (get_next_line(fd, &line) > 0){
				fileline = line;
				free(line);
				line = nullptr;
				response.pageAdd(fileline + "\n");
			}
			close(fd);
			response.setVersion();
			response.setStatusCode(404);
			response.setReasonPhrase("Not Found");
			//response.setAllow();
			response.setConnection("close");
			response.setContentLength(response.getPage().length());
			response.setContentType("text/html");// charset=UTF-8");
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
	//response.setAllow();
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
	ResponseHeaders	response;
	std::string 	ret;
	std::string 	statusCode;
	std::string 	contentLength;
	std::string 	fileline;
	char 			*line;
	int 			file;

	file = open("error501.html", O_RDONLY);
	while (get_next_line(file, &line) > 0){
		fileline = line;
		free(line);
		line = nullptr;
		response.pageAdd(fileline + "\n");
	}
	close(file);
	response.setVersion();
	response.setStatusCode(501);
	response.setReasonPhrase("Not Implemented");
	response.setAllow();
	response.setConnection("close");
	response.setContentLength(fileline.length());
	response.setContentType("text/html");// charset=UTF-8");
	response.setDate(request);
	response.setServer();
	statusCode = std::to_string(response.getStatusCode()); //Добавить сюда свой итоа
	contentLength = std::to_string(response.getContentLength());
	ret = response.getVersion() + " " + statusCode + " " + response.getReasonPhrase() + "\nAllow: " + response.getAllow();
	ret += "\nConnection: " + response.getConnection() + "\nContent-Length: " + contentLength + "\nContent-Type: " + response.getContentType();
	ret += "\nServer: " + response.getServer();
	ret += "\r\n\r\n" + response.getPage();
	line = ft_strdup(ret.c_str());
	return (line);
}

char 	*generateAnswer(RequestHeaders request) {
	ConfigClass					server;
	std::vector<ConfigClass>	config;
	std::string 				method;
	char 						*ret;

	server.server_name = "default_server";
	server.ip = "127.0.0.1";
	server.port = 80;
	server.root = "/Users/alexander/webserver/directory_for_tests";
	chdir(server.root.c_str());
	config.push_back(server);
	method = request.get_method();
	if (method == "GET") {
		ret = GET(request, server);
	}
	else if (method == "POST") {
		ret = POST(request, server);
	}
	else {
		ret = noSuchMethod(request);
	}
	return (ret);
}
