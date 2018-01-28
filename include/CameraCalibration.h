/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef CAMERA_CALIBRATION_H
#define CAMERA_CALIBRATION_H

#include "gtkmm.h"
#include "IWindowControl.h"
#include "iostream"

class CameraCalibration : public IWindowControl{
public:
    CameraCalibration();

	bool on_keyboard(GdkEventKey* event, Gtk::Window*) override;

    void on_button_load(Gtk::FileChooserDialog*) override;
	void on_button_save(Gtk::Entry* ) override;
	void on_button_load_save(Gtk::FileChooserDialog*) override;

	void on_combo_box_input_path(Gtk::ComboBoxText*) override;
	void on_combo_box_color_team1(Gtk::ComboBoxText*) override;
	void on_combo_box_color_team2(Gtk::ComboBoxText*) override;
	void on_combo_box_color_robot1(Gtk::ComboBoxText*) override;
	void on_combo_box_color_robot2(Gtk::ComboBoxText*) override;
	void on_combo_box_color_robot3(Gtk::ComboBoxText*) override;
	void on_combo_box_color_robot4(Gtk::ComboBoxText*) override;
	void on_combo_box_color_robot5(Gtk::ComboBoxText*) override;
	void on_combo_box_color_select(Gtk::ComboBoxText*) override;

	void on_scale_h_max(Gtk::Scale*) override;
	void on_scale_h_min(Gtk::Scale*) override;
	void on_scale_s_max(Gtk::Scale*) override;
	void on_scale_s_min(Gtk::Scale*) override;
	void on_scale_v_max(Gtk::Scale*) override;
	void on_scale_v_min(Gtk::Scale*) override;

	void on_scale_gain(Gtk::Scale*) override;
	void on_scale_contrast(Gtk::Scale*) override;
	void on_scale_rotation(Gtk::Scale*) override;
	void on_scale_exposure(Gtk::Scale*) override;
	void on_scale_brightness(Gtk::Scale*) override;
	void on_scale_saturation(Gtk::Scale*) override;

	void on_radio_button_image(Gtk::RadioButton*) override;
	void on_radio_button_video(Gtk::RadioButton*) override;
	void on_radio_button_camera(Gtk::RadioButton*) override; 
	void on_toggle_button_cut_mode(Gtk::ToggleButton*) override; 

	
};

#endif // CAMERA_CALIBRATION_H