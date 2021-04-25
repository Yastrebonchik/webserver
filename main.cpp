#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <fstream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "RequestHeaders.hpp"

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
	//std::fstream	file("log.txt");
	RequestHeaders	request;
	int				sock, listener;
	struct			sockaddr_in addr;
	char			buf[1024];
	char			ret[] = "HTTP/1.1 200 OK\r\nServer: webserver/n/r/r/nDate: Sat, 08 Mar 2014 22:53:46 GMT\r\nContent-Type: text/html\r\nContent-Length: 161\r\nLast-Modified: Sun, 21 Apr 2021 14:40:30 GMT\r\nConnection: keep-alive\r\n\r\n<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n<meta charset=\"UTF-8\">\n<title>ABOB</title>\n</head>\n<body>\n<a href=\"https://memepedia.ru/aboba/\">ABOBA</a>\n</body>\n</html>";
	int				bytes_read;

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
	//while(1)
	//
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
			request.getSource(buf);
			request.getInfo();
			//file << buf;
			if(bytes_read <= 0) break;
			send(sock, ret, bytes_read, 0);
		}

		close(sock);
	//}
	//file.close();
    return 0;
}
