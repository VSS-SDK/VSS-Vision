#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <gtkmm.h>
#include <iostream>

using namespace std;

class MainWindow {

private:
	Gtk::Window* window = nullptr;
	Gtk::Button* button_play = nullptr;
	Gtk::Button* button_calibration = nullptr;
	Gtk::Button* button_simulator = nullptr;
	Gtk::Button* button_arduino = nullptr;
	Gtk::Button* button_exit = nullptr;
	
	void set_signal_widget();
	void load_builder_from_file();

	bool onKeyboard(GdkEventKey*);
	void onButtonPlay();
	void onButtonCalibration();
	void onButtonSimulator();
	void onButtonArduino();
	void onButtonExit();

public:
	MainWindow();
	virtual ~MainWindow();
};

#endif