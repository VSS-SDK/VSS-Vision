/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include <Windows/Vision/VisionWindow.h>
#include <Core/StringHelper.h>

bool VisionWindow::onKeyboard(GdkEventKey *event, Gtk::Window *) {
    if (event->keyval == GDK_KEY_space) {
        window->hide();
    } else if (event->keyval == GDK_KEY_Return) {
        window->hide();
    } else if (event->keyval == GDK_KEY_Escape) {
        window->hide();
    }
    return true;
}

void VisionWindow::onRobotsNewPositions(std::vector<vss::Robot> robots, vss::Ball ball) {

    //@TODO: diferenciar time e adversario
    //@TODO: adaptar para permitir mais de 3 robos

    // send positions
    if(playing)
        stateSender->sendState(robots, ball);

    // update positions label with new positions
    stringstream ss;
    ss << "[ " << ball.x << " x " << ball.y << " ]";
    labelPositionBall->set_text(ss.str());

    ss.str("");
    ss << "[ " << robots[0].x << " x " << robots[0].y << " ]";
    labelPositionRobot1->set_text(ss.str());

    ss.str("");
    ss << "[ " << robots[1].x << " x " << robots[1].y << " ]";
    labelPositionRobot2->set_text(ss.str());

    ss.str("");
    ss << "[ " << robots[2].x << " x " << robots[2].y << " ]";
    labelPositionRobot3->set_text(ss.str());

    ss.str("");
    ss << "[ " << robots[3].x << " x " << robots[3].y << " ]";
    labelPositionOpponent1->set_text(ss.str());

    ss.str("");
    ss << "[ " << robots[4].x << " x " << robots[4].y << " ]";
    labelPositionOpponent2->set_text(ss.str());

    ss.str("");
    ss << "[ " << robots[5].x << " x " << robots[5].y << " ]";
    labelPositionOpponent3->set_text(ss.str());

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

void VisionWindow::onButtonLoadGameConfig(Gtk::FileChooserDialog* fileChooser, Gtk::Entry* entry) {
    if (entry->get_text_length() > 0){
        setupWhoseColor(fileChooser->get_filename());
        fileChooser->hide();
    }
}

void VisionWindow::onButtonSaveGameConfig(Gtk::FileChooserDialog* fileChooser, Gtk::Entry* entry) {
    if (entry->get_text_length() > 0){
        std::stringstream aux;
        aux << fileChooser->get_current_folder() << "/" << entry->get_text();
        saveWhoseColor(aux.str());
        fileChooser->hide();
    }
}

void VisionWindow::onButtonOpenLoadDialog(Gtk::FileChooserDialog* fileChooser) {
    fileChooser->run();
}

void VisionWindow::onButtonOpenSaveDialog(Gtk::FileChooserDialog* fileChooser, Gtk::Entry* entry) {
    entry->set_sensitive(true);
    fileChooser->show();
}

void VisionWindow::onRadioButtonImage(Gtk::RadioButton *radioButton) {
    inputReader->close();

    inputReader = new ImageFileReader();
    configureInputReceivement(inputReader);
}

void VisionWindow::onRadioButtonVideo(Gtk::RadioButton *radioButton) {
//    if (!radioButton->get_active())
//        std::cout << "Video: " << radioButton->get_active() << std::endl;
}

void VisionWindow::onRadioButtonCamera(Gtk::RadioButton *radioButton) {
    inputReader->close();

    inputReader = new CameraReader();
    configureInputReceivement(inputReader);
}


void VisionWindow::onComboBoxSelectPath(Gtk::ComboBox *combobox) {
//  std::cout << combobox->get_active_row_number() << std::endl;
}

void VisionWindow::onComboBoxSelectColorTeam1(Gtk::ComboBox *combobox) {
    vector<string> color = {"Blue", "Yellow"};
    ColorType colorType = toColorType(color[combobox->get_active_row_number()]);
    game->whoseColor[colorType] = WhoseName::Team1;
}

void VisionWindow::onComboBoxSelectColorTeam2(Gtk::ComboBox *combobox) {
    vector<string> color = {"Blue", "Yellow"};
    ColorType colorType = toColorType(color[combobox->get_active_row_number()]);
    game->whoseColor[colorType] = WhoseName::Team2;
}

void VisionWindow::onComboBoxSelectColorRobot1(Gtk::ComboBox *combobox) {
    vector<string> color = {"Green", "Pink", "Purple", "Red", "Brown"};
    ColorType colorType = toColorType(color[combobox->get_active_row_number()]);
    game->whoseColor[colorType] = WhoseName::Robot1;
}

void VisionWindow::onComboBoxSelectColorRobot2(Gtk::ComboBox *combobox) {
    vector<string> color = {"Green", "Pink", "Purple", "Red", "Brown"};
    ColorType colorType = toColorType(color[combobox->get_active_row_number()]);
    game->whoseColor[colorType] = WhoseName::Robot2;
}

void VisionWindow::onComboBoxSelectColorRobot3(Gtk::ComboBox *combobox) {
    vector<string> color = {"Green", "Pink", "Purple", "Red", "Brown"};
    ColorType colorType = toColorType(color[combobox->get_active_row_number()]);
    game->whoseColor[colorType] = WhoseName::Robot3;
}

void VisionWindow::onComboBoxSelectColorRobot4(Gtk::ComboBox *combobox) {
    vector<string> color = {"Green", "Pink", "Purple", "Red", "Brown"};
    ColorType colorType = toColorType(color[combobox->get_active_row_number()]);
    game->whoseColor[colorType] = WhoseName::Robot4;
}

void VisionWindow::onComboBoxSelectColorRobot5(Gtk::ComboBox *combobox) {
    vector<string> color = {"Green", "Pink", "Purple", "Red", "Brown"};
    ColorType colorType = toColorType(color[combobox->get_active_row_number()]);
    game->whoseColor[colorType] = WhoseName::Robot5;
}

void VisionWindow::saveWhoseColor(std::string path) {
    gameRepository->create(path, *game);
}

void VisionWindow::setupWhoseColor(std::string path) {
    std::ifstream ifs (path, std::ifstream::in);
    std::map <WhoseName, Gtk::ComboBox*> whoseNameToComboBox;
    whoseNameToComboBox.insert(std::pair<WhoseName, Gtk::ComboBox*>(WhoseName::Team1, comboBoxColorTeam1));
    whoseNameToComboBox.insert(std::pair<WhoseName, Gtk::ComboBox*>(WhoseName::Team2, comboBoxColorTeam2));
    whoseNameToComboBox.insert(std::pair<WhoseName, Gtk::ComboBox*>(WhoseName::Robot1, comboBoxColorRobot1));
    whoseNameToComboBox.insert(std::pair<WhoseName, Gtk::ComboBox*>(WhoseName::Robot2, comboBoxColorRobot2));
    whoseNameToComboBox.insert(std::pair<WhoseName, Gtk::ComboBox*>(WhoseName::Robot3, comboBoxColorRobot3));
    whoseNameToComboBox.insert(std::pair<WhoseName, Gtk::ComboBox*>(WhoseName::Robot4, comboBoxColorRobot4));
    whoseNameToComboBox.insert(std::pair<WhoseName, Gtk::ComboBox*>(WhoseName::Robot5, comboBoxColorRobot5));

    *game = gameRepository->read(path, whoseNameToComboBox);
    if (game->calibrationPath.length() > 0) {
        calibration = calibrationRepository->read(game->calibrationPath);
    }
};
