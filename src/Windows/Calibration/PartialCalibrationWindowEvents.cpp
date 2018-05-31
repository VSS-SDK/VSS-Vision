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

void CalibrationWindow::onButtonOpenSaveDialog(Gtk::FileChooserDialog* fileChooser, Gtk::Entry* entry){
  entry->set_sensitive(true);
  fileChooser->show();
}

void CalibrationWindow::onButtonOpenLoadDialog(Gtk::FileChooserDialog* fileChooser, Gtk::Entry* entry){
  entry->set_sensitive(false);
  fileChooser->show();
}

void CalibrationWindow::onButtonSave(Gtk::FileChooserDialog* fileChooser, Gtk::Entry* entry){
  if (entry->get_text_length() > 0){
    std::stringstream aux;
    aux << fileChooser->get_current_folder() << "/" << entry->get_text();
    calibrationRepository->create(aux.str(), calibration);
    fileChooser->hide();
  }
}

void CalibrationWindow::onButtonLoad(Gtk::FileChooserDialog* fileChooser, Gtk::Entry* entry, std::vector<Gtk::Scale*> scale_cam_config){
  if (entry->get_text_length() > 0){
    calibration = calibrationRepository->read(fileChooser->get_filename());
    scale_cam_config[Saturation]->set_value(calibration.saturation);
    scale_cam_config[Brightness]->set_value(calibration.brightness);
    scale_cam_config[Exposure]->set_value(calibration.exposure);
    scale_cam_config[Contrast]->set_value(calibration.contrast);
    scale_cam_config[Rotation]->set_value(calibration.rotation);
    scale_cam_config[Gain]->set_value(calibration.gain);
    fileChooser->hide();
  }
} 

void CalibrationWindow::onScaleHMAX(Gtk::Scale* scale){
  calibration.colorsRange.at(actualColorRangeIndex).max[H] = static_cast<float>(scale->get_value());
  colorRecognizer->setColorRange(calibration.colorsRange.at(actualColorRangeIndex));
}

void CalibrationWindow::onScaleHMIN(Gtk::Scale* scale){
  calibration.colorsRange.at(actualColorRangeIndex).min[H] = static_cast<float>(scale->get_value());
  colorRecognizer->setColorRange(calibration.colorsRange.at(actualColorRangeIndex));
}

void CalibrationWindow::onScaleSMAX(Gtk::Scale* scale){
  calibration.colorsRange.at(actualColorRangeIndex).max[S] = static_cast<float>(scale->get_value());
  colorRecognizer->setColorRange(calibration.colorsRange.at(actualColorRangeIndex));
}

void CalibrationWindow::onScaleSMIN(Gtk::Scale* scale){
  calibration.colorsRange.at(actualColorRangeIndex).min[S] = static_cast<float>(scale->get_value());
  colorRecognizer->setColorRange(calibration.colorsRange.at(actualColorRangeIndex));
}

void CalibrationWindow::onScaleVMAX(Gtk::Scale* scale){
  calibration.colorsRange.at(actualColorRangeIndex).max[V] = static_cast<float>(scale->get_value());
  colorRecognizer->setColorRange(calibration.colorsRange.at(actualColorRangeIndex));
}

void CalibrationWindow::onScaleVMIN(Gtk::Scale* scale){
  calibration.colorsRange.at(actualColorRangeIndex).min[V] = static_cast<float>(scale->get_value());
  colorRecognizer->setColorRange(calibration.colorsRange.at(actualColorRangeIndex));
}

void CalibrationWindow::onScaleGain(Gtk::Scale* scale){
  calibration.gain = static_cast<float>(scale->get_value());
  inputReader->setGain(calibration.gain);
}

void CalibrationWindow::onScaleContrast(Gtk::Scale* scale){
  calibration.contrast = static_cast<float>(scale->get_value());
  inputReader->setContrast(calibration.contrast);
}

void CalibrationWindow::onScaleRotation(Gtk::Scale* scale){
  calibration.rotation = static_cast<float>(scale->get_value());
}

void CalibrationWindow::onScaleExposure(Gtk::Scale* scale){
  calibration.exposure = static_cast<float>(scale->get_value());
}

void CalibrationWindow::onScaleBrightness(Gtk::Scale* scale){
  calibration.brightness = static_cast<float>(scale->get_value());
  inputReader->setBrightness(calibration.brightness);
}

void CalibrationWindow::onScaleSaturation(Gtk::Scale* scale){
  calibration.saturation = static_cast<float>(scale->get_value());
  inputReader->setSaturation(calibration.saturation);
}

void CalibrationWindow::onRadioButtonImage(Gtk::RadioButton* radioButton){
//  if (!radioButton->get_active())
//    std::cout << "Image: " << radioButton->get_active() << std::endl;
}

void CalibrationWindow::onRadioButtonVideo(Gtk::RadioButton* radioButton){
//  if (!radioButton->get_active())
//    std::cout << "Video: " << radioButton->get_active() << std::endl;
}

void CalibrationWindow::onRadioButtonCamera(Gtk::RadioButton* radioButton){
//  if (!radioButton->get_active())
//    std::cout << "Camera: " << radioButton->get_active() << std::endl;
}

void CalibrationWindow::onToggleButtonCutMode(Gtk::ToggleButton* toggleButton){
  screenImage->set_cut_mode(!toggleButton->get_active());
  
  if (toggleButton->get_active()) {
    calibration.cut.resize(2);
    calibration.cut[0] = Point2d(screenImage->get_cut_point_1().x, screenImage->get_cut_point_1().y);
    calibration.cut[1] = Point2d(screenImage->get_cut_point_2().x, screenImage->get_cut_point_2().y);

    calibration.shouldCropImage = true;
  }
}

void CalibrationWindow::onButtonRestoreCut() {
    calibration.shouldCropImage = false;

    calibration.cut[0] = Point2d(0,0);
    calibration.cut[1] = Point2d(0,0);

    screenImage->set_cut_point_1(cv::Point(0,0));
    screenImage->set_cut_point_2(cv::Point(0,0));
}

void CalibrationWindow::onSignalSelectFileInDialog(Gtk::FileChooserDialog* fileChooser, Gtk::Entry* entry){
  std::string str = fileChooser->get_filename();
  std::size_t sub_str = str.find_last_of("/\\");
  entry->set_text(str.substr(sub_str+1));
}

void CalibrationWindow::onComboBoxSelectPath(Gtk::ComboBox* inputPath){
//  std::cout << inputPath->get_active_row_number() << std::endl;
}

void CalibrationWindow::onComboBoxSelectColor(Gtk::ComboBox* combobox, std::vector<Gtk::Scale*> scale){
  vector<string> color = {"Blue", "Yellow", "Orange", "Green", "Pink", "Purple", "Red", "Brown"};
  int row = combobox->get_active_row_number();
  auto actualColorToCalibrate = toColorType(color[row]);
  applyActualColorRangeToSlidersHSV(actualColorToCalibrate, scale);
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

void CalibrationWindow::applyActualColorRangeToSlidersHSV(ColorType type, std::vector<Gtk::Scale*> scale) {
  defineActualColorRange(type);

  scale[H_MAX]->set_value(calibration.colorsRange.at(actualColorRangeIndex).max[H]);
  scale[S_MAX]->set_value(calibration.colorsRange.at(actualColorRangeIndex).max[S]);
  scale[V_MAX]->set_value(calibration.colorsRange.at(actualColorRangeIndex).max[V]);

  scale[H_MIN]->set_value(calibration.colorsRange.at(actualColorRangeIndex).min[H]);
  scale[S_MIN]->set_value(calibration.colorsRange.at(actualColorRangeIndex).min[S]);
  scale[V_MIN]->set_value(calibration.colorsRange.at(actualColorRangeIndex).min[V]);
}