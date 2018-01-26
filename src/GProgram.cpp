/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "GProgram.h"
#include "CameraCalibration.h"

GProgram::GProgram(){
	window_control = new CameraCalibration();
}

GProgram::~GProgram(){
}

void GProgram::initialize_widget(){

/*
	//combo_box_color_select->append("text");

	for (unsigned int i = 0; i < 2; i++){	
		combo_box_color_team1->append(text_color[i]);
		combo_box_color_team2->append(text_color[i]);
	}

	for (unsigned int i = 3; i < text_color.size(); i++){	
		combo_box_color_robot1->append(text_color[i]);
		combo_box_color_robot2->append(text_color[i]);
		combo_box_color_robot3->append(text_color[i]);
	}
*/

	radio_button_image->set_active();	

	g_image->set_image(cv::imread("../mock/images/model.jpg"));	

	window->maximize();
	window->show_all();
}

void GProgram::run(int argc, char *argv[]){
    Gtk::Main kit(argc, argv);

	load_widget_from_file();
	set_widget_signal();
	initialize_widget();

    Gtk::Main::run(*window);
}
 
void GProgram::load_widget_from_file(){

	auto builder = Gtk::Builder::create();

	try {
		builder->add_from_file("../glade/GProgram.glade");

		builder->get_widget("window", window);
		
		builder->get_widget_derived("image", g_image);
		
		builder->get_widget("button_save", button_save);
		builder->get_widget("button_load", button_load);
		builder->get_widget("button_load_save", button_load_save);
		builder->get_widget("filechooserdialog", file_chooser);
	
	/* 	
		builder->get_widget("comboboxtext_input", combo_box_input_path);
		builder->get_widget("comboboxtext_team_1", combo_box_color_team1);
		builder->get_widget("comboboxtext_team_2", combo_box_color_team2);
		builder->get_widget("comboboxtext_robot_1", combo_box_color_robot1);
		builder->get_widget("comboboxtext_robot_2", combo_box_color_robot2);
		builder->get_widget("comboboxtext_robot_3", combo_box_color_robot3);
		builder->get_widget("comboboxtext_set_color", combo_box_color_select);
	*/
		builder->get_widget("hscale_hmax", scale_h_max);
		builder->get_widget("hscale_hmin", scale_h_min);
		builder->get_widget("hscale_smax", scale_s_max);
		builder->get_widget("hscale_smin", scale_s_min);
		builder->get_widget("hscale_vmax", scale_v_max);
		builder->get_widget("hscale_vmin", scale_v_min);
		builder->get_widget("hscale_rotation", scale_rotation);
		builder->get_widget("hscale_brightness", scale_brightness);
		builder->get_widget("hscale_contrast", scale_contrast);
		builder->get_widget("hscale_exposure", scale_exposure);
		builder->get_widget("hscale_saturation", scale_saturation);
		builder->get_widget("hscale_gain", scale_gain);
	
		builder->get_widget("radiobutton_image", radio_button_image);    
		builder->get_widget("radiobutton_video", radio_button_video);    
		builder->get_widget("radiobutton_camera", radio_button_camera);
	
	} catch(const Glib::FileError& ex) {
		std::cerr << "FileError: " << ex.what() << std::endl;

	} catch(const Glib::MarkupError& ex) {
		std::cerr << "MarkupError: " << ex.what() << std::endl;

	} catch(const Gtk::BuilderError& ex) {
		std::cerr << "BuilderError: " << ex.what() << std::endl;
	}
}

void GProgram::set_widget_signal(){
	
	window->signal_key_press_event().connect(sigc::bind<Gtk::Window*>(sigc::mem_fun(window_control, &IWindowControl::on_keyboard), window) , false);
	
	button_load->signal_clicked().connect(sigc::bind<Gtk::FileChooserDialog*>(sigc::mem_fun(window_control, &IWindowControl::on_button_load), file_chooser ));
	button_save->signal_clicked().connect(sigc::bind<Gtk::FileChooserDialog*>(sigc::mem_fun(window_control, &IWindowControl::on_button_save), file_chooser ));
	button_load_save->signal_clicked().connect(sigc::bind<Gtk::FileChooserDialog*>(sigc::mem_fun(window_control, &IWindowControl::on_button_load_save), file_chooser ));

/* 
	combo_box_input_path   ->signal_changed().connect(sigc::bind<Gtk::ComboBoxText*>(sigc::mem_fun(window_control, &IWindowControl::on_combo_box_input_path), combo_box_input_path));
	combo_box_color_team1  ->signal_changed().connect(sigc::bind<Gtk::ComboBoxText*>(sigc::mem_fun(window_control, &IWindowControl::on_combo_box_color_team1), combo_box_color_team1));
	combo_box_color_team2  ->signal_changed().connect(sigc::bind<Gtk::ComboBoxText*>(sigc::mem_fun(window_control, &IWindowControl::on_combo_box_color_team2), combo_box_color_team2));
	combo_box_color_robot1 ->signal_changed().connect(sigc::bind<Gtk::ComboBoxText*>(sigc::mem_fun(window_control, &IWindowControl::on_combo_box_color_robot1), combo_box_color_robot1));
	combo_box_color_robot2 ->signal_changed().connect(sigc::bind<Gtk::ComboBoxText*>(sigc::mem_fun(window_control, &IWindowControl::on_combo_box_color_robot2), combo_box_color_robot2));
	combo_box_color_robot3 ->signal_changed().connect(sigc::bind<Gtk::ComboBoxText*>(sigc::mem_fun(window_control, &IWindowControl::on_combo_box_color_robot3), combo_box_color_robot3));
	combo_box_color_select->signal_changed().connect(sigc::bind<Gtk::ComboBoxText*>(sigc::mem_fun(window_control, &IWindowControl::on_combo_box_color_select), combo_box_color_select));
*/
	scale_h_max->signal_value_changed().connect(sigc::bind<Gtk::Scale*>(sigc::mem_fun(window_control, &IWindowControl::on_scale_h_max), scale_h_max));
 	scale_h_min->signal_value_changed().connect(sigc::bind<Gtk::Scale*>(sigc::mem_fun(window_control, &IWindowControl::on_scale_h_min), scale_h_min));
	scale_s_max->signal_value_changed().connect(sigc::bind<Gtk::Scale*>(sigc::mem_fun(window_control, &IWindowControl::on_scale_s_max), scale_s_max));
	scale_s_min->signal_value_changed().connect(sigc::bind<Gtk::Scale*>(sigc::mem_fun(window_control, &IWindowControl::on_scale_s_min), scale_s_min));
	scale_v_max->signal_value_changed().connect(sigc::bind<Gtk::Scale*>(sigc::mem_fun(window_control, &IWindowControl::on_scale_v_max), scale_v_max));
	scale_v_min->signal_value_changed().connect(sigc::bind<Gtk::Scale*>(sigc::mem_fun(window_control, &IWindowControl::on_scale_v_min), scale_v_min));

	scale_gain		->signal_value_changed().connect(sigc::bind<Gtk::Scale*>(sigc::mem_fun(window_control, &IWindowControl::on_scale_gain), scale_gain));
	scale_rotation	->signal_value_changed().connect(sigc::bind<Gtk::Scale*>(sigc::mem_fun(window_control, &IWindowControl::on_scale_rotation), scale_rotation));
	scale_contrast	->signal_value_changed().connect(sigc::bind<Gtk::Scale*>(sigc::mem_fun(window_control, &IWindowControl::on_scale_contrast), scale_contrast));
	scale_exposure	->signal_value_changed().connect(sigc::bind<Gtk::Scale*>(sigc::mem_fun(window_control, &IWindowControl::on_scale_exposure), scale_exposure));
	scale_brightness->signal_value_changed().connect(sigc::bind<Gtk::Scale*>(sigc::mem_fun(window_control, &IWindowControl::on_scale_brightness), scale_brightness));
	scale_saturation->signal_value_changed().connect(sigc::bind<Gtk::Scale*>(sigc::mem_fun(window_control, &IWindowControl::on_scale_saturation), scale_saturation));

    radio_button_image ->signal_pressed().connect(sigc::bind<Gtk::RadioButton*>(sigc::mem_fun(window_control, &IWindowControl::on_radio_button_image), radio_button_image));
    radio_button_video ->signal_pressed().connect(sigc::bind<Gtk::RadioButton*>(sigc::mem_fun(window_control, &IWindowControl::on_radio_button_video), radio_button_video));
    radio_button_camera->signal_pressed().connect(sigc::bind<Gtk::RadioButton*>(sigc::mem_fun(window_control, &IWindowControl::on_radio_button_camera), radio_button_camera));
}