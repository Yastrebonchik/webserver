//
// Created by Karyn Cedra on 6/29/21.
//

#include "Connection.hpp"

Connection::Connection() {
}

Connection::~Connection() {
}

Connection::Connection(int listenfd, int connectionfd) : _connectionfd(connectionfd), _answer(NULL) {
}

void 	Connection::setAnswer(char *answer) {
	this->_answer = answer;
}

void 	Connection::clearAnswer() {
	free(this->_answer);
	this->_answer = NULL;
}

int 	Connection::getConnectionfd() {
	return (this->_connectionfd);
}

char* 	Connection::getAnswer() {
	return (this->_answer);
}