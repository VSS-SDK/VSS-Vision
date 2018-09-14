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
#include <mutex>
#include <gtkmm.h>
#include <iostream>

#include "DefaultFilesPath.h"
#include <CameraReader.h>
#include <ColorRecognizer.h>
#include <ImageFileReader.h>
#include <Domain/ProgramState.h>
#include <Domain/ObjectType.h>
#include <Domain/ColorType.h>
#include <Domain/ColorPattern.h>
#include <Domain/ColorPosition.h>
#include <Interfaces/IInputReader.h>
#include <Interfaces/ICalibrationRepository.h>
#include <Interfaces/ICalibrationBuilder.h>
#include <Interfaces/IColorRecognizer.h>
#include <Helpers/FrameHelper.h>
#include <Helpers/TimeHelper.h>
#include <Helpers/Math.h>
#include <Domain/Ball.h>
#include <Domain/Robot.h>
#include <Interfaces/IRobotRecognizer.h>
#include <RobotRecognizer.h>
#include <StateSenderAdapter.h>
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
    void onButtonPlay(Gtk::ToggleButton *) override;
    void onButtonLoad(Gtk::FileChooserDialog *) override;
    void onButtonOpenLoadDialog(Gtk::FileChooserDialog *) override;
    void onRadioButtonImage(Gtk::RadioButton *) override;
    void onRadioButtonVideo(Gtk::RadioButton *) override;
    void onRadioButtonCamera(Gtk::RadioButton *) override;
    void onComboBoxSelectPath(Gtk::ComboBox *) override;
    void onComboBoxSelectColorTeam(Gtk::ComboBox *) override;
    void onComboBoxSelectColorOpponent(Gtk::ComboBox *) override;
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
    mutable std::mutex mtxUpdateFrame;
    mutable std::mutex mtxChangeInput;

    // Comunication between threads
    Glib::Dispatcher dispatcher_update_gtkmm_frame;

    // Classes
    IInputReader *inputReader;
    IStateSenderAdapter* stateSender;
    ICalibrationBuilder *calibrationBuilderFromRepository;
    ICalibrationRepository *calibrationRepository;

    IRobotRecognizer *robotRecognizer;

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

    Gtk::ComboBox *comboBoxPath = nullptr;
    Gtk::ComboBox *comboBoxColorTeam1 = nullptr;
    Gtk::ComboBox *comboBoxColorTeam2 = nullptr;
    Gtk::ComboBox *comboBoxPattern1 = nullptr;
    Gtk::ComboBox *comboBoxPattern2 = nullptr;
    Gtk::ComboBox *comboBoxPattern3 = nullptr;
    Gtk::ComboBox *comboBoxPattern4 = nullptr;
    Gtk::ComboBox *comboBoxPattern5 = nullptr;

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

    Gtk::Button *buttonLoad = nullptr;
    Gtk::ToggleButton *buttonPlay = nullptr;

    // GTKMM - File Chooser Window
    Gtk::FileChooserDialog *fileChooserDialog = nullptr;
    Gtk::Button *buttonOpenLoadDialog = nullptr;

    // Control method
    void initializeWidget();
    void setSignals();
    void builderWidget();
    void windowThreadWrapper();
    void cameraThreadWrapper();

    // Update frame
    void processFrame(cv::Mat);
    void updateGtkImage();
    void receiveNewFrame(cv::Mat);
    void updateLabel(int);
    void send(std::vector<vss::Robot>, std::vector<vss::Robot>, vss::Ball);
    };

#endif
