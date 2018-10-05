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

void CalibrationWindow::applyActualColorRangeToSlidersHSV(ColorType type, std::vector<Gtk::Scale*> scale) {

  for(unsigned int i = 0 ; i < calibration.colorsRange.size() ; i++) {
    if(calibration.colorsRange.at(i).colorType == type) actualColorRangeIndex = i;
  }

  scale[H_MAX]->set_value(calibration.colorsRange.at(actualColorRangeIndex).max[H]);
  scale[S_MAX]->set_value(calibration.colorsRange.at(actualColorRangeIndex).max[S]);
  scale[V_MAX]->set_value(calibration.colorsRange.at(actualColorRangeIndex).max[V]);

  scale[H_MIN]->set_value(calibration.colorsRange.at(actualColorRangeIndex).min[H]);
  scale[S_MIN]->set_value(calibration.colorsRange.at(actualColorRangeIndex).min[S]);
  scale[V_MIN]->set_value(calibration.colorsRange.at(actualColorRangeIndex).min[V]);
}

void CalibrationWindow::updateLabel(int i){
  string title = "CALIBRATION (" + to_string(i) + ")";
  window->set_title(title);
}

bool CalibrationWindow::onKeyboard(GdkEventKey* event, Gtk::Window* window){
  if(event->keyval == GDK_KEY_space) {
    // window->hide();
  } else if(event->keyval == GDK_KEY_Return) {
    window->hide();
  } else if(event->keyval == GDK_KEY_Escape) {
    window->hide();
  } else if(event->keyval == GDK_KEY_F1) {
    showBinaryImage = !showBinaryImage;
  }
  return true;
}

void CalibrationWindow::onButtonSave(Gtk::FileChooserDialog* fileChooser, Gtk::Entry* entry){
  string filename = entry->get_text();
  if (not filename.empty()){
    std::stringstream aux;
    aux << fileChooser->get_current_folder() << "/" << filename;
    calibrationRepository->create(aux.str(), calibration);
    fileChooser->hide();
  }
}

void CalibrationWindow::onButtonLoad(Gtk::FileChooserDialog* fileChooser, Gtk::Entry* entry, Gtk::Scale* scale_rotation){
  if (entry->get_text_length() > 0){
    calibration = calibrationRepository->read(fileChooser->get_filename());
    scale_rotation->set_value(calibration.rotation);
    fileChooser->hide();
  }
}

void CalibrationWindow::onToggleButtonCutMode(Gtk::ToggleButton* toggleButton){
  screenImage->set_cut_mode(!toggleButton->get_active());

  if (toggleButton->get_active()) {
    calibration.cut.resize(2);
    calibration.cut[0] = vss::Point(screenImage->get_cut_point_1().x, screenImage->get_cut_point_1().y);
    calibration.cut[1] = vss::Point(screenImage->get_cut_point_2().x, screenImage->get_cut_point_2().y);

    if(calibration.cut[1].x != 0 and calibration.cut[1].y != 0)
        calibration.shouldCropImage = true;
    else
        calibration.shouldCropImage = false;
  }
}

void CalibrationWindow::onButtonRestoreCut() {
    calibration.shouldCropImage = false;

    calibration.cut[0] = vss::Point(0,0);
    calibration.cut[1] = vss::Point(0,0);

    screenImage->set_cut_point_1(cv::Point(0,0));
    screenImage->set_cut_point_2(cv::Point(0,0));
}

void CalibrationWindow::onSignalSelectFileInDialog(Gtk::FileChooserDialog* fileChooser, Gtk::Entry* entry){
  std::string str = fileChooser->get_filename();
  std::size_t sub_str = str.find_last_of("/\\");
  entry->set_text(str.substr(sub_str+1));
}

void CalibrationWindow::onComboBoxSelectPath(Gtk::ComboBox* inputPath){
  // std::cout << inputPath->get_active_row_number() << std::endl;
}

void CalibrationWindow::onComboBoxSelectColor(Gtk::ComboBox* combobox, std::vector<Gtk::Scale*> scale){
  vector<string> color = {"Blue", "Yellow", "Orange", "Green", "Pink", "Purple", "Red", "Brown"};
  int row = combobox->get_active_row_number();
  auto actualColorToCalibrate = toColorType(color[row]);
  applyActualColorRangeToSlidersHSV(actualColorToCalibrate, scale);
}

void CalibrationWindow::onButtonOpenSaveDialog(Gtk::FileChooserDialog* fileChooser, Gtk::Entry* entry){
  entry->set_sensitive(true);
  buttonLoad->set_visible(false);
  buttonSave->set_visible(true);
  fileChooser->show();
}

void CalibrationWindow::onButtonOpenLoadDialog(Gtk::FileChooserDialog* fileChooser, Gtk::Entry* entry){
  entry->set_sensitive(false);
  buttonLoad->set_visible(true);
  buttonSave->set_visible(false);
  fileChooser->show();
}

void CalibrationWindow::onRadioButtonImage(Gtk::RadioButton* radioButton){
    if(inputReader) {
        mtxChangeInput.lock();
            inputReader->stopReceivement();
            inputReader = new ImageFileReader();
            inputReader->setSource(inputReader->getAllPossibleSources().at(0));
            inputReader->initializeReceivement();
        mtxChangeInput.unlock();
    }
}

void CalibrationWindow::onRadioButtonCamera(Gtk::RadioButton* radioButton){
    if(inputReader) {
        mtxChangeInput.lock();
            inputReader->stopReceivement();
            inputReader = new CameraReader();
            inputReader->setSource(inputReader->getAllPossibleSources().at(0));
            inputReader->initializeReceivement();
        mtxChangeInput.unlock();
    }
}

void CalibrationWindow::onRadioButtonVideo(Gtk::RadioButton* radioButton){
  //  if (!radioButton->get_active())
  //    std::cout << "Video: " << radioButton->get_active() << std::endl;
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

void CalibrationWindow::onScaleRotation(Gtk::Scale* scale){
  calibration.rotation = static_cast<float>(scale->get_value());
}