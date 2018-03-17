/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include <Windows/Menu/MenuWindow.h>

MenuWindow::MenuWindow(){
}

MenuWindow::~MenuWindow(){
}

void MenuWindow::run(int argc, char *argv[]){
  Gtk::Main kit(argc, argv);

  threadWindowControl = new thread( std::bind( &MenuWindow::windowThreadWrapper, this ));
  threadWindowControl->join();
}

void MenuWindow::windowThreadWrapper() {
  builderWidget();
  setSignals();
  initializeWidget();

  Gtk::Main::run(*window);
}

void MenuWindow::initializeWidget(){
  //window->maximize();
  window->show_all_children();
}

void MenuWindow::builderWidget(){

  auto builder = Gtk::Builder::create();

  try {
    builder->add_from_file("../glade/Menu.glade");

    builder->get_widget("window", window);

    builder->get_widget("button_vision", buttonVision);
    builder->get_widget("button_calibration", buttonCalibration);

  } catch(const Glib::FileError& ex) {
    std::cerr << "FileError: " << ex.what() << std::endl;

  } catch(const Glib::MarkupError& ex) {
    std::cerr << "MarkupError: " << ex.what() << std::endl;

  } catch(const Gtk::BuilderError& ex) {
    std::cerr << "BuilderError: " << ex.what() << std::endl;
  }
}

void MenuWindow::setSignals(){ 
  window->signal_key_press_event().connect(sigc::bind<Gtk::Window*>(sigc::mem_fun(this, &IMenuWindow::onKeyboard), window) , false);

  buttonVision->signal_clicked().connect(sigc::mem_fun(this, &IMenuWindow::onButtonVision));
  buttonCalibration->signal_clicked().connect(sigc::mem_fun(this, &IMenuWindow::onButtonCalibration));
}