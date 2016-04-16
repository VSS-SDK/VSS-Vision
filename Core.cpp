#include "Core.h"

Core::Core(){
	guiStatus = RUNNING;
    visionStatus = strategyStatus = systemStatus = STOPPED;
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
		strategyStatus = STARTING;

		visionThread = new thread(bind(&Core::vision_thread, this));
		strategyThread = new thread(bind(&Core::strategy_thread, this));

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
			strategyStatus = ENDING;

			visionThread->join();
			strategyThread->join();

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
	protoState.set_sir1_x(robot->at(0).getPosition().x);
    protoState.set_sir1_y(robot->at(0).getPosition().y);
    protoState.set_sir1_theta(robot->at(0).getOrientation().y);

    protoState.set_sir2_x(robot->at(1).getPosition().x);
    protoState.set_sir2_y(robot->at(1).getPosition().y);
    protoState.set_sir2_theta(robot->at(1).getOrientation().y);

    protoState.set_sir3_x(robot->at(2).getPosition().x);
    protoState.set_sir3_y(robot->at(2).getPosition().y);
    protoState.set_sir3_theta(robot->at(2).getPosition().y);

    protoState.set_adv1_x(robot->at(3).getPosition().x);
    protoState.set_adv1_y(robot->at(3).getPosition().y);
    protoState.set_adv1_theta(robot->at(3).getOrientation().y);

    protoState.set_adv2_x(robot->at(4).getPosition().x);
    protoState.set_adv2_y(robot->at(4).getPosition().y);
    protoState.set_adv2_theta(robot->at(4).getOrientation().y);

    protoState.set_adv3_x(robot->at(5).getPosition().x);
    protoState.set_adv3_y(robot->at(5).getPosition().y);
    protoState.set_adv3_theta(robot->at(5).getOrientation().y);

    protoState.set_ball_x(ball->getPosition().x);
    protoState.set_ball_y(ball->getPosition().y);
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

void Core::strategy_thread(){
	Zocket zocket;
	zocket.connectServer();
	
	while(strategyStatus != ENDING){
		if(hasNewState){
			strategyStatus = RUNNING;
			zocket.setState(protoState);
			//zocket.showState();
			zocket.sendState();
			hasNewState = false;
		}else{
			strategyStatus = PAUSED;
			usleep(33333);
		}
	}
	strategyStatus = FINISHED;
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

int Core::getStrategyStatus(){
	return strategyStatus;
}

int Core::getTypeRun(){
	return typeRun;
}