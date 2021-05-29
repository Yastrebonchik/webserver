#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <fstream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "RequestHeaders.hpp"
#include <errno.h>
#include <ctime>
#include <fcntl.h>
#include <sys/select.h>
#include "methods.h"

//struct in_addr {
//	unsigned long s_addr;
//};
//
//struct sockaddr_in {
//	short int          sin_family;  // Семейство адресов
//	unsigned short int sin_port;    // Номер порта
//	struct in_addr     sin_addr;    // IP-адрес
//	unsigned char      sin_zero[8]; // "Дополнение" до размера структуры sockaddr
//};

int main() {
	RequestHeaders				request;
	std::vector<ConfigClass>	config;
	ConfigClass					server;
	std::string 				line;
	int							sock, listener;
	struct						sockaddr_in addr;
	char						buf[1024];
	char 						*ret;
	int							bytes_read;

	ret = NULL;
	config_parser((char*)"config_parser_v.0.1/config/config_file", config);
	server = config[0];
	listener = socket(AF_INET, SOCK_STREAM, 0);
	//fcntl(listener, F_SETFL, O_NONBLOCK);
	if(listener < 0) {
		perror("socket");
		exit(1);
	}

	addr.sin_family = AF_INET;
	addr.sin_port = server.getPort();
	addr.sin_addr.s_addr = server.getIp();
	if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("bind");
		exit(2);
	}

	listen(listener, 1);
	while(1) {
		sock = accept(listener, NULL, NULL);
		//fcntl(sock, F_SETFL, O_NONBLOCK);
		std::cout << "I'm here" << std::endl;
		if(sock < 0) {
			perror("accept");
			exit(3);
		}

		while(1) {
			bytes_read = recv(sock, buf, 1024, 0);
			if (bytes_read <= 0)
				break;
			request.setSource(buf);
			request.setInfo();
			ft_bzero(buf, 1024);
			ret = generateAnswer(request, server);
			if (send(sock, ret, ft_strlen(ret) + 1, 0) < 0)
				std::cout << "Error number = " << errno << std::endl;
			free(ret);
			ret = NULL;
			request.clear();
		}
		if (request.get_connection() == "close")
			close(sock);
	}
	close(listener);
    return 0;
}
