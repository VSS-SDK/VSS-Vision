/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "interface.h"

Interface::Interface(){
}

void Interface::createSocketSendState(vss_state::Global_State *global_state){
	this->global_state = global_state;

	context = new zmq::context_t(1);
	socket = new zmq::socket_t(*context, ZMQ_PUB);

	std::cout << "Connecting Server Multicast Sender: " << addr_server_multicast << std::endl;
	socket->bind(addr_server_multicast);

	/*while (true) {
		usleep (100000);

		std::string msg_str;
	    global_state->SerializeToString(&msg_str);

	    zmq::message_t request (msg_str.size());
	    memcpy ((void *) request.data (), msg_str.c_str(), msg_str.size());
	    std::cout << "Sending State data ..." << std::endl;
	    socket.send(request);
	}*/
}

void Interface::sendState(){
	std::string msg_str;
    global_state->SerializeToString(&msg_str);

    zmq::message_t request (msg_str.size());
    memcpy ((void *) request.data (), msg_str.c_str(), msg_str.size());
    std::cout << "Sending State data ..." << std::endl;
    socket->send(request);
}

void Interface::createSocketReceiveState(vss_state::Global_State *global_state){
	this->global_state = global_state;
	
	context = new zmq::context_t(1);
	socket = new zmq::socket_t(*context, ZMQ_SUB);

	std::cout << "Connecting Client Multicast Receiver: " << addr_client_multicast << std::endl;
	socket->connect(addr_client_multicast);

	socket->setsockopt(ZMQ_SUBSCRIBE, "", 0);

	/*int request_nbr;
	while(true){
		zmq::message_t request;
        socket.recv (&request, 0); //  Wait for next request from client
        std::cout << "Received" << std::endl;
        std::string msg_str(static_cast<char*>(request.data()), request.size());
        global_state->ParseFromString(msg_str);
        printState();
	}
	socket.close();*/
}

void Interface::receiveState(){
	zmq::message_t request;
	socket->recv(&request, 0); //  Wait for next request from client
	std::cout << "Received" << std::endl;
	std::string msg_str(static_cast<char*>(request.data()), request.size());
	global_state->ParseFromString(msg_str);
	printState();
}

void Interface::createLoopSendCommandsTeam1(vss_command::Global_Commands* global_commands){
	this->global_commands = global_commands;
	
	zmq::context_t context(1);
	zmq::socket_t socket (context, ZMQ_PAIR);

	std::cout << "Connecting Client Sender Team 1: " << addr_client_simulator_team1 << std::endl;
	socket.connect(addr_client_simulator_team1);

	while (true) {
		usleep (100000);

		std::string msg_str;
	    global_commands->SerializeToString(&msg_str);

	    zmq::message_t request (msg_str.size());
	    memcpy ((void *) request.data (), msg_str.c_str(), msg_str.size());
	    std::cout << "Sending State data ..." << std::endl;
	    socket.send(request);
	}
}

void Interface::createLoopSendCommandsTeam2(vss_command::Global_Commands* global_commands){
	this->global_commands = global_commands;
	
	zmq::context_t context(1);
	zmq::socket_t socket (context, ZMQ_PAIR);

	std::cout << "Connecting Client Sender Team 2: " << addr_client_simulator_team2 << std::endl;
	socket.connect(addr_client_simulator_team2);

	while (true) {
		usleep (100000);

		std::string msg_str;
	    global_commands->SerializeToString(&msg_str);

	    zmq::message_t request (msg_str.size());
	    memcpy ((void *) request.data (), msg_str.c_str(), msg_str.size());
	    std::cout << "Sending State data ..." << std::endl;
	    socket.send(request);
	}
}

void Interface::createLoopReceiveCommandsTeam1(vss_command::Global_Commands* global_commands){
	this->global_commands = global_commands;

	zmq::context_t context (1);
	zmq::socket_t socket (context, ZMQ_PAIR);

	std::cout << "Connecting Server Receiver Team 1: " << addr_server_simulator_team1 << std::endl;
	socket.bind(addr_server_simulator_team1);


	int request_nbr;
	while(true){
		zmq::message_t request;
        socket.recv(&request);
        std::cout << "Received" << std::endl;
        std::string msg_str(static_cast<char*>(request.data()), request.size());
        global_commands->ParseFromString(msg_str);
        printCommand();
	}
	socket.close();
}

void Interface::createLoopReceiveCommandsTeam2(vss_command::Global_Commands* global_commands){
	this->global_commands = global_commands;

	zmq::context_t context (1);
	zmq::socket_t socket (context, ZMQ_PAIR);

	std::cout << "Connecting Server Receiver Team 2: " << addr_server_simulator_team2 << std::endl;
	socket.bind(addr_server_simulator_team2);


	int request_nbr;
	while(true){
		zmq::message_t request;
        socket.recv(&request);
        std::cout << "Received" << std::endl;
        std::string msg_str(static_cast<char*>(request.data()), request.size());
        global_commands->ParseFromString(msg_str);
        printCommand();
	}
	socket.close();
}

void Interface::printState(){
	std::string text_str;
    google::protobuf::TextFormat::PrintToString(*global_state, &text_str);
    std::cout << text_str << std::endl;
}

void Interface::printCommand(){
	std::string text_str;
    google::protobuf::TextFormat::PrintToString(*global_commands, &text_str);
    std::cout << text_str << std::endl;
}