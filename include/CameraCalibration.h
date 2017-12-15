#ifndef CAMERA_CALIBRATION_H
#define CAMERA_CALIBRATION_H

#include "gtkmm.h"
#include "IWindowControl.h"
#include "iostream"

class CameraCalibration : public IWindowControl{
public:
    CameraCalibration();
    bool on_keyboard(GdkEventKey* event, Gtk::Window*) override;
    void on_button_load(Gtk::FileChooserWidget*) override;
	void on_button_save(Gtk::FileChooserWidget*) override;
	void on_button_window_file(Gtk::Window*) override;
	void on_combo_box_color_select(Gtk::ComboBoxText*) override;
	void on_combo_box_color_team1(Gtk::ComboBoxText*) override;
	void on_combo_box_color_team2(Gtk::ComboBoxText*) override;
	void on_combo_box_color_robot1(Gtk::ComboBoxText*) override;
	void on_combo_box_color_robot2(Gtk::ComboBoxText*) override;
	void on_combo_box_color_robot3(Gtk::ComboBoxText*) override;
	void on_combo_box_input_path(Gtk::ComboBoxText*) override;
	void on_scale_h_max(Gtk::Scale*) override;
	void on_scale_h_min(Gtk::Scale*) override;
	void on_scale_s_max(Gtk::Scale*) override;
	void on_scale_s_min(Gtk::Scale*) override;
	void on_scale_v_max(Gtk::Scale*) override;
	void on_scale_v_min(Gtk::Scale*) override;
	void on_scale_rotation(Gtk::Scale*) override;
	void on_scale_brightness(Gtk::Scale*) override;
	void on_scale_contrast(Gtk::Scale*) override;
	void on_scale_saturation(Gtk::Scale*) override;
	void on_scale_exposure(Gtk::Scale*) override;
	void on_scale_gain(Gtk::Scale*) override;
	void on_radio_button_image(Gtk::RadioButton*) override;
	void on_radio_button_video(Gtk::RadioButton*) override;
	void on_radio_button_camera(Gtk::RadioButton*) override; 
};

#endif // CAMERA_CALIBRATION_H