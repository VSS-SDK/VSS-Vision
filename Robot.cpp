/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "Robot.h"

Robot::Robot(){
	id = 0;
	team = 0;

	position = btVector3(0, 0, 0);
	orientation = btVector3(0, 0, 0);
	linearVelocity = btVector3(0, 0, 0);
	angularVelocity = btVector3(0, 0, 0);
	colorTeam = Pixel(255, 190, 0);
	colorRobot = Pixel(0, 0, 255);
}

Robot::Robot(int id){
	this->id = id;
	team = 0;

	position = btVector3(0, 0, 0);
	orientation = btVector3(0, 0, 0);
	linearVelocity = btVector3(0, 0, 0);
	angularVelocity = btVector3(0, 0, 0);
	colorTeam = Pixel(255, 190, 0);
	colorRobot = Pixel(0, 0, 255);
}

Robot::Robot(Robot *r){
	id = r->id;
	team = r->team;

	position = r->position;
	orientation = r->orientation;
	linearVelocity = r->linearVelocity;
	angularVelocity = r->angularVelocity;
	colorTeam = r->colorTeam;
	colorRobot = r->colorRobot;
}

void Robot::setId(int id){
	this->id = id;
}

void Robot::setTeam(int team){
	this->team = team;
}

void Robot::setPosition(btVector3 position){
	this->position = position;
}

void Robot::setOrientation(btVector3 orientation){
	this->orientation = orientation;
}

void Robot::setLinearVelocity(btVector3 linearVelocity){
	this->linearVelocity = linearVelocity;
}

void Robot::setAngularVelocity(btVector3 angularVelocity){
	this->angularVelocity = angularVelocity;
}

void Robot::setColorTeam(Pixel colorTeam){
	this->colorTeam = colorTeam;
}

void Robot::setColorRobot(Pixel colorRobot){
	this->colorRobot = colorRobot;
}

void Robot::setVisionColorTeam(VisionColor visionColorTeam){
	this->visionColorTeam = visionColorTeam;
}

void Robot::setVisionColorRobot(VisionColor visionColorRobot){
	this->visionColorRobot = visionColorRobot;
}

void Robot::setIdColorTeam(int idColorTeam){
	this->idColorTeam = idColorTeam;
}

void Robot::setIdColorRobot(int idColorRobot){
	this->idColorRobot = idColorRobot;
}

int Robot::getId(){
	return id;
}

int Robot::getTeam(){
	return team;
}

btVector3 Robot::getPosition(){
	return position;
}

btVector3 Robot::getOrientation(){
	return orientation;
}

btVector3 Robot::getLinearVelocity(){
	return linearVelocity;
}

btVector3 Robot::getAngularVelocity(){
	return angularVelocity;
}

Pixel Robot::getColorTeam(){
	return colorTeam;
}

Pixel Robot::getColorRobot(){
	return colorRobot;
}

VisionColor Robot::getVisionColorTeam(){
	return visionColorTeam;
}

VisionColor Robot::getVisionColorRobot(){
	return visionColorRobot;
}

int Robot::getIdColorTeam(){
	return idColorTeam;
}

int Robot::getIdColorRobot(){
	return idColorRobot;
}