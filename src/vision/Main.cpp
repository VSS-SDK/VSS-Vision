/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "GUI.h"

#include "thread"

int main(int, char**){
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	/*Interface interface;
	vss_state::Global_State global_state;

	global_state.set_id(0);

	for(int i = 0 ; i < 3 ; i++){
		vss_state::Robot_State *robot = global_state.add_robots_yellow();
		robot->set_x(0);
		robot->set_y(0);
		robot->set_yaw(0);
	}

	for(int i = 0 ; i < 3 ; i++){
		vss_state::Robot_State *robot = global_state.add_robots_blue();
		robot->set_x(0);
		robot->set_y(0);
		robot->set_yaw(0);
	}


	interface.createLoopSendState(&global_state);*/


	GUI gui;
	gui.init();

    return 0;
}
