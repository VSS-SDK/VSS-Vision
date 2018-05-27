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
//    inputReader = new CameraReader();
    inputReader = new ImageFileReader();

    calibrationBuilderFromRepository = new CalibrationBuilder();
    calibrationRepository = new CalibrationRepository(calibrationBuilderFromRepository);
    calibration = calibrationBuilderFromRepository->getInstance();

    colorRecognizer = new ColorRecognizer();
    robotRecognizer = new RobotRecognizer();

    interface.createSocketSendState(&global_state);
}

VisionWindow::~VisionWindow() {
}

int VisionWindow::run(int argc, char *argv[]) {

    threadWindowControl = new thread(std::bind(&VisionWindow::windowThreadWrapper, this));
    threadCameraReader = new thread(std::bind(&VisionWindow::cameraThreadWrapper, this));

    threadWindowControl->join();
    threadCameraReader->detach();

    return MENU;
}

void VisionWindow::cameraThreadWrapper() {
    auto path = inputReader->getAllPossibleSources();
    inputReader->setSource(path.at(0));
    inputReader->start();
    inputReader->initializeReceivement();
}

void VisionWindow::windowThreadWrapper() {
    builderWidget();
    setSignals();
    initializeWidget();
    initializeWhoseColor();

    Gtk::Main::run(*window);
}

void VisionWindow::initializeWidget() {
    screenImage->set_image(cv::imread("../mock/images/model.jpg"));

    window->maximize();
    window->show_all_children();
}

void VisionWindow::builderWidget() {

    auto builder = Gtk::Builder::create();

    try {
        builder->add_from_file("../glade/Vision.glade");

        builder->get_widget("window", window);

        builder->get_widget_derived("drawingarea_frame", screenImage);

        builder->get_widget("button_play", buttonPlay);
        builder->get_widget("button_load_calibration", buttonLoad);
        builder->get_widget("button_load_dialog", buttonOpenLoadDialog);

        builder->get_widget("entry_chooser", entryChooserDialog);
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

    } catch (const Glib::FileError &ex) {
        std::cerr << "FileError: " << ex.what() << std::endl;

    } catch (const Glib::MarkupError &ex) {
        std::cerr << "MarkupError: " << ex.what() << std::endl;

    } catch (const Gtk::BuilderError &ex) {
        std::cerr << "BuilderError: " << ex.what() << std::endl;
    }
}

void VisionWindow::setSignals() {

    signal_set_new_frame.connect(sigc::mem_fun(this, &VisionWindow::setNewFrame));

    inputReader->signal_new_frame.connect(sigc::mem_fun(this, &VisionWindow::receiveNewFrame));

    window->signal_key_press_event().connect(
            sigc::bind<Gtk::Window *>(sigc::mem_fun(this, &IVisionWindow::onKeyboard), window), false);

    buttonPlay->signal_clicked().connect(sigc::mem_fun(this, &IVisionWindow::onButtonPlay));
    buttonLoad->signal_clicked().connect(
            sigc::bind<Gtk::FileChooserDialog *, Gtk::Entry *>(sigc::mem_fun(this, &IVisionWindow::onButtonLoad),
                                                               fileChooserDialog, entryChooserDialog));
    buttonOpenLoadDialog->signal_clicked().connect(sigc::bind<Gtk::FileChooserDialog *, Gtk::Entry *>(
            sigc::mem_fun(this, &IVisionWindow::onButtonOpenLoadDialog), fileChooserDialog, entryChooserDialog));

    fileChooserDialog->signal_selection_changed().connect(sigc::bind<Gtk::FileChooserDialog *, Gtk::Entry *>(
            sigc::mem_fun(this, &IVisionWindow::onSignalSelectFileInDialog), fileChooserDialog, entryChooserDialog));

    radioButtonImage->signal_pressed().connect(
            sigc::bind<Gtk::RadioButton *>(sigc::mem_fun(this, &IVisionWindow::onRadioButtonImage), radioButtonImage));
    radioButtonVideo->signal_pressed().connect(
            sigc::bind<Gtk::RadioButton *>(sigc::mem_fun(this, &IVisionWindow::onRadioButtonVideo), radioButtonVideo));
    radioButtonCamera->signal_pressed().connect(
            sigc::bind<Gtk::RadioButton *>(sigc::mem_fun(this, &IVisionWindow::onRadioButtonCamera),
                                           radioButtonCamera));

    comboBoxPath->signal_changed().connect(
            sigc::bind<Gtk::ComboBox *>(sigc::mem_fun(this, &IVisionWindow::onComboBoxSelectPath), comboBoxPath));
    comboBoxColorTeam1->signal_changed().connect(
            sigc::bind<Gtk::ComboBox *>(sigc::mem_fun(this, &IVisionWindow::onComboBoxSelectColorTeam1),
                                        comboBoxColorTeam1));
    comboBoxColorTeam2->signal_changed().connect(
            sigc::bind<Gtk::ComboBox *>(sigc::mem_fun(this, &IVisionWindow::onComboBoxSelectColorTeam2),
                                        comboBoxColorTeam2));
    comboBoxColorRobot1->signal_changed().connect(
            sigc::bind<Gtk::ComboBox *>(sigc::mem_fun(this, &IVisionWindow::onComboBoxSelectColorRobot1),
                                        comboBoxColorRobot1));
    comboBoxColorRobot2->signal_changed().connect(
            sigc::bind<Gtk::ComboBox *>(sigc::mem_fun(this, &IVisionWindow::onComboBoxSelectColorRobot2),
                                        comboBoxColorRobot2));
    comboBoxColorRobot3->signal_changed().connect(
            sigc::bind<Gtk::ComboBox *>(sigc::mem_fun(this, &IVisionWindow::onComboBoxSelectColorRobot3),
                                        comboBoxColorRobot3));
    comboBoxColorRobot4->signal_changed().connect(
            sigc::bind<Gtk::ComboBox *>(sigc::mem_fun(this, &IVisionWindow::onComboBoxSelectColorRobot4),
                                        comboBoxColorRobot4));
    comboBoxColorRobot5->signal_changed().connect(
            sigc::bind<Gtk::ComboBox *>(sigc::mem_fun(this, &IVisionWindow::onComboBoxSelectColorRobot5),
                                        comboBoxColorRobot5));
}

void VisionWindow::initializeWhoseColor() {
    whoseColor.insert(std::pair<ColorType, WhoseName>(ColorType::Red, WhoseName::Unknown));
    whoseColor.insert(std::pair<ColorType, WhoseName>(ColorType::Blue, WhoseName::Unknown));
    whoseColor.insert(std::pair<ColorType, WhoseName>(ColorType::Pink, WhoseName::Unknown));
    whoseColor.insert(std::pair<ColorType, WhoseName>(ColorType::Green, WhoseName::Unknown));
    whoseColor.insert(std::pair<ColorType, WhoseName>(ColorType::Brown, WhoseName::Unknown));
    whoseColor.insert(std::pair<ColorType, WhoseName>(ColorType::Yellow, WhoseName::Unknown));
    whoseColor.insert(std::pair<ColorType, WhoseName>(ColorType::Orange, WhoseName::Ball));
    whoseColor.insert(std::pair<ColorType, WhoseName>(ColorType::Purple, WhoseName::Unknown));
}
