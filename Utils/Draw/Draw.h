/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef DRAW_H_
#define DRAW_H_

#include <GL/glew.h>		// Ambiente Gráfico
#include <GLFW/glfw3.h>		// Ambiente Gráfico

#include "../../Constants.h"
#include "../../Robot.h"

using namespace common;

class Draw{
protected:
	int idCamera;
	bool timePlay;
	glRigidBody glCam;
	glRigidBody floor;
	glRigidBody walls[6];
	glRigidBody goal[2];
	glRigidBody goalW[2][3];
	glRigidBody lines[7];

	void drawCube(glRigidBody);
    void drawSphere(double, int, int);

    void drawBall(btVector3);
    void drawRobot(Robot);

    void positionCam();
    void drawField();

    btVector3 handlePosition(btVector3);

public:
	Draw();

    void drawWorld(vector<Robot>, btVector3);
    void setCamera(int);
    void setTimePlay(bool);
    void setColorGoal(int, Pixel);
};

#endif	