/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include <Windows/Vision/VisionWindow.h>

bool VisionWindow::onKeyboard(GdkEventKey *event, Gtk::Window *) {
    if (event->keyval == GDK_KEY_space) {
//        window->hide();
    } else if (event->keyval == GDK_KEY_Return) {
        window->hide();
    } else if (event->keyval == GDK_KEY_Escape) {
        window->hide();
    }
    return true;
}

void VisionWindow::onRobotsNewPositions(std::vector<vss::Robot> blueRobots, std::vector<vss::Robot> yellowRobots, vss::Ball ball) {

    //@TODO: diferenciar time e adversario
    //@TODO: adaptar para permitir mais de 3 robos

    std::vector<vss::Robot> teamPositions;
    std::vector<vss::Robot> opponentPositions;

    if(whoseColor[ColorType::Blue] == ObjectType::Team) {
        teamPositions = blueRobots;
        opponentPositions = yellowRobots;
    } else {
        teamPositions = yellowRobots;
        opponentPositions = blueRobots;
    }

    // update positions label with new positions
    stringstream ss;
    ss << "[ " << ball.x << " x " << ball.y << " ]";
    labelPositionBall->set_text(ss.str());

    if (not teamPositions.empty()) {
        ss.str("");
        ss << "[ " << teamPositions[0].x << " x " << teamPositions[0].y << " ]";
        labelPositionRobot1->set_text(ss.str());

        ss.str("");
        ss << "[ " << teamPositions[1].x << " x " << teamPositions[1].y << " ]";
        labelPositionRobot2->set_text(ss.str());

        ss.str("");
        ss << "[ " << teamPositions[2].x << " x " << teamPositions[2].y << " ]";
        labelPositionRobot3->set_text(ss.str());
    }

    if (not opponentPositions.empty()) {
        ss.str("");
        ss << "[ " << opponentPositions[0].x << " x " << opponentPositions[0].y << " ]";
        labelPositionOpponent1->set_text(ss.str());

        ss.str("");
        ss << "[ " << opponentPositions[1].x << " x " << opponentPositions[1].y << " ]";
        labelPositionOpponent2->set_text(ss.str());

        ss.str("");
        ss << "[ " << opponentPositions[2].x << " x " << opponentPositions[2].y << " ]";
        labelPositionOpponent3->set_text(ss.str());
    }
}

void VisionWindow::onButtonPlay(Gtk::ToggleButton * toggleButton) {
    if(toggleButton->get_active())
        toggleButton->set_label("Pause");
    else
        toggleButton->set_label("Play");

    playing = !playing;
}

void VisionWindow::onButtonLoad(Gtk::FileChooserDialog* fileChooser) {
    fileChooser->hide();
    string filename = fileChooser->get_filename();

    if (not filename.empty()){
        calibration = calibrationRepository->read(filename);

        screenImage->set_cut_point_1(cv::Point((int)calibration.cut[0].x, (int)calibration.cut[0].y));
        screenImage->set_cut_point_2(cv::Point((int)calibration.cut[1].x, (int)calibration.cut[1].y));
    }
}

void VisionWindow::onButtonOpenLoadDialog(Gtk::FileChooserDialog* fileChooser) {
    fileChooser->run();
}

void VisionWindow::onRadioButtonImage(Gtk::RadioButton *radioButton) {
    if(inputReader) {
        mtxChangeInput.lock();
            inputReader->stopReceivement();
            inputReader = new ImageFileReader();
            inputReader->setSource(inputReader->getAllPossibleSources().at(0));
            inputReader->initializeReceivement();
        mtxChangeInput.unlock();
    }
}

void VisionWindow::onRadioButtonVideo(Gtk::RadioButton *radioButton) {
//    if (!radioButton->get_active())
//        std::cout << "Video: " << radioButton->get_active() << std::endl;
}

void VisionWindow::onRadioButtonCamera(Gtk::RadioButton *radioButton) {
    if(inputReader) {
        mtxChangeInput.lock();
            inputReader->stopReceivement();
            inputReader = new CameraReader();
            inputReader->setSource(inputReader->getAllPossibleSources().at(0));
            inputReader->initializeReceivement();
        mtxChangeInput.unlock();
    }
}

void VisionWindow::onComboBoxSelectPath(Gtk::ComboBox *combobox) {
//  std::cout << combobox->get_active_row_number() << std::endl;
}

void VisionWindow::onComboBoxSelectColorTeam(Gtk::ComboBox *combobox) {
    vector<string> color = {"Blue", "Yellow"};

    auto result = std::find_if(whoseColor.begin(), whoseColor.end(), [&](pair<ColorType, ObjectType> a) {return a.second == ObjectType::Team; });
    if(result != whoseColor.end()) result->second = ObjectType::Unknown;

    ColorType colorType = toColorType(color[combobox->get_active_row_number()]);
    whoseColor[colorType] = ObjectType::Team;
}

void VisionWindow::onComboBoxSelectColorOpponent(Gtk::ComboBox *combobox) {
    vector<string> color = {"Blue", "Yellow"};

    auto result = std::find_if(whoseColor.begin(), whoseColor.end(), [&](pair<ColorType, ObjectType> a) {return a.second == ObjectType::Opponent; });
    if(result != whoseColor.end()) result->second = ObjectType::Unknown;

    ColorType colorType = toColorType(color[combobox->get_active_row_number()]);
    whoseColor[colorType] = ObjectType::Opponent;
}

void VisionWindow::onComboBoxSelectColorRobot1(Gtk::ComboBox *combobox) {
    vector<string> color = {"Green", "Pink", "Purple", "Red", "Brown"};

    auto result = std::find_if(whoseColor.begin(), whoseColor.end(), [&](pair<ColorType, ObjectType> a) {return a.second == ObjectType::Robot1; });
    if(result != whoseColor.end()) result->second = ObjectType::Unknown;

    ColorType colorType = toColorType(color[combobox->get_active_row_number()]);
    whoseColor[colorType] = ObjectType::Robot1;
}

void VisionWindow::onComboBoxSelectColorRobot2(Gtk::ComboBox *combobox) {
    vector<string> color = {"Green", "Pink", "Purple", "Red", "Brown"};

    auto result = std::find_if(whoseColor.begin(), whoseColor.end(), [&](pair<ColorType, ObjectType> a) {return a.second == ObjectType::Robot2; });
    if(result != whoseColor.end()) result->second = ObjectType::Unknown;

    ColorType colorType = toColorType(color[combobox->get_active_row_number()]);
    whoseColor[colorType] = ObjectType::Robot2;
}

void VisionWindow::onComboBoxSelectColorRobot3(Gtk::ComboBox *combobox) {
    vector<string> color = {"Green", "Pink", "Purple", "Red", "Brown"};

    auto result = std::find_if(whoseColor.begin(), whoseColor.end(), [&](pair<ColorType, ObjectType> a) {return a.second == ObjectType::Robot3; });
    if(result != whoseColor.end()) result->second = ObjectType::Unknown;

    ColorType colorType = toColorType(color[combobox->get_active_row_number()]);
    whoseColor[colorType] = ObjectType::Robot3;
}

void VisionWindow::onComboBoxSelectColorRobot4(Gtk::ComboBox *combobox) {
    vector<string> color = {"Green", "Pink", "Purple", "Red", "Brown"};

    auto result = std::find_if(whoseColor.begin(), whoseColor.end(), [&](pair<ColorType, ObjectType> a) {return a.second == ObjectType::Robot4; });
    if(result != whoseColor.end()) result->second = ObjectType::Unknown;

    ColorType colorType = toColorType(color[combobox->get_active_row_number()]);
    whoseColor[colorType] = ObjectType::Robot4;
}

void VisionWindow::onComboBoxSelectColorRobot5(Gtk::ComboBox *combobox) {
    vector<string> color = {"Green", "Pink", "Purple", "Red", "Brown"};

    auto result = std::find_if(whoseColor.begin(), whoseColor.end(), [&](pair<ColorType, ObjectType> a) {return a.second == ObjectType::Robot5; });
    if(result != whoseColor.end()) result->second = ObjectType::Unknown;

    ColorType colorType = toColorType(color[combobox->get_active_row_number()]);
    whoseColor[colorType] = ObjectType::Robot5;
}

void VisionWindow::updateFpsLabel(int i){
    string title = "VISION (" + to_string(i) + ")";
    window->set_title(title);
}
