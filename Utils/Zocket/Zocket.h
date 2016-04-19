/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

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