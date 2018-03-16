/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef VISION_WINDOW_H_
#define VISION_WINDOW_H_

#include <gtkmm.h>
#include <iostream>
#include <thread>
#include "IVisionWindow.h"

using namespace std;

class VisionWindow : public IVisionWindow {
public:
    VisionWindow();
    virtual ~VisionWindow();

    void run(int argc, char *argv[]) override;

    bool onKeyboard(GdkEventKey*, Gtk::Window*) override;

    void onButtonOpenSaveDialog(Gtk::FileChooserDialog*, Gtk::Entry*) override;
	void onButtonOpenLoadDialog(Gtk::FileChooserDialog*, Gtk::Entry*) override;

    void onButtonSave(Gtk::FileChooserDialog*, Gtk::Entry*) override;
    void onButtonLoad(Gtk::FileChooserDialog*, Gtk::Entry*) override;

    void onRadioButtonImage(Gtk::RadioButton*) override;
    void onRadioButtonVideo(Gtk::RadioButton*) override;
    void onRadioButtonCamera(Gtk::RadioButton*) override;

    void onSignalSelectFileInDialog(Gtk::FileChooserDialog*, Gtk::Entry*) override;
	
    void onComboBoxSelectPath(Gtk::ComboBox*) override;

private:
	// Threads
    std::thread *threadWindowControl;

	// GTKMM - Calibration Window
		Gtk::Window* window = nullptr;

		Gtk::RadioButton* radioButtonImage = nullptr;
		Gtk::RadioButton* radioButtonVideo = nullptr;
		Gtk::RadioButton* radioButtonCamera = nullptr;

		Gtk::ComboBox* comboBoxPath = nullptr;
		Gtk::ComboBox* comboBoxColorTeam1 = nullptr;
		Gtk::ComboBox* comboBoxColorTeam2 = nullptr;
		Gtk::ComboBox* comboBoxColorRobot1 = nullptr;
		Gtk::ComboBox* comboBoxColorRobot2 = nullptr;
		Gtk::ComboBox* comboBoxColorRobot3 = nullptr;
		Gtk::ComboBox* comboBoxColorRobot4 = nullptr;
		Gtk::ComboBox* comboBoxColorRobot5 = nullptr;

		Gtk::Button* buttonSave = nullptr;
		Gtk::Button* buttonLoad = nullptr;

	// GTKMM - File Chooser Window
		Gtk::FileChooserDialog* fileChooserDialog = nullptr;

		Gtk::Entry* entryChooserDialog = nullptr;

		Gtk::Button* buttonOpenSaveDialog = nullptr;
		Gtk::Button* buttonOpenLoadDialog = nullptr;


	// Control method
	void initializeWidget();
	void setSignals();
	void builderWidget();

    void windowThreadWrapper();

};
#endif
