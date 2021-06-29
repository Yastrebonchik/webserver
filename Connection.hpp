//
// Created by Karyn Cedra on 6/29/21.
//

#ifndef WEBSERVER_CONNECTION_HPP
#define WEBSERVER_CONNECTION_HPP

#include <unistd.h>
#include <stdlib.h>

class Connection {
private:
	int 	_connectionfd;
	char 	*_answer;
public:
	Connection();
	Connection(int listenfd, int connectionfd);
	~Connection();

	void 	setAnswer(char *answer);
	void 	clearAnswer();
	int 	getConnectionfd();
	char 	*getAnswer();
};


#endif //WEBSERVER_CONNECTION_HPP
