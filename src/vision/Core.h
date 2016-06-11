/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef CORE_H_
#define CORE_H_

#include "unistd.h"
#include "thread"
#include "Vision.h"
#include "Utils/interface/interface.h"

//! This class is responsible for control the Vision thread and the Interface thread.
class Core{
protected:
    Vision vision;
    Interface interface;
    
    vss_state::Global_State global_state;
    int idData;
    bool hasNewState;
    
    int guiStatus;
    int visionStatus;
    int interfaceStatus;
    int systemStatus;

    thread *visionThread;
    thread *interfaceThread;

    vector<Robot> *robot;
    Robot *ball;
    Rect *cut;
    float *rotation;

    int *idCam;
    bool *device;
    string *imagePath;
    int typeRun;

    vector<string> logs;
public:
    //! Construtor
    Core();

    //! Method responsible for initialize the software: control variables and threads.
    void init();

    //! Method responsible for handle the thread of computer Vision, getting new states of robots and ball.
    void vision_thread();

    //! Method responsible for handle the thread of Interface, sending data to VSS-SampleStrategy and VSS-Viewer.
    void interface_thread();
   
    //! Method responsible for update de vss_state::Global_State with new states tracking from Vision thread.
    void updateState();     // Protobuf+ZMQ

    //! Method responsible for return the state of Vision thread: STOPPED, STARTING, RUNNING, PAUSING, PAUSED, ENDING, FINISHED, CRASHED.
    int getVisionStatus();

    //! Method responsible for return the state of Interface thread: STOPPED, STARTING, RUNNING, PAUSING, PAUSED, ENDING, FINISHED, CRASHED.
    int getInterfaceStatus();

    //! Method responsible for start the core via GUI.
    void start();

    //! Method responsible for finish the core via GUI.
    void finish();

    //! Method responsible for set a pointer of device, if the software use a camera of an image.
    void setDevice(bool *device);

    //! Method responsible for set a pointer of idCamera, which camera use.
    void setIdCamera(int *id);

    //! Method responsible for set a pointer of imagePath, which image use.
    void setImagePath(string *imagePath);

    //! Method responsible for set a pointer of the vector of robots, all the robots.
    void setRobots(vector<Robot>*);

    //! Method responsible for set a pointer of ball.
    void setBall(Robot*);

    //! Method responsible for set a pointer of rotation, the rotation in Z of input image.
    void setRotation(float*);

    //! Method responsible for set a pointer of cut, the points of cut of input image.
    void setCut(Rect*);

    //! Method responsible for get a pointer of device, if the software use a camera of an image.
    bool* getDevice();

    //! Method responsible for get a pointer of idCamera, which camera use.
    int* getIdCamera();

    //! Method responsible for get a pointer of imagePath, which image use.
    string* getImagePath();

    //! Method responsible for get a pointer of the vector of robots, all the robots.
    vector<Robot>* getRobots();

    //! Method responsible for get a pointer of ball.
    Robot* getBall();

    //! Method responsible for get a pointer of rotation, the rotation in Z of input image.
    float* getRotation();

    //! Method responsible for get a pointer of cut, the points of cut of input image.
    Rect* getCut();

};

#endif 