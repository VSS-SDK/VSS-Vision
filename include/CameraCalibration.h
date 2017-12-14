#ifndef CAMERA_CALIBRATION_H
#define CAMERA_CALIBRATION_H

#include "gtkmm.h"
#include "ICameraReader.h"
#include "iostream"

class CameraCalibration : public ICameraReader{
public:
    CameraCalibration();
    bool on_keyboard(GdkEventKey* event, Gtk::Window* window) override;
    
    void on_button_load(Gtk::FileChooserWidget* file_chooser) override;
	void on_button_save(Gtk::FileChooserWidget* file_chooser) override;
	void on_button_window_file(Gtk::Window* window_file) override;
	void on_color_selected(Gtk::ComboBoxText* color_selected) override;
	void on_color_team_1(Gtk::ComboBoxText* color_team_1) override;
	void on_color_team_2(Gtk::ComboBoxText* color_team_2) override;
	void on_color_robot_1(Gtk::ComboBoxText* color_robot_1) override;
	void on_color_robot_2(Gtk::ComboBoxText* color_robot_2) override;
	void on_color_robot_3(Gtk::ComboBoxText* color_robot_3) override;
	void on_input_path(Gtk::ComboBoxText* input_path) override;
	void on_scale_h_max(Gtk::Scale* scale_h_max) override;
	void on_scale_h_min(Gtk::Scale* scale_h_min) override;
	void on_scale_s_max(Gtk::Scale* scale_s_max) override;
	void on_scale_s_min(Gtk::Scale* scale_s_min) override;
	void on_scale_v_max(Gtk::Scale* scale_v_max) override;
	void on_scale_v_min(Gtk::Scale* scale_v_min) override;
	void on_scale_rotation(Gtk::Scale* scale_rotation) override;
	void on_scale_brightness(Gtk::Scale* scale_brightness) override;
	void on_scale_contrast(Gtk::Scale* scale_contrast) override;
	void on_scale_saturation(Gtk::Scale* scale_saturation) override;
	void on_scale_exposure(Gtk::Scale* scale_exposure) override;
	void on_scale_gain(Gtk::Scale* scale_gain) override;
	void on_radio_button_image(Gtk::RadioButton* radio_button_image) override;
	void on_radio_button_video(Gtk::RadioButton* radio_button_video) override;
	void on_radio_button_camera(Gtk::RadioButton* radio_button_camera) override; 
};

#endif // CAMERA_CALIBRATION_H