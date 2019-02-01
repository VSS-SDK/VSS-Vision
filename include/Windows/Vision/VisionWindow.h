/*
* This file is part of the VSS-Vision project.
*
* This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
* v. 3.0. If a copy of the GPL was not distributed with this
* file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
*/

#ifndef VISION_WINDOW_H_
#define VISION_WINDOW_H_

#include <mutex>
#include <thread>
#include <iostream>
#include <gtkmm.h>

#include <CameraReader.h>
#include <ColorRecognizer.h>
#include <RobotRecognizer.h>
#include <PatternRecognizer.h>
#include <ImageFileReader.h>
#include <StateSenderAdapter.h>

#include "GImage.h"
#include "IVisionWindow.h"
#include "DefaultFilesPath.h"
#include "opencv2/highgui/highgui.hpp"

#include <Domain/Ball.h>
#include <Domain/Robot.h>
#include <Domain/ColorType.h>
#include <Domain/ObjectType.h>
#include <Domain/ProgramState.h>
#include <Domain/ColorPattern.h>
#include <Domain/ColorPosition.h>

#include <Interfaces/IInputReader.h>
#include <Interfaces/IColorRecognizer.h>
#include <Interfaces/IRobotRecognizer.h>
#include <Interfaces/ICalibrationBuilder.h>
#include <Interfaces/IPatternRecognizer.h>
#include <Interfaces/ICalibrationRepository.h>

#include <Helpers/FrameHelper.h>
#include <Helpers/TimeHelper.h>
#include <Helpers/Math.h>

using namespace std;

class VisionWindow : public IVisionWindow {
public:
    VisionWindow();
    virtual ~VisionWindow();

    int run(int argc, char *argv[]) override;

    bool onKeyboard(GdkEventKey *, Gtk::Window *) override;
    void onButtonPlay(Gtk::ToggleButton *) override;
    void onButtonOpenLoadDialog() override;
    void onRadioButtonImage(Gtk::RadioButton *) override;
    void onRadioButtonVideo(Gtk::RadioButton *) override;
    void onRadioButtonCamera(Gtk::RadioButton *) override;
    void onComboBoxSelectPath(Gtk::ComboBox *) override;
    void onComboBoxSelectColorTeam(Gtk::ComboBox *) override;
    void onComboBoxSelectColorPattern1(Gtk::ComboBox *) override;
    void onComboBoxSelectColorPattern2(Gtk::ComboBox *) override;
    void onComboBoxSelectColorPattern3(Gtk::ComboBox *) override;
    void onComboBoxSelectColorPattern4(Gtk::ComboBox *) override;
    void onComboBoxSelectColorPattern5(Gtk::ComboBox *) override;

private:
    // Threads
    std::thread *threadCameraReader;
    std::thread *threadWindowControl;

    mutable std::mutex mtxGetRobots;
    mutable std::mutex mutexFrame;
    mutable std::mutex mutexChangeInput;
    mutable std::mutex mtxPattern;
    mutable std::mutex mutexCalibration;
    mutable std::mutex mutexFPS;

    // Comunication between threads
    Glib::Dispatcher dispatcher_update_gtkmm_frame;
    sigc::connection connection_update_screen;

    // Classes
    IInputReader *inputReader;
    IStateSenderAdapter* stateSender;
    ICalibrationBuilder *calibrationBuilderFromRepository;
    ICalibrationRepository *calibrationRepository;

    IRobotRecognizer *robotRecognizer;
    IPatternRecognizer *patternRecognizer;

    std::vector<ColorType> mainColorList;
    std::vector<ObjectType> objectList;
    std::vector<ColorPattern> pattern;

    Calibration calibration;

    cv::Mat frame;
    TimeHelper timeHelper;

    bool playing;
    bool shouldReadInput;

    // GTKMM
    Gtk::Window *window = nullptr;
    GImage *screenImage = nullptr;

    Gtk::RadioButton *radioButtonImage = nullptr;
    Gtk::RadioButton *radioButtonVideo = nullptr;
    Gtk::RadioButton *radioButtonCamera = nullptr;

    Gtk::ComboBoxText *comboBoxPath = nullptr;
    Gtk::ComboBoxText *comboBoxColorTeam1 = nullptr;
    Gtk::ComboBoxText *comboBoxPattern1 = nullptr;
    Gtk::ComboBoxText *comboBoxPattern2 = nullptr;
    Gtk::ComboBoxText *comboBoxPattern3 = nullptr;
    Gtk::ComboBoxText *comboBoxPattern4 = nullptr;
    Gtk::ComboBoxText *comboBoxPattern5 = nullptr;

    Gtk::Label *labelPositionBall = nullptr;
    Gtk::Label *labelPositionRobot1 = nullptr;
    Gtk::Label *labelPositionRobot2 = nullptr;
    Gtk::Label *labelPositionRobot3 = nullptr;
    Gtk::Label *labelPositionRobot4 = nullptr;
    Gtk::Label *labelPositionRobot5 = nullptr;
    Gtk::Label *labelPositionOpponent1 = nullptr;
    Gtk::Label *labelPositionOpponent2 = nullptr;
    Gtk::Label *labelPositionOpponent3 = nullptr;
    Gtk::Label *labelPositionOpponent4 = nullptr;
    Gtk::Label *labelPositionOpponent5 = nullptr;

    Gtk::ToggleButton *buttonPlay = nullptr;
    Gtk::Button *buttonOpenLoadDialog = nullptr;

    // Control method
    void initializeWidget();
    void setSignals();
    void builderWidget();
    void windowThreadWrapper();
    void cameraThreadWrapper();

    // Update frame
    void processFrame(cv::Mat);
    void receiveNewFrame(cv::Mat);
    
    void updateGtkImage();
    bool emitUpdateGtkImage();
    
    void updateLabel(int, std::vector<vss::Robot>, std::vector<vss::Robot>, vss::Ball);
    void send(std::vector<vss::Robot>, std::vector<vss::Robot>, vss::Ball);
    cv::Mat drawRobot(cv::Mat, std::vector<vss::Robot> , std::vector<vss::Robot>, vss::Ball);
    };

#endif
