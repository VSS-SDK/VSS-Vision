/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include <Repositories/CalibrationRepository.h>
#include <Builders/CalibrationBuilder.h>
#include <CameraReader.h>
#include "CalibrationWindow.h"
#include "CalibrationRoutine.h"

CalibrationWindow::CalibrationWindow(){
  calibrationBuilderFromRepository = new CalibrationBuilder();
  calibrationBuilderFromRoutine = new CalibrationBuilder();
  cameraReader = new CameraReader();

  calibrationRepository = new CalibrationRepository(calibrationBuilderFromRepository);

  calibrationRoutine = new CalibrationRoutine(calibrationRepository, calibrationBuilderFromRoutine);
}

CalibrationWindow::~CalibrationWindow(){
}

void CalibrationWindow::run(int argc, char *argv[]){
  Gtk::Main kit(argc, argv);

  threadWindowControl = new thread( std::bind( &CalibrationWindow::windowThreadWrapper, this ));
  threadCameraReader = new thread( std::bind( &CalibrationWindow::cameraThreadWrapper, this ));
  
  threadWindowControl->join();
  threadCameraReader->detach();
}

void CalibrationWindow::cameraThreadWrapper() {
  cameraReader->setCameraIndex(0);
  cameraReader->start();
  cameraReader->initializeCapture();
}

void CalibrationWindow::windowThreadWrapper() {
  builderWidget();
  setSignals();
  initializeWidget();
  bindWidgetToCalibrationRoutine();

  Gtk::Main::run(*window);
}

void CalibrationWindow::initializeWidget(){

  //TABLES
  table_input->attach(*comboBoxInputPath, 0, 3, 3, 4, Gtk::FILL, Gtk::EXPAND);
  table_set_color->attach(*comboBoxColorSelect, 0, 1, 1, 2, Gtk::FILL, Gtk::EXPAND);
  table_color_robot->attach(*comboBoxColorTeam1 , 1, 2, 1, 2, Gtk::FILL | Gtk::EXPAND, Gtk::EXPAND);
  table_color_robot->attach(*comboBoxColorTeam2 , 1, 2, 2, 3, Gtk::FILL | Gtk::EXPAND, Gtk::EXPAND);
  table_color_robot->attach(*comboBoxColorRobot1, 1, 2, 3, 4, Gtk::FILL | Gtk::EXPAND, Gtk::EXPAND);
  table_color_robot->attach(*comboBoxColorRobot2, 1, 2, 4, 5, Gtk::FILL | Gtk::EXPAND, Gtk::EXPAND);
  table_color_robot->attach(*comboBoxColorRobot3, 1, 2, 5, 6, Gtk::FILL | Gtk::EXPAND, Gtk::EXPAND);
  table_color_robot->attach(*comboBoxColorRobot4, 1, 2, 6, 7, Gtk::FILL | Gtk::EXPAND, Gtk::EXPAND);
  table_color_robot->attach(*comboBoxColorRobot5, 1, 2, 7, 8, Gtk::FILL | Gtk::EXPAND, Gtk::EXPAND);

  //COMBOBOXTEXT
  vector<Glib::ustring> colors = {"Blue", "Yellow", "Orange", "Green", "Pink", "Purple", "Red", "Brown"};

  for (unsigned int i = 0; i < colors.size(); i++){
    comboBoxColorSelect->append(colors[i]);
  }

  for (unsigned int i = 0; i < 2; i++){
    comboBoxColorTeam1->append(colors[i]);
    comboBoxColorTeam2->append(colors[i]);
  }

  for (unsigned int i = 3; i < colors.size(); i++){
    comboBoxColorRobot1->append(colors[i]);
    comboBoxColorRobot2->append(colors[i]);
    comboBoxColorRobot3->append(colors[i]);
    comboBoxColorRobot4->append(colors[i]);
    comboBoxColorRobot5->append(colors[i]);
  }
  
  //RADIOBUTTON
  radioButtonImage->set_active();

  window->maximize();
  window->show_all_children();

  //DRAWINGAREA
  gImage->set_image(cv::imread("../mock/images/model.jpg"));
}

void CalibrationWindow::builderWidget(){

  auto builder = Gtk::Builder::create();

  try {
    builder->add_from_file("../glade/Calibration.glade");

    builder->get_widget("window", window);

    builder->get_widget_derived("image", gImage);

    builder->get_widget("button_save_calibration", button_save_calibration);
    builder->get_widget("button_load_calibration", button_load_calibration);
    builder->get_widget("button_save_dialog", button_save_dialog);
    builder->get_widget("button_load_dialog", button_load_dialog);

    builder->get_widget("entry_chooser", entry_chooser);
    builder->get_widget("filechooserdialog", file_chooser);

    //SCALE
    scale_hsv.resize(6);
    for (unsigned int i = 0; i < scale_hsv.size(); i++){
      scale_hsv[i] = nullptr;
    }

    builder->get_widget("hscale_hmax", scale_hsv[H_MAX]);
    builder->get_widget("hscale_hmin", scale_hsv[H_MIN]);
    builder->get_widget("hscale_smax", scale_hsv[S_MAX]);
    builder->get_widget("hscale_smin", scale_hsv[S_MIN]);
    builder->get_widget("hscale_vmax", scale_hsv[V_MAX]);
    builder->get_widget("hscale_vmin", scale_hsv[V_MIN]);

    scale_cam_config.resize(7);
    for (unsigned int i = 0; i < scale_cam_config.size(); i++){
      scale_cam_config[i] = nullptr;
    }

    builder->get_widget("hscale_gain", scale_cam_config[Gain]);
    builder->get_widget("hscale_rotation", scale_cam_config[Rotation]);
    builder->get_widget("hscale_contrast", scale_cam_config[Contrast]);
    builder->get_widget("hscale_exposure", scale_cam_config[Exposure]);
    builder->get_widget("hscale_brightness", scale_cam_config[Brightness]);
    builder->get_widget("hscale_saturation", scale_cam_config[Saturation]);

    builder->get_widget("radiobutton_image", radioButtonImage);
    builder->get_widget("radiobutton_video", radioButtonVideo);
    builder->get_widget("radiobutton_camera", radioButtonCamera);
    builder->get_widget("togglebutton_cut_mode", togglebutton_cut_mode);

    builder->get_widget("table_input", table_input);
    builder->get_widget("table_set_color", table_set_color);
    builder->get_widget("table_color_robot", table_color_robot);

    comboBoxInputPath    = new Gtk::ComboBoxText();
    comboBoxColorSelect  = new Gtk::ComboBoxText();
    comboBoxColorTeam1  = new Gtk::ComboBoxText();
    comboBoxColorTeam2  = new Gtk::ComboBoxText();
    comboBoxColorRobot1 = new Gtk::ComboBoxText();
    comboBoxColorRobot2 = new Gtk::ComboBoxText();
    comboBoxColorRobot3 = new Gtk::ComboBoxText();
    comboBoxColorRobot4 = new Gtk::ComboBoxText();
    comboBoxColorRobot5 = new Gtk::ComboBoxText();

  } catch(const Glib::FileError& ex) {
    std::cerr << "FileError: " << ex.what() << std::endl;

  } catch(const Glib::MarkupError& ex) {
    std::cerr << "MarkupError: " << ex.what() << std::endl;

  } catch(const Gtk::BuilderError& ex) {
    std::cerr << "BuilderError: " << ex.what() << std::endl;
  }
}

void CalibrationWindow::setSignals(){ 
  
  window->signal_key_press_event().connect(sigc::bind<Gtk::Window*>(sigc::mem_fun(calibrationRoutine, &ICalibrationRoutine::on_keyboard), window) , false);

  button_save_dialog->signal_clicked().connect(sigc::bind<Gtk::FileChooserDialog*, Gtk::Entry*>(sigc::mem_fun(calibrationRoutine, &ICalibrationRoutine::on_button_save_dialog), file_chooser, entry_chooser ));
  button_load_dialog->signal_clicked().connect(sigc::bind<Gtk::FileChooserDialog*, Gtk::Entry*>(sigc::mem_fun(calibrationRoutine, &ICalibrationRoutine::on_button_load_dialog), file_chooser, entry_chooser ));
  button_save_calibration->signal_clicked().connect(sigc::bind<Gtk::FileChooserDialog*, Gtk::Entry*>(sigc::mem_fun(calibrationRoutine, &ICalibrationRoutine::on_button_save_calibration), file_chooser, entry_chooser ));
  button_load_calibration->signal_clicked().connect(sigc::bind<Gtk::FileChooserDialog*, Gtk::Entry*, std::vector<Gtk::Scale*>>(sigc::mem_fun(calibrationRoutine, &ICalibrationRoutine::on_button_load_calibration), file_chooser, entry_chooser, scale_cam_config ));

  file_chooser->signal_selection_changed().connect(sigc::bind<Gtk::FileChooserDialog*, Gtk::Entry*>(sigc::mem_fun(calibrationRoutine, &ICalibrationRoutine::on_signal_select_dialog), file_chooser, entry_chooser ));

  scale_hsv[H_MAX]->signal_value_changed().connect(sigc::bind<Gtk::Scale*>(sigc::mem_fun(calibrationRoutine, &ICalibrationRoutine::on_scale_h_max), scale_hsv[H_MAX]));
  scale_hsv[H_MIN]->signal_value_changed().connect(sigc::bind<Gtk::Scale*>(sigc::mem_fun(calibrationRoutine, &ICalibrationRoutine::on_scale_h_min), scale_hsv[H_MIN]));
  scale_hsv[S_MAX]->signal_value_changed().connect(sigc::bind<Gtk::Scale*>(sigc::mem_fun(calibrationRoutine, &ICalibrationRoutine::on_scale_s_max), scale_hsv[S_MAX]));
  scale_hsv[S_MIN]->signal_value_changed().connect(sigc::bind<Gtk::Scale*>(sigc::mem_fun(calibrationRoutine, &ICalibrationRoutine::on_scale_s_min), scale_hsv[S_MIN]));
  scale_hsv[V_MAX]->signal_value_changed().connect(sigc::bind<Gtk::Scale*>(sigc::mem_fun(calibrationRoutine, &ICalibrationRoutine::on_scale_v_max), scale_hsv[V_MAX]));
  scale_hsv[V_MIN]->signal_value_changed().connect(sigc::bind<Gtk::Scale*>(sigc::mem_fun(calibrationRoutine, &ICalibrationRoutine::on_scale_v_min), scale_hsv[V_MIN]));

  scale_cam_config[Gain]->signal_value_changed().connect(sigc::bind<Gtk::Scale*>(sigc::mem_fun(calibrationRoutine, &ICalibrationRoutine::on_scale_gain), scale_cam_config[Gain]));
  scale_cam_config[Rotation]->signal_value_changed().connect(sigc::bind<Gtk::Scale*>(sigc::mem_fun(calibrationRoutine, &ICalibrationRoutine::on_scale_rotation), scale_cam_config[Rotation]));
  scale_cam_config[Contrast]->signal_value_changed().connect(sigc::bind<Gtk::Scale*>(sigc::mem_fun(calibrationRoutine, &ICalibrationRoutine::on_scale_contrast), scale_cam_config[Contrast]));
  scale_cam_config[Exposure]->signal_value_changed().connect(sigc::bind<Gtk::Scale*>(sigc::mem_fun(calibrationRoutine, &ICalibrationRoutine::on_scale_exposure), scale_cam_config[Exposure]));
  scale_cam_config[Brightness]->signal_value_changed().connect(sigc::bind<Gtk::Scale*>(sigc::mem_fun(calibrationRoutine, &ICalibrationRoutine::on_scale_brightness), scale_cam_config[Brightness]));
  scale_cam_config[Saturation]->signal_value_changed().connect(sigc::bind<Gtk::Scale*>(sigc::mem_fun(calibrationRoutine, &ICalibrationRoutine::on_scale_saturation), scale_cam_config[Saturation]));

  radioButtonImage->signal_pressed().connect(sigc::bind<Gtk::RadioButton*>(sigc::mem_fun(calibrationRoutine, &ICalibrationRoutine::on_radio_button_image), radioButtonImage));
  radioButtonVideo->signal_pressed().connect(sigc::bind<Gtk::RadioButton*>(sigc::mem_fun(calibrationRoutine, &ICalibrationRoutine::on_radio_button_video), radioButtonVideo));
  radioButtonCamera->signal_pressed().connect(sigc::bind<Gtk::RadioButton*>(sigc::mem_fun(calibrationRoutine, &ICalibrationRoutine::on_radio_button_camera), radioButtonCamera));
  togglebutton_cut_mode->signal_pressed().connect(sigc::bind<Gtk::ToggleButton*>(sigc::mem_fun(calibrationRoutine, &ICalibrationRoutine::on_toggle_button_cut_mode), togglebutton_cut_mode));

  comboBoxInputPath->signal_changed().connect(sigc::bind<Gtk::ComboBoxText*>(sigc::mem_fun(calibrationRoutine, &ICalibrationRoutine::on_combo_box_input_path), comboBoxInputPath));
  comboBoxColorTeam1->signal_changed().connect(sigc::bind<Gtk::ComboBoxText*>(sigc::mem_fun(calibrationRoutine, &ICalibrationRoutine::on_combo_box_color_team1), comboBoxColorTeam1));
  comboBoxColorTeam2->signal_changed().connect(sigc::bind<Gtk::ComboBoxText*>(sigc::mem_fun(calibrationRoutine, &ICalibrationRoutine::on_combo_box_color_team2), comboBoxColorTeam2));
  comboBoxColorRobot1->signal_changed().connect(sigc::bind<Gtk::ComboBoxText*>(sigc::mem_fun(calibrationRoutine, &ICalibrationRoutine::on_combo_box_color_robot1), comboBoxColorRobot1));
  comboBoxColorRobot2->signal_changed().connect(sigc::bind<Gtk::ComboBoxText*>(sigc::mem_fun(calibrationRoutine, &ICalibrationRoutine::on_combo_box_color_robot2), comboBoxColorRobot2));
  comboBoxColorRobot3->signal_changed().connect(sigc::bind<Gtk::ComboBoxText*>(sigc::mem_fun(calibrationRoutine, &ICalibrationRoutine::on_combo_box_color_robot3), comboBoxColorRobot3));
  comboBoxColorRobot4->signal_changed().connect(sigc::bind<Gtk::ComboBoxText*>(sigc::mem_fun(calibrationRoutine, &ICalibrationRoutine::on_combo_box_color_robot4), comboBoxColorRobot4));
  comboBoxColorRobot5->signal_changed().connect(sigc::bind<Gtk::ComboBoxText*>(sigc::mem_fun(calibrationRoutine, &ICalibrationRoutine::on_combo_box_color_robot5), comboBoxColorRobot5));

  comboBoxColorSelect->signal_changed().connect(sigc::bind<Gtk::ComboBoxText*, std::vector<Gtk::Scale*>>(sigc::mem_fun(calibrationRoutine, &ICalibrationRoutine::on_combo_box_color_select), comboBoxColorSelect, scale_hsv));
  // signals to update frame
  dispatcher_frame.connect(sigc::mem_fun( this, &CalibrationWindow::setNewFrame) );
  cameraReader->signal_new_frame.connect( sigc::mem_fun(this, &CalibrationWindow::receiveNewFrame) ); 
}

void CalibrationWindow::setNewFrame(){
  gImage->set_image(frame);
}

void CalibrationWindow::receiveNewFrame(cv::Mat _frame){
  frame = _frame;
  dispatcher_frame.emit();
}