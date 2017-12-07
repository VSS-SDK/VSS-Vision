#include "mainwindow.h"

MainWindow::MainWindow(){
	auto app = Gtk::Application::create();

	load_builder_from_file();
	set_signal_widget();
	
	app->run(*window);
}

MainWindow::~MainWindow(){
}

void MainWindow::load_builder_from_file(){

	auto builder = Gtk::Builder::create();
	try
	{
		builder->add_from_file("src/Menu.glade");
	}
	catch(const Glib::FileError& ex)
	{
		std::cerr << "FileError: " << ex.what() << std::endl;
	}
	catch(const Glib::MarkupError& ex)
	{
		std::cerr << "MarkupError: " << ex.what() << std::endl;
	}
	catch(const Gtk::BuilderError& ex)
	{
		std::cerr << "BuilderError: " << ex.what() << std::endl;
	}
	
	builder->get_widget("Window Menu", window);	
	builder->get_widget("Button Play", button_play);
	builder->get_widget("Button Calibration", button_calibration);
	builder->get_widget("Button Simulator", button_simulator);
	builder->get_widget("Button Arduino", button_arduino);
	builder->get_widget("Button Exit", button_exit);
}

void MainWindow::set_signal_widget(){
	window->signal_key_press_event().connect(sigc::mem_fun(this, &MainWindow::onKeyboard), false);
	button_play->signal_clicked().connect( sigc::mem_fun(this, &MainWindow::onButtonPlay) );
	button_calibration->signal_clicked().connect( sigc::mem_fun(this, &MainWindow::onButtonCalibration) );
	button_simulator->signal_clicked().connect( sigc::mem_fun(this, &MainWindow::onButtonSimulator) );
	button_arduino->signal_clicked().connect( sigc::mem_fun(this, &MainWindow::onButtonArduino) );
	button_exit->signal_clicked().connect( sigc::mem_fun(this, &MainWindow::onButtonExit) );
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

void MainWindow::onButtonPlay(){ 
	window->close(); 
}
void MainWindow::onButtonCalibration(){ 
	window->close(); 
}
void MainWindow::onButtonSimulator(){ 
	window->close(); 
}
void MainWindow::onButtonArduino(){ 
	window->close(); 
}
void MainWindow::onButtonExit(){
	window->close();
}