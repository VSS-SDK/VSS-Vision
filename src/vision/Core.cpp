/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "Core.h"

//! Addendum
//! --------
//! 
//! > Initialize control variables
Core::Core(){
	guiStatus = RUNNING;
    visionStatus = interfaceStatus = systemStatus = STOPPED;
    typeRun = NONE;
    idData = 0;
    hasNewState = false;
}


//! Addendum
//! --------
//! 
//! > Initialize beyond all threads, all threads status:
//! > - STOPPED
//! > - STARTING (Select this)
//! > - RUNNING
//! > - PAUSING
//! > - PAUSED
//! > - ENDING
//! > - FINISHED
//! > - CRASHED
void Core::init(){
	while(systemStatus != ENDING){
		while(systemStatus == STOPPED){
			usleep(100000);
			//cout << "STOPPED" << endl;
		}

		visionStatus = STARTING;
		interfaceStatus = STARTING;

		visionThread = new thread(bind(&Core::vision_thread, this));
		interfaceThread = new thread(bind(&Core::interface_thread, this));

		while(systemStatus == STARTING){
			//cout << "STARTING" << endl;
			usleep(100000);
		}

		while(systemStatus == RUNNING){
			//cout << "RUNNING" << endl;
			usleep(100000);
		}

		if(systemStatus == ENDING){
			visionStatus = ENDING;
			interfaceStatus = ENDING;

			visionThread->join();
			interfaceThread->join();

			systemStatus = STOPPED;
		}
	}	
}

//! Addendum
//! --------
//! 
//! > Must have this method, cause GUI instance Core.
void Core::start(){
	systemStatus = STARTING;
}

//! Addendum
//! --------
//! 
//! > Must have this method, cause GUI instance Core.
void Core::finish(){
	systemStatus = STOPPED;
	visionStatus = ENDING;
}

//! Addendum
//! --------
//! 
//! > The data vss_state::Global_State states carry all states "Poses" of robots and ball.
//! 
//! > It's a data of Interface that allows the communication between VSS-SampleStrategy, VSS-Vision, VSS-Simulator and VSS-Viewer.
//! 
//! Was created by a compilation of proto file.  See: [Protobuf](https://developers.google.com/protocol-buffers/).
void Core::updateState(){
	idData++;
	cout << idData << endl;
	//cout << "teste" << endl;
	global_state = vss_state::Global_State();
	global_state.set_id(idData);
	global_state.set_origin(true);

	vss_state::Ball_State *ball_s = global_state.add_balls();
	ball_s->set_x(ball->getPosition().getX());
	ball_s->set_y(ball->getPosition().getY());

	for(int i = 0 ; i < 3 ; i++){
		vss_state::Robot_State *robot_s = global_state.add_robots_blue();
		robot_s->set_x(robot->at(i).getPosition().getX());
		robot_s->set_y(robot->at(i).getPosition().getY());
		robot_s->set_yaw(robot->at(i).getOrientation().getY());

		vss_state::RGB *color = robot_s->mutable_color();
		color->set_r(robot->at(i).getColorRobot().rgb[0]);
		color->set_g(robot->at(i).getColorRobot().rgb[1]);
		color->set_b(robot->at(i).getColorRobot().rgb[2]);
	}

	for(int i = 0 ; i < 3 ; i++){
		vss_state::Robot_State *robot_s = global_state.add_robots_yellow();
		robot_s->set_x(robot->at(i+3).getPosition().getX());
		robot_s->set_y(robot->at(i+3).getPosition().getY());
		robot_s->set_yaw(robot->at(i+3).getOrientation().getY());

		vss_state::RGB *color = robot_s->mutable_color();
		color->set_r(robot->at(i+3).getColorRobot().rgb[0]);
		color->set_g(robot->at(i+3).getColorRobot().rgb[1]);
		color->set_b(robot->at(i+3).getColorRobot().rgb[2]);
	}

	//interface.printState();
    hasNewState = true;
}


//! Addendum
//! --------
//!
//!
void Core::vision_thread(){
	//! > Initializes the configuration of execution made by user in GUI, like:
	//! > - If user select camera or image
	//! > - Which camera or image the user selected
	vision.setVisionStatus(&visionStatus);
	vision.setIdCamera(idCam);
	vision.setDevice(device);
	vision.setImagePath(imagePath);
    vision.setRobots(robot);
    vision.setBall(ball);
    vision.setRotation(rotation);
    vision.setCut(cut);

    //! > Test the input device for 1 second after start the thread loop.
	vision.init();

	visionStatus = RUNNING;
	while(visionStatus != ENDING){
		//cout << "VISION" << endl;
		vision.recognize();
		updateState();
	}

	vision.finish();
	visionStatus = FINISHED;
}

//! Addendum
//! --------
//!
//!
void Core::interface_thread(){
	//! > Create a socket using [ZMQ](http://zeromq.org/).
	interface.createSocketSendState(&global_state);

	//! > Only send data if have a new one.
	while(interfaceStatus != ENDING){
		if(hasNewState){
			interfaceStatus = RUNNING;
			interface.sendState();
			hasNewState = false;
		}else{
			interfaceStatus = PAUSED;
			//! > Works with 30Hz (30Fps)
			usleep(33333);
		}
	}
	interfaceStatus = FINISHED;
}

void Core::setDevice(bool* device){
	this->device = device;
}

void Core::setIdCamera(int* id){
	this->idCam = id;
}

void Core::setImagePath(string* imagePath){
	this->imagePath = imagePath;
}

void Core::setRobots(vector<Robot> *robot){
	this->robot = robot;
}

void Core::setBall(Robot *ball){
	this->ball = ball;
}

void Core::setCut(Rect *cut){
	this->cut = cut;
}

void Core::setRotation(float *rotation){
	this->rotation = rotation;
}

bool* Core::getDevice(){
	return device;
}

int* Core::getIdCamera(){
	return idCam;
}

string* Core::getImagePath(){
	return imagePath;
}

vector<Robot>* Core::getRobots(){
	return robot;
}

Robot* Core::getBall(){
	return ball;
}

Rect* Core::getCut(){
	return cut;
}

float* Core::getRotation(){
	return rotation;
}

int Core::getVisionStatus(){
	return visionStatus;
}

int Core::getInterfaceStatus(){
	return interfaceStatus;
}