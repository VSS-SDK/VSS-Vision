#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <gtkmm.h>
#include <iostream>

using namespace std;

class MainWindow {

private:
	Gtk::Window* window = nullptr;
	Gtk::FileChooserButton* button_load = nullptr;
	
 	Gtk::ComboBoxText* color_selected = nullptr;
	Gtk::ComboBoxText* color_team_1 = nullptr;
	Gtk::ComboBoxText* color_team_2 = nullptr;
	Gtk::ComboBoxText* color_robot_1 = nullptr;
	Gtk::ComboBoxText* color_robot_2 = nullptr;
	Gtk::ComboBoxText* color_robot_3 = nullptr;
	Gtk::ComboBoxText* input_path = nullptr;

	Gtk::Scale* scale_h_max = nullptr;
	Gtk::Scale* scale_h_min = nullptr;
	Gtk::Scale* scale_s_max = nullptr;
	Gtk::Scale* scale_s_min = nullptr;
	Gtk::Scale* scale_v_max = nullptr;
	Gtk::Scale* scale_v_min = nullptr;
	Gtk::Scale* scale_rotation;
	Gtk::Scale* scale_brightness;
	Gtk::Scale* scale_contrast;
	Gtk::Scale* scale_exposure;
	Gtk::Scale* scale_saturation;
	Gtk::Scale* scale_gain;

	Gtk::RadioButton* radio_button_image;
	Gtk::RadioButton* radio_button_video;
	Gtk::RadioButton* radio_button_camera;
	
	
	void set_widget_signal();
	void load_widget_from_file();
	void initialize_widget();

	bool on_keyboard(GdkEventKey *event);
	void on_button_load();

	void on_color_selected();
	void on_color_team_1();
	void on_color_team_2();
	void on_color_robot_1();
	void on_color_robot_2();
	void on_color_robot_3();
	void on_input_path();

	void on_scale_h_max();
	void on_scale_h_min();
	void on_scale_s_max();
	void on_scale_s_min();
	void on_scale_v_max();
	void on_scale_v_min();
	void on_scale_rotation();
	void on_scale_brightness();
	void on_scale_contrast();
	void on_scale_saturation();
	void on_scale_exposure();
	void on_scale_gain();

	void on_radio_button_image();
	void on_radio_button_video();
	void on_radio_button_camera();

public:
	MainWindow();
	virtual ~MainWindow();
	void run();
};

#endif
