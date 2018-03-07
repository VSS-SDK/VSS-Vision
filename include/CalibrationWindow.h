/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef GPROGRAM_H_
#define GPROGRAM_H_

#include "ICalibrationWindow.h"
#include <gtkmm.h>
#include <iostream>
#include <Interfaces/ICalibrationRepository.h>
#include <Interfaces/ICalibrationBuilder.h>
#include <Interfaces/ICameraReader.h>
#include <thread>

#include "GImage.h"
#include "ICalibrationRoutine.h"
#include "opencv2/highgui/highgui.hpp"

using namespace std;

class CalibrationWindow : public ICalibrationWindow {
private:
	// Threads
	std::thread *threadCameraReader;
    std::thread *threadWindowControl;

	// Classes
	ICalibrationRoutine *calibrationRoutine;
	ICalibrationRepository *calibrationRepository;
	ICameraReader *cameraReader;
    ICalibrationBuilder *calibrationBuilderFromRepository;
	ICalibrationBuilder *calibrationBuilderFromRoutine;

	// Window - calibration
	Gtk::Window* window = nullptr;

	// Opencv image
	GImage* gImage = nullptr;

	// Button
	Gtk::RadioButton* radioButtonImage = nullptr;
	Gtk::RadioButton* radioButtonVideo = nullptr;
	Gtk::RadioButton* radioButtonCamera = nullptr;

	// Select text
	Gtk::ComboBoxText* comboBoxInputPath = nullptr;
	Gtk::ComboBoxText* comboBoxColorSelect = nullptr;
	Gtk::ComboBoxText* comboBoxColorTeam1 = nullptr;
	Gtk::ComboBoxText* comboBoxColorTeam2 = nullptr;
	Gtk::ComboBoxText* comboBoxColorRobot1 = nullptr;
	Gtk::ComboBoxText* comboBoxColorRobot2 = nullptr;
	Gtk::ComboBoxText* comboBoxColorRobot3 = nullptr;
	Gtk::ComboBoxText* comboBoxColorRobot4 = nullptr;
	Gtk::ComboBoxText* comboBoxColorRobot5 = nullptr;

	// Table
	Gtk::Table* table_input = nullptr;
	Gtk::Table* table_set_color = nullptr;
	Gtk::Table* table_color_robot = nullptr;

	// Slider
	Gtk::Scale* scale_h_max = nullptr;
	Gtk::Scale* scale_h_min = nullptr;
	Gtk::Scale* scale_s_max = nullptr;
	Gtk::Scale* scale_s_min = nullptr;
	Gtk::Scale* scale_v_max = nullptr;
	Gtk::Scale* scale_v_min = nullptr;
	Gtk::Scale* scale_gain  = nullptr;
	Gtk::Scale* scale_rotation = nullptr;
	Gtk::Scale* scale_contrast = nullptr;
	Gtk::Scale* scale_exposure = nullptr;
	Gtk::Scale* scale_brightness = nullptr;
	Gtk::Scale* scale_saturation = nullptr;

	// File Chooser - save/load file
	Gtk::FileChooserDialog* file_chooser = nullptr;

	// Entry
	Gtk::Entry* entry_chooser = nullptr;

	// Button
	Gtk::Button* button_load_dialog = nullptr;
	Gtk::Button* button_save_dialog = nullptr;
	Gtk::Button* button_save_calibration = nullptr;
	Gtk::Button* button_load_calibration = nullptr;
	Gtk::ToggleButton* togglebutton_cut_mode = nullptr;

	// Control method
	void initializeWidget();
	void setSignalWidget();
	void builderWidget();
	void bindWidgetToCalibrationRoutine();

	void cameraThreadWrapper();
    void windowThreadWrapper();
	
public:
	CalibrationWindow();
	virtual ~CalibrationWindow();
	void run(int argc, char *argv[]) override;
};
#endif
