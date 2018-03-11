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
#include <Interfaces/IImageInputReader.h>
#include <thread>
#include <Interfaces/IColorRecognizer.h>
#include "GImage.h"
#include "opencv2/highgui/highgui.hpp"

using namespace std;

class CalibrationWindow : public ICalibrationWindow {
public:
    CalibrationWindow();
    virtual ~CalibrationWindow();

    void run(int argc, char *argv[]) override;

    bool on_keyboard(GdkEventKey* event, Gtk::Window*) override;

    void on_signal_select_dialog(Gtk::FileChooserDialog* , Gtk::Entry*) override;
    void on_button_load_dialog(Gtk::FileChooserDialog* , Gtk::Entry*) override;
    void on_button_save_dialog(Gtk::FileChooserDialog* , Gtk::Entry*) override;
    void on_button_save_calibration(Gtk::FileChooserDialog* , Gtk::Entry*) override;
    void on_button_load_calibration(Gtk::FileChooserDialog* , Gtk::Entry*, std::vector<Gtk::Scale*>) override;

    void on_combo_box_input_path(Gtk::ComboBoxText*) override;
    void on_combo_box_color_team1(Gtk::ComboBoxText*) override;
    void on_combo_box_color_team2(Gtk::ComboBoxText*) override;
    void on_combo_box_color_robot1(Gtk::ComboBoxText*) override;
    void on_combo_box_color_robot2(Gtk::ComboBoxText*) override;
    void on_combo_box_color_robot3(Gtk::ComboBoxText*) override;
    void on_combo_box_color_robot4(Gtk::ComboBoxText*) override;
    void on_combo_box_color_robot5(Gtk::ComboBoxText*) override;
    void on_combo_box_color_select(Gtk::ComboBoxText*, std::vector<Gtk::Scale*>) override;

    void on_scale_h_max(Gtk::Scale*) override;
    void on_scale_h_min(Gtk::Scale*) override;
    void on_scale_s_max(Gtk::Scale*) override;
    void on_scale_s_min(Gtk::Scale*) override;
    void on_scale_v_max(Gtk::Scale*) override;
    void on_scale_v_min(Gtk::Scale*) override;

    void on_scale_gain(Gtk::Scale*) override;
    void on_scale_contrast(Gtk::Scale*) override;
    void on_scale_rotation(Gtk::Scale*) override;
    void on_scale_exposure(Gtk::Scale*) override;
    void on_scale_brightness(Gtk::Scale*) override;
    void on_scale_saturation(Gtk::Scale*) override;

    void on_radio_button_image(Gtk::RadioButton*) override;
    void on_radio_button_video(Gtk::RadioButton*) override;
    void on_toggle_button_cut_mode(Gtk::ToggleButton*) override;
    void on_radio_button_camera(Gtk::RadioButton*) override;


private:
	// Threads
	std::thread *threadCameraReader;
    std::thread *threadWindowControl;

	Glib::Dispatcher dispatcher_frame;

	// Classes
	ICalibrationRepository *calibrationRepository;
	IImageInputReader *inputReader;
	ICalibrationBuilder *calibrationBuilder;
    ICalibrationBuilder *calibrationBuilderFromRepository;
	IColorRecognizer *colorRecognizer;

    Calibration calibration;
    ColorRange *actualColorRange;
	unsigned int actualColorRangeIndex;

	// Window - calibration
	Gtk::Window* window = nullptr;

	// Opencv image
	cv::Mat frame;	
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
	std::vector<Gtk::Scale*> scale_hsv;
	std::vector<Gtk::Scale*> scale_cam_config;

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
	void setSignals();
	void builderWidget();

	void cameraThreadWrapper();
    void windowThreadWrapper();

	// Update frame
	void setNewFrame();
	void receiveNewFrame(cv::Mat);

    void applyActualColorRangeToSlidersHSV(ColorType type, std::vector<Gtk::Scale*>);
    void defineActualColorRange(ColorType type);
};
#endif
