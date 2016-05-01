/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "Vision.h"

Vision::Vision(){
	idLoop = 0;
	timer = false;
	topDerive = 5;
	currentDerive = 0;
	okDerive = false;
}

void Vision::init(){	
	if(*device){
		cam = VideoCapture(*idCam);	
	}else{
		response = imread(*imagePath);
	}

	for(int i = 0 ; i < 30 ; i++){
		if(*device)
			cam >> input;
		else
			input = response.clone();
	}
}

void Vision::finish(){
	for(int i = 0 ; i < 30 ; i++){
		destroyAllWindows();
	}
	*visionStatus = FINISHED;
}

#ifdef DEBUG
	void Vision::convertToRGB(){
		cvtColor(input, input, COLOR_HSV2RGB);
	}

	void Vision::drawVision(){
		for(int i = 0 ; i < labels.size() ; i++){
			for(int j = 0 ; j < labels.at(i).size() ; j++){
				rectangle(input, Point(labels.at(i).at(j).x + 5, labels.at(i).at(j).y + 5), Point(labels.at(i).at(j).x - 5, labels.at(i).at(j).y - 5), Scalar(0,0,255));
			}
		}

		convertToRGB();
		imshow("input", input);
		waitKey(1);
	}
#endif

void Vision::setVisionStatus(int* visionStatus){
	this->visionStatus;
}

int* Vision::getVisionStatus(){
	return visionStatus;
}

void Vision::recognize(){
	labels.clear();
	
	if(*device){
		cam >> input;
	}else{
		input = response.clone();
		usleep(33333);
	}

	applyRotation(); // Rotação do campo
	cutImage();

	if(timer)	
		invertField();	// Caso seja segundo tempo TODO: trocar de campo

	convertToHSV();

	searchLabelBall();

	for(int i = 0 ; i < 2 ; i++){
		searchLabelsTeams(i);
	}

	for(int i = 0 ; i < 3 ; i++){
		searchLabelsRobots(i);
	}

	#ifdef DEBUG
		drawVision();
	#endif

	//fillLabels();
	recognizeObjects();
	//fakeObjects();

	if(!*device)
		usleep(33333);
}

void Vision::searchLabelBall(){
	vector<Point> game;	
	VisionColor hsv;
	
	int hsvMin[3];
	int hsvMax[3];

	hsv = ball->getVisionColorTeam();
	
	for(int i = 0 ; i < 3 ; i++){
		hsvMin[i] = hsv.min.rgb[i];
		hsvMax[i] = hsv.max.rgb[i];
	}

	inRange(input,
		Scalar(hsvMin[0], hsvMin[1], hsvMin[2]),
		Scalar(hsvMax[0], hsvMax[1], hsvMax[2]),
		output);

	medianBlur(output, output, 3);
	findContours(output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	vector<vector<Point> > contours_poly( contours.size() );
	vector<Rect> boundRect( contours.size() );

	for( int i = 0; i < contours.size(); i++ ){
		approxPolyDP( Mat(contours[i]), contours_poly[i], 0, true );
		boundRect[i] = boundingRect( Mat(contours_poly[i]) );
	}

	for( int i = 0; i< contours.size(); i++ ){
		if(itsALabel(boundRect[i])){
			game.push_back(Point(boundRect[i].x + (boundRect[i].width/2), boundRect[i].y  + (boundRect[i].height/2)));
		}
	}

	labels.push_back(game);
	contours.clear();
	hierarchy.clear();
}

void Vision::searchLabelsTeams(int idTeam){
	vector<Point> game;	
	VisionColor hsv;
	
	int hsvMin[3];
	int hsvMax[3];

	hsv = robot->at(idTeam*3).getVisionColorTeam();
	
	for(int i = 0 ; i < 3 ; i++){
		hsvMin[i] = hsv.min.rgb[i];
		hsvMax[i] = hsv.max.rgb[i];
	}

	inRange(input,
		Scalar(hsvMin[0], hsvMin[1], hsvMin[2]),
		Scalar(hsvMax[0], hsvMax[1], hsvMax[2]),
		output);

	medianBlur(output, output, 3);
	findContours(output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	vector<vector<Point> > contours_poly( contours.size() );
	vector<Rect> boundRect( contours.size() );

	for( int i = 0; i < contours.size(); i++ ){
		approxPolyDP( Mat(contours[i]), contours_poly[i], 0, true );
		boundRect[i] = boundingRect( Mat(contours_poly[i]) );
	}

	for( int i = 0; i< contours.size(); i++ ){
		if(itsALabel(boundRect[i])){
			game.push_back(Point(boundRect[i].x + (boundRect[i].width/2), boundRect[i].y  + (boundRect[i].height/2)));
		}
	}

	labels.push_back(game);
	contours.clear();
	hierarchy.clear();
}

void Vision::searchLabelsRobots(int idRobot){
	vector<Point> game;	
	VisionColor hsv;
	
	int hsvMin[3];
	int hsvMax[3];

	hsv = robot->at(idRobot).getVisionColorRobot();
	
	for(int i = 0 ; i < 3 ; i++){
		hsvMin[i] = hsv.min.rgb[i];
		hsvMax[i] = hsv.max.rgb[i];
	}

	inRange(input,
		Scalar(hsvMin[0], hsvMin[1], hsvMin[2]),
		Scalar(hsvMax[0], hsvMax[1], hsvMax[2]),
		output);

	/*if(idRobot == 2){
		imshow("HSV", input);
		imshow("output", output);
		hsv.show();
	}*/

	medianBlur(output, output, 3);
	findContours(output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	vector<vector<Point> > contours_poly( contours.size() );
	vector<Rect> boundRect( contours.size() );

	for( int i = 0; i < contours.size(); i++ ){
		approxPolyDP( Mat(contours[i]), contours_poly[i], 0, true );
		boundRect[i] = boundingRect( Mat(contours_poly[i]) );
	}

	for( int i = 0; i< contours.size(); i++ ){
		if(itsALabel(boundRect[i])){
			game.push_back(Point(boundRect[i].x + (boundRect[i].width/2), boundRect[i].y  + (boundRect[i].height/2)));
		}
	}

	labels.push_back(game);
	contours.clear();
	hierarchy.clear();
}


bool Vision::validPoint(Point p){
	/*if(p.x < 0 || p.y < 0){
		return false;
	}else{
		return true;
	}*/
	return true;
}

void Vision::recognizeObjects(){
	// Bola
	if(labels.at(0).size() > 0){
		ball->setPosition(btVector3(labels.at(0).at(0).x, labels.at(0).at(0).y, 0));
	}
	// Robôs Adversários
	for(int i = 0 ; i < labels.at(2).size() && i < 3 ; i++){
		if( validPoint(labels.at(2).at(i)) ){
			robot->at(i+3).setPosition(btVector3(labels.at(2).at(i).x, labels.at(2).at(i).y, 0));
		}
	}

	//if(labels.at(1).size() > 0){
	for(int k = 0 ; k < labels.at(1).size() && k < 3 ; k++){
		float distM = 1024;
		int idM = -1;
		int idM0 = -1;
		
		for(int i = 3 ; i < 6 ; i++){
			for(int j = 0 ; j < labels.at(i).size() ; j++){
				float distR = distance(labels.at(1).at(k), labels.at(i).at(j));
				//cout << "3" << ", " << distR << endl;
				if(distR < distM && distR < DISTANCE_MIN){
					distM = distR;
					idM = j;
					idM0 = i;
				}
			}

			if(idM != -1 && idM0 != -1){
				Point mid = midpoint(labels.at(1).at(k), labels.at(idM0).at(idM));
				float ang = angulation(labels.at(1).at(k), labels.at(idM0).at(idM));
				
				//Vetor diferença real entre os pontos da cor do time e a cor do player
				btVector3 vecFront;
				vecFront.x = labels.at(idM0).at(idM).x - labels.at(1).at(k).x;
				vecFront.y = labels.at(idM0).at(idM).y - labels.at(1).at(k).y;

				//Vetor unitário entre os pontos da cor do time e a cor do player para ajustar o eixo X(é sempre 45° do eixo X por conta das tags das cores)
				btVector3 vecZero(sqrt(2.f)/2.f,sqrt(2.f)/2.f,0);

				//Vetor unitário real entre os pontos da cor do time e a cor do player
				float modVecFront = sqrt(vecFront.x*vecFront.x + vecFront.y*vecFront.y);
				if(modVecFront == 0) modVecFront = 0.00001;
				btVector3 uVecFront(vecFront.x/modVecFront,vecFront.y/modVecFront,0);

				//Arco cosseno do ângulo
				float arcAng = uVecFront.x*vecZero.x + uVecFront.y*vecZero.y;

				//Transformação para graus
				float angAux = 180*acos(arcAng)/CV_PI;

				//Se o vetor unitário Y estiver apontando para o eixo negativo, adiciona-se 360° para se oter ângulos entre 0 e 360°
				if(uVecFront.y < 0) angAux = 360 - angAux;

				ang = angAux;
				robot->at(idM0-3).setPosition(btVector3(mid.x, mid.y, 0));
				robot->at(idM0-3).setOrientation(btVector3(0, ang, 0));
				//robot->at(idM0-3).setOrientation(btVector3(0, ang, 0));
			}
		}
	}
} 

void Vision::fakeObjects(){
	for(int i = 0 ; i < 6 ; i++){
		robot->at(i).setPosition(btVector3(100+(i*40), 100, 0));
		robot->at(i).setOrientation(btVector3(0, i*45, 0));
	}

	ball->setPosition(btVector3(400, 100, 0));
}

void Vision::convertToHSV(){
	cvtColor(input, input, COLOR_RGB2HSV);
}

void Vision::applyRotation(){
	Mat aux;
	warpAffine(input, aux, getRotationMatrix2D(Point2f(input.cols/2, input.rows/2), *rotation, 1.0), input.size());
	input = aux;
}

void Vision::invertField(){
	Mat aux;
	warpAffine(input, aux, getRotationMatrix2D(Point2f(input.cols/2, input.rows/2), 180, 1.0), input.size());
	input = aux;
}

void Vision::cutImage(){
	// TODO: Pensar em uma regras melhor, pois pode existir uma config x ou y 0
	if(cut->br().x != 0 || cut->br().y != 0 || cut->tl().x != 0 || cut->tl().y != 0){
		Mat rep, rep2;

		rep = input(*cut);
		
		resize(rep, rep2, Size(640, 480), 0, 0, 0);
		input = rep2.clone();
	}
}

bool Vision::itsALabel(Rect rect){
	float proportion = (float)rect.width/rect.height;
	
	if((rect.width * rect.height) > AREA_MIN && (rect.width * rect.height) < AREA_MAX && proportion > PROPORTION_MIN && proportion < PROPORTION_MAX)
		return true;
	else
		return false;
}

void Vision::setDevice(bool *device){
	this->device = device;
}

void Vision::setIdCamera(int *id){
	this->idCam = id;
}

void Vision::setImagePath(string *imagePath){
	this->imagePath = imagePath;
}

void Vision::setRobots(vector<Robot>* robot){
	this->robot = robot;
}

void Vision::setBall(Robot *ball){
	this->ball = ball;
}

void Vision::setRotation(float *rotation){
	this->rotation = rotation;
}

void Vision::setCut(Rect *cut){
	this->cut = cut;
}

bool* Vision::getDevice(){
	return device;
}

int* Vision::getIdCamera(){
	return idCam;
}

string* Vision::getImagePath(){
	return imagePath;
}

Mat Vision::getImage(){
	return input;
}

vector<Robot>* Vision::getRobots(){
	return robot;
}

Robot* Vision::getBall(){
	return ball;
}

float* Vision::getRotation(){
	return rotation;
}

Rect* Vision::getCut(){
	return cut;
}
