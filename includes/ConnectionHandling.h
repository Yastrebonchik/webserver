//
// Created by Karyn Cedra on 7/4/21.
//

#ifndef WEBSERVER_CONNECTIONHANDLING_H
# define WEBSERVER_CONNECTIONHANDLING_H

# define RECIEVE_SIZE 100000

# include "methods.h"
# include "ConnectionClass.hpp"

int		selectSet(fd_set *readfds, fd_set *writefds, std::vector<int> &listener,
					 std::vector<ConnectionClass> &connections);
void	makeConnection(int i, std::vector<ConnectionClass> &connections, std::vector<int> &listener);
void	recieveData(int i, std::vector<ConnectionClass> &connections, std::vector<ConfigClass*> config);
void	sendData(int i, std::vector<ConnectionClass> &connections);
void 	dropConnections(std::vector<ConnectionClass> &connections);

#endif //WEBSERVER_CONNECTIONHANDLING_H
