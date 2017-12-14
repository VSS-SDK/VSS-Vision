/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef IWINDOW_CONTROL_H
#define IWINDOW_CONTROL_H

#include "gtkmm.h"

// Vai servir para buscar os dados do opencv
// Vai ser utilizado tanto na calibragem quanto na fase de execução
// Calibragem e execucao vai implementar essa interface
// Não poderá ser utilizado a calibragem e a execução ao mesmo tempo
// Quando for trocar entre um e outro, utilizar dynamic_cast
class IWindowControl{
public:

    virtual bool on_keyboard(GdkEventKey* event, Gtk::Window* window) = 0;

    virtual void on_button_load(Gtk::FileChooserWidget* file_chooser) = 0;
	virtual void on_button_save(Gtk::FileChooserWidget* file_chooser) = 0;
	virtual void on_button_window_file(Gtk::Window* window_file) = 0;
	virtual void on_color_selected(Gtk::ComboBoxText* color_selected) = 0;
	virtual void on_color_team_1(Gtk::ComboBoxText* color_team_1) = 0;
	virtual void on_color_team_2(Gtk::ComboBoxText* color_team_2) = 0;
	virtual void on_color_robot_1(Gtk::ComboBoxText* color_robot_1) = 0;
	virtual void on_color_robot_2(Gtk::ComboBoxText* color_robot_2) = 0;
	virtual void on_color_robot_3(Gtk::ComboBoxText* color_robot_3) = 0;
	virtual void on_input_path(Gtk::ComboBoxText* input_path) = 0;
	virtual void on_scale_h_max(Gtk::Scale* scale_h_max) = 0;
	virtual void on_scale_h_min(Gtk::Scale* scale_h_min) = 0;
	virtual void on_scale_s_max(Gtk::Scale* scale_s_max) = 0;
	virtual void on_scale_s_min(Gtk::Scale* scale_s_min) = 0;
	virtual void on_scale_v_max(Gtk::Scale* scale_v_max) = 0;
	virtual void on_scale_v_min(Gtk::Scale* scale_v_min) = 0;
	virtual void on_scale_rotation(Gtk::Scale* scale_rotation) = 0;
	virtual void on_scale_brightness(Gtk::Scale* scale_brightness) = 0;
	virtual void on_scale_contrast(Gtk::Scale* scale_contrast) = 0;
	virtual void on_scale_saturation(Gtk::Scale* scale_saturation) = 0;
	virtual void on_scale_exposure(Gtk::Scale* scale_exposure) = 0;
	virtual void on_scale_gain(Gtk::Scale* scale_gain) = 0;
	virtual void on_radio_button_image(Gtk::RadioButton* radio_button_image) = 0;
	virtual void on_radio_button_video(Gtk::RadioButton* radio_button_video) = 0;
	virtual void on_radio_button_camera(Gtk::RadioButton* radio_button_camera) = 0; 
};

#endif // ICAMERA_READER_H