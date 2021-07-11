//
// Created by Karyn Cedra on 6/29/21.
//

#include "ConnectionClass.hpp"

ConnectionClass::ConnectionClass() {
}

ConnectionClass::~ConnectionClass() {
}

ConnectionClass::ConnectionClass(int connectionfd, uint32_t listenIp, uint16_t listenPort) :
	_connectionfd(connectionfd), _listenIp(listenIp), _listenPort(listenPort), _closeFlag(0), _sendFlag(0), \
	_answer(nullptr) {
}

void 		ConnectionClass::setAnswer(void *answer) {
	if (this->_answer != nullptr)
		free(this->_answer);
	this->_answer = answer;
}

void 		ConnectionClass::setAnswerSize(size_t answer_size) {
	this->_answersize = answer_size;
}

void 		ConnectionClass::clearAnswer() {
	if (this->_answer != nullptr)
		free(this->_answer);
	this->_answer = nullptr;
}

void 		ConnectionClass::setCloseFlag(bool flag) {
	this->_closeFlag = flag;
}

void 		ConnectionClass::setSendFlag(bool flag) {
	this->_sendFlag = flag;
}

void 		ConnectionClass::setServer(ConfigClass server) {
	this->_server = server;
};

int 		ConnectionClass::getConnectionfd() {
	return (this->_connectionfd);
}

uint32_t	ConnectionClass::getListenIp() {
	return (this->_listenIp);
};

uint16_t	ConnectionClass::getListenPort() {
	return (this->_listenPort);
};

void* 		ConnectionClass::getAnswer() {
	return (this->_answer);
}

bool 		ConnectionClass::getCloseFlag() {
	return (this->_closeFlag);
}

bool 		ConnectionClass::getSendFlag() {
	return (this->_sendFlag);
}

ConfigClass	ConnectionClass::getServer() {
	return (this->_server);
};

size_t 		ConnectionClass::getAnswerSize() {
	return (this->_answersize);
}