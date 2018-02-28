/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef CAMERA_CALIBRATION_H
#define CAMERA_CALIBRATION_H

#include "gtkmm.h"
#include "ICameraCalibration.h"
#include "iostream"
#include <string>
#include <sstream>
#include <cstddef>
#include <Interfaces/ICalibrationBuilder.h>
#include "ICalibrationRepository.h"

class CameraCalibration : public ICameraCalibration{
public:
	CameraCalibration(ICalibrationRepository *calibrationRepository, ICalibrationBuilder *calibrationBuilder);

	bool on_keyboard(GdkEventKey* event, Gtk::Window*) override;

	void on_signal_select_dialog(Gtk::FileChooserDialog* , Gtk::Entry*) override;
	void on_button_save_calibration(Gtk::FileChooserDialog* , Gtk::Entry*) override;
	void on_button_load_calibration(Gtk::FileChooserDialog* , Gtk::Entry*) override;
	void on_button_load_dialog(Gtk::FileChooserDialog* , Gtk::Entry*) override;
	void on_button_save_dialog(Gtk::FileChooserDialog* , Gtk::Entry*) override;

	void on_combo_box_input_path(Gtk::ComboBoxText*) override;
	void on_combo_box_color_team1(Gtk::ComboBoxText*) override;
	void on_combo_box_color_team2(Gtk::ComboBoxText*) override;
	void on_combo_box_color_robot1(Gtk::ComboBoxText*) override;
	void on_combo_box_color_robot2(Gtk::ComboBoxText*) override;
	void on_combo_box_color_robot3(Gtk::ComboBoxText*) override;
	void on_combo_box_color_robot4(Gtk::ComboBoxText*) override;
	void on_combo_box_color_robot5(Gtk::ComboBoxText*) override;
	void on_combo_box_color_select(Gtk::ComboBoxText*) override;

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

	void bind_scale_h_max(Gtk::Scale*) override;
	void bind_scale_h_min(Gtk::Scale*) override;
	void bind_scale_s_max(Gtk::Scale*) override;
	void bind_scale_s_min(Gtk::Scale*) override;
	void bind_scale_v_max(Gtk::Scale*) override;
	void bind_scale_v_min(Gtk::Scale*) override;

	void bind_scale_gain(Gtk::Scale*) override;
	void bind_scale_contrast(Gtk::Scale*) override;
	void bind_scale_rotation(Gtk::Scale*) override;
	void bind_scale_exposure(Gtk::Scale*) override;
	void bind_scale_brightness(Gtk::Scale*) override;
	void bind_scale_saturation(Gtk::Scale*) override;

private:
	ICalibrationBuilder *calibrationBuilder;
	ICalibrationRepository *calibrationRepository;

	Calibration calibration;

	ColorType actualColorToCalibrate;

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

	void applyActualColorRangeToSlidersHSV(ColorType type);

    ColorRange getColorRangeFromCalibration(ColorType type);

    void setColorRangePart(ColorRangePart part, double value);
};

#endif // CAMERA_CALIBRATION_H
