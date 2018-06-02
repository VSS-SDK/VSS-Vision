/*
* This file is part of the VSS-Vision project.
*
* This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
* v. 3.0. If a copy of the GPL was not distributed with this
* file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
*/

#ifndef VISION_WINDOW_H_
#define VISION_WINDOW_H_

#include <thread>
#include <gtkmm.h>
#include <iostream>

#include <CameraReader.h>
#include <ColorRecognizer.h>
#include <ImageFileReader.h>
#include <Domain/ProgramState.h>
#include <Interfaces/IImageInputReader.h>
#include <Domain/WhoseName.h>
#include <Domain/ColorType.h>
#include <Domain/ColorPosition.h>
#include <Interfaces/ICalibrationRepository.h>
#include <Interfaces/ICalibrationBuilder.h>
#include <Interfaces/IColorRecognizer.h>

#include <interface.h>
#include <Ball.h>
#include <Robot.h>
#include <Interfaces/IRobotRecognizer.h>
#include <RobotRecognizer.h>
#include "GImage.h"
#include "IVisionWindow.h"
#include "opencv2/highgui/highgui.hpp"

using namespace std;

class VisionWindow : public IVisionWindow {
public:
    VisionWindow();

    virtual ~VisionWindow();

    int run(int argc, char *argv[]) override;

    bool onKeyboard(GdkEventKey *, Gtk::Window *) override;

    void onButtonPlay() override;

    void onButtonLoad(Gtk::FileChooserDialog *) override;

    void onButtonOpenLoadDialog(Gtk::FileChooserDialog *) override;

    void onRadioButtonImage(Gtk::RadioButton *) override;

    void onRadioButtonVideo(Gtk::RadioButton *) override;

    void onRadioButtonCamera(Gtk::RadioButton *) override;

    void onComboBoxSelectPath(Gtk::ComboBox *) override;

    void onComboBoxSelectColorTeam1(Gtk::ComboBox *) override;

    void onComboBoxSelectColorTeam2(Gtk::ComboBox *) override;

    void onComboBoxSelectColorRobot1(Gtk::ComboBox *) override;

    void onComboBoxSelectColorRobot2(Gtk::ComboBox *) override;

    void onComboBoxSelectColorRobot3(Gtk::ComboBox *) override;

    void onComboBoxSelectColorRobot4(Gtk::ComboBox *) override;

    void onComboBoxSelectColorRobot5(Gtk::ComboBox *) override;

private:

    Interface interface;
    vss_state::Global_State global_state;

    // Threads
    std::thread *threadCameraReader;
    std::thread *threadWindowControl;

    // Comunication between threads
    Glib::Dispatcher signal_set_new_frame;

    // Classes
    IImageInputReader *inputReader;
    ICalibrationBuilder *calibrationBuilderFromRepository;
    ICalibrationRepository *calibrationRepository;
    IColorRecognizer *colorRecognizer;
    IRobotRecognizer *robotRecognizer;

    Calibration calibration;

    // Opencv image
    cv::Mat frame;

    // GTKMM - Calibration Window
    Gtk::Window *window = nullptr;

    GImage *screenImage = nullptr;

    Gtk::RadioButton *radioButtonImage = nullptr;
    Gtk::RadioButton *radioButtonVideo = nullptr;
    Gtk::RadioButton *radioButtonCamera = nullptr;

    Gtk::ComboBox *comboBoxPath = nullptr;
    Gtk::ComboBox *comboBoxColorTeam1 = nullptr;
    Gtk::ComboBox *comboBoxColorTeam2 = nullptr;
    Gtk::ComboBox *comboBoxColorRobot1 = nullptr;
    Gtk::ComboBox *comboBoxColorRobot2 = nullptr;
    Gtk::ComboBox *comboBoxColorRobot3 = nullptr;
    Gtk::ComboBox *comboBoxColorRobot4 = nullptr;
    Gtk::ComboBox *comboBoxColorRobot5 = nullptr;

    Gtk::Button *buttonLoad = nullptr;
    Gtk::Button *buttonPlay = nullptr;

    // GTKMM - File Chooser Window
    Gtk::FileChooserDialog *fileChooserDialog = nullptr;

    Gtk::Button *buttonOpenLoadDialog = nullptr;

    std::map<ColorType, WhoseName> whoseColor;

    // Control method
    void initializeWidget();

    void setSignals();

    void builderWidget();

    void initializeWhoseColor();

    void windowThreadWrapper();

    void cameraThreadWrapper();

    // Update frame
    void setNewFrame();

    void processFrame();

    void receiveNewFrame(cv::Mat);

    std::map<WhoseName, ColorPosition> getColorPosition();

    // Send state
    void sendState(std::vector<vss::Robot>, vss::Ball);

};

#endif
