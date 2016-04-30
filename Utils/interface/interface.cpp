#include "interface.h"

Interface::Interface(){

}

/*void Interface::createLoopSendState(vss_state::Global_State *global_state){
	this->global_state = global_state;	// assim não há a necessidade de atualizar "setAlgo" o dado toda hora

	zmq::context_t context (1);
	zmq::socket_t socket (context, ZMQ_PUB);

	std::cout << "Connecting to hello world server…" << std::endl;
	socket.bind("tcp://*:5555");

	while (true) {
		usleep (100000);

		std::string msg_str;
	    global_state.SerializeToString(&msg_str);

	    zmq::message_t request (msg_str.size());
	    memcpy ((void *) request.data (), msg_str.c_str(), msg_str.size());
	    std::cout << "Sending Person data ..." << std::endl;
	    socket.send (request);
	}
}

void Interface::createLoopReceiveState(vss_state::Global_State *global_state){
	this->global_state = global_state;	// assim não há a necessidade de atualizar "setAlgo" o dado toda hora
	
	zmq::context_t context(1);
	const char * protocol =
	"tcp://localhost:5555";
	//  Socket to talk to server
	printf ("Connecting to hello world server...");
	zmq::socket_t socket (context, ZMQ_SUB);
	//  sock.bind("epgm://eth0;239.192.1.1:5556");
	socket.connect(protocol);
	socket.setsockopt (ZMQ_SUBSCRIBE, "", 0);
	printf ("done. \n");

	int request_nbr;
	while(true){
		zmq::message_t request;
        socket.recv (&request, 0); //  Wait for next request from client
        std::cout << "Received" << std::endl;
        vss_state::Global_State global_state;
        std::string msg_str(static_cast<char*>(request.data()), request.size());
        global_state.ParseFromString(msg_str);
        std::string text_str;
        google::protobuf::TextFormat::PrintToString(global_state, &text_str);
        std::cout << text_str << std::endl;
	}
	socket.close();
}

void Interface::createLoopSendCommands(vss_state::Global_Commands*){

}

void Interface::createLoopReceiveCommands(vss_state::Global_Commands*){

}*/