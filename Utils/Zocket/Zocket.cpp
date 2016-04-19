/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "Zocket.h"

Zocket::Zocket(){
	context = new zmq::context_t(1);
	socket = new zmq::socket_t(*context, ZMQ_PAIR);
}

void Zocket::connectClient(){
	socket->connect("tcp://localhost:5555");
}

void Zocket::connectServer(){
    socket->bind("tcp://*:5555");
}

//	State
void Zocket::sendState(){
    state.SerializeToString(&msg_str);
   
    zmq::message_t request (msg_str.size());
    memcpy ((void *) request.data (), msg_str.c_str(), msg_str.size());
   	socket->send (request);
}

void Zocket::receiveState(){
	socket->recv(&request);
    std::string msg_str(static_cast<char*>(request.data()), request.size());
    state.ParseFromString(msg_str);
}

void Zocket::setState(sirlab::State state){
	this->state = state;
}

sirlab::State Zocket::getState(){
	return state;
}

void Zocket::showState(){
	string text_str;
	google::protobuf::TextFormat::PrintToString(state, &text_str);
	cout << text_str << endl;
}