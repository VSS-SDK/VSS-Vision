#include "mainwindow.h"

MainWindow::MainWindow(){
}

MainWindow::~MainWindow(){
}

void MainWindow::run(){
	auto app = Gtk::Application::create();

	load_widget_from_file();
	set_widget_signal();

	app->run(*window);
}

void MainWindow::load_widget_from_file(){

	auto builder = Gtk::Builder::create();

	builder->add_from_file("src/mainwindow.glade");
	
	builder->get_widget("window", window);
	builder->get_widget("menubar", menu_bar);
}

void MainWindow::set_widget_signal(){
	window->signal_key_press_event().connect(sigc::mem_fun(this, &MainWindow::onKeyboard), false);
}

bool MainWindow::onKeyboard(GdkEventKey* event){
	if(event->keyval == GDK_KEY_space) {
		window->close();
	} else if(event->keyval == GDK_KEY_Return) {
		window->close();
	} else if(event->keyval == GDK_KEY_Escape) {
		window->close();
	}
}