/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef GUI_H_
#define GUI_H_

#include "thread"
#include "vector"

#include "Utils/Imgui/imgui.h"            
#include "Utils/Imgui/imgui_impl_glfw.h"  
            
#include "Utils/Draw/Draw.h"
#include "Core.h"
#include "Utils/CRUD/CRUD.h"

using namespace common;

static void error_callback(int error, const char* description);

class GUI{
private:
    Core core;
    CRUD crud;
    Draw draw;

    thread *coreThread;
    thread *guiThread;

    vector<string> errors;

    TeamConfiguration teamConfig[2];
    vector<Robot> robot;
    Robot ball;

    string name;
    int width, height;

    bool show_window_play, show_test_window, show_warning_window, show_configteam_window, show_status_window, show_credits_window;

    ImVec4 clear_color;
    GLFWwindow* window;
    bool report;
    int teamSelected;

    bool timePlay;
    bool setCalibrationPosition;
    string pathImage;
    int idCamera;

    int useCamera;
    bool device;
    int teamSirOk;
    int teamAdvOk;

    vector<string> devices;
    vector<string> images;

    vector<Pixel> colors;               // RGB
    vector<VisionColor> visionColors;   // HSV
    float rotation;
    Rect cut;
    
    void getAllDevices();
    void getAllImages();
    
    void setRobotsDefaultPosition();
    void loadAllColors();

    void guiMainMenu();
    void guiWindowPlay();
    void guiWindowWarning();
    void guiWindowConfigTeam(int);
    void guiWindowStatus();
    void guiWindowCredits();

    void guiShowWindows();
    void checkThings();

public:
    GUI();

    void init();

    void gui_thread();
    void core_thread();

    void release();
    void loop();

    void setWindowName(string name);
    void setWidth(int width);
    void setHeight(int height);

    string getWindowName();
    int getWidth();
    int getHeight();
};

#endif 