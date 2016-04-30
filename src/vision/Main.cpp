/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "GUI.h"
		
int main(int, char**){
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	GUI gui;
	gui.init();

    return 0;
}
