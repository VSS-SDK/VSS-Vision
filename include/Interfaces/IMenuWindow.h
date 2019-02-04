/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef I_MENU_WINDOW_H_
#define I_MENU_WINDOW_H_

#include "gtkmm.h"

class IMenuWindow {
public:
    virtual int run(int argc, char *argv[]) = 0;

    virtual bool onKeyboard(GdkEventKey*, Gtk::Window*) = 0;

    virtual void onButtonVision() = 0;
    virtual void onButtonCalibration() = 0;
};
#endif