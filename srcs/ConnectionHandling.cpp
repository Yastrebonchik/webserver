//
// Created by Karyn Cedra on 7/4/21.
//

#include "ConnectionHandling.h"

int	selectSet(fd_set *readfds, fd_set *writefds, std::vector<int> &listener, std::vector<ConnectionClass> &connections) {
	int maxfd = 0;

	FD_ZERO(readfds);
	FD_ZERO(writefds);

	for (size_t i = 0; i < listener.size(); ++i) {
		if (listener[i] > maxfd)
			maxfd = listener[i];
		FD_SET(listener[i], readfds);
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

	sock = accept(listener[i], nullptr, nullptr);
	if (sock < 0) {
		perror("accept");
		exit(3);
	}
	fcntl(sock, F_SETFL, O_NONBLOCK);
	connections.push_back(ConnectionClass(sock, config[i]));
}

void	recieveData(int i, std::vector<ConnectionClass> &connections) {
	int 			bytes_read;
	char 			*source = (char *)malloc(1);
	char			buf[RECIEVE_SIZE];
	ResponseHeaders	resp;
	RequestHeaders	request;

	bytes_read = recv(connections[i].getConnectionfd(), buf, RECIEVE_SIZE - 1, 0);
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
		while (bytes_read > 0) {
			source = ft_strjoin(source, buf);
			ft_bzero(buf, RECIEVE_SIZE);
			bytes_read = recv(connections[i].getConnectionfd(), buf, RECIEVE_SIZE - 1, 0);
		}
		ft_bzero(buf, RECIEVE_SIZE);
		request.setSource(source);
		request.setInfo();
		connections[i].setAnswer(generateAnswer(request, connections[i].getServer()));
		connections[i].setCloseFlag(0);
		if (request.get_connection() == "close")
			connections[i].setCloseFlag(1);
		request.clear();
		connections[i].setSendFlag(1);
		free(source);
		source = nullptr;
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