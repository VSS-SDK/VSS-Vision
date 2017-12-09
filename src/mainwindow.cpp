#include "mainwindow.h"

MainWindow::MainWindow(){
}

MainWindow::~MainWindow(){
}

void MainWindow::run(){
	auto app = Gtk::Application::create();

	load_widget_from_file();
	set_widget_signal();
	initialize_widget();

	app->run(*window);
}

void MainWindow::load_widget_from_file(){

	auto builder = Gtk::Builder::create();

	try {
		builder->add_from_file("src/mainwindow.glade");
	} catch(const Glib::FileError& ex) {
		std::cerr << "FileError: " << ex.what() << std::endl;
	} catch(const Glib::MarkupError& ex) {
		std::cerr << "MarkupError: " << ex.what() << std::endl;
	} catch(const Gtk::BuilderError& ex) {
		std::cerr << "BuilderError: " << ex.what() << std::endl;
	}

	builder->add_from_file("src/mainwindow.glade");
	
	builder->get_widget("window", window);
	builder->get_widget("button_load", button_load);
}

void MainWindow::set_widget_signal(){
	window->signal_key_press_event().connect(sigc::mem_fun(this, &MainWindow::on_keyboard), false);
	button_load->signal_file_set().connect( sigc::mem_fun(this, &MainWindow::on_button_load) );

}

void MainWindow::initialize_widget(){
	window->maximize();
}

bool MainWindow::on_keyboard(GdkEventKey* event){
	if(event->keyval == GDK_KEY_space) {
		window->close();
	} else if(event->keyval == GDK_KEY_Return) {
		window->close();
	} else if(event->keyval == GDK_KEY_Escape) {
		window->close();
	}
}

void MainWindow::on_button_load(){
	cout << button_load->get_filename() << endl;
}