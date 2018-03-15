/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef VISION_WINDOW_H_
#define VISION_WINDOW_H_

#include <gtkmm.h>
#include <iostream>
#include "IVisionWindow.h"

using namespace std;

class VisionWindow : public IVisionWindow{
public:
    VisionWindow();
    virtual ~VisionWindow();

    void run(int argc, char *argv[]) override;

    bool on_keyboard(GdkEventKey*, Gtk::Window*) override;

    void on_button_load_dialog(Gtk::FileChooserDialog* , Gtk::Entry*) override;
    void on_button_load_calibration(Gtk::FileChooserDialog* , Gtk::Entry*) override;

    void on_combo_box_input_path(Gtk::ComboBoxText*) override;
    void on_combo_box_color_team1(Gtk::ComboBoxText*) override;
    void on_combo_box_color_team2(Gtk::ComboBoxText*) override;
    void on_combo_box_color_robot1(Gtk::ComboBoxText*) override;
    void on_combo_box_color_robot2(Gtk::ComboBoxText*) override;
    void on_combo_box_color_robot3(Gtk::ComboBoxText*) override;
    void on_combo_box_color_robot4(Gtk::ComboBoxText*) override;
    void on_combo_box_color_robot5(Gtk::ComboBoxText*) override;

    void on_radio_button_image(Gtk::RadioButton*) override;
    void on_radio_button_video(Gtk::RadioButton*) override;
    void on_radio_button_camera(Gtk::RadioButton*) override;

private:

    // Button
	Gtk::RadioButton* radioButtonImage = nullptr;
	Gtk::RadioButton* radioButtonVideo = nullptr;
	Gtk::RadioButton* radioButtonCamera = nullptr;
    
    // Select text
    Gtk::ComboBoxText* comboBoxColorTeam1 = nullptr;
	Gtk::ComboBoxText* comboBoxColorTeam2 = nullptr;
	Gtk::ComboBoxText* comboBoxColorRobot1 = nullptr;
	Gtk::ComboBoxText* comboBoxColorRobot2 = nullptr;
	Gtk::ComboBoxText* comboBoxColorRobot3 = nullptr;
	Gtk::ComboBoxText* comboBoxColorRobot4 = nullptr;
	Gtk::ComboBoxText* comboBoxColorRobot5 = nullptr;
    
};
#endif