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

class IVisionWindow {
public:
    virtual int run(int argc, char *argv[]) = 0;

    virtual bool onKeyboard(GdkEventKey*, Gtk::Window*) = 0;

    virtual void onButtonPlay() = 0;    
    virtual void onButtonLoad(Gtk::FileChooserDialog*) = 0;
	virtual void onButtonOpenLoadDialog(Gtk::FileChooserDialog*) = 0;

    virtual void onRadioButtonImage(Gtk::RadioButton*) = 0;
    virtual void onRadioButtonVideo(Gtk::RadioButton*) = 0;
    virtual void onRadioButtonCamera(Gtk::RadioButton*) = 0;
	
    virtual void onComboBoxSelectPath(Gtk::ComboBox*) = 0;
    virtual void onComboBoxSelectColorTeam1(Gtk::ComboBox*) = 0;
    virtual void onComboBoxSelectColorTeam2(Gtk::ComboBox*) = 0;
    virtual void onComboBoxSelectColorRobot1(Gtk::ComboBox*) = 0;
    virtual void onComboBoxSelectColorRobot2(Gtk::ComboBox*) = 0;
    virtual void onComboBoxSelectColorRobot3(Gtk::ComboBox*) = 0;
    virtual void onComboBoxSelectColorRobot4(Gtk::ComboBox*) = 0;
    virtual void onComboBoxSelectColorRobot5(Gtk::ComboBox*) = 0;

};
#endif