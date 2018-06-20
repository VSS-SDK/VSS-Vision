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
    colorRecognizer = new ColorRecognizer();
    robotRecognizer = new RobotRecognizer();

    stateSender = new StateSenderAdapter();
    stateSender->createSocket();

    playing = true;
    shouldReadInput = true;
}

VisionWindow::~VisionWindow() = default;

int VisionWindow::run(int argc, char *argv[]) {

    threadWindowControl = new thread(std::bind(&VisionWindow::windowThreadWrapper, this));
    threadCameraReader = new thread(std::bind(&VisionWindow::cameraThreadWrapper, this));

    threadWindowControl->join();

    inputReader->close();
    shouldReadInput = false;
    threadCameraReader->detach();

    return MENU;
}

void VisionWindow::cameraThreadWrapper() {
    configureInputReceivement(inputReader);

    while(shouldReadInput) {
        inputReader->initializeReceivement();
    }
}

void VisionWindow::windowThreadWrapper() {
    builderWidget();
    setSignals();
    initializeWidget();
    initializeWhoseColor();

    Gtk::Main::run(*window);
}

void VisionWindow::configureInputReceivement(IInputReader* input){
    input->signal_new_frame_from_reader.connect(sigc::mem_fun(this, &VisionWindow::receiveNewFrame));

    auto path = input->getAllPossibleSources();
    input->setSource(path.at(0));
    input->start();
}

void VisionWindow::initializeWidget() {

    radioButtonImage->set_active();

    screenImage->set_image(cv::imread(defaultFilesPath + "/mock/images/model.jpg"));

    // show only .txt files
    auto filterText = fileChooserDialog->get_filter();
    filterText->set_name("Text files");
    filterText->add_pattern("*.txt");
    fileChooserDialog->add_filter(*filterText);

    // define initial folder for file chooser
    fileChooserDialog->set_current_folder(defaultFilesPath + "/data");

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
        builder->get_widget("button_load_calibration", buttonLoad);
        builder->get_widget("button_load_dialog", buttonOpenLoadDialog);

        builder->get_widget("file_chooser_dialog", fileChooserDialog);

        builder->get_widget("radiobutton_image", radioButtonImage);
        builder->get_widget("radiobutton_video", radioButtonVideo);
        builder->get_widget("radiobutton_camera", radioButtonCamera);

        builder->get_widget("combobox_path", comboBoxPath);
        builder->get_widget("combobox_team_1", comboBoxColorTeam1);
        builder->get_widget("combobox_team_2", comboBoxColorTeam2);
        builder->get_widget("combobox_robot_1", comboBoxColorRobot1);
        builder->get_widget("combobox_robot_2", comboBoxColorRobot2);
        builder->get_widget("combobox_robot_3", comboBoxColorRobot3);
        builder->get_widget("combobox_robot_4", comboBoxColorRobot4);
        builder->get_widget("combobox_robot_5", comboBoxColorRobot5);

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

    } catch (const Glib::FileError &ex) {
        std::cerr << "FileError: " << ex.what() << std::endl;

    } catch (const Glib::MarkupError &ex) {
        std::cerr << "MarkupError: " << ex.what() << std::endl;

    } catch (const Gtk::BuilderError &ex) {
        std::cerr << "BuilderError: " << ex.what() << std::endl;
    }
}

void VisionWindow::setSignals() {
    dispatcher_update_gtkmm_frame.connect(sigc::mem_fun(this, &VisionWindow::updateGtkImage));
    signalRobotsNewPositions.connect(sigc::mem_fun(this, &VisionWindow::onRobotsNewPositions));

    window->signal_key_press_event().connect(sigc::bind<Gtk::Window *>(sigc::mem_fun(this, &IVisionWindow::onKeyboard), window), false);

    buttonPlay->signal_clicked().connect(sigc::bind<Gtk::ToggleButton *>(sigc::mem_fun(this, &IVisionWindow::onButtonPlay), buttonPlay));
    buttonLoad->signal_clicked().connect(sigc::bind<Gtk::FileChooserDialog *>(sigc::mem_fun(this, &IVisionWindow::onButtonLoad), fileChooserDialog));
    buttonOpenLoadDialog->signal_clicked().connect(sigc::bind<Gtk::FileChooserDialog *>(sigc::mem_fun(this, &IVisionWindow::onButtonOpenLoadDialog), fileChooserDialog));

    radioButtonImage->signal_pressed().connect(sigc::bind<Gtk::RadioButton *>(sigc::mem_fun(this, &IVisionWindow::onRadioButtonImage), radioButtonImage));
    radioButtonVideo->signal_pressed().connect(sigc::bind<Gtk::RadioButton *>(sigc::mem_fun(this, &IVisionWindow::onRadioButtonVideo), radioButtonVideo));
    radioButtonCamera->signal_pressed().connect(sigc::bind<Gtk::RadioButton *>(sigc::mem_fun(this, &IVisionWindow::onRadioButtonCamera), radioButtonCamera));

    comboBoxPath->signal_changed().connect(sigc::bind<Gtk::ComboBox *>(sigc::mem_fun(this, &IVisionWindow::onComboBoxSelectPath), comboBoxPath));
    comboBoxColorTeam1->signal_changed().connect(sigc::bind<Gtk::ComboBox *>(sigc::mem_fun(this, &IVisionWindow::onComboBoxSelectColorTeam1), comboBoxColorTeam1));
    comboBoxColorTeam2->signal_changed().connect(sigc::bind<Gtk::ComboBox *>(sigc::mem_fun(this, &IVisionWindow::onComboBoxSelectColorTeam2), comboBoxColorTeam2));
    comboBoxColorRobot1->signal_changed().connect(sigc::bind<Gtk::ComboBox *>(sigc::mem_fun(this, &IVisionWindow::onComboBoxSelectColorRobot1), comboBoxColorRobot1));
    comboBoxColorRobot2->signal_changed().connect(sigc::bind<Gtk::ComboBox *>(sigc::mem_fun(this, &IVisionWindow::onComboBoxSelectColorRobot2), comboBoxColorRobot2));
    comboBoxColorRobot3->signal_changed().connect(sigc::bind<Gtk::ComboBox *>(sigc::mem_fun(this, &IVisionWindow::onComboBoxSelectColorRobot3), comboBoxColorRobot3));
    comboBoxColorRobot4->signal_changed().connect(sigc::bind<Gtk::ComboBox *>(sigc::mem_fun(this, &IVisionWindow::onComboBoxSelectColorRobot4), comboBoxColorRobot4));
    comboBoxColorRobot5->signal_changed().connect(sigc::bind<Gtk::ComboBox *>(sigc::mem_fun(this, &IVisionWindow::onComboBoxSelectColorRobot5), comboBoxColorRobot5));
}

void VisionWindow::initializeWhoseColor() {
    whoseColor.insert(std::pair<ColorType, ObjectType>(ColorType::Red, ObjectType::Unknown));
    whoseColor.insert(std::pair<ColorType, ObjectType>(ColorType::Blue, ObjectType::Unknown));
    whoseColor.insert(std::pair<ColorType, ObjectType>(ColorType::Pink, ObjectType::Unknown));
    whoseColor.insert(std::pair<ColorType, ObjectType>(ColorType::Green, ObjectType::Unknown));
    whoseColor.insert(std::pair<ColorType, ObjectType>(ColorType::Brown, ObjectType::Unknown));
    whoseColor.insert(std::pair<ColorType, ObjectType>(ColorType::Yellow, ObjectType::Unknown));
    whoseColor.insert(std::pair<ColorType, ObjectType>(ColorType::Orange, ObjectType::Ball));
    whoseColor.insert(std::pair<ColorType, ObjectType>(ColorType::Purple, ObjectType::Unknown));
}
