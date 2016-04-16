#ifndef _Zocket_H_
#define _Zocket_H_

#include <iostream>
#include <string>
#include "zmq.hpp"
#include <google/protobuf/text_format.h>
#include "Protos/sirlab.pb.h"

using namespace std;

class Zocket{
private:
	zmq::message_t request;
	zmq::context_t *context;
    zmq::socket_t *socket;
	sirlab::State state;
    string msg_str;

public:
	Zocket();

	void connectClient();
	void connectServer();

	void sendState();
	void receiveState();
	void setState(sirlab::State);
	sirlab::State getState();
	void showState();

};

#endif