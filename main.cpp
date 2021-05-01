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
	//char			ret[1024] = "HTTP/1.1 200 OK\r\nServer: webserver/n/r/r/nDate: Sat, 08 Mar 2014 22:53:46 GMT\r\nContent-Type: text/html\r\nContent-Length: 161\r\nLast-Modified: Sun, 21 Apr 2021 14:40:30 GMT\r\nConnection: keep-alive\r\n\r\n<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n<meta charset=\"UTF-8\">\n<title>ABOB</title>\n</head>\n<body>\n<a href=\"https://memepedia.ru/aboba/\">ABOBA</a>\n</body>\n</html>";
	int				bytes_read;

	std::srand(std::time(0));
	listener = socket(AF_INET, SOCK_STREAM, 0);
	if(listener < 0)
	{
		perror("socket");
		exit(1);
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(80);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		perror("bind");
		exit(2);
	}

	listen(listener, 1);
	while(1){

		sock = accept(listener, NULL, NULL);
		std::cout << "I'm here" << std::endl;
		if(sock < 0)
		{
			perror("accept");
			exit(3);
		}

		while(1)
		{
			bytes_read = recv(sock, buf, 1024, 0);
			if(bytes_read <= 0) break;
			request.getSource(buf);
			request.setInfo();
			ft_bzero(buf, 1024);
			//ft_bzero(ret, 1024);
			if (request.get_method() == "GET"){
				random = std::rand() % 2;
				if (random == 0) {
					errorfile.open("error400.html", std::fstream::in);
					isopen = errorfile.is_open();
					while (std::getline(errorfile, line)) {
						error += line;
						error += '\n';
					}
					ret = ft_strdup("HTTP/1.1 400 Bad Request\n" \
                        "Server: webserver\n" \
                        "Date: Sat, 01 May 2021 17:15:05 GMT\n" \
                        "Content-Type: text/html\n" \
                        "Content-Length: 152\n" \
                        "Connection: close\n" \
                        "Strict-Transport-Security: max-age=86400\r\n\r\n");
					strcat(ret, error.c_str());
					errorfile.close();
				}
				else {
					retfile.open("testpage.html", std::fstream::in);
					isopen = retfile.is_open();
					while (std::getline(retfile, line)) {
						error += line;
						error += '\n';
					}
					ret = ft_strdup("HTTP/1.1 200 OK\n" \
                        "Server: webserver\n" \
                        "Date: Sat, 01 May 2021 17:15:05 GMT\n" \
                        "Content-Type: text/html\n" \
                        "Content-Length: 161\n" \
                        "Connection: close\n" \
                        "Strict-Transport-Security: max-age=86400\r\n\r\n");
					strcat(ret, error.c_str());
					retfile.close();
				}
			}
			send(sock, ret, bytes_read, 0);
			//free(ret);
			ret = nullptr;
			request.clear();
			error.clear();
		}
		close(sock);
	}
	close(listener);
	//file.close();
    return 0;
}
