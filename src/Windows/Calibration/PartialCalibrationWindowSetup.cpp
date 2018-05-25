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
#include <ImageFileReader.h>
#include <ColorRecognizer.h>
#include <Domain/ColorSpace.h>
#include <Windows/Calibration/CalibrationWindow.h>

CalibrationWindow::CalibrationWindow(){
  calibrationBuilder = new CalibrationBuilder();
  calibrationBuilderFromRepository = new CalibrationBuilder();

  calibrationBuilder->shouldInitializeColors(true);
  calibrationBuilder->shouldInitializeCuts(true);
  calibration = calibrationBuilder->getInstance();
  actualColorRangeIndex = 0;

  inputReader = new CameraReader();
  //inputReader = new ImageFileReader();

  colorRecognizer = new ColorRecognizer();

  calibrationRepository = new CalibrationRepository(calibrationBuilderFromRepository);
}

CalibrationWindow::~CalibrationWindow(){
}

int CalibrationWindow::run(int argc, char *argv[]){

  threadWindowControl = new thread( std::bind( &CalibrationWindow::windowThreadWrapper, this ));
  threadCameraReader = new thread( std::bind( &CalibrationWindow::cameraThreadWrapper, this ));

  threadWindowControl->join();
  threadCameraReader->detach();

  return MENU;
}

void CalibrationWindow::cameraThreadWrapper() {
  auto path = inputReader->getAllPossibleSources();
  inputReader->setSource(path.at(0));
  inputReader->start();
  inputReader->initializeReceivement();
}

void CalibrationWindow::windowThreadWrapper() {
  builderWidget();
  setSignals();
  initializeWidget();

  Gtk::Main::run(*window);
}

void CalibrationWindow::initializeWidget(){

  radioButtonImage->set_active();
  
  screenImage->set_image(cv::imread("../mock/images/model.jpg"));

  window->maximize();
  window->show_all_children();
}

void CalibrationWindow::builderWidget(){

  auto builder = Gtk::Builder::create();

  try {
    builder->add_from_file("../glade/Calibration.glade");

    builder->get_widget("window", window);

    builder->get_widget_derived("image", screenImage);

    builder->get_widget("button_save_calibration", buttonSave);
    builder->get_widget("button_load_calibration", buttonLoad);
    builder->get_widget("button_save_dialog", buttonOpenSaveDialog);
    builder->get_widget("button_load_dialog", buttonOpenLoadDialog);

    builder->get_widget("entry_chooser", entryChooserDialog);
    builder->get_widget("file_chooser_dialog", fileChooserDialog);

    scaleHSV.resize(6);
    builder->get_widget("hscale_hmax", scaleHSV[H_MAX]);
    builder->get_widget("hscale_hmin", scaleHSV[H_MIN]);
    builder->get_widget("hscale_smax", scaleHSV[S_MAX]);
    builder->get_widget("hscale_smin", scaleHSV[S_MIN]);
    builder->get_widget("hscale_vmax", scaleHSV[V_MAX]);
    builder->get_widget("hscale_vmin", scaleHSV[V_MIN]);

    scaleCameraConfig.resize(7);
    builder->get_widget("hscale_rotation", scaleCameraConfig[Rotation]);
    builder->get_widget("hscale_gain", scaleCameraConfig[Gain]);
    builder->get_widget("hscale_contrast", scaleCameraConfig[Contrast]);
    builder->get_widget("hscale_exposure", scaleCameraConfig[Exposure]);
    builder->get_widget("hscale_brightness", scaleCameraConfig[Brightness]);
    builder->get_widget("hscale_saturation", scaleCameraConfig[Saturation]);

    builder->get_widget("radiobutton_image", radioButtonImage);
    builder->get_widget("radiobutton_video", radioButtonVideo);
    builder->get_widget("radiobutton_camera", radioButtonCamera);

    builder->get_widget("combobox_path", comboBoxPath);
    builder->get_widget("combobox_color", comboBoxColor);
    
    builder->get_widget("togglebutton_cut_mode", toggleButtonCutMode);

  } catch(const Glib::FileError& ex) {
    std::cerr << "FileError: " << ex.what() << std::endl;

  } catch(const Glib::MarkupError& ex) {
    std::cerr << "MarkupError: " << ex.what() << std::endl;

  } catch(const Gtk::BuilderError& ex) {
    std::cerr << "BuilderError: " << ex.what() << std::endl;
  }
}

void CalibrationWindow::setSignals(){
  
  signal_set_new_frame.connect(sigc::mem_fun( this, &CalibrationWindow::setNewFrame) );

  inputReader->signal_new_frame.connect( sigc::mem_fun(this, &CalibrationWindow::receiveNewFrame) );
  inputReader->signal_loaded_capture.connect(sigc::mem_fun(this, &CalibrationWindow::getAllAttributsFromCapture));

  window->signal_key_press_event().connect(sigc::bind<Gtk::Window*>(sigc::mem_fun(this, &ICalibrationWindow::onKeyboard), window) , false);

  buttonOpenSaveDialog->signal_clicked().connect(sigc::bind<Gtk::FileChooserDialog*, Gtk::Entry*>(sigc::mem_fun(this, &ICalibrationWindow::onButtonOpenSaveDialog), fileChooserDialog, entryChooserDialog ));
  buttonOpenLoadDialog->signal_clicked().connect(sigc::bind<Gtk::FileChooserDialog*, Gtk::Entry*>(sigc::mem_fun(this, &ICalibrationWindow::onButtonOpenLoadDialog), fileChooserDialog, entryChooserDialog ));
  
  buttonSave->signal_clicked().connect(sigc::bind<Gtk::FileChooserDialog*, Gtk::Entry*>(sigc::mem_fun(this, &ICalibrationWindow::onButtonSave), fileChooserDialog, entryChooserDialog ));
  buttonLoad->signal_clicked().connect(sigc::bind<Gtk::FileChooserDialog*, Gtk::Entry*, std::vector<Gtk::Scale*>>(sigc::mem_fun(this, &ICalibrationWindow::onButtonLoad), fileChooserDialog, entryChooserDialog, scaleCameraConfig ));

  scaleHSV[H_MAX]->signal_value_changed().connect(sigc::bind<Gtk::Scale*>(sigc::mem_fun(this, &ICalibrationWindow::onScaleHMAX), scaleHSV[H_MAX]));
  scaleHSV[H_MIN]->signal_value_changed().connect(sigc::bind<Gtk::Scale*>(sigc::mem_fun(this, &ICalibrationWindow::onScaleHMIN), scaleHSV[H_MIN]));
  scaleHSV[S_MAX]->signal_value_changed().connect(sigc::bind<Gtk::Scale*>(sigc::mem_fun(this, &ICalibrationWindow::onScaleSMAX), scaleHSV[S_MAX]));
  scaleHSV[S_MIN]->signal_value_changed().connect(sigc::bind<Gtk::Scale*>(sigc::mem_fun(this, &ICalibrationWindow::onScaleSMIN), scaleHSV[S_MIN]));
  scaleHSV[V_MAX]->signal_value_changed().connect(sigc::bind<Gtk::Scale*>(sigc::mem_fun(this, &ICalibrationWindow::onScaleVMAX), scaleHSV[V_MAX]));
  scaleHSV[V_MIN]->signal_value_changed().connect(sigc::bind<Gtk::Scale*>(sigc::mem_fun(this, &ICalibrationWindow::onScaleVMIN), scaleHSV[V_MIN]));

  scaleCameraConfig[Gain]->signal_value_changed().connect(sigc::bind<Gtk::Scale*>(sigc::mem_fun(this, &ICalibrationWindow::onScaleGain), scaleCameraConfig[Gain]));
  scaleCameraConfig[Contrast]->signal_value_changed().connect(sigc::bind<Gtk::Scale*>(sigc::mem_fun(this, &ICalibrationWindow::onScaleContrast), scaleCameraConfig[Contrast]));
  scaleCameraConfig[Rotation]->signal_value_changed().connect(sigc::bind<Gtk::Scale*>(sigc::mem_fun(this, &ICalibrationWindow::onScaleRotation), scaleCameraConfig[Rotation]));
  scaleCameraConfig[Exposure]->signal_value_changed().connect(sigc::bind<Gtk::Scale*>(sigc::mem_fun(this, &ICalibrationWindow::onScaleExposure), scaleCameraConfig[Exposure]));
  scaleCameraConfig[Brightness]->signal_value_changed().connect(sigc::bind<Gtk::Scale*>(sigc::mem_fun(this, &ICalibrationWindow::onScaleBrightness), scaleCameraConfig[Brightness]));
  scaleCameraConfig[Saturation]->signal_value_changed().connect(sigc::bind<Gtk::Scale*>(sigc::mem_fun(this, &ICalibrationWindow::onScaleSaturation), scaleCameraConfig[Saturation]));

  radioButtonImage->signal_pressed().connect(sigc::bind<Gtk::RadioButton*>(sigc::mem_fun(this, &ICalibrationWindow::onRadioButtonImage), radioButtonImage));
  radioButtonVideo->signal_pressed().connect(sigc::bind<Gtk::RadioButton*>(sigc::mem_fun(this, &ICalibrationWindow::onRadioButtonVideo), radioButtonVideo));
  radioButtonCamera->signal_pressed().connect(sigc::bind<Gtk::RadioButton*>(sigc::mem_fun(this, &ICalibrationWindow::onRadioButtonCamera), radioButtonCamera));
  
  toggleButtonCutMode->signal_pressed().connect(sigc::bind<Gtk::ToggleButton*>(sigc::mem_fun(this, &ICalibrationWindow::onToggleButtonCutMode), toggleButtonCutMode));

  fileChooserDialog->signal_selection_changed().connect(sigc::bind<Gtk::FileChooserDialog*, Gtk::Entry*>(sigc::mem_fun(this, &ICalibrationWindow::onSignalSelectFileInDialog), fileChooserDialog, entryChooserDialog ));
  
  comboBoxPath->signal_changed().connect(sigc::bind<Gtk::ComboBox*>(sigc::mem_fun(this, &ICalibrationWindow::onComboBoxSelectPath), comboBoxPath));
  comboBoxColor->signal_changed().connect(sigc::bind<Gtk::ComboBox*, std::vector<Gtk::Scale*>>(sigc::mem_fun(this, &ICalibrationWindow::onComboBoxSelectColor), comboBoxColor, scaleHSV));
}