/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef GPROGRAM_H_
#define GPROGRAM_H_

#include <gtkmm.h>
#include <iostream>

#include "GImage.h"
#include "IWindowControl.h"
#include "opencv2/highgui/highgui.hpp"

using namespace std;

class GProgram {

private:

	IWindowControl *window_control;
	
// Window - calibration
	Gtk::Window* window = nullptr;

	// Opencv image
	GImage* g_image = nullptr;

	// Button
	Gtk::RadioButton* radio_button_image = nullptr;
	Gtk::RadioButton* radio_button_video = nullptr;
	Gtk::RadioButton* radio_button_camera = nullptr;

	// Select text
	Gtk::ComboBoxText* combobox_input_path = nullptr;
	Gtk::ComboBoxText* combobox_color_select = nullptr;
	Gtk::ComboBoxText* combobox_color_team_1 = nullptr;
	Gtk::ComboBoxText* combobox_color_team_2 = nullptr;
	Gtk::ComboBoxText* combobox_color_robot_1 = nullptr;
	Gtk::ComboBoxText* combobox_color_robot_2 = nullptr;
	Gtk::ComboBoxText* combobox_color_robot_3 = nullptr;
	Gtk::ComboBoxText* combobox_color_robot_4 = nullptr;
	Gtk::ComboBoxText* combobox_color_robot_5 = nullptr;

	// Table
	Gtk::Table* table_input = nullptr;
	Gtk::Table* table_set_color = nullptr;
	Gtk::Table* table_color_robot = nullptr;

	// Slider
	Gtk::Scale* scale_h_max = nullptr;
	Gtk::Scale* scale_h_min = nullptr;
	Gtk::Scale* scale_s_max = nullptr;
	Gtk::Scale* scale_s_min = nullptr;
	Gtk::Scale* scale_v_max = nullptr;
	Gtk::Scale* scale_v_min = nullptr;
	Gtk::Scale* scale_gain  = nullptr;
	Gtk::Scale* scale_rotation = nullptr;
	Gtk::Scale* scale_contrast = nullptr;
	Gtk::Scale* scale_exposure = nullptr;
	Gtk::Scale* scale_brightness = nullptr;
	Gtk::Scale* scale_saturation = nullptr;

// File Chooser - save/load file 
	Gtk::FileChooserDialog* file_chooser = nullptr;

	// Entry
	Gtk::Entry* entry_chooser = nullptr;
 
	// Button
	Gtk::Button* button_save = nullptr;
	Gtk::Button* button_load = nullptr;
	Gtk::Button* button_load_save = nullptr;
	Gtk::ToggleButton* togglebutton_cut_mode = nullptr;

// Control method
	void initialize_widget();
	void set_signal_widget();
	void builder_widget();

public:

	GProgram();
	virtual ~GProgram();
	void run(int argc, char *argv[]);

};
#endif
