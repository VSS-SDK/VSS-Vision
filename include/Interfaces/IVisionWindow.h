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
    virtual void run(int argc, char *argv[]) = 0;

    virtual bool on_keyboard(GdkEventKey* event, Gtk::Window*) = 0;

    virtual void on_button_load_dialog(Gtk::FileChooserDialog* , Gtk::Entry*) = 0;
    virtual void on_button_load_calibration(Gtk::FileChooserDialog* , Gtk::Entry*) = 0;

    virtual void on_combo_box_input_path(Gtk::ComboBoxText*) = 0;
    virtual void on_combo_box_color_team1(Gtk::ComboBoxText*) = 0;
    virtual void on_combo_box_color_team2(Gtk::ComboBoxText*) = 0;
    virtual void on_combo_box_color_robot1(Gtk::ComboBoxText*) = 0;
    virtual void on_combo_box_color_robot2(Gtk::ComboBoxText*) = 0;
    virtual void on_combo_box_color_robot3(Gtk::ComboBoxText*) = 0;
    virtual void on_combo_box_color_robot4(Gtk::ComboBoxText*) = 0;
    virtual void on_combo_box_color_robot5(Gtk::ComboBoxText*) = 0;

    virtual void on_radio_button_image(Gtk::RadioButton*) = 0;
    virtual void on_radio_button_video(Gtk::RadioButton*) = 0;
    virtual void on_radio_button_camera(Gtk::RadioButton*) = 0;
};
#endif