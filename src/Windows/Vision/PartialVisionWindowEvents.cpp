/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include <Windows/Vision/VisionWindow.h>

bool VisionWindow::onKeyboard(GdkEventKey* event, Gtk::Window*) {
    if(event->keyval == GDK_KEY_space) {
        window->hide();
    } else if(event->keyval == GDK_KEY_Return) {
        window->hide();
    } else if(event->keyval == GDK_KEY_Escape) {
        window->hide();
    }
    return true;
}

void VisionWindow::onButtonPlay() {

}

void VisionWindow::onButtonLoad(Gtk::FileChooserDialog* fileChooser, Gtk::Entry* entry) {
    if (entry->get_text_length() > 0){
    //calibration = calibrationRepository->read(file_chooser->get_filename());
    fileChooser->hide();
  }
}

void VisionWindow::onButtonOpenLoadDialog(Gtk::FileChooserDialog* fileChooser, Gtk::Entry* entry) {
    entry->set_sensitive(true);
    fileChooser->show();
}

void VisionWindow::onRadioButtonImage(Gtk::RadioButton* radioButton) {
//    if (!radioButton->get_active())
//        std::cout << "Image: " << radioButton->get_active() << std::endl;
}

void VisionWindow::onRadioButtonVideo(Gtk::RadioButton* radioButton) {
//    if (!radioButton->get_active())
//        std::cout << "Video: " << radioButton->get_active() << std::endl;
}

void VisionWindow::onRadioButtonCamera(Gtk::RadioButton* radioButton) {
//    if (!radioButton->get_active())
//        std::cout << "Camera: " << radioButton->get_active() << std::endl;
}

void VisionWindow::onSignalSelectFileInDialog(Gtk::FileChooserDialog* fileChooser, Gtk::Entry* entry) {
    std::string str = fileChooser->get_filename();
    std::size_t sub_str = str.find_last_of("/\\");
    entry->set_text(str.substr(sub_str+1));
}

void VisionWindow::onComboBoxSelectPath(Gtk::ComboBox* combobox) {
//  std::cout << combobox->get_active_row_number() << std::endl;
}

void VisionWindow::onComboBoxSelectColorTeam1(Gtk::ComboBox* combobox) {
    vector<string> color = {"Blue", "Yellow"};
    ColorType colorType = toColorType(color[combobox->get_active_row_number()]);
    WhoseName whoseName = WhoseName::Team1;
    WhoseColor whoseColor(whoseName, colorType);
    objects.push_back(whoseColor);
}

void VisionWindow::onComboBoxSelectColorTeam2(Gtk::ComboBox* combobox) {
    vector<string> color = {"Blue", "Yellow"};
    ColorType colorType = toColorType(color[combobox->get_active_row_number()]);
    WhoseName whoseName = WhoseName::Team2;
    WhoseColor whoseColor(whoseName, colorType);
    objects.push_back(whoseColor);
}

void VisionWindow::onComboBoxSelectColorRobot1(Gtk::ComboBox* combobox) {
    vector<string> color = {"Green", "Pink", "Purple", "Red", "Brown"};
    ColorType colorType = toColorType(color[combobox->get_active_row_number()]);
    WhoseName whoseName = WhoseName::Robot1;
    WhoseColor whoseColor(whoseName, colorType);
    objects.push_back(whoseColor);
}

void VisionWindow::onComboBoxSelectColorRobot2(Gtk::ComboBox* combobox) {
    vector<string> color = {"Green", "Pink", "Purple", "Red", "Brown"};
    ColorType colorType = toColorType(color[combobox->get_active_row_number()]);
    WhoseName whoseName = WhoseName::Robot2;
    WhoseColor whoseColor(whoseName, colorType);
    objects.push_back(whoseColor);
}

void VisionWindow::onComboBoxSelectColorRobot3(Gtk::ComboBox* combobox) {
    vector<string> color = {"Green", "Pink", "Purple", "Red", "Brown"};
    ColorType colorType = toColorType(color[combobox->get_active_row_number()]);
    WhoseName whoseName = WhoseName::Robot3;
    WhoseColor whoseColor(whoseName, colorType);
    objects.push_back(whoseColor);
}

void VisionWindow::onComboBoxSelectColorRobot4(Gtk::ComboBox* combobox) {
    vector<string> color = {"Green", "Pink", "Purple", "Red", "Brown"};
    ColorType colorType = toColorType(color[combobox->get_active_row_number()]);
    WhoseName whoseName = WhoseName::Robot4;
    WhoseColor whoseColor(whoseName, colorType);
    objects.push_back(whoseColor);
}

void VisionWindow::onComboBoxSelectColorRobot5(Gtk::ComboBox* combobox) {
    vector<string> color = {"Green", "Pink", "Purple", "Red", "Brown"};
    ColorType colorType = toColorType(color[combobox->get_active_row_number()]);
    WhoseName whoseName = WhoseName::Robot5;
    WhoseColor whoseColor(whoseName, colorType);
    objects.push_back(whoseColor);
}