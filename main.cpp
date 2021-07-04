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
#include "ConnectionClass.hpp"

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

int	selectSet(fd_set *readfds, fd_set *writefds, std::vector<int> &listener, std::vector<ConnectionClass> &connections) {
	int maxfd = 0;

	FD_ZERO(readfds);
	FD_ZERO(writefds);

	for (size_t i = 0; i < listener.size(); ++i) {
		if (listener[i] > maxfd)
			maxfd = listener[i];
		FD_SET(listener[i], readfds);
		//FD_SET(listener[i], writefds);
	}
	for (size_t i = 0; i < connections.size(); ++i) {
		if (connections[i].getConnectionfd() > maxfd)
			maxfd = connections[i].getConnectionfd();
		FD_SET(connections[i].getConnectionfd(), readfds);
		if (connections[i].getSendFlag())
			FD_SET(connections[i].getConnectionfd(), writefds);
	}
	return (maxfd);
}

void	makeConnection(int i, std::vector<ConnectionClass> &connections, std::vector<ConfigClass> &config,
		std::vector<int> &listener) {
	int 						sock;
//	size_t 						j = 0;
//	struct sockaddr				address;
//	socklen_t 					address_len;

	sock = accept(listener[i], nullptr, nullptr);
//	sock = accept(listener[i], &address, &address_len);
//	if (connections[i].getAddr() == address)
	//std::cout << address.sa_data << std::endl;
//	while (j < config.size()) {
//		j++;
//	}
	if (sock < 0) {
		perror("accept");
		exit(3);
	}
	fcntl(sock, F_SETFL, O_NONBLOCK);
	connections.push_back(ConnectionClass(sock, config[i]));
}

void	recieveData(int i, std::vector<ConnectionClass> &connections) {
	int 			bytes_read;
	//char 			*source = (char *)malloc(1);
	char			buf[100000];
	ResponseHeaders	resp;
	RequestHeaders	request;

	bytes_read = recv(connections[i].getConnectionfd(), buf, 100000 - 1, 0);
	if (bytes_read == -1) {
		perror("recv");
		exit(3);
	}
	else if (bytes_read == 0) {
		close(connections[i].getConnectionfd()); // Удаляем соединение, закрываем сокет
		connections[i].clearAnswer();
		connections.erase(connections.begin() + i);
	}
	else if (bytes_read > 0) {
	//	while (bytes_read > 0) {
		//	source = ft_strjoin(source, buf);
		//	bytes_read = recv(connections[i].getConnectionfd(), buf, 100000 - 1, 0);
		//}
		request.setSource(buf);
		request.setInfo();
		ft_bzero(buf, 100000);
		connections[i].setAnswer(generateAnswer(request, connections[i].getServer()));
		connections[i].setCloseFlag(0);
		if (request.get_connection() == "close")
			connections[i].setCloseFlag(1);
		request.clear();
		connections[i].setSendFlag(1);
		//free(source);
		//source = nullptr;
	}
}

void	sendData(int i, std::vector<ConnectionClass> &connections) {

	if (connections[i].getSendFlag()) {
		connections[i].setSendFlag(0);
		if (send(connections[i].getConnectionfd(), connections[i].getAnswer(),
			 ft_strlen(connections[i].getAnswer()) + 1, 0) < 0) {
			std::cerr << "Error while sending data" << std::endl;
		}
	}
	if (connections[i].getCloseFlag()) {
		close(connections[i].getConnectionfd()); // Удаляем соединение, закрываем сокет
		connections[i].clearAnswer();
		connections.erase(connections.begin() + i);
	}
}

void 	dropConnections(std::vector<ConnectionClass> &connections) {
	for (size_t i = 0; i < connections.size(); ++i) {
		close(connections[i].getConnectionfd()); // Удаляем соединение, закрываем сокет
		connections[i].clearAnswer();
		connections.erase(connections.begin() + i);
	}
}

int main() {
	std::vector<ConnectionClass>	connections;
	std::vector<ConfigClass>		config;
	std::vector<int> 				listener;
	ConfigClass						server;
	std::string 					line;
	fd_set 							readfds;
	fd_set							writefds;
	size_t 							i = 0;
	struct							sockaddr_in addr;
	struct 							timeval timeout;
	int 							maxfd;
	int 							selectRes;

	//ret = NULL;
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
		maxfd = selectSet(&readfds, &writefds, listener, connections);
		if ((selectRes = select(maxfd + 1, &readfds, &writefds, NULL, &timeout)) > 0) {
			i = 0;
			while (i < connections.size()) {
				if (FD_ISSET(connections[i].getConnectionfd(), &readfds))
					recieveData(i, connections);
				if (FD_ISSET(connections[i].getConnectionfd(), &writefds))
					sendData(i, connections);
				i++;
			}
			i = 0;
			while (i < listener.size()) {
				if (FD_ISSET(listener[i], &readfds))
					makeConnection(i, connections, config, listener);
				i++;
			}
		}
		else if (selectRes == 0) {
			dropConnections(connections);
			continue; //Нужно добавлять sock в перечень читаемых fd и удалять его при истечении времени (FD_CLR и close)
		}
		else {
			perror("select");
			exit(errno);
		}
	}
    //return 0;
}
