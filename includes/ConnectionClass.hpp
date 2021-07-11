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
	uint32_t		_listenIp;
	uint16_t		_listenPort;
	bool 			_closeFlag;
	bool 			_sendFlag;
	void 			*_answer;
	size_t 			_answersize;
	ConfigClass		_server;

public:
	ConnectionClass();
	ConnectionClass(int connectionfd, uint32_t listenIp, uint16_t listenPort);
	~ConnectionClass();

	void 		setAnswer(void *answer);
	void 		setAnswerSize(size_t answer_size);
	void 		clearAnswer();
	void 		setCloseFlag(bool flag);
	void 		setSendFlag(bool flag);
	void 		setServer(ConfigClass server);
	int 		getConnectionfd();
	uint32_t	getListenIp();
	uint16_t	getListenPort();
	void 		*getAnswer();
	bool 		getCloseFlag();
	bool 		getSendFlag();
	size_t 		getAnswerSize();
	ConfigClass	getServer();
};


#endif //WEBSERVER_CONNECTIONCLASS_HPP
