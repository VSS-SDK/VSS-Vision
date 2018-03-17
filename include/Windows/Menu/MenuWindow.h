/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef MENU_WINDOW_H_
#define MENU_WINDOW_H_

#include <gtkmm.h>
#include <iostream>
#include <thread>
#include "IMenuWindow.h"

using namespace std;

class MenuWindow : public IMenuWindow {
public:
    MenuWindow();
    virtual ~MenuWindow();

    void run(int argc, char *argv[]) override;

    bool onKeyboard(GdkEventKey*, Gtk::Window*) override;

    void onButtonVision() override;
    void onButtonCalibration() override;

private:
	// Threads
    std::thread *threadWindowControl;

	// GTKMM - Calibration Window
		Gtk::Window* window = nullptr;

		Gtk::Button* buttonVision = nullptr;
		Gtk::Button* buttonCalibration = nullptr;

	// Control method
	void initializeWidget();
	void setSignals();
	void builderWidget();

    void windowThreadWrapper();
};
#endif
