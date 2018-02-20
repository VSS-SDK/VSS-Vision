/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include <Repositories/CalibrationRepository.h>
#include "GProgram.h"
#include "CameraCalibration.h"

GProgram::GProgram(){
	calibration_repository = new CalibrationRepository();
	window_control = new CameraCalibration(calibration_repository);
}

GProgram::~GProgram(){
}

void GProgram::initialize_widget(){

	//TABLES
	table_input->attach(*combobox_input_path, 0, 3, 3, 4, Gtk::FILL, Gtk::EXPAND);
	table_set_color->attach(*combobox_color_select, 0, 1, 1, 2, Gtk::FILL, Gtk::EXPAND);
	table_color_robot->attach(*combobox_color_team_1 , 1, 2, 1, 2, Gtk::FILL | Gtk::EXPAND, Gtk::EXPAND);
	table_color_robot->attach(*combobox_color_team_2 , 1, 2, 2, 3, Gtk::FILL | Gtk::EXPAND, Gtk::EXPAND);
	table_color_robot->attach(*combobox_color_robot_1, 1, 2, 3, 4, Gtk::FILL | Gtk::EXPAND, Gtk::EXPAND);
	table_color_robot->attach(*combobox_color_robot_2, 1, 2, 4, 5, Gtk::FILL | Gtk::EXPAND, Gtk::EXPAND);
	table_color_robot->attach(*combobox_color_robot_3, 1, 2, 5, 6, Gtk::FILL | Gtk::EXPAND, Gtk::EXPAND);
	table_color_robot->attach(*combobox_color_robot_4, 1, 2, 6, 7, Gtk::FILL | Gtk::EXPAND, Gtk::EXPAND);
	table_color_robot->attach(*combobox_color_robot_5, 1, 2, 7, 8, Gtk::FILL | Gtk::EXPAND, Gtk::EXPAND);

	//COMBOBOXTEXT
	vector<Glib::ustring> colors = {"Blue", "Yellow", "Orange", "Green", "Pink", "Purple", "Red", "Brown"};

	for (unsigned int i = 0; i < colors.size(); i++){
		combobox_color_select->append(colors[i]);
	}

	for (unsigned int i = 0; i < 2; i++){
		combobox_color_team_1->append(colors[i]);
		combobox_color_team_2->append(colors[i]);
	}

	for (unsigned int i = 3; i < colors.size(); i++){
		combobox_color_robot_1->append(colors[i]);
		combobox_color_robot_2->append(colors[i]);
		combobox_color_robot_3->append(colors[i]);
		combobox_color_robot_4->append(colors[i]);
		combobox_color_robot_5->append(colors[i]);
	}

	//RADIOBUTTON
	radio_button_image->set_active();

	g_image->set_image(cv::imread("../mock/images/model.jpg"));

	window->maximize();
	window->show_all_children();

	//DRAWINGAREA
	g_image->set_image(cv::imread("../mock/images/model.jpg"));
}

void GProgram::run(int argc, char *argv[]){
	Gtk::Main kit(argc, argv);

	builder_widget();
	set_signal_widget();
	initialize_widget();
	bind_widgets_to_calibration();

	Gtk::Main::run(*window);
}

void GProgram::builder_widget(){

	auto builder = Gtk::Builder::create();

	try {
		builder->add_from_file("../glade/Calibration.glade");

		builder->get_widget("window", window);

		builder->get_widget_derived("image", g_image);

		builder->get_widget("button_save", button_save);
		builder->get_widget("button_load", button_load);
		builder->get_widget("button_load_save", button_load_save);
		builder->get_widget("entry_chooser", entry_chooser);
		builder->get_widget("filechooserdialog", file_chooser);

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
		builder->get_widget("togglebutton_cut_mode", togglebutton_cut_mode);

		builder->get_widget("table_input", table_input);
		builder->get_widget("table_set_color", table_set_color);
		builder->get_widget("table_color_robot", table_color_robot);

		combobox_input_path    = new Gtk::ComboBoxText();
		combobox_color_select  = new Gtk::ComboBoxText();
		combobox_color_team_1  = new Gtk::ComboBoxText();
		combobox_color_team_2  = new Gtk::ComboBoxText();
		combobox_color_robot_1 = new Gtk::ComboBoxText();
		combobox_color_robot_2 = new Gtk::ComboBoxText();
		combobox_color_robot_3 = new Gtk::ComboBoxText();
		combobox_color_robot_4 = new Gtk::ComboBoxText();
		combobox_color_robot_5 = new Gtk::ComboBoxText();

	} catch(const Glib::FileError& ex) {
		std::cerr << "FileError: " << ex.what() << std::endl;

	} catch(const Glib::MarkupError& ex) {
		std::cerr << "MarkupError: " << ex.what() << std::endl;

	} catch(const Gtk::BuilderError& ex) {
		std::cerr << "BuilderError: " << ex.what() << std::endl;
	}
}

void GProgram::set_signal_widget(){

	window->signal_key_press_event().connect(sigc::bind<Gtk::Window*>(sigc::mem_fun(window_control, &IWindowControl::on_keyboard), window) , false);

	button_load->signal_clicked().connect(sigc::bind<Gtk::FileChooserDialog*>(sigc::mem_fun(window_control, &IWindowControl::on_button_load), file_chooser ));
	button_save->signal_clicked().connect(sigc::bind<Gtk::Entry*>(sigc::mem_fun(window_control, &IWindowControl::on_button_save), entry_chooser ));
	button_load_save->signal_clicked().connect(sigc::bind<Gtk::FileChooserDialog*>(sigc::mem_fun(window_control, &IWindowControl::on_button_load_save), file_chooser ));

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
    togglebutton_cut_mode->signal_pressed().connect(sigc::bind<Gtk::ToggleButton*>(sigc::mem_fun(window_control, &IWindowControl::on_toggle_button_cut_mode), togglebutton_cut_mode));

	combobox_input_path   ->signal_changed().connect(sigc::bind<Gtk::ComboBoxText*>(sigc::mem_fun(window_control, &IWindowControl::on_combo_box_input_path), combobox_input_path));
	combobox_color_select ->signal_changed().connect(sigc::bind<Gtk::ComboBoxText*>(sigc::mem_fun(window_control, &IWindowControl::on_combo_box_color_select), combobox_color_select));
	combobox_color_team_1 ->signal_changed().connect(sigc::bind<Gtk::ComboBoxText*>(sigc::mem_fun(window_control, &IWindowControl::on_combo_box_color_team1), combobox_color_team_1));
	combobox_color_team_2 ->signal_changed().connect(sigc::bind<Gtk::ComboBoxText*>(sigc::mem_fun(window_control, &IWindowControl::on_combo_box_color_team2), combobox_color_team_2));
	combobox_color_robot_1->signal_changed().connect(sigc::bind<Gtk::ComboBoxText*>(sigc::mem_fun(window_control, &IWindowControl::on_combo_box_color_robot1), combobox_color_robot_1));
	combobox_color_robot_2->signal_changed().connect(sigc::bind<Gtk::ComboBoxText*>(sigc::mem_fun(window_control, &IWindowControl::on_combo_box_color_robot2), combobox_color_robot_2));
	combobox_color_robot_3->signal_changed().connect(sigc::bind<Gtk::ComboBoxText*>(sigc::mem_fun(window_control, &IWindowControl::on_combo_box_color_robot3), combobox_color_robot_3));
	combobox_color_robot_4->signal_changed().connect(sigc::bind<Gtk::ComboBoxText*>(sigc::mem_fun(window_control, &IWindowControl::on_combo_box_color_robot4), combobox_color_robot_4));
	combobox_color_robot_5->signal_changed().connect(sigc::bind<Gtk::ComboBoxText*>(sigc::mem_fun(window_control, &IWindowControl::on_combo_box_color_robot5), combobox_color_robot_5));

}

void GProgram::bind_widgets_to_calibration() {
	window_control->bind_scale_brightness(scale_brightness);
	window_control->bind_scale_contrast(scale_contrast);
	window_control->bind_scale_exposure(scale_exposure);
	window_control->bind_scale_gain(scale_gain);
	window_control->bind_scale_rotation(scale_rotation);
	window_control->bind_scale_saturation(scale_saturation);

	window_control->bind_scale_h_max(scale_h_max);
	window_control->bind_scale_h_min(scale_h_min);

	window_control->bind_scale_s_max(scale_s_max);
	window_control->bind_scale_s_min(scale_s_min);

	window_control->bind_scale_v_max(scale_v_max);
	window_control->bind_scale_v_min(scale_v_min);
}
