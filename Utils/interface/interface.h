#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include <sstream>
#include <iostream>
#include <string>
#include "unistd.h"

#include "zmq.hpp"
#include <google/protobuf/text_format.h>
#include "protos/state.pb.h"
#include "protos/command.pb.h"

class Interface{
private:
	vss_state::Global_State *global_state;
	vss_command::Global_Commands *global_commands;
	
public:
	Interface();

	/*void createLoopSendState(vss_state::Global_State*);
	void createLoopReceiveState(vss_state::Global_State*);
	void createLoopSendCommands(vss_state::Global_Commands*);
	void createLoopReceiveCommands(vss_state::Global_Commands*);*/	
};

#endif // _INTERFACE_H_