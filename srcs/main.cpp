#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <ctime>
#include <sys/select.h>
#include <vector>
#include "ConnectionClass.hpp"
#include "ConnectionHandling.h"

# define CONNECTION_DROP_TIME 5

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

	config_parser((char*)"configs/tester_config", config);
	timeout.tv_sec = CONNECTION_DROP_TIME;
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
		setsockopt(listener[i], SOL_SOCKET, SO_REUSEADDR, &listener.back(), sizeof(int));
		fcntl(listener[i], F_SETFL, O_NONBLOCK);
		i++;
	}

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
			perror("select");
			exit(errno);
		}
	}
}
