#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <gtkmm.h>
#include <iostream>

using namespace std;

class MainWindow {

private:
	Gtk::Window* window = nullptr;
	Gtk::MenuBar* menu_bar = nullptr;
	
	void set_widget_signal();
	void load_widget_from_file();

	bool onKeyboard(GdkEventKey*);

public:
	MainWindow();
	virtual ~MainWindow();
	void run();
};

#endif