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
#include "Connection.hpp"

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
std::vector<int>			connection;
int							sock;

//void	sigquit(int sig)
//{
//	std::cout << "\b\b\033SIGQUIT\033[0m" << std::endl;
//	for (std::vector<int>::iterator it = listener.begin(); it != listener.end(); ++it) {
//		close(*it);
//	}
//	close(sock);
//	exit(sig);
//}
//
//void	sigint(int sig)
//{
//	std::cout << "\b\b\033[31mSIGINT\033[0m" << std::endl;
//	for (std::vector<int>::iterator it = listener.begin(); it != listener.end(); ++it) {
//		close(*it);
//	}
//	close(sock);
//	exit(sig);
//}
//
//void	sigterm(int sig)
//{
//	std::cout << "\b\b\033[31mSIGTERM\033[0m" << std::endl;
//	for (std::vector<int>::iterator it = listener.begin(); it != listener.end(); ++it) {
//		std::cout << "Inside SIGTERM" << std::endl;
//		close(*it);
//	}
//	close(sock);
//	usleep(1000);
//	exit(sig);
//}

int	selectSet(fd_set *readfds, fd_set *writefds) {
	int maxfd;

	FD_ZERO(readfds);
	FD_ZERO(writefds);

	for (size_t i = 0; i < listener.size(); ++i) {
		if (listener[i] > maxfd)
			maxfd = listener[i];
		FD_SET(listener[i], readfds);
		FD_SET(listener[i], writefds);
	}
	for (size_t i = 0; i < connection.size(); ++i) {
		if (connection[i] > maxfd)
			maxfd = connection[i];
		FD_SET(connection[i], readfds);
		FD_SET(connection[i], writefds);
	}
	return (maxfd);
}

void	makeConnection(int i, char *buf, std::vector<Connection> &c, std::vector<ConfigClass> &config) {
	int 			bytes_read;
	ResponseHeaders	resp;
	RequestHeaders	request;
	ConfigClass		server;

	sock = accept(listener[i], NULL, NULL);
	if (sock < 0) {
		perror("accept");
		exit(3);
	}
	fcntl(sock, F_SETFL, O_NONBLOCK);

	bytes_read = recv(sock, buf, 100000 - 1, 0);
	if (bytes_read == 0) {
		close(sock);
	}
	else if (bytes_read < -1) {
		perror("recv");
		exit(3);
	}
	else {
		connection.push_back(sock);
		request.setSource(buf);
		request.setInfo();
		ft_bzero(buf, 100000);
		resp = generateAnswer(request, server);
	}
}

void	recieveData() {

}

void	sendData() {

}

void 	dropConnections() {

}

int main() {
	int 							check = 0;
	RequestHeaders					request;
	std::vector<ResponseHeaders>	response;
	std::vector<ConfigClass>		config;
	ConfigClass						server;
	std::string 					line;
	fd_set 							readfds;
	fd_set							writefds;
	int 							maxfd = 0;
	size_t 							i = 0;
	struct							sockaddr_in addr;
	struct 							timeval timeout;
	char							buf[100000];
	char 							*ret;
	int								bytes_read;

	ret = NULL;
//	signal(SIGINT, sigint);
//	signal(SIGQUIT, sigquit);
//	signal(SIGTERM, sigterm);
	config_parser((char*)"config_parser_v.0.1/config/config_file", config);
	timeout.tv_sec = 5;
	timeout.tv_usec = 0;
	for (std::vector<ConfigClass>::iterator it = config.begin(); it != config.end(); ++it) {
		listener.push_back(socket(AF_INET, SOCK_STREAM, 0));
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
		listen(listener[i], SOMAXCONN);
		fcntl(listener[i], F_SETFL, O_NONBLOCK);
		i++;
	}

	i = 0;
	while(1) {
		maxfd = selectSet(&readfds, &writefds);
		if (select(maxfd + 1, &readfds, &writefds, NULL, &timeout) > 0) {
			i = 0;
			while (i < listener.size()) {
				if (FD_ISSET(listener[i], &readfds))
					makeConnection(i, buf, response);
				i++;
			}
			i = 0;
			while (i < connection.size()) {
				if (FD_ISSET(connection[i], &readfds))
					recieveData();
				if (FD_ISSET(connection[i], &writefds))
					sendData();
				i++;
			}
			//sock = accept(listener[i], NULL, NULL);
			//int opt = 1;
			//setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)); // Возможно придется убрать (позволяет избежать попаболи с bind)
			//FD_SET(sock, &readfds);
			//FD_SET()
			//fcntl(listener[i], F_SETFL, O_NONBLOCK);
			server = config[i];
			//std::cout << "I'm here" << std::endl;
			if (sock < 0) {
				perror("accept");
				exit(3);
			}

			while (1) {
				check++;

				bytes_read = recv(sock, buf, 100000 - 1, 0);
				if (bytes_read < 1) {
					std::cout << check << std::endl;
					close(sock);
					break;
				}
				request.setSource(buf);
				request.setInfo();
				ft_bzero(buf, 100000);
				ret = generateAnswer(request, server);
				if (send(sock, ret, ft_strlen(ret) + 1, 0) < 0)
					std::cout << "Error number = " << errno << std::endl;
				free(ret);
				ret = NULL;
				request.clear();
				//close(sock);
			//if (request.get_connection() == "close")
			}
			//close(sock);
		}
		else {
			dropConnections();
			continue; //Нужно добавлять sock в перечень читаемых fd и удалять его при истечении времени (FD_CLR и close)
		}
	}
    return 0;
}
