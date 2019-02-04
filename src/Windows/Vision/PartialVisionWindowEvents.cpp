/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include <Windows/Vision/VisionWindow.h>
#include <Helpers/RobotHelper.h>

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

void VisionWindow::onButtonPlay(Gtk::ToggleButton * toggleButton) {
    if(toggleButton->get_active())
        toggleButton->set_label("Pause");
    else
        toggleButton->set_label("Play");

    playing = !playing;
}

void VisionWindow::onButtonOpenLoadDialog() {
    Gtk::FileChooserDialog dialog("Please choose a file", Gtk::FILE_CHOOSER_ACTION_OPEN);

    dialog.set_transient_for(*window);
    dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    dialog.add_button("_Open", Gtk::RESPONSE_OK);
    dialog.set_current_folder(defaultFilesPath + "/data");

    auto filter_text = Gtk::FileFilter::create();
    filter_text->set_name("Text files");
    filter_text->add_mime_type("text/plain");
    dialog.add_filter(filter_text);

    switch( dialog.run() ) {
        case(Gtk::RESPONSE_OK) : {
            std::string filename = dialog.get_filename();

            mutexCalibration.lock();
                calibration = calibrationRepository->read(filename);
            mutexCalibration.unlock();

            mutexCalibration.lock();
                ColorRange range(calibration.colorsRange, ColorType::Orange );
            mutexCalibration.unlock();

            mtxPattern.lock();
                pattern[ObjectType::Ball].id = ObjectType::Ball;
                pattern[ObjectType::Ball].singleColorType = ColorType::Orange;
                pattern[ObjectType::Ball].singleColorRange = range;
            mtxPattern.unlock();

            break;
        }
        case(Gtk::RESPONSE_CANCEL) : {
            break;
        }
        default : {
            break;
        }
    }
}

void VisionWindow::onRadioButtonImage(Gtk::RadioButton *radioButton) {
    if(inputReader) {
        mutexChangeInput.lock();
            inputReader->stopReceivement();
            inputReader = new ImageFileReader();
            inputReader->setSource(inputReader->getAllPossibleSources().at(0));
            inputReader->initializeReceivement();
        mutexChangeInput.unlock();
    }
}

void VisionWindow::onRadioButtonVideo(Gtk::RadioButton *radioButton) {
//    if (!radioButton->get_active())
//        std::cout << "Video: " << radioButton->get_active() << std::endl;
}

void VisionWindow::onRadioButtonCamera(Gtk::RadioButton *radioButton) {
    if(inputReader) {
        mutexChangeInput.lock();
            inputReader->stopReceivement();
            inputReader = new CameraReader();
            inputReader->setSource(inputReader->getAllPossibleSources().at(0));
            inputReader->initializeReceivement();
        mutexChangeInput.unlock();
    }
}

void VisionWindow::onComboBoxSelectPath(Gtk::ComboBoxText *combobox) {
    // std::cout << combobox->get_active_row_number() << std::endl;
}

void VisionWindow::onComboBoxSelectColorTeam(Gtk::ComboBoxText *combobox) {
    string s = combobox->get_active_text();
    int row = combobox->get_active_row_number();

    mutexCalibration.lock();
        ColorRange range(calibration.colorsRange, mainColorList[row] );
    mutexCalibration.unlock();

    mtxPattern.lock();
        pattern[ObjectType::Team].id = ObjectType::Team;
        pattern[ObjectType::Team].singleColorType = mainColorList[row];
        pattern[ObjectType::Team].singleColorRange = range;

        if(pattern[ObjectType::Opponent].singleColorType == mainColorList[row]){
//            comboBoxColorTeam2->set_active(-1);
            pattern[ObjectType::Opponent] = ColorPattern();
        }
    mtxPattern.unlock();
}

void VisionWindow::onComboBoxSelectColorPattern1(Gtk::ComboBoxText *combobox) {
    int row = combobox->get_active_row_number();
    ObjectType object = objectList[row];

    ColorPattern colorPattern;
    colorPattern.id = object;
    colorPattern.singleColorType = ColorType::Pink;

    mtxPattern.lock();
        auto find = std::find(pattern.begin(), pattern.end(), colorPattern);

        if(find != pattern.end()){
            *find = ColorPattern();
        }

        pattern[object] = colorPattern;
    mtxPattern.unlock();
}

void VisionWindow::onComboBoxSelectColorPattern2(Gtk::ComboBoxText *combobox) {
    int row = combobox->get_active_row_number();
    ObjectType object = objectList[row];

    ColorPattern colorPattern;
    colorPattern.id = object;
    colorPattern.singleColorType = ColorType::Green;

    mtxPattern.lock();
        auto find = std::find(pattern.begin(), pattern.end(), colorPattern);

        if(find != pattern.end()){
            *find = ColorPattern();
        }

        pattern[object] = colorPattern;
    mtxPattern.unlock();
}

void VisionWindow::onComboBoxSelectColorPattern3(Gtk::ComboBoxText *combobox) {
    int row = combobox->get_active_row_number();
    ObjectType object = objectList[row];

    ColorPattern colorPattern;
    colorPattern.id = object;
    colorPattern.singleColorType = ColorType::Red;

    mtxPattern.lock();
        auto find = std::find(pattern.begin(), pattern.end(), colorPattern);

        if(find != pattern.end()){
            *find = ColorPattern();
        }

        pattern[object] = colorPattern;
    mtxPattern.unlock();

}

void VisionWindow::onComboBoxSelectColorPattern4(Gtk::ComboBoxText *combobox) {
    int row = combobox->get_active_row_number();
    ObjectType object = objectList[row];

    ColorPattern colorPattern;
    colorPattern.id = object;
    colorPattern.singleColorType = ColorType::Green;

    mtxPattern.lock();
        auto find = std::find(pattern.begin(), pattern.end(), colorPattern);

        if(find != pattern.end()){
            *find = ColorPattern();
        }

        pattern[object] = colorPattern;
    mtxPattern.unlock();

}

void VisionWindow::onComboBoxSelectColorPattern5(Gtk::ComboBoxText *combobox) {
    int row = combobox->get_active_row_number();
    ObjectType object = objectList[row];

    ColorPattern colorPattern;
    colorPattern.id = object;
    colorPattern.singleColorType = ColorType::Pink;

    mtxPattern.lock();
        auto find = std::find(pattern.begin(), pattern.end(), colorPattern);

        if(find != pattern.end()){
            *find = ColorPattern();
        }

        pattern[object] = colorPattern;
    mtxPattern.unlock();
}

void VisionWindow::updateLabel(int i, std::vector<vss::Robot> blueRobots, std::vector<vss::Robot> yellowRobots, vss::Ball ball) {

    window->set_title( "VISION (" + to_string(i) + ")" );

    std::vector<vss::Robot> teamPositions;
    std::vector<vss::Robot> opponentPositions;

    if (pattern[ObjectType::Team].singleColorType == ColorType::Blue) {
        teamPositions = blueRobots;
        opponentPositions = yellowRobots;

    } else {
        teamPositions = yellowRobots;
        opponentPositions = blueRobots;
    }

    handleLabel(labelBall, labelPositionBall, ball);

    if (teamPositions.size() == 5) {
        handleLabel(labelRobot1, labelPositionRobot1, teamPositions[0]);
        handleLabel(labelRobot2, labelPositionRobot2, teamPositions[1]);
        handleLabel(labelRobot3, labelPositionRobot3, teamPositions[2]);
        handleLabel(labelRobot4, labelPositionRobot4, teamPositions[3]);
        handleLabel(labelRobot5, labelPositionRobot5, teamPositions[4]);
    }

    if (opponentPositions.size() == 5) {
        handleLabel(labelOpponent1, labelPositionOpponent1, opponentPositions[0]);
        handleLabel(labelOpponent2, labelPositionOpponent2, opponentPositions[1]);
        handleLabel(labelOpponent3, labelPositionOpponent3, opponentPositions[2]);
        handleLabel(labelOpponent4, labelPositionOpponent4, opponentPositions[3]);
        handleLabel(labelOpponent5, labelPositionOpponent5, opponentPositions[4]);
    }
}

void VisionWindow::handleLabel(Gtk::Label* label, Gtk::Label* labelPosition, vss::Point robot){

    stringstream ss;

    if (isEmpty(robot)) {
        label->hide();
        labelPosition->hide();
    } else {
        ss << "[ " << robot.x << " x " << robot.y << " ]";
        labelPosition->set_text(ss.str());

        labelPosition->show();
        label->show();
    }

}