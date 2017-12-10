#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <gtkmm.h>
#include <iostream>

using namespace std;

class MainWindow {

private:
	Gtk::Window* window = nullptr;
	Gtk::FileChooserButton* button_load = nullptr;
	
	
	void set_widget_signal();
	void load_widget_from_file();
	void initialize_widget();

	bool on_keyboard(GdkEventKey*);
	void on_button_load();

public:
	MainWindow();
	virtual ~MainWindow();
	void run();
};

#endif