//
// Created by Karyn Cedra on 6/29/21.
//

#ifndef WEBSERVER_CONNECTIONCLASS_HPP
# define WEBSERVER_CONNECTIONCLASS_HPP

# include <unistd.h>
# include <stdlib.h>
# include "config_parser.hpp"

class ConnectionClass {
private:
	int 			_connectionfd;
	bool 			_closeFlag;
	bool 			_sendFlag;
	char 			*_answer;
	ConfigClass		_server;

public:
	ConnectionClass();
	ConnectionClass(int connectionfd, ConfigClass server);
	~ConnectionClass();

	void 		setAnswer(char *answer);
	void 		clearAnswer();
	void 		setCloseFlag(bool flag);
	void 		setSendFlag(bool flag);
//	void 		setAddr(sockaddr addr);
	int 		getConnectionfd();
	char 		*getAnswer();
	bool 		getCloseFlag();
	bool 		getSendFlag();
	ConfigClass	getServer();
//	sockaddr	getAddr();
};


#endif //WEBSERVER_CONNECTIONCLASS_HPP
