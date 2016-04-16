/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#include "Utils/Commons/Commons.h"

using namespace common;

class Robot{
private:
	int id, team;

	// Kinematics
	btVector3 position;
	btVector3 orientation;
	btVector3 linearVelocity;
	btVector3 angularVelocity;

	// Colors
	Pixel colorTeam, colorRobot;
	VisionColor visionColorTeam, visionColorRobot;
	int idColorTeam, idColorRobot;

public:
	Robot();	
	Robot(int);
	Robot(Robot*);

	void setId(int);
	void setTeam(int);
	void setPosition(btVector3);
	void setOrientation(btVector3);
	void setLinearVelocity(btVector3);
	void setAngularVelocity(btVector3);
	void setColorTeam(Pixel);
	void setColorRobot(Pixel);
	void setVisionColorTeam(VisionColor);
	void setVisionColorRobot(VisionColor);
	void setIdColorTeam(int);
	void setIdColorRobot(int);

	int getId();
	int getTeam();
	btVector3 getPosition();
	btVector3 getOrientation();
	btVector3 getLinearVelocity();
	btVector3 getAngularVelocity();
	Pixel getColorTeam();
	Pixel getColorRobot();
	VisionColor getVisionColorTeam();
	VisionColor getVisionColorRobot();
	int getIdColorTeam();
	int getIdColorRobot();
};

#endif	