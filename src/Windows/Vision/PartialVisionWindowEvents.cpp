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

void VisionWindow::onButtonPlay() {

}

void VisionWindow::onButtonLoad(Gtk::FileChooserDialog* fileChooser, Gtk::Entry* entry) {
    if (entry->get_text_length() > 0){
        calibration = calibrationRepository->read(fileChooser->get_filename());

        screenImage->set_cut_point_1(cv::Point((int)calibration.cut[0].x, (int)calibration.cut[0].y));
        screenImage->set_cut_point_2(cv::Point((int)calibration.cut[1].x, (int)calibration.cut[1].y));

        fileChooser->hide();
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

void VisionWindow::onButtonOpenLoadDialog(Gtk::FileChooserDialog* fileChooser, Gtk::Entry* entry) {
    entry->set_sensitive(false);
    fileChooser->show();
}

void VisionWindow::onButtonOpenSaveDialog(Gtk::FileChooserDialog* fileChooser, Gtk::Entry* entry) {
    entry->set_sensitive(true);
    fileChooser->show();
}

void VisionWindow::onRadioButtonImage(Gtk::RadioButton *radioButton) {
//    if (!radioButton->get_active())
//        std::cout << "Image: " << radioButton->get_active() << std::endl;
}

void VisionWindow::onRadioButtonVideo(Gtk::RadioButton *radioButton) {
//    if (!radioButton->get_active())
//        std::cout << "Video: " << radioButton->get_active() << std::endl;
}

void VisionWindow::onRadioButtonCamera(Gtk::RadioButton *radioButton) {
//    if (!radioButton->get_active())
//        std::cout << "Camera: " << radioButton->get_active() << std::endl;
}

void VisionWindow::onSignalSelectFileInDialog(Gtk::FileChooserDialog *fileChooser, Gtk::Entry *entry) {
    std::string str = fileChooser->get_filename();
    std::size_t sub_str = str.find_last_of("/\\");
    entry->set_text(str.substr(sub_str + 1));
}


void VisionWindow::onComboBoxSelectPath(Gtk::ComboBox *combobox) {
//  std::cout << combobox->get_active_row_number() << std::endl;
}

void VisionWindow::onComboBoxSelectColorTeam1(Gtk::ComboBox *combobox) {
    vector<string> color = {"Blue", "Yellow"};
    ColorType colorType = toColorType(color[combobox->get_active_row_number()]);
    whoseColor[colorType] = WhoseName::Team1;
}

void VisionWindow::onComboBoxSelectColorTeam2(Gtk::ComboBox *combobox) {
    vector<string> color = {"Blue", "Yellow"};
    ColorType colorType = toColorType(color[combobox->get_active_row_number()]);
    whoseColor[colorType] = WhoseName::Team2;
}

void VisionWindow::onComboBoxSelectColorRobot1(Gtk::ComboBox *combobox) {
    vector<string> color = {"Green", "Pink", "Purple", "Red", "Brown"};
    ColorType colorType = toColorType(color[combobox->get_active_row_number()]);
    whoseColor[colorType] = WhoseName::Robot1;
}

void VisionWindow::onComboBoxSelectColorRobot2(Gtk::ComboBox *combobox) {
    vector<string> color = {"Green", "Pink", "Purple", "Red", "Brown"};
    ColorType colorType = toColorType(color[combobox->get_active_row_number()]);
    whoseColor[colorType] = WhoseName::Robot2;
}

void VisionWindow::onComboBoxSelectColorRobot3(Gtk::ComboBox *combobox) {
    vector<string> color = {"Green", "Pink", "Purple", "Red", "Brown"};
    ColorType colorType = toColorType(color[combobox->get_active_row_number()]);
    whoseColor[colorType] = WhoseName::Robot3;
}

void VisionWindow::onComboBoxSelectColorRobot4(Gtk::ComboBox *combobox) {
    vector<string> color = {"Green", "Pink", "Purple", "Red", "Brown"};
    ColorType colorType = toColorType(color[combobox->get_active_row_number()]);
    whoseColor[colorType] = WhoseName::Robot4;
}

void VisionWindow::onComboBoxSelectColorRobot5(Gtk::ComboBox *combobox) {
    vector<string> color = {"Green", "Pink", "Purple", "Red", "Brown"};
    ColorType colorType = toColorType(color[combobox->get_active_row_number()]);
    whoseColor[colorType] = WhoseName::Robot5;
}

void VisionWindow::saveWhoseColor(std::string path) {
    std::ofstream file;
    file.open(path);
    cout << path << endl;
    for(std::map<ColorType, WhoseName>::iterator it = whoseColor.begin(); it != whoseColor.end(); it++) {
        if(it->first != ColorType::Orange && it->second != WhoseName::Unknown) {
            file << toDescription(it->first) << " " << toDescription(it->second) << std::endl;
        }
    }
    file.close();
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

    std::map <ColorType, int> colorToIndex;
    colorToIndex.insert(std::pair<ColorType, int>(ColorType::UnknownType, -1));
    colorToIndex.insert(std::pair<ColorType, int>(ColorType::Blue, 0));
    colorToIndex.insert(std::pair<ColorType, int>(ColorType::Yellow, 1));
    colorToIndex.insert(std::pair<ColorType, int>(ColorType::Green, 0));
    colorToIndex.insert(std::pair<ColorType, int>(ColorType::Pink, 1));
    colorToIndex.insert(std::pair<ColorType, int>(ColorType::Purple, 2));
    colorToIndex.insert(std::pair<ColorType, int>(ColorType::Red, 3));
    colorToIndex.insert(std::pair<ColorType, int>(ColorType::Brown, 4));

    for (std::string line; std::getline(ifs, line); ) {
        std::vector<std::string> tokens = explode(line, ' ');
        ColorType colorType = toColorType(tokens[0]);
        whoseColor[colorType] = toWhoseName(tokens[1]);
        if (whoseColor[colorType] != WhoseName::Unknown) {
            whoseNameToComboBox[whoseColor[colorType]]->set_active(colorToIndex[colorType]);
        }
    }

};
