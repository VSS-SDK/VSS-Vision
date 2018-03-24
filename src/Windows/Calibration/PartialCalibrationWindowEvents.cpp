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

bool CalibrationWindow::onKeyboard(GdkEventKey* event, Gtk::Window* window){
  if(event->keyval == GDK_KEY_space) {
    window->hide();
  } else if(event->keyval == GDK_KEY_Return) {
    window->hide();
  } else if(event->keyval == GDK_KEY_Escape) {
    window->hide();
  }
  return true;
}

void CalibrationWindow::onButtonOpenSaveDialog(Gtk::FileChooserDialog* file_chooser, Gtk::Entry* entry){
  entry->set_sensitive(false);
  file_chooser->show();
}

void CalibrationWindow::onButtonOpenLoadDialog(Gtk::FileChooserDialog* file_chooser, Gtk::Entry* entry){
  entry->set_sensitive(true);
  file_chooser->show();
}

void CalibrationWindow::onButtonSave(Gtk::FileChooserDialog* file_chooser, Gtk::Entry* entry){
  if (entry->get_text_length() > 0){
    std::stringstream aux;
    aux << file_chooser->get_current_folder() << "/" << entry->get_text();
    calibrationRepository->create(aux.str(), calibration);
    file_chooser->hide();
  }
}

void CalibrationWindow::onButtonLoad(Gtk::FileChooserDialog* file_chooser, Gtk::Entry* entry, std::vector<Gtk::Scale*> scale_cam_config){
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

void CalibrationWindow::onScaleHMAX(Gtk::Scale* scale_h_max){
  calibration.colorsRange.at(actualColorRangeIndex).max[H] = static_cast<float>(scale_h_max->get_value());
  colorRecognizer->setColorRange(calibration.colorsRange.at(actualColorRangeIndex));
}

void CalibrationWindow::onScaleHMIN(Gtk::Scale* scale_h_min){
  calibration.colorsRange.at(actualColorRangeIndex).min[H] = static_cast<float>(scale_h_min->get_value());
  colorRecognizer->setColorRange(calibration.colorsRange.at(actualColorRangeIndex));
}

void CalibrationWindow::onScaleSMAX(Gtk::Scale* scale_s_max){
  calibration.colorsRange.at(actualColorRangeIndex).max[S] = static_cast<float>(scale_s_max->get_value());
  colorRecognizer->setColorRange(calibration.colorsRange.at(actualColorRangeIndex));
}

void CalibrationWindow::onScaleSMIN(Gtk::Scale* scale_s_min){
  calibration.colorsRange.at(actualColorRangeIndex).min[S] = static_cast<float>(scale_s_min->get_value());
  colorRecognizer->setColorRange(calibration.colorsRange.at(actualColorRangeIndex));
}

void CalibrationWindow::onScaleVMAX(Gtk::Scale* scale_v_max){
  calibration.colorsRange.at(actualColorRangeIndex).max[V] = static_cast<float>(scale_v_max->get_value());
  colorRecognizer->setColorRange(calibration.colorsRange.at(actualColorRangeIndex));
}

void CalibrationWindow::onScaleVMIN(Gtk::Scale* scale_v_min){
  calibration.colorsRange.at(actualColorRangeIndex).min[V] = static_cast<float>(scale_v_min->get_value());
  colorRecognizer->setColorRange(calibration.colorsRange.at(actualColorRangeIndex));
}

void CalibrationWindow::onScaleGain(Gtk::Scale* scale_gain){
  calibration.gain = static_cast<float>(scale_gain->get_value());
  inputReader->setGain(calibration.gain);
}

void CalibrationWindow::onScaleContrast(Gtk::Scale* scale_contrast){
  calibration.contrast = static_cast<float>(scale_contrast->get_value());
  inputReader->setContrast(calibration.contrast);
}

void CalibrationWindow::onScaleRotation(Gtk::Scale* scale_rotation){
  calibration.rotation = static_cast<float>(scale_rotation->get_value());
}

void CalibrationWindow::onScaleExposure(Gtk::Scale* scale_exposure){
  calibration.exposure = static_cast<float>(scale_exposure->get_value());
}

void CalibrationWindow::onScaleBrightness(Gtk::Scale* scale_brightness){
  calibration.brightness = static_cast<float>(scale_brightness->get_value());
  inputReader->setBrightness(calibration.brightness);
}

void CalibrationWindow::onScaleSaturation(Gtk::Scale* scale_saturation){
  calibration.saturation = static_cast<float>(scale_saturation->get_value());
  inputReader->setSaturation(calibration.saturation);
}

void CalibrationWindow::onRadioButtonImage(Gtk::RadioButton* radio_button_image){
//  if (!radio_button_image->get_active())
//    std::cout << "Image: " << radio_button_image->get_active() << std::endl;
}

void CalibrationWindow::onRadioButtonVideo(Gtk::RadioButton* radio_button_video){
//  if (!radio_button_video->get_active())
//    std::cout << "Video: " << radio_button_video->get_active() << std::endl;
}

void CalibrationWindow::onRadioButtonCamera(Gtk::RadioButton* radio_button_camera){
//  if (!radio_button_camera->get_active())
//    std::cout << "Camera: " << radio_button_camera->get_active() << std::endl;
}

void CalibrationWindow::onToggleButtonCutMode(Gtk::ToggleButton* toggle_button_cut_mode){
//  std::cout << toggle_button_cut_mode->get_active() << std::endl;
}

void CalibrationWindow::onSignalSelectFileInDialog(Gtk::FileChooserDialog* file_chooser, Gtk::Entry* entry){
  std::string str = file_chooser->get_filename();
  std::size_t sub_str = str.find_last_of("/\\");
  entry->set_text(str.substr(sub_str+1));
}

void CalibrationWindow::onComboBoxSelectPath(Gtk::ComboBox* input_path){
//  std::cout << input_path->get_active_row_number() << std::endl;
}

void CalibrationWindow::onComboBoxSelectColor(Gtk::ComboBox* color_select, std::vector<Gtk::Scale*> scale_hsv){
  vector<string> color = {"Blue", "Yellow", "Orange", "Green", "Pink", "Purple", "Red", "Brown"};
  int row = color_select->get_active_row_number();
  auto actualColorToCalibrate = toColorType(color[row]);
  applyActualColorRangeToSlidersHSV(actualColorToCalibrate, scale_hsv);
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
  scaleCameraConfig[Gain]->set_value(inputReader->getGain());
  scaleCameraConfig[Contrast]->set_value(inputReader->getContrast());
  scaleCameraConfig[Brightness]->set_value(inputReader->getBrightness());
  scaleCameraConfig[Saturation]->set_value(inputReader->getSaturation());
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