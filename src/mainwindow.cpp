/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

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
		builder->add_from_file("../glade/mainwindow.glade");

		builder->get_widget("window", window);
		
		builder->get_widget("window_file", window_file);
		builder->get_widget("button_save", button_save);
		builder->get_widget("button_load", button_load);
		builder->get_widget("button_window_file", button_window_file);
		builder->get_widget("file_chooser", file_chooser);
	
		builder->get_widget("color_selected", color_selected);
		builder->get_widget("color_team_1", color_team_1);
		builder->get_widget("color_team_2", color_team_2);
		builder->get_widget("color_robot_1", color_robot_1);
		builder->get_widget("color_robot_2", color_robot_2);
		builder->get_widget("color_robot_3", color_robot_3);
		builder->get_widget("combo_box_input_path", input_path);
	
		builder->get_widget("scale_h_max", scale_h_max);
		builder->get_widget("scale_h_min", scale_h_min);
		builder->get_widget("scale_s_max", scale_s_max);
		builder->get_widget("scale_s_min", scale_s_min);
		builder->get_widget("scale_v_max", scale_v_max);
		builder->get_widget("scale_v_min", scale_v_min);
		builder->get_widget("scale_rotation", scale_rotation);
		builder->get_widget("scale_brightness", scale_brightness);
		builder->get_widget("scale_contrast", scale_contrast);
		builder->get_widget("scale_exposure", scale_exposure);
		builder->get_widget("scale_saturation", scale_saturation);
		builder->get_widget("scale_gain", scale_gain);
	
		builder->get_widget("radio_button_image", radio_button_image);    
		builder->get_widget("radio_button_video", radio_button_video);    
		builder->get_widget("radio_button_camera", radio_button_camera);    
			
	} catch(const Glib::FileError& ex) {
		std::cerr << "FileError: " << ex.what() << std::endl;

	} catch(const Glib::MarkupError& ex) {
		std::cerr << "MarkupError: " << ex.what() << std::endl;

	} catch(const Gtk::BuilderError& ex) {
		std::cerr << "BuilderError: " << ex.what() << std::endl;
	}
}

void MainWindow::set_widget_signal(){
	window->signal_key_press_event().connect(sigc::mem_fun(this, &MainWindow::on_keyboard), false);
	
	button_load->signal_clicked().connect(sigc::mem_fun(this, &MainWindow::on_button_load) );
	button_save->signal_clicked().connect(sigc::mem_fun(this, &MainWindow::on_button_save) );
	button_window_file->signal_clicked().connect(sigc::mem_fun(this, &MainWindow::on_button_window_file));

	input_path	  ->signal_changed().connect(sigc::mem_fun(this, &MainWindow::on_input_path));
	color_team_1  ->signal_changed().connect(sigc::mem_fun(this, &MainWindow::on_color_team_1));
	color_team_2  ->signal_changed().connect(sigc::mem_fun(this, &MainWindow::on_color_team_2));
	color_robot_1 ->signal_changed().connect(sigc::mem_fun(this, &MainWindow::on_color_robot_1));
	color_robot_2 ->signal_changed().connect(sigc::mem_fun(this, &MainWindow::on_color_robot_2));
	color_robot_3 ->signal_changed().connect(sigc::mem_fun(this, &MainWindow::on_color_robot_3));
	color_selected->signal_changed().connect(sigc::mem_fun(this, &MainWindow::on_color_selected));

	scale_h_max->signal_value_changed().connect(sigc::mem_fun(this, &MainWindow::on_scale_h_max));
 	scale_h_min->signal_value_changed().connect(sigc::mem_fun(this, &MainWindow::on_scale_h_min));
	scale_s_max->signal_value_changed().connect(sigc::mem_fun(this, &MainWindow::on_scale_s_max));
	scale_s_min->signal_value_changed().connect(sigc::mem_fun(this, &MainWindow::on_scale_s_min));
	scale_v_max->signal_value_changed().connect(sigc::mem_fun(this, &MainWindow::on_scale_v_max));
	scale_v_min->signal_value_changed().connect(sigc::mem_fun(this, &MainWindow::on_scale_v_min));

	scale_gain		->signal_value_changed().connect(sigc::mem_fun(this, &MainWindow::on_scale_gain));
	scale_rotation	->signal_value_changed().connect(sigc::mem_fun(this, &MainWindow::on_scale_rotation));
	scale_contrast	->signal_value_changed().connect(sigc::mem_fun(this, &MainWindow::on_scale_contrast));
	scale_exposure	->signal_value_changed().connect(sigc::mem_fun(this, &MainWindow::on_scale_exposure));
	scale_brightness->signal_value_changed().connect(sigc::mem_fun(this, &MainWindow::on_scale_brightness));
	scale_saturation->signal_value_changed().connect(sigc::mem_fun(this, &MainWindow::on_scale_saturation));

    radio_button_image ->signal_pressed().connect(sigc::mem_fun(this, &MainWindow::on_radio_button_image));
    radio_button_video ->signal_pressed().connect(sigc::mem_fun(this, &MainWindow::on_radio_button_video));
    radio_button_camera->signal_pressed().connect(sigc::mem_fun(this, &MainWindow::on_radio_button_camera));
}

void MainWindow::initialize_widget(){
	window->maximize();
	radio_button_image->set_active();
}

bool MainWindow::on_keyboard(GdkEventKey* event){
	if(event->keyval == GDK_KEY_space) {
		window->close();
	} else if(event->keyval == GDK_KEY_Return) {
		window->close();
	} else if(event->keyval == GDK_KEY_Escape) {
		window->close();
	}
	return true;
}

void MainWindow::on_button_load(){
	cout << file_chooser->get_filename() << endl;
}

void MainWindow::on_button_save(){
	cout << file_chooser->get_filename() << endl;
}

void MainWindow::on_button_window_file(){
	window_file->show();
}

void MainWindow::on_color_selected(){
	cout << color_selected->get_active_text() << endl;
}

void MainWindow::on_color_team_1(){
	cout << color_team_1->get_active_text() << endl;
}

void MainWindow::on_color_team_2(){
	cout << color_team_2->get_active_text() << endl;
}

void MainWindow::on_color_robot_1(){
	cout << color_robot_1->get_active_text() << endl;
}

void MainWindow::on_color_robot_2(){
	cout << color_robot_2->get_active_text() << endl;
}

void MainWindow::on_color_robot_3(){
	cout << color_robot_3->get_active_text() << endl;
}

void MainWindow::on_input_path(){
	cout << input_path->get_active_text() << endl;
}

void MainWindow::on_scale_h_max(){
	cout << scale_h_max->get_value() << endl;	
}

void MainWindow::on_scale_h_min(){
	cout << scale_h_min->get_value() << endl;	
}

void MainWindow::on_scale_s_max(){
	cout << scale_s_max->get_value() << endl;	
}

void MainWindow::on_scale_s_min(){
	cout << scale_s_min->get_value() << endl;	
}

void MainWindow::on_scale_v_max(){
	cout << scale_v_max->get_value() << endl;	
}

void MainWindow::on_scale_v_min(){
	cout << scale_v_min->get_value() << endl;	
}

void MainWindow::on_scale_rotation(){
	cout << scale_rotation->get_value() << endl;
}

void MainWindow::on_scale_brightness(){
	cout << scale_brightness->get_value() << endl;
}

void MainWindow::on_scale_contrast(){
	cout << scale_contrast->get_value() << endl;
}

void MainWindow::on_scale_saturation(){
	cout << scale_saturation->get_value() << endl;
}

void MainWindow::on_scale_exposure(){
	cout << scale_exposure->get_value() << endl;
}

void MainWindow::on_scale_gain(){
	cout << scale_gain->get_value() << endl;
}

void MainWindow::on_radio_button_image(){
	if (!radio_button_image->get_active())
		cout << "Image: " << radio_button_image->get_active() << endl;
}
void MainWindow::on_radio_button_video(){
	if (!radio_button_video->get_active())
		cout << "Video: " << radio_button_video->get_active() << endl;
}
void MainWindow::on_radio_button_camera(){
	if (!radio_button_camera->get_active())
		cout << "Camera: " << radio_button_camera->get_active() << endl;
}