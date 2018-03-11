/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include <Repositories/CalibrationRepository.h>
#include <CameraReader.h>
#include <Windows/Calibration/CalibrationWindow.h>
#include <Domain/ColorSpace.h>

bool CalibrationWindow::on_keyboard(GdkEventKey* event, Gtk::Window* window){
  if(event->keyval == GDK_KEY_space) {
    window->hide();
  } else if(event->keyval == GDK_KEY_Return) {
    window->hide();
  } else if(event->keyval == GDK_KEY_Escape) {
    window->hide();
  }
  return true;
}

void CalibrationWindow::on_signal_select_dialog(Gtk::FileChooserDialog* file_chooser, Gtk::Entry* entry){
  std::string str = file_chooser->get_filename();
  std::size_t sub_str = str.find_last_of("/\\");
  entry->set_text(str.substr(sub_str+1));
}

void CalibrationWindow::on_button_save_calibration(Gtk::FileChooserDialog* file_chooser, Gtk::Entry* entry){
  if (entry->get_text_length() > 0){
    std::stringstream aux;
    aux << file_chooser->get_current_folder() << "/" << entry->get_text();
    calibrationRepository->create(aux.str(), calibration);
    file_chooser->hide();
  }
}

void CalibrationWindow::on_button_load_calibration(Gtk::FileChooserDialog* file_chooser, Gtk::Entry* entry, std::vector<Gtk::Scale*> scale_cam_config){
  if (entry->get_text_length() > 0){
    calibration = calibrationRepository->read(file_chooser->get_filename());
    scale_cam_config[Saturation]->set_value(calibration.saturation);
    scale_cam_config[Brightness]->set_value(calibration.brightness);
    scale_cam_config[Exposure]->set_value(calibration.exposure);
    scale_cam_config[Contrast]->set_value(calibration.contrast);
    scale_cam_config[Rotation]->set_value(calibration.rotation);
    scale_cam_config[Gain]->set_value(calibration.gain);
    file_chooser->hide();
  }
}

void CalibrationWindow::on_button_load_dialog(Gtk::FileChooserDialog* file_chooser, Gtk::Entry* entry){
  entry->set_sensitive(false);
  file_chooser->show();
}

void CalibrationWindow::on_button_save_dialog(Gtk::FileChooserDialog* file_chooser, Gtk::Entry* entry){
  entry->set_sensitive(true);
  file_chooser->show();
}

void CalibrationWindow::on_combo_box_color_select(Gtk::ComboBoxText* color_select, std::vector<Gtk::Scale*> scale_hsv){
  auto actualColorToCalibrate = toColorType(color_select->get_active_text());
  applyActualColorRangeToSlidersHSV(actualColorToCalibrate, scale_hsv);
}

void CalibrationWindow::on_combo_box_color_team1(Gtk::ComboBoxText* color_team_1){
  std::cout << color_team_1->get_active_text() << std::endl;
}

void CalibrationWindow::on_combo_box_color_team2(Gtk::ComboBoxText* color_team_2){
  std::cout << color_team_2->get_active_text() << std::endl;
}

void CalibrationWindow::on_combo_box_color_robot1(Gtk::ComboBoxText* color_robot_1){
  std::cout << color_robot_1->get_active_text() << std::endl;
}

void CalibrationWindow::on_combo_box_color_robot2(Gtk::ComboBoxText* color_robot_2){
  std::cout << color_robot_2->get_active_text() << std::endl;
}

void CalibrationWindow::on_combo_box_color_robot3(Gtk::ComboBoxText* color_robot_3){
  std::cout << color_robot_3->get_active_text() << std::endl;
}

void CalibrationWindow::on_combo_box_color_robot4(Gtk::ComboBoxText* color_robot_4){
  std::cout << color_robot_4->get_active_text() << std::endl;
}

void CalibrationWindow::on_combo_box_color_robot5(Gtk::ComboBoxText* color_robot_5){
  std::cout << color_robot_5->get_active_text() << std::endl;
}

void CalibrationWindow::on_combo_box_input_path(Gtk::ComboBoxText* input_path){
  std::cout << input_path->get_active_text() << std::endl;
}

void CalibrationWindow::on_scale_h_max(Gtk::Scale* scale_h_max){
  calibration.colorsRange.at(actualColorRangeIndex).max[H] = static_cast<float>(scale_h_max->get_value());
  colorRecognizer->setColorRange(calibration.colorsRange.at(actualColorRangeIndex));
}

void CalibrationWindow::on_scale_h_min(Gtk::Scale* scale_h_min){
  calibration.colorsRange.at(actualColorRangeIndex).min[H] = static_cast<float>(scale_h_min->get_value());
  colorRecognizer->setColorRange(calibration.colorsRange.at(actualColorRangeIndex));
}

void CalibrationWindow::on_scale_s_max(Gtk::Scale* scale_s_max){
  calibration.colorsRange.at(actualColorRangeIndex).max[S] = static_cast<float>(scale_s_max->get_value());
  colorRecognizer->setColorRange(calibration.colorsRange.at(actualColorRangeIndex));
}

void CalibrationWindow::on_scale_s_min(Gtk::Scale* scale_s_min){
  calibration.colorsRange.at(actualColorRangeIndex).min[S] = static_cast<float>(scale_s_min->get_value());
  colorRecognizer->setColorRange(calibration.colorsRange.at(actualColorRangeIndex));
}

void CalibrationWindow::on_scale_v_max(Gtk::Scale* scale_v_max){
  calibration.colorsRange.at(actualColorRangeIndex).max[V] = static_cast<float>(scale_v_max->get_value());
  colorRecognizer->setColorRange(calibration.colorsRange.at(actualColorRangeIndex));
}

void CalibrationWindow::on_scale_v_min(Gtk::Scale* scale_v_min){
  calibration.colorsRange.at(actualColorRangeIndex).min[V] = static_cast<float>(scale_v_min->get_value());
  colorRecognizer->setColorRange(calibration.colorsRange.at(actualColorRangeIndex));
}

void CalibrationWindow::on_scale_rotation(Gtk::Scale* scale_rotation){
  calibration.rotation = static_cast<float>(scale_rotation->get_value());
}

void CalibrationWindow::on_scale_brightness(Gtk::Scale* scale_brightness){
  calibration.brightness = static_cast<float>(scale_brightness->get_value());
  inputReader->setBrightness(calibration.brightness);
}

void CalibrationWindow::on_scale_contrast(Gtk::Scale* scale_contrast){
  calibration.contrast = static_cast<float>(scale_contrast->get_value());
  inputReader->setContrast(calibration.contrast);
}

void CalibrationWindow::on_scale_saturation(Gtk::Scale* scale_saturation){
  calibration.saturation = static_cast<float>(scale_saturation->get_value());
  inputReader->setSaturation(calibration.saturation);
}

void CalibrationWindow::on_scale_exposure(Gtk::Scale* scale_exposure){
  calibration.exposure = static_cast<float>(scale_exposure->get_value());
}

void CalibrationWindow::on_scale_gain(Gtk::Scale* scale_gain){
  calibration.gain = static_cast<float>(scale_gain->get_value());
  inputReader->setGain(calibration.gain);
}

void CalibrationWindow::on_toggle_button_cut_mode(Gtk::ToggleButton* toggle_button_cut_mode){
  std::cout << toggle_button_cut_mode->get_active() << std::endl;
}

void CalibrationWindow::on_radio_button_image(Gtk::RadioButton* radio_button_image){
  if (!radio_button_image->get_active())
    std::cout << "Image: " << radio_button_image->get_active() << std::endl;
}
void CalibrationWindow::on_radio_button_video(Gtk::RadioButton* radio_button_video){
  if (!radio_button_video->get_active())
    std::cout << "Video: " << radio_button_video->get_active() << std::endl;
}
void CalibrationWindow::on_radio_button_camera(Gtk::RadioButton* radio_button_camera){
  if (!radio_button_camera->get_active())
    std::cout << "Camera: " << radio_button_camera->get_active() << std::endl;
}

void CalibrationWindow::applyActualColorRangeToSlidersHSV(ColorType type, std::vector<Gtk::Scale*> scale_hsv) {
  defineActualColorRange(type);

  scale_hsv[H_MAX]->set_value(calibration.colorsRange.at(actualColorRangeIndex).max[H]);
  scale_hsv[S_MAX]->set_value(calibration.colorsRange.at(actualColorRangeIndex).max[S]);
  scale_hsv[V_MAX]->set_value(calibration.colorsRange.at(actualColorRangeIndex).max[V]);

  scale_hsv[H_MIN]->set_value(calibration.colorsRange.at(actualColorRangeIndex).min[H]);
  scale_hsv[S_MIN]->set_value(calibration.colorsRange.at(actualColorRangeIndex).min[S]);
  scale_hsv[V_MIN]->set_value(calibration.colorsRange.at(actualColorRangeIndex).min[V]);
}

void CalibrationWindow::defineActualColorRange(ColorType type) {
  for(unsigned int i = 0 ; i < calibration.colorsRange.size() ; i++){
    if(calibration.colorsRange.at(i).colorType == type) {
      actualColorRangeIndex = i;
      break;
    }
  }
}

void CalibrationWindow::getAllAttributsFromCapture(bool signal) {
  scale_cam_config[Gain]->set_value(inputReader->getGain());
  scale_cam_config[Contrast]->set_value(inputReader->getContrast());
  scale_cam_config[Brightness]->set_value(inputReader->getBrightness());
  scale_cam_config[Saturation]->set_value(inputReader->getSaturation());
}
