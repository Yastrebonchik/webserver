//
// Created by Karyn Cedra on 4/5/21.
//

#include "methods.h"

char 	*GET(RequestHeaders request) {
	return nullptr;
}

char 	*POST(RequestHeaders request) {

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
	response.setVersion();
	response.setStatusCode(501);
	response.setReasonPhrase("Not Implemented");
	response.setAllow();
	response.setConnection("close");
	response.setContentLength(fileline.length());
	response.setContentType("text/html");
	response.setServer();
	statusCode = std::to_string(response.getStatusCode()); //Добавить сюда свой итоа
	contentLength = response.getContentLength();
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
	server.root = "/Users/kcedra/webserver/directory_for_tests";
	chdir(server.root.c_str());
	config.push_back(server);
	method = request.get_method();
	if (method == "GT") {
		ret = GET(request);
	}
	else if (method == "POST") {
		ret = POST(request);
	}
	else {
		ret = noSuchMethod(request);
	}
	return (ret);
}
