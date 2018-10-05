/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef IGPROGRAM_H_
#define IGPROGRAM_H_

#include "gtkmm.h"
#include <gtkmm/filechooserdialog.h>
#include <gtkmm/entry.h>
#include <gtkmm/comboboxtext.h>
#include "iostream"

class ICalibrationWindow {
public:
    
    virtual int run(int argc, char *argv[]) = 0;

    virtual bool onKeyboard(GdkEventKey*, Gtk::Window*) = 0;

    virtual void onButtonOpenSaveDialog(Gtk::FileChooserDialog*, Gtk::Entry*) = 0;
	virtual void onButtonOpenLoadDialog(Gtk::FileChooserDialog*, Gtk::Entry*) = 0;

    virtual void onButtonSave(Gtk::FileChooserDialog*, Gtk::Entry*) = 0;
    virtual void onButtonLoad(Gtk::FileChooserDialog*, Gtk::Entry*, Gtk::Scale*) = 0;

    virtual void onScaleHMAX(Gtk::Scale*) = 0;
    virtual void onScaleHMIN(Gtk::Scale*) = 0;
    virtual void onScaleSMAX(Gtk::Scale*) = 0;
    virtual void onScaleSMIN(Gtk::Scale*) = 0;
    virtual void onScaleVMAX(Gtk::Scale*) = 0;
    virtual void onScaleVMIN(Gtk::Scale*) = 0;

    virtual void onScaleRotation(Gtk::Scale*) = 0;

    virtual void onRadioButtonImage(Gtk::RadioButton*) = 0;
    virtual void onRadioButtonVideo(Gtk::RadioButton*) = 0;
    virtual void onRadioButtonCamera(Gtk::RadioButton*) = 0;

    virtual void onToggleButtonCutMode(Gtk::ToggleButton*) = 0;
    virtual void onButtonRestoreCut() = 0;

    virtual void onSignalSelectFileInDialog(Gtk::FileChooserDialog*, Gtk::Entry*) = 0;
	
    virtual void onComboBoxSelectPath(Gtk::ComboBox*) = 0;
    virtual void onComboBoxSelectColor(Gtk::ComboBox*, std::vector<Gtk::Scale*>) = 0;

};
#endif