/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef VISION_H_
#define VISION_H_

#include "Constants.h"
#include "Utils/CRUD/CRUD.h"
#include "Robot.h"
#include "unistd.h"

class Vision{
private:
	CRUD crud;
	vector<Robot>* robot;
	Robot *ball;

	int *idCam;
	bool *device;
	string *imagePath;
	float *rotation;
	Rect *cut;
	int *visionStatus;

	bool timer;
	int idLoop;
	int topDerive, currentDerive;
	float deriveTime;
	bool okDerive;

	VideoCapture cam;
	Mat input, output, response;
	Point boundTop, boundBottom;
	
	// Qualquer blob colorido escolhido por algum time encontrado pela visão
	vector<vector<Point> > labels;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	
	void applyRotation();
	void cutImage();
	void invertField();
	void searchLabelBall();
	void searchLabelsTeams(int);
	void searchLabelsRobots(int);
	void convertToHSV();
	bool itsALabel(Rect rect);
	bool validPoint(Point p);

	void recognizeObjects();
	void fakeObjects();		// Auxilia o desenvolvimento
	//void filterHighPass();
	//void filterKalman();

	
public:
	Vision();

	void init();
	void finish();
	void recognize();

	void setIdCamera(int *id);
	void setDevice(bool *device);
	void setImagePath(string *s);
	void setRobots(vector<Robot>*);
	void setBall(Robot *ball);
	void setCut(Rect *cut);
	void setRotation(float*);
	void setVisionStatus(int*);

	void setTime(bool);
	void setDeriveTime(float i);

	bool* getDevice();
	int* getIdCamera();
	string* getImagePath(); 
	vector<Robot>* getRobots();
	Robot* getBall();
	Rect* getCut();
	float* getRotation();
	int* getVisionStatus();
	
	Mat getImage();
	void storesDataDerive();

	#ifdef DEBUG
		void convertToRGB();
		void drawVision();
	#endif
};

#endif