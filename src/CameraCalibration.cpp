/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "CameraCalibration.h"

CameraCalibration::CameraCalibration(ICalibrationRepository *calibrationRepository){
  this->calibrationRepository = calibrationRepository;
}

bool CameraCalibration::on_keyboard(GdkEventKey* event, Gtk::Window* window){
  if(event->keyval == GDK_KEY_space) {
    window->hide();
  } else if(event->keyval == GDK_KEY_Return) {
    window->hide();
  } else if(event->keyval == GDK_KEY_Escape) {
    window->hide();
  }
  return true;
}

void CameraCalibration::on_button_load(Gtk::FileChooserDialog* file_chooser){
  calibration = calibrationRepository->read(file_chooser->get_filename());

  scale_saturation->set_value(calibration.saturation);
  scale_brightness->set_value(calibration.brightness);
  scale_exposure->set_value(calibration.exposure);
  scale_contrast->set_value(calibration.contrast);
  scale_rotation->set_value(calibration.rotation);
  scale_gain->set_value(calibration.gain);
}

void CameraCalibration::on_button_save(Gtk::Entry* entry){
    std::cout << entry->get_text() << std::endl;
}

void CameraCalibration::on_button_load_save(Gtk::FileChooserDialog* file_chooser){
  file_chooser->show();
}

void CameraCalibration::on_combo_box_color_select(Gtk::ComboBoxText* color_select){
  std::cout << color_select->get_active_text() << std::endl;
}

void CameraCalibration::on_combo_box_color_team1(Gtk::ComboBoxText* color_team_1){
  std::cout << color_team_1->get_active_text() << std::endl;
}

void CameraCalibration::on_combo_box_color_team2(Gtk::ComboBoxText* color_team_2){
  std::cout << color_team_2->get_active_text() << std::endl;
}

void CameraCalibration::on_combo_box_color_robot1(Gtk::ComboBoxText* color_robot_1){
  std::cout << color_robot_1->get_active_text() << std::endl;
}

void CameraCalibration::on_combo_box_color_robot2(Gtk::ComboBoxText* color_robot_2){
  std::cout << color_robot_2->get_active_text() << std::endl;
}

void CameraCalibration::on_combo_box_color_robot3(Gtk::ComboBoxText* color_robot_3){
  std::cout << color_robot_3->get_active_text() << std::endl;
}

void CameraCalibration::on_combo_box_color_robot4(Gtk::ComboBoxText* color_robot_4){
  std::cout << color_robot_4->get_active_text() << std::endl;
}

void CameraCalibration::on_combo_box_color_robot5(Gtk::ComboBoxText* color_robot_5){
  std::cout << color_robot_5->get_active_text() << std::endl;
}

void CameraCalibration::on_combo_box_input_path(Gtk::ComboBoxText* input_path){
  std::cout << input_path->get_active_text() << std::endl;
}

void CameraCalibration::on_scale_h_max(Gtk::Scale* scale_h_max){
  std::cout << scale_h_max->get_value() << std::endl;
}

void CameraCalibration::on_scale_h_min(Gtk::Scale* scale_h_min){
  std::cout << scale_h_min->get_value() << std::endl;
}

void CameraCalibration::on_scale_s_max(Gtk::Scale* scale_s_max){
  std::cout << scale_s_max->get_value() << std::endl;
}

void CameraCalibration::on_scale_s_min(Gtk::Scale* scale_s_min){
  std::cout << scale_s_min->get_value() << std::endl;
}

void CameraCalibration::on_scale_v_max(Gtk::Scale* scale_v_max){
  std::cout << scale_v_max->get_value() << std::endl;
}

void CameraCalibration::on_scale_v_min(Gtk::Scale* scale_v_min){
  std::cout << scale_v_min->get_value() << std::endl;
}

void CameraCalibration::on_scale_rotation(Gtk::Scale* scale_rotation){
  std::cout << scale_rotation->get_value() << std::endl;
  calibration.rotation = (float)scale_rotation->get_value();
}

void CameraCalibration::on_scale_brightness(Gtk::Scale* scale_brightness){
  std::cout << scale_brightness->get_value() << std::endl;
  calibration.brightness = (float)scale_brightness->get_value();
}

void CameraCalibration::on_scale_contrast(Gtk::Scale* scale_contrast){
  std::cout << scale_contrast->get_value() << std::endl;
  calibration.contrast = (float)scale_contrast->get_value();

}

void CameraCalibration::on_scale_saturation(Gtk::Scale* scale_saturation){
  std::cout << scale_saturation->get_value() << std::endl;
  calibration.saturation = (float)scale_saturation->get_value();
}

void CameraCalibration::on_scale_exposure(Gtk::Scale* scale_exposure){
  std::cout << scale_exposure->get_value() << std::endl;
  calibration.exposure = (float)scale_exposure->get_value();
}

void CameraCalibration::on_scale_gain(Gtk::Scale* scale_gain){
  std::cout << scale_gain->get_value() << std::endl;
  calibration.gain = (float)scale_gain->get_value();
}

void CameraCalibration::on_toggle_button_cut_mode(Gtk::ToggleButton* toggle_button_cut_mode){
    std::cout << toggle_button_cut_mode->get_active() << std::endl;
}

void CameraCalibration::on_radio_button_image(Gtk::RadioButton* radio_button_image){
  if (!radio_button_image->get_active())
    std::cout << "Image: " << radio_button_image->get_active() << std::endl;
}
void CameraCalibration::on_radio_button_video(Gtk::RadioButton* radio_button_video){
  if (!radio_button_video->get_active())
    std::cout << "Video: " << radio_button_video->get_active() << std::endl;
}
void CameraCalibration::on_radio_button_camera(Gtk::RadioButton* radio_button_camera){
  if (!radio_button_camera->get_active())
    std::cout << "Camera: " << radio_button_camera->get_active() << std::endl;
}

void CameraCalibration::bind_scale_h_max(Gtk::Scale *scale_h_max) {
  this->scale_h_max = scale_h_max;
}

void CameraCalibration::bind_scale_h_min(Gtk::Scale *scale_h_min) {
  this->scale_h_min = scale_h_min;
}

void CameraCalibration::bind_scale_s_max(Gtk::Scale *scale_s_max) {
  this->scale_s_max = scale_s_max;
}

void CameraCalibration::bind_scale_s_min(Gtk::Scale *scale_s_min) {
  this->scale_s_min = scale_s_min;
}

void CameraCalibration::bind_scale_v_max(Gtk::Scale *scale_v_max) {
  this->scale_v_max = scale_v_max;
}

void CameraCalibration::bind_scale_v_min(Gtk::Scale *scale_v_min) {
  this->scale_v_min = scale_v_min;
}

void CameraCalibration::bind_scale_gain(Gtk::Scale *scale_gain) {
  this->scale_gain = scale_gain;
}

void CameraCalibration::bind_scale_contrast(Gtk::Scale *scale_contrast) {
  this->scale_contrast = scale_contrast;
}

void CameraCalibration::bind_scale_rotation(Gtk::Scale *scale_rotation) {
  this->scale_rotation = scale_rotation;
}

void CameraCalibration::bind_scale_exposure(Gtk::Scale *scale_exposure) {
  this->scale_exposure = scale_exposure;
}

void CameraCalibration::bind_scale_brightness(Gtk::Scale *scale_brightness) {
  this->scale_brightness = scale_brightness;
}

void CameraCalibration::bind_scale_saturation(Gtk::Scale *scale_saturation) {
  this->scale_saturation = scale_saturation;
}
