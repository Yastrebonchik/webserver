//
// Created by Karyn Cedra on 6/29/21.
//

#include "../includes/ConnectionClass.hpp"

ConnectionClass::ConnectionClass() {
}

ConnectionClass::~ConnectionClass() {
}

ConnectionClass::ConnectionClass(int connectionfd, ConfigClass server) : _connectionfd(connectionfd), _closeFlag(0), \
	_sendFlag(0), _answer(NULL), _server(server) {
}

void 		ConnectionClass::setAnswer(char *answer) {
	//if (this->_answer != nullptr)
		//free(this->_answer);
	this->_answer = answer;
}

void 		ConnectionClass::clearAnswer() {
	//if (this->_answer != nullptr)
		//free(this->_answer);
	this->_answer = nullptr;
}

void 		ConnectionClass::setCloseFlag(bool flag) {
	this->_closeFlag = flag;
}

void 		ConnectionClass::setSendFlag(bool flag) {
	this->_sendFlag = flag;
}

//void 		ConnectionClass::setAddr(sockaddr addr) {
//	this->_addr = addr;
//}

int 		ConnectionClass::getConnectionfd() {
	return (this->_connectionfd);
}

char* 		ConnectionClass::getAnswer() {
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

//sockaddr	ConnectionClass::getAddr() {
//	return (this->_addr);
//}