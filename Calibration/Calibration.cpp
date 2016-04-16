/*
 *      SIR Lab - Laboratório de Sistemas Inteligentes e Robótica
 *      SirSoccer - Sistema dedicado a categoria IEEE Very Small Size Soccer
 *
 *      Orientadores: Alberto Angonese e Eduardo Krempser
 *      Membros (2014): Johnathan Fercher, Oscar Neiva, Lucas Borsatto, Lucas Marques e Hebert Luiz.
 *      Membros (2015): Johnathan Fercher, Oscar Neiva, Lucas Borsatto, Hebert Luiz, Felipe Amaral, Manoel Stilpen e Samantha Vilaça.
 */

#include "Headers.h"

Mat staticInputImage;
Mat staticInput2Image;
int staticStateMouse = 0;
Point staticBoundTop, staticBoundBottom;
Rect staticBounds;

VisionColor staticVisionColor;
int staticVisionColorHelper[6];
Pixel staticColor;
float rotation;

Calibration::Calibration(){}

void Calibration::applyRotation(){
	Mat aux;
	warpAffine(inputImage, aux, getRotationMatrix2D(Point2f(inputImage.cols/2, inputImage.rows/2), rotation, 1.0), inputImage.size());
	inputImage = aux;
}

// callback do mouse para calibragem de cor (Johnathan)
void Calibration::callbackMouseClickColor(int evt, int x, int y, int flags, void* param){
	if(evt == CV_EVENT_LBUTTONDOWN){
		// staticInputImage está em HSV e staticInputImage2 está em RGB
		Vec3b p = staticInputImage.at<Vec3b>(y,x);
		Vec3b p2 = staticInput2Image.at<Vec3b>(y,x);
		
		/*	
			- Pega o valor do HSV do click, adiciona uma porcentagem para cima para ser o limite superior
			e retira uma porcentagem para ser o limite inferior do intervalo de cor
		*/
		int hMin = (int)p[0]*0.8;
		int sMin = (int)p[1]*0.6;
		int vMin = (int)p[2]*0.6;
		int hMax = (int)p[0]*1.2;
		int sMax = (int)p[1]*1.4;
		int vMax = (int)p[2]*1.4;

		/* Guarda o valor em RGB do click */
		staticColor.rgb[r] = (int)p2[2];
		staticColor.rgb[g] = (int)p2[1];
		staticColor.rgb[b] = (int)p2[0];

		// Pega os valores de HSV Max e Min criados com o click e atualiza as trackbars
		staticVisionColorHelper[0] = hMin;
		staticVisionColorHelper[1] = sMin;
		staticVisionColorHelper[2] = vMin;

		staticVisionColorHelper[3] = hMax;
		staticVisionColorHelper[4] = sMax;
		staticVisionColorHelper[5] = vMax;

		setTrackbarPos("HMin", "values", staticVisionColorHelper[0]);
		setTrackbarPos("HMax", "values", staticVisionColorHelper[3]);

		setTrackbarPos("SMin", "values", staticVisionColorHelper[1]);
		setTrackbarPos("SMax", "values", staticVisionColorHelper[4]);

		setTrackbarPos("VMin", "values", staticVisionColorHelper[2]);
		setTrackbarPos("VMax", "values", staticVisionColorHelper[5]);
	}
}

// callback do mouse para calibragem de corte (Johnathan)
void Calibration::callbackMouseClickCut(int evt, int x, int y, int flags, void* param){
	if(evt == CV_EVENT_LBUTTONDOWN){
		staticBoundTop = Point(x, y);	
	}else
	if(evt == CV_EVENT_RBUTTONDOWN){
		staticBoundBottom = Point(x,y);
	}
}

void Calibration::applyFilters(){
	staticInput2Image = inputImage;
	cvtColor(inputImage, convertImage, COLOR_RGB2HSV);

	staticInputImage = convertImage;
	inRange(convertImage,
		Scalar(staticVisionColorHelper[0], staticVisionColorHelper[1], staticVisionColorHelper[2]),
		Scalar(staticVisionColorHelper[3], staticVisionColorHelper[4], staticVisionColorHelper[5]),
		outputImage);
}

void Calibration::init(){
	if(device){
		cam = VideoCapture(idCam);
		for(int i = 0 ; i < 30 ; i++){
			cam >> inputImage;
		}
	}

	rotation = 0;
	for(int i = 0 ; i < 3 ; i++){
		staticVisionColorHelper[i] = 0;
		staticVisionColorHelper[i+3] = 255;
		staticVisionColor.min = Pixel(0, 0, 0);
		staticVisionColor.max = Pixel(0, 0, 0);
	}

	// Se o estágio de calibragem é uma cor
	if(calibrationStage >= 0 && calibrationStage <= 7){
		calibrationVisionColor();
	}else{
		if(calibrationStage == ROTATION){
			calibrationRotation();
		}else
		if(calibrationStage == CUT){
			calibrationCut();
		}
	}
}

void Calibration::calibrationVisionColor(){
	namedWindow("input");
	namedWindow("values");

	createTrackbar("HMin", "values", &staticVisionColorHelper[0], 180, callbackHueMin, &staticVisionColorHelper[0]);
	createTrackbar("HMax", "values", &staticVisionColorHelper[3], 180, callbackHueMax, &staticVisionColorHelper[3]);

	createTrackbar("SMin", "values", &staticVisionColorHelper[1], 255, callbackSaturationMin, &staticVisionColorHelper[1]);
	createTrackbar("SMax", "values", &staticVisionColorHelper[4], 255, callbackSaturationMax, &staticVisionColorHelper[4]);

	createTrackbar("VMin", "values", &staticVisionColorHelper[2], 255, callbackValueMin, &staticVisionColorHelper[2]);
	createTrackbar("VMax", "values", &staticVisionColorHelper[5], 255, callbackValueMax, &staticVisionColorHelper[5]);

	while(true){
		if(!device){
			inputImage = imread(imagePath);
		}else{
			cam >> inputImage;
		}
		
		applyFilters();
		setMouseCallback("input", callbackMouseClickColor, 0);
	
		draw();
		imshow("input", inputImage);
		medianBlur(outputImage, outputImage, 3);
		imshow("output", outputImage);


		char key = waitKey(10); 
		if(key == 27){
			break;
		}else if(key == 32){
			for(int i = 0 ; i < 3 ; i++){
				staticVisionColor.min.rgb[i] = staticVisionColorHelper[i];
				staticVisionColor.max.rgb[i] = staticVisionColorHelper[i+3];
			}

			handleHSV(staticVisionColor.min);
			handleHSV(staticVisionColor.max);

			saveHSV();
			saveRGB();
			break;
		}
	}
}

void Calibration::calibrationRotation(){
	namedWindow("input");

	while(true){
		if(!device){
			inputImage = imread(imagePath);
		}else{
			cam >> inputImage;
		}
		
		applyRotation();

		draw();

		for(int i = -1 ; i <= 480 ; i += 160){
			line(inputImage, Point(0, i), Point(640, i), Scalar(255, 255, 255), 1, 8, 0);
		}

		for(int i = -1 ; i <= 640 ; i += 160){
			line(inputImage, Point(i, 0), Point(i, 480), Scalar(255, 255, 255), 1, 8, 0);
		}

		imshow("input", inputImage);

		char key = waitKey(10); 
		if(key == 27){
			break;
		}else if(key == 32){
			stringstream ss;

			ss << PATHSAVE << "Vision/";
			ss << "rotation.csv";
			
			crud.saveRotation(ss.str(), rotation);
			break;
		}else
		if(key == 'd'){
			rotation += 0.1;
		}else
		if(key == 'a'){
			rotation -= 0.1;
		}
	}
}

void Calibration::calibrationCut(){
	namedWindow("input");

	while(true){
		if(!device){
			inputImage = imread(imagePath);
		}else{
			cam >> inputImage;
		}
		
		setMouseCallback("input", callbackMouseClickCut, 0);
	
		draw();
		rectangle(inputImage, staticBoundBottom, staticBoundTop, CV_RGB(255, 255, 255), 1, 8, 0);

		imshow("input", inputImage);

		char key = waitKey(10); 
		if(key == 27){
			break;
		}else if(key == 32){
			stringstream ss;

			ss << PATHSAVE << "Vision/";
			ss << "cut.csv";

			staticBounds = Rect(staticBoundTop, staticBoundBottom);
			crud.saveCut(ss.str(), staticBounds);
			break;
		}
	}
}

void Calibration::setDevice(bool camera){
	device = camera;
}

void Calibration::setImagePath(string path){
	imagePath = path;
}

void Calibration::setCalibrationStage(int stage){
	calibrationStage = stage;
}

void Calibration::setID(int id){
	idCam = id;
}

void Calibration::callbackHueMin(int value, void *data){
	staticVisionColorHelper[0] = value;
}

void Calibration::callbackSaturationMin(int value, void *data){
	staticVisionColorHelper[1] = value;
}

void Calibration::callbackValueMin(int value, void *data){
	staticVisionColorHelper[2] = value;
}

void Calibration::callbackHueMax(int value, void *data){
	staticVisionColorHelper[3] = value;
}

void Calibration::callbackSaturationMax(int value, void *data){
	staticVisionColorHelper[4] = value;
}

void Calibration::callbackValueMax(int value, void *data){
	staticVisionColorHelper[5] = value;
}

void Calibration::draw(){
	switch(calibrationStage){
		case ORANGE:{
			putText(inputImage, "Laranja", Point(12, 15), 0, 0.5, CV_RGB(255, 255, 0), 1, 8, false);
		}break;
		case BLUE:{
			putText(inputImage, "Azul", Point(12, 15), 0, 0.5, CV_RGB(255, 255, 0), 1, 8, false);
		}break;
		case YELLOW:{
			putText(inputImage, "Amarelo", Point(12, 15), 0, 0.5, CV_RGB(255, 255, 0), 1, 8, false);
		}break;
		case PURPLE:{
			putText(inputImage, "Roxo", Point(12, 15), 0, 0.5, CV_RGB(255, 255, 0), 1, 8, false);
		}break;
		case PINK:{
			putText(inputImage, "Rosa", Point(12, 15), 0, 0.5, CV_RGB(255, 255, 0), 1, 8, false);
		}break;
		case BROWN:{
			putText(inputImage, "Marrom", Point(12, 15), 0, 0.5, CV_RGB(255, 255, 0), 1, 8, false);
		}break;
		case RED:{
			putText(inputImage, "Vermelho", Point(12, 15), 0, 0.5, CV_RGB(255, 255, 0), 1, 8, false);
		}break;
		case GREEN:{
			putText(inputImage, "Verde", Point(12, 15), 0, 0.5, CV_RGB(255, 255, 0), 1, 8, false);
		}break;
		case ROTATION:{
			putText(inputImage, "Rotacao", Point(12, 15), 0, 0.5, CV_RGB(255, 255, 0), 1, 8, false);
		}break;
		case CUT:{
			putText(inputImage, "Corte", Point(12, 15), 0, 0.5, CV_RGB(255, 255, 0), 1, 8, false);
		}break;
		default:{
			putText(inputImage, "Unknown", Point(12, 15), 0, 0.5, CV_RGB(255, 255, 0), 1, 8, false);
		}break;
	}
}

void Calibration::handleHSV(Pixel &hsv){
	for(int i = 0 ; i < 3 ; i++){
		if(hsv.rgb[i] < 0)		hsv.rgb[i] = 0;
		if(i != 0){
			if(hsv.rgb[i] > 255)	hsv.rgb[i] = 255;
		}else{
			if(hsv.rgb[i] > 180)	hsv.rgb[i] = 180;
		}
	}
}

void Calibration::saveHSV(){
	stringstream path;
	path << PATHSAVE << "Vision/";

	switch(calibrationStage){
		case ORANGE:{
			path << "orangeHSV.csv";
			crud.saveVisionColor(path.str(), staticVisionColor);
		}break;
		case BLUE:{
			path << "blueHSV.csv";
			crud.saveVisionColor(path.str(), staticVisionColor);
		}break;
		case YELLOW:{
			path << "yellowHSV.csv";
			crud.saveVisionColor(path.str(), staticVisionColor);
		}break;
		case PURPLE:{
			path << "purpleHSV.csv";
			crud.saveVisionColor(path.str(), staticVisionColor);	
		}break;
		case PINK:{
			path << "pinkHSV.csv";
			crud.saveVisionColor(path.str(), staticVisionColor);
		}break;
		case BROWN:{
			path << "brownHSV.csv";
			crud.saveVisionColor(path.str(), staticVisionColor);	
		}break;
		case RED:{
			path << "redHSV.csv";
			crud.saveVisionColor(path.str(), staticVisionColor);	
		}break;
		case GREEN:{
			path << "greenHSV.csv";
			crud.saveVisionColor(path.str(), staticVisionColor);
		}break;
		case ROTATION:{
			path << "rotation.csv";
			crud.saveVisionColor(path.str(), staticVisionColor);
		}break;
		case CUT:{
			path << "cut.csv";
			crud.saveVisionColor(path.str(), staticVisionColor);
		}break;
		default:{
			cout << "Opcao Invalida !" << endl;
		}break;
	}
}

void Calibration::saveRGB(){
	stringstream path;
	path << PATHSAVE << "Draw/";

	switch(calibrationStage){
		case ORANGE:{
			path << "orangeRGB.csv";
			crud.saveColor(path.str(), staticColor);
		}break;
		case BLUE:{
			path << "blueRGB.csv";
			crud.saveColor(path.str(), staticColor);
		}break;
		case YELLOW:{
			path << "yellowRGB.csv";
			crud.saveColor(path.str(), staticColor);
		}break;
		case PURPLE:{
			path << "purpleRGB.csv";
			crud.saveColor(path.str(), staticColor);	
		}break;
		case PINK:{
			path << "pinkRGB.csv";
			crud.saveColor(path.str(), staticColor);
		}break;
		case BROWN:{
			path << "brownRGB.csv";
			crud.saveColor(path.str(), staticColor);	
		}break;
		case RED:{
			path << "redRGB.csv";
			crud.saveColor(path.str(), staticColor);	
		}break;
		case GREEN:{
			path << "greenRGB.csv";
			crud.saveColor(path.str(), staticColor);
		}break;
	}
}