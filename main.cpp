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
	std::fstream	errorfile;
	std::fstream	retfile;
	std::string 	error;
	std::string 	line;
	RequestHeaders	request;
	int 			random;
	bool 			isopen;
	int				sock, listener;
	struct			sockaddr_in addr;
	char			buf[1024];
	char 			*ret;
	int				bytes_read;

	std::srand(std::time(0)); //Обновление последовательности рандомизации
	ret = NULL;
	listener = socket(AF_INET, SOCK_STREAM, 0);
	//fcntl(listener, F_SETFL, O_NONBLOCK);
	if(listener < 0) {
		perror("socket");
		exit(1);
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(80);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
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
			if(bytes_read <= 0) break;
			request.setSource(buf);
			request.setInfo();
			ft_bzero(buf, 1024);
			ret = generateAnswer(request);
//			if (request.get_method() == "GET"){
//				random = std::rand() % 2;
//				if (random == 0) {
//					errorfile.open("error400.html", std::fstream::in);
//					isopen = errorfile.is_open();
//					while (std::getline(errorfile, line)) {
//						error += line;
//						error += '\n';
//					}
//					ret = (char*)malloc(sizeof(char) * (195 + error.length() + 1));
//					ft_bzero(ret, 195 + error.length() + 1);
//					ft_strlcpy(ret, "HTTP/1.1 400 Bad Request\n" \
//                        "Server: webserver\n" \
//                        "Date: Sat, 01 May 2021 17:15:05 GMT\n" \
//                        "Content-Type: text/html\n" \
//                        "Content-Length: 152\n" \
//                        "Connection: close\n" \
//                        "Strict-Transport-Security: max-age=86400\r\n\r\n", 195 + 1);
//					ft_strlcat(ret, error.c_str(), 195 + error.length() + 1);
//					errorfile.close();
//				}
//				else {
//					retfile.open("testpage.html", std::fstream::in);
//					isopen = retfile.is_open();
//					while (std::getline(retfile, line)) {
//						error += line;
//						error += '\n';
//					}
//					ret = (char*)malloc(sizeof(char) * (194 + error.length() + 1));
//					ft_bzero(ret, 194 + error.length() + 1);
//					ft_strlcpy(ret, "HTTP/1.1 200 OK\n" \
//                        "Server: webserver\n" \
//                        "Date: Sat, 01 May 2021 17:15:05 GMT\n" \
//                        "Content-Type: text/html\n" \
//                        "Content-Length: 161\n" \
//                        "Connection: close\n" \
//                        "Strict-Transport-Security: max-age=86400\r\n\r\n", 194 + 1);
//					ft_strlcat(ret, error.c_str(), 194 + error.length() + 1);
//					retfile.close();
//				}
//			}
			if (send(sock, ret, ft_strlen(ret) + 1, 0) < 0)
				std::cout << "Error number = " << errno << std::endl;
			free(ret);
			ret = NULL;
			request.clear();
			error.clear();
		}
		close(sock);
	}
	close(listener);
	//file.close();
    return 0;
}
