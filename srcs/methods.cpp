//
// Created by Karyn Cedra on 4/5/21.
//

#include "../includes/methods.h"

char 	*returnError(RequestHeaders request, size_t statusC, std::string reason) {
	ResponseHeaders	response;
	std::string 	statusCode;
	std::string 	contentLength;
	std::string 	fileline;
	std::string 	ret;
	char 			*line;
	int 			fd;

	fd = open(std::string("/Users/kcedra/webserver/default_errors/error" +
			std::to_string(statusC) + ".html").c_str(), O_RDONLY); // Убрать косталь с моим абсоютным путем
	while (get_next_line(fd, &line) > 0) {
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
	response.setConnection("keep-alive");
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
	ResponseHeaders			response;
	std::string 			ret;
	std::string 			statusCode;
	std::string				contentLength;
	std::string 			fileline;
	std::string 			file;
	std::string 			directory;
	std::string     		uri = request.get_uri();
	std::string::iterator	it;
	std::string::iterator	ite;
	struct stat 			*buf = (struct stat*)malloc(sizeof(struct stat));
	struct dirent			*entry;
	std::string     		seekfilename;
	std::string 			root;
	//size_t					binaryLen = 0;
	size_t 					bufRead;
	char 					*line;
	DIR 					*dir;
	int 					fd;
	size_t 					pos;

	if (request.get_uri() == "/") {
		file = server.getIndex(); // Нужно будет сделать выбор файла с опциям, по приоритету и т.п.
	}
	else {
		if ((pos = uri.find("?")) != std::string::npos)
			uri.erase(pos, uri.length() - 1);
		it = uri.end();
		ite = uri.end();
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
			if (dir != NULL)
				closedir(dir);
			return (returnError(request, 404, "Not Found"));
		}
		file = directory + file;
	}
	if ((pos = file.find("?")) != std::string::npos)
		file.erase(pos, file.length() - 1);
	fd = open(file.c_str(), O_RDONLY);
	if (fd < 0)
		return (returnError(request, 404, "Not Found"));
	else {
		if (mimeDetect(file) == "image/png" || mimeDetect(file) == "image/jpeg"
		|| mimeDetect(file).find("font") != std::string::npos) {
			line = (char *)malloc(128);
			while ((bufRead = read(fd, line, 127)) > 0) {
				line[bufRead] = '\0';
				fileline = line;
				response.pageAdd(fileline);
				//binaryLen += bufRead;
				//ft_bzero(line, 128);
				//response.binaryPageAdd(line);
			}
		}
		else {
			while (get_next_line(fd, &line)) {
				fileline = line;
				free(line);
				line = nullptr;
				response.pageAdd(fileline + "\n");
			}
			response.binaryPageAdd(nullptr);
		}
		close(fd);
	}
	response.setVersion();
	response.setStatusCode(200);
	response.setReasonPhrase("OK");
	response.setConnection("keep-alive");
	//if (response.getBinaryPage() != nullptr)
	//	response.setContentLength(ft_strlen(response.getBinaryPage()));
	//else
	response.setContentLength(response.getPage().length());
	response.setContentType(mimeDetect(file));
	response.setDate(request);
	response.setServer();
	statusCode = std::to_string(response.getStatusCode()); //Добавить сюда свой итоа
	contentLength = std::to_string(response.getContentLength());
	ret = response.getVersion() + " " + statusCode + " " + response.getReasonPhrase();
	ret += "\nConnection: " + response.getConnection() + "\nContent-Length: " + contentLength + "\nContent-Type: " + response.getContentType();
	ret += "\nServer: " + response.getServer();
	ret += "\r\n\r\n";
	if (mimeDetect(file) == "image/png" || mimeDetect(file) == "image/jpeg"
	|| mimeDetect(file).find("font") != std::string::npos) {
		line = ft_strjoin(ret.c_str(), response.getBinaryPage());
	}
	else {
		ret += response.getPage();
		line = ft_strdup(ret.c_str());
	}
	response.binaryPageAdd(nullptr);
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
		ret += "\nConnection: " + response.getConnection();
		ret += "\nServer: " + response.getServer() + "\n";
		return (ft_strdup(ret.c_str()));
	}
	return nullptr;
}

char 	*noSuchMethod(RequestHeaders request) {
	return (returnError(request, 501, "Not Implemented"));
}

char 	*generateAnswer(RequestHeaders request, ConfigClass config) {
	//ConfigClass					server;
	std::string 				method;
	char 						*ret;

	chdir(config.getRoot().c_str());
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
