#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <ctime>
#include <sys/select.h>
#include <vector>
#include "ConnectionClass.hpp"
#include "ConnectionHandling.h"

# define CONNECTION_DROP_TIME 2

std::vector<ConnectionClass>	connections;
std::vector<int> 				listener;

void	sigint(int) {
	for (std::vector<int>::iterator it = listener.begin(); it != listener.end(); ++it) {
		close(*it);
	}
	dropConnections(connections);
}

void	sigTerm(int) {
	for (std::vector<int>::iterator it = listener.begin(); it != listener.end(); ++it) {
		close(*it);
	}
	dropConnections(connections);
}

bool	checkPort(std::vector<uint16_t> ports, uint16_t port) {
	for (size_t i = 0; i < ports.size(); ++i) {
		if (port == ports[i])
			return (1);
	}
	return (0);
}

int main(int argc, char **argv) {
	std::vector<ConfigClass*>		config;
	std::vector<uint16_t>			ports;
	ConfigClass						*server;
	std::string 					line;
	fd_set 							readfds;
	fd_set							writefds;
	size_t 							i = 0;
	struct							sockaddr_in addr;
	struct 							timeval timeout;
	int 							maxfd;
	int 							selectRes;
	int								opt = 1;

	signal(SIGINT, sigint);
	signal(SIGTERM, sigTerm);
	if (argc != 2) {
		std::cerr << "Invalid number of arguments" << std::endl;
		exit(1);
	}
	if (config_parser(argv[1], config) != 0) {
		exit(1);
	}
	std::cout << "Webserver start" << std::endl;
	timeout.tv_sec = CONNECTION_DROP_TIME;
	timeout.tv_usec = 0;
	for (std::vector<ConfigClass*>::iterator it = config.begin(); it != config.end(); ++it) {
		listener.push_back(socket(AF_INET, SOCK_STREAM, 0));
		if(listener[i] < 0) {
			std::cerr << "Socket creating error" << std::endl;
			exit(1);
		}
		server = *it;
		addr.sin_family = AF_INET;
		addr.sin_port = server->getPort();
		addr.sin_addr.s_addr = server->getIp();
		if (checkPort(ports, server->getPort())) {
			close(listener[i]);
			listener.pop_back();
		}
		else {
			if (bind(listener[i], (struct sockaddr *) &addr, sizeof(addr)) < 0) {
				std::cerr << "Bind error" << std::endl;
				exit(1);
			}
			listen(listener[i], SOMAXCONN);
			setsockopt(listener[i], SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
			fcntl(listener[i], F_SETFL, O_NONBLOCK);
			ports.push_back(server->getPort());
			i++;
		}
	}

	while(1) {
		maxfd = selectSet(&readfds, &writefds, listener, connections);
		if ((selectRes = select(maxfd + 1, &readfds, &writefds, NULL, &timeout)) > 0) {
			i = 0;
			while (i < connections.size()) {
				if (FD_ISSET(connections[i].getConnectionfd(), &readfds))
					recieveData(i, connections, config);
				if (FD_ISSET(connections[i].getConnectionfd(), &writefds))
					sendData(i, connections);
				i++;
			}
			i = 0;
			while (i < listener.size()) {
				if (FD_ISSET(listener[i], &readfds))
					makeConnection(i, connections, listener);
				i++;
			}
			timeout.tv_sec = CONNECTION_DROP_TIME;
			timeout.tv_usec = 0;
		}
		else if (selectRes == 0) {
			timeout.tv_sec = CONNECTION_DROP_TIME;
			timeout.tv_usec = 0;
			dropConnections(connections);
			continue;
		}
		else {
			std::cerr << "Select error" << std::endl;
			exit(1);
		}
	}
}
