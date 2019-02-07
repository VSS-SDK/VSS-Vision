/*
* This file is part of the VSS-Vision project.
*
* This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
* v. 3.0. If a copy of the GPL was not distributed with this
* file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
*/

#include <Windows/Vision/VisionWindow.h>
#include <Builders/CalibrationBuilder.h>
#include <Repositories/CalibrationRepository.h>

VisionWindow::VisionWindow() {

    calibrationBuilderFromRepository = new CalibrationBuilder();
    calibrationRepository = new CalibrationRepository(calibrationBuilderFromRepository);
    calibration = calibrationBuilderFromRepository->getInstance();

    inputReader = new ImageFileReader();

    robotRecognizer = new RobotRecognizer();
    patternRecognizer = new PatternRecognizer();

    stateSender = new vss::StateSender();
    stateSender->createSocket();

    playing = true;
    shouldReadInput = true;

    pattern.resize(9);
    
    mainColorList = {ColorType::Blue, ColorType::Yellow};
    objectList = {ObjectType::Robot1, ObjectType::Robot2, ObjectType::Robot3, ObjectType::Robot4, ObjectType::Robot5};
    listOptions = {"Robot 1", "Robot 2", "Robot 3", "Robot 4", "Robot 5"};
}

VisionWindow::~VisionWindow() {
    stateSender->closeSocket();
}

int VisionWindow::run(int argc, char *argv[]) {

    threadWindowControl = new thread(std::bind(&VisionWindow::windowThreadWrapper, this));
    threadCameraReader = new thread(std::bind(&VisionWindow::cameraThreadWrapper, this));

    threadWindowControl->join();
    threadCameraReader->detach();

    shouldReadInput = false;
    inputReader->stopReceivement();

    return MENU;
}

void VisionWindow::cameraThreadWrapper() {
    inputReader->setSource( inputReader->getAllPossibleSources().at(0) );
    inputReader->initializeReceivement();

    while(shouldReadInput) {
        mutexChangeInput.lock();
            cv::Mat receivedFrame = inputReader->getFrame();
        mutexChangeInput.unlock();

        receiveNewFrame( receivedFrame );
    }
}

void VisionWindow::windowThreadWrapper() {
    builderWidget();
    setSignals();
    initializeWidget();

    Gtk::Main::run(*window);
}

void VisionWindow::initializeWidget() {

    for (unsigned int i = 0; i < listOptions.size(); i++){
        comboBoxPattern1->append(to_string(i),listOptions[i]);
        comboBoxPattern2->append(to_string(i),listOptions[i]);
        comboBoxPattern3->append(to_string(i),listOptions[i]);
        comboBoxPattern4->append(to_string(i),listOptions[i]);
        comboBoxPattern5->append(to_string(i),listOptions[i]);
    }

    radioButtonImage->set_active();

    comboBoxColorTeam1->append("Blue");
    comboBoxColorTeam1->append("Yellow");

    screenImage->setImage(cv::imread(defaultFilesPath + "/mock/images/model.jpg"));

    window->maximize();
    window->show_all_children();
}

void VisionWindow::builderWidget() {

    auto builder = Gtk::Builder::create();

    try {
        builder->add_from_file(defaultFilesPath + "/glade/Vision.glade");

        builder->get_widget("window", window);

        builder->get_widget_derived("drawingarea_frame", screenImage);

        builder->get_widget("togglebutton_play", buttonPlay);
        builder->get_widget("button_load_dialog", buttonOpenLoadDialog);

        builder->get_widget("radiobutton_image", radioButtonImage);
        builder->get_widget("radiobutton_video", radioButtonVideo);
        builder->get_widget("radiobutton_camera", radioButtonCamera);

        builder->get_widget("combobox_path", comboBoxPath);
        builder->get_widget("combobox_team_1", comboBoxColorTeam1);
        builder->get_widget("combobox_pattern_1", comboBoxPattern1);
        builder->get_widget("combobox_pattern_2", comboBoxPattern2);
        builder->get_widget("combobox_pattern_3", comboBoxPattern3);
        builder->get_widget("combobox_pattern_4", comboBoxPattern4);
        builder->get_widget("combobox_pattern_5", comboBoxPattern5);

        builder->get_widget("label_position_bal", labelPositionBall);

        builder->get_widget("label_position_robot_1", labelPositionRobot1);
        builder->get_widget("label_position_robot_2", labelPositionRobot2);
        builder->get_widget("label_position_robot_3", labelPositionRobot3);
        builder->get_widget("label_position_robot_4", labelPositionRobot4);
        builder->get_widget("label_position_robot_5", labelPositionRobot5);

        builder->get_widget("label_position_opponent_1", labelPositionOpponent1);
        builder->get_widget("label_position_opponent_2", labelPositionOpponent2);
        builder->get_widget("label_position_opponent_3", labelPositionOpponent3);
        builder->get_widget("label_position_opponent_4", labelPositionOpponent4);
        builder->get_widget("label_position_opponent_5", labelPositionOpponent5);

        builder->get_widget("label_position_ball", labelBall);
        builder->get_widget("label_position_robot_1_1", labelRobot1);
        builder->get_widget("label_position_robot_2_2", labelRobot2);
        builder->get_widget("label_position_robot_3_3", labelRobot3);
        builder->get_widget("label_position_robot_4_4", labelRobot4);
        builder->get_widget("label_position_robot_5_5", labelRobot5);

        builder->get_widget("label_position_opponent_1_1", labelOpponent1);
        builder->get_widget("label_position_opponent_2_2", labelOpponent2);
        builder->get_widget("label_position_opponent_3_3", labelOpponent3);
        builder->get_widget("label_position_opponent_4_4", labelOpponent4);
        builder->get_widget("label_position_opponent_5_5", labelOpponent5);

    } catch (const Glib::FileError &ex) {
        std::cerr << "FileError: " << ex.what() << std::endl;

    } catch (const Glib::MarkupError &ex) {
        std::cerr << "MarkupError: " << ex.what() << std::endl;

    } catch (const Gtk::BuilderError &ex) {
        std::cerr << "BuilderError: " << ex.what() << std::endl;
    }
}

void VisionWindow::setSignals() {

    connection_update_screen = Glib::signal_timeout().connect(sigc::mem_fun( this, &VisionWindow::emitUpdateGtkImage), 16);
    dispatcher_update_gtkmm_frame.connect(sigc::mem_fun(this, &VisionWindow::updateGtkImage));

    window->signal_key_press_event().connect(sigc::bind<Gtk::Window *>(sigc::mem_fun(this, &IVisionWindow::onKeyboard), window), false);

    buttonPlay->signal_clicked().connect(sigc::bind<Gtk::ToggleButton *>(sigc::mem_fun(this, &IVisionWindow::onButtonPlay), buttonPlay));
    buttonOpenLoadDialog->signal_clicked().connect(sigc::mem_fun(this, &IVisionWindow::onButtonOpenLoadDialog));

    radioButtonImage->signal_pressed().connect(sigc::bind<Gtk::RadioButton *>(sigc::mem_fun(this, &IVisionWindow::onRadioButtonImage), radioButtonImage));
    radioButtonVideo->signal_pressed().connect(sigc::bind<Gtk::RadioButton *>(sigc::mem_fun(this, &IVisionWindow::onRadioButtonVideo), radioButtonVideo));
    radioButtonCamera->signal_pressed().connect(sigc::bind<Gtk::RadioButton *>(sigc::mem_fun(this, &IVisionWindow::onRadioButtonCamera), radioButtonCamera));

    comboBoxPath->signal_changed().connect(sigc::bind<Gtk::ComboBoxText *>(sigc::mem_fun(this, &IVisionWindow::onComboBoxSelectPath), comboBoxPath));
    comboBoxColorTeam1->signal_changed().connect(sigc::bind<Gtk::ComboBoxText *>(sigc::mem_fun(this, &IVisionWindow::onComboBoxSelectColorTeam), comboBoxColorTeam1));
    comboBoxPattern1->signal_changed().connect(sigc::bind<Gtk::ComboBoxText *>(sigc::mem_fun(this, &IVisionWindow::onComboBoxSelectColorPattern1), comboBoxPattern1));
    comboBoxPattern2->signal_changed().connect(sigc::bind<Gtk::ComboBoxText *>(sigc::mem_fun(this, &IVisionWindow::onComboBoxSelectColorPattern2), comboBoxPattern2));
    comboBoxPattern3->signal_changed().connect(sigc::bind<Gtk::ComboBoxText *>(sigc::mem_fun(this, &IVisionWindow::onComboBoxSelectColorPattern3), comboBoxPattern3));
    comboBoxPattern4->signal_changed().connect(sigc::bind<Gtk::ComboBoxText *>(sigc::mem_fun(this, &IVisionWindow::onComboBoxSelectColorPattern4), comboBoxPattern4));
    comboBoxPattern5->signal_changed().connect(sigc::bind<Gtk::ComboBoxText *>(sigc::mem_fun(this, &IVisionWindow::onComboBoxSelectColorPattern5), comboBoxPattern5));
}