#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <ctime>
#include <sys/select.h>
#include <vector>
#include "ConnectionClass.hpp"
#include "ConnectionHandling.h"

# define CONNECTION_DROP_TIME 5

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

//	signal(SIGINT, sigint);
//	signal(SIGQUIT, sigquit);
//	signal(SIGTERM, sigterm);
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
