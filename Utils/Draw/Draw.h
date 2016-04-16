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