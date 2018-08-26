/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef I_VISION_WINDOW_H_
#define I_VISION_WINDOW_H_

#include "gtkmm.h"
#include "Domain/Robot.h"
#include "Domain/Ball.h"

class IVisionWindow {
public:
    virtual int run(int argc, char *argv[]) = 0;

    virtual bool onKeyboard(GdkEventKey*, Gtk::Window*) = 0;

    virtual void onButtonPlay(Gtk::ToggleButton *) = 0;
    virtual void onButtonLoad(Gtk::FileChooserDialog*) = 0;
	virtual void onButtonOpenLoadDialog(Gtk::FileChooserDialog*) = 0;

    virtual void onRadioButtonImage(Gtk::RadioButton*) = 0;
    virtual void onRadioButtonVideo(Gtk::RadioButton*) = 0;
    virtual void onRadioButtonCamera(Gtk::RadioButton*) = 0;

    virtual void onComboBoxSelectPath(Gtk::ComboBox*) = 0;
    virtual void onComboBoxSelectColorTeam(Gtk::ComboBox *) = 0;
	virtual void onComboBoxSelectColorOpponent(Gtk::ComboBox *) = 0;
    virtual void onComboBoxSelectColorPattern1(Gtk::ComboBox*) = 0;
    virtual void onComboBoxSelectColorPattern2(Gtk::ComboBox*) = 0;
    virtual void onComboBoxSelectColorPattern3(Gtk::ComboBox*) = 0;
    virtual void onComboBoxSelectColorPattern4(Gtk::ComboBox*) = 0;
    virtual void onComboBoxSelectColorPattern5(Gtk::ComboBox*) = 0;

    virtual void onRobotsNewPositions(std::vector<vss::Robot> blueRobots, std::vector<vss::Robot> yellowRobots, vss::Ball ball) = 0;
};
#endif
