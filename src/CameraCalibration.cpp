/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include <Domain/ColorSpace.h>
#include "CameraCalibration.h"

CameraCalibration::CameraCalibration(ICalibrationRepository *calibrationRepository, ICalibrationFactory *calibrationFactory){
  this->calibrationRepository = calibrationRepository;
  this->calibrationFactory = calibrationFactory;

  actualColorToCalibrate = ColorType::UnknownType;
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

void CameraCalibration::on_signal_select_dialog(Gtk::FileChooserDialog* file_chooser, Gtk::Entry* entry){
  std::string str = file_chooser->get_filename();
  std::size_t sub_str = str.find_last_of("/\\");
  entry->set_text(str.substr(sub_str+1));
}

void CameraCalibration::on_button_save_calibration(Gtk::FileChooserDialog* file_chooser, Gtk::Entry* entry){
  if (entry->get_text_length() > 0){
    std::stringstream aux;
    aux << file_chooser->get_current_folder() << "/" << entry->get_text();
    calibrationRepository->create(aux.str(), calibration);
    file_chooser->hide();
  }
}

void CameraCalibration::on_button_load_calibration(Gtk::FileChooserDialog* file_chooser, Gtk::Entry* entry){
  if (entry->get_text_length() > 0){
    calibration = calibrationRepository->read(file_chooser->get_filename());
    scale_saturation->set_value(calibration.saturation);
    scale_brightness->set_value(calibration.brightness);
    scale_exposure->set_value(calibration.exposure);
    scale_contrast->set_value(calibration.contrast);
    scale_rotation->set_value(calibration.rotation);
    scale_gain->set_value(calibration.gain);
    file_chooser->hide();    
  }
}

void CameraCalibration::on_button_load_dialog(Gtk::FileChooserDialog* file_chooser, Gtk::Entry* entry){
  entry->set_sensitive(false);
  file_chooser->show();
}

void CameraCalibration::on_button_save_dialog(Gtk::FileChooserDialog* file_chooser, Gtk::Entry* entry){
  entry->set_sensitive(true);  
  file_chooser->show();    
}

void CameraCalibration::on_combo_box_color_select(Gtk::ComboBoxText* color_select){
  actualColorToCalibrate = toColorType(color_select->get_active_text());
  applyActualColorRangeToSlidersHSV(actualColorToCalibrate);
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
  setColorRangePart(ColorRangePart::H_MAX, scale_h_max->get_value());
}

void CameraCalibration::on_scale_h_min(Gtk::Scale* scale_h_min){
  setColorRangePart(ColorRangePart::H_MIN, scale_h_min->get_value());
}

void CameraCalibration::on_scale_s_max(Gtk::Scale* scale_s_max){
  setColorRangePart(ColorRangePart::S_MAX, scale_s_max->get_value());
}

void CameraCalibration::on_scale_s_min(Gtk::Scale* scale_s_min){
  setColorRangePart(ColorRangePart::S_MIN, scale_s_min->get_value());
}

void CameraCalibration::on_scale_v_max(Gtk::Scale* scale_v_max){
  setColorRangePart(ColorRangePart::V_MAX, scale_v_max->get_value());
}

void CameraCalibration::on_scale_v_min(Gtk::Scale* scale_v_min){
  setColorRangePart(ColorRangePart::V_MIN, scale_v_min->get_value());
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

void CameraCalibration::applyActualColorRangeToSlidersHSV(ColorType type) {
  auto colorRange = getColorRangeFromCalibration(type);

  scale_h_max->set_value(colorRange.max[H]);
  scale_s_max->set_value(colorRange.max[S]);
  scale_v_max->set_value(colorRange.max[V]);

  scale_h_min->set_value(colorRange.min[H]);
  scale_s_min->set_value(colorRange.min[S]);
  scale_v_min->set_value(colorRange.min[V]);
}

ColorRange CameraCalibration::getColorRangeFromCalibration(ColorType type) {
  std::cout << calibration << std::endl;
  for (auto& colorRange : calibration.colorsRange) {
    if(colorRange.colorType == type)
      return colorRange;
  }

  return new ColorRange();
}

void CameraCalibration::setColorRangePart(ColorRangePart part, double value) {
  for (auto& colorRange : calibration.colorsRange) {
    if(colorRange.colorType == actualColorToCalibrate){
      switch (part){
        case ColorRangePart::H_MAX:
          colorRange.max[H] = static_cast<float>(value);
          break;
        case ColorRangePart::H_MIN:
          colorRange.min[H] = static_cast<float>(value);
          break;
        case ColorRangePart::S_MAX:
          colorRange.max[S] = static_cast<float>(value);
          break;
        case ColorRangePart::S_MIN:
          colorRange.min[S] = static_cast<float>(value);
          break;
        case ColorRangePart::V_MAX:
          colorRange.max[V] = static_cast<float>(value);
          break;
        case ColorRangePart::V_MIN:
          colorRange.min[V] = static_cast<float>(value);
          break;
      }
    }
  }
}
