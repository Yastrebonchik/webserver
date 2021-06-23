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
#include <vector>

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

std::vector<int> 			listener;
int							sock;

void	sigquit(int sig)
{
	std::cout << "\b\b\033SIGQUIT\033[0m" << std::endl;
	for (std::vector<int>::iterator it = listener.begin(); it != listener.end(); ++it) {
		close(*it);
	}
	close(sock);
	exit(0);
}

void	sigint(int sig)
{
	std::cout << "\b\b\033[31mSIGINT\033[0m" << std::endl;
	for (std::vector<int>::iterator it = listener.begin(); it != listener.end(); ++it) {
		close(*it);
	}
	close(sock);
	exit(0);
}

void	sigterm(int sig)
{
	std::cout << "\b\b\033[31mSIGTERM\033[0m" << std::endl;
	for (std::vector<int>::iterator it = listener.begin(); it != listener.end(); ++it) {
		close(*it);
	}
	close(sock);
	exit(0);
}

int main() {
	RequestHeaders				request;
	std::vector<ConfigClass>	config;
	ConfigClass					server;
	std::string 				line;
	fd_set 						readfds;
	fd_set						writefds;
	int 						maxfd = 0;
	int 						selectres;
	int 						i = 0;
	struct						sockaddr_in addr;
	struct 						timeval timeout;
	char						buf[1024];
	char 						*ret;
	int							bytes_read;

	ret = NULL;
	signal(SIGINT, sigint);
	signal(SIGQUIT, sigquit);
	signal(SIGTERM, sigterm);
	config_parser((char*)"config_parser_v.0.1/config/config_file", config);
	timeout.tv_sec = 5;
	timeout.tv_usec = 0;
	FD_ZERO(&readfds);
	FD_ZERO(&writefds);
	for (std::vector<ConfigClass>::iterator it = config.begin(); it != config.end(); ++it) {
		listener.push_back(socket(AF_INET, SOCK_STREAM, 0));
		if (listener[i] > maxfd)
			maxfd = listener[i];
		if(listener[i] < 0) {
			perror("socket");
			exit(1);
		}
		server = *it;
		addr.sin_family = AF_INET;
		addr.sin_port = server.getPort();
		addr.sin_addr.s_addr = server.getIp();
		if(bind(listener[i], (struct sockaddr *)&addr, sizeof(addr)) < 0) {
			perror("bind");
			exit(2);
		}
		fcntl(listener[i], F_SETFL, O_NONBLOCK);
		listen(listener[i], 1);
		FD_SET(listener[i], &readfds);
		FD_SET(listener[i], &writefds);
		i++;
	}

	i = 0;
	while(1) {
		if (select(maxfd + 1, &readfds, &writefds, NULL, &timeout) > 0) {
			while (FD_ISSET(listener[i], &readfds) == false)
				i++;
			sock = accept(listener[i], NULL, NULL);
			std::cout << "I'm here" << std::endl;
			if (sock < 0) {
				perror("accept");
				exit(3);
			}

			while (1) {
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
			//if (request.get_connection() == "close")
			close(sock);
			i = 0;
		}
		else {
			continue;
		}
	}
    return 0;
}
