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
	int 						opt = 1;

	sock = accept(listener[i], nullptr, nullptr);
	if (sock < 0) {
		perror("accept");
		exit(3);
	}
	fcntl(sock, F_SETFL, O_NONBLOCK);
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	connections.push_back(ConnectionClass(sock, config[i]));
}

void	recieveData(int i, std::vector<ConnectionClass> &connections) {
	int 			bytes_read;
	static char 	*source = nullptr;
	char 			*line;
	char			buf[RECIEVE_SIZE];
	ResponseHeaders	resp;
	RequestHeaders	request;

	ft_bzero(buf, RECIEVE_SIZE);
	bytes_read = recv(connections[i].getConnectionfd(), buf, RECIEVE_SIZE - 1, 0);
	if (bytes_read == -1) {
		close(connections[i].getConnectionfd()); // Удаляем соединение, закрываем сокет
		connections[i].clearAnswer();
		connections.erase(connections.begin() + i);
	}
	else if (bytes_read == 0) {
		close(connections[i].getConnectionfd()); // Удаляем соединение, закрываем сокет
		connections[i].clearAnswer();
		connections.erase(connections.begin() + i);
	}
	else if (bytes_read > 0) {
		if (bytes_read == RECIEVE_SIZE - 1) {
			buf[bytes_read] = '\0';
			line = source;
			if (source != nullptr) {
				free(source);
			}
			source = ft_strjoin(line, buf);
			free(line);
		}
		else {
			buf[bytes_read] = '\0';
			line = source;
			if (source != nullptr) {
				free(source);
			}
			source = ft_strjoin(line, buf);
			free(line);
			request.setSource(source);
			request.setInfo();
			if (!connections[i].getSendFlag())
				connections[i].setAnswer(generateAnswer(request, connections[i].getServer()));
			connections[i].setCloseFlag(0);
			if (request.get_connection() == "close")
				connections[i].setCloseFlag(1);
			request.clear();
			connections[i].setSendFlag(1);
			delete(source);
			source = nullptr;
		}
	}
}

void	sendData(int i, std::vector<ConnectionClass> &connections) {

	if (connections[i].getSendFlag()) {
		connections[i].setSendFlag(0);
		if (connections[i].getAnswer() != nullptr) {
			std::cout << connections[i].getAnswer() << std::endl;
			std::cout << "------------------------" << std::endl;
		}
		if (connections[i].getAnswer() != nullptr && send(connections[i].getConnectionfd(), connections[i].getAnswer(),
				 ft_strlen(connections[i].getAnswer()), 0) < 0) {
			std::cerr << "Error while sending data" << std::endl;
		}
	}
	if (connections.size() > 0 && connections[i].getCloseFlag()) {
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