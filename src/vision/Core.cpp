/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "Core.h"

Core::Core(){
	guiStatus = RUNNING;
    visionStatus = interfaceStatus = systemStatus = STOPPED;
    typeRun = NONE;
    idData = 0;
    hasNewState = false;
}

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

void Core::start(){
	systemStatus = STARTING;
}

void Core::finishVSS(){
	systemStatus = STOPPED;
	visionStatus = ENDING;
}

void Core::updateState(){
	cout << "teste" << endl;
	global_state = vss_state::Global_State();
	global_state.set_id(0);

	vss_state::Ball_State *ball_s = global_state.add_balls();
	ball_s->set_x(ball->getPosition().x);
	ball_s->set_y(ball->getPosition().y);

	for(int i = 0 ; i < 3 ; i++){
		vss_state::Robot_State *robot_s = global_state.add_robots_yellow();
		robot_s->set_x(robot->at(i).getPosition().x);
		robot_s->set_y(robot->at(i).getPosition().y);
		robot_s->set_yaw(robot->at(i).getOrientation().y);
	}

	for(int i = 0 ; i < 3 ; i++){
		vss_state::Robot_State *robot_s = global_state.add_robots_blue();
		robot_s->set_x(robot->at(i+3).getPosition().x);
		robot_s->set_y(robot->at(i+3).getPosition().y);
		robot_s->set_yaw(robot->at(i+3).getOrientation().y);
	}

	interface.printState();
    hasNewState = true;
}

void Core::vision_thread(){
	vision.setVisionStatus(&visionStatus);
	vision.setIdCamera(idCam);
	vision.setDevice(device);
	vision.setImagePath(imagePath);
    vision.setRobots(robot);
    vision.setBall(ball);
    vision.setRotation(rotation);
    vision.setCut(cut);
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

void Core::interface_thread(){
	interface.createSocketSendState(&global_state);

	while(interfaceStatus != ENDING){
		if(hasNewState){
			interfaceStatus = RUNNING;
			interface.sendState();
			hasNewState = false;
		}else{
			interfaceStatus = PAUSED;
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

void Core::setTypeRun(int typeRun){
	this->typeRun = typeRun;
}

void Core::setCut(Rect *cut){
	this->cut = cut;
}

void Core::setRotation(float *rotation){
	this->rotation = rotation;
}

void Core::setStrategies(vector<string> *strategies){
	this->strategies = strategies;
}

void Core::setStrategySir(string *strategySir){
	this->strategySir = strategySir;
	cout << *strategySir << endl;
}

void Core::setStrategyAdv(string *strategyAdv){
	this->strategyAdv = strategyAdv;
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

int Core::getTypeRun(){
	return typeRun;
}