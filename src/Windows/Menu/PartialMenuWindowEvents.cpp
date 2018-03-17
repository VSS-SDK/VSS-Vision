/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include <Windows/Menu/MenuWindow.h>

bool MenuWindow::onKeyboard(GdkEventKey* event, Gtk::Window*) {
    if(event->keyval == GDK_KEY_space) {
        window->hide();
    } else if(event->keyval == GDK_KEY_Return) {
        window->hide();
    } else if(event->keyval == GDK_KEY_Escape) {
        window->hide();
    }
    return true;
}

void MenuWindow::onButtonVision() {

}

void MenuWindow::onButtonCalibration() {

}