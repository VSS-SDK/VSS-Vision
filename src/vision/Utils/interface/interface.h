/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

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
	zmq::message_t request;
	zmq::context_t *context;
    zmq::socket_t *socket;
    
	vss_state::Global_State *global_state;
	vss_command::Global_Commands *global_commands;

	
	// Simulator and VSS -> Strategys
	const char *addr_server_multicast = "tcp://*:5555";
	const char *addr_client_multicast = "tcp://localhost:5555";

	// Strategy Yellow -> Simulator
	const char *addr_server_simulator_yellow = "tcp://*:5556";
	const char *addr_client_simulator_yellow = "tcp://localhost:5556";

	// Strategy Blue -> Simulator
	const char *addr_server_simulator_blue = "tcp://*:5557";
	const char *addr_client_simulator_blue = "tcp://localhost:5557";
public:
	Interface();

	void createSocketSendState(vss_state::Global_State*);
	void sendState();
	void createSocketReceiveState(vss_state::Global_State*);
	void receiveState();

	void createLoopSendCommandsYellow(vss_command::Global_Commands*);
	void createLoopReceiveCommandsYellow(vss_command::Global_Commands*);

	void createLoopSendCommandsBlue(vss_command::Global_Commands*);
	void createLoopReceiveCommandsBlue(vss_command::Global_Commands*);	
	
	void printState();
	void printCommand();
};

#endif // _INTERFACE_H_