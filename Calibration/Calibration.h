/*
 *      SIR Lab - Laboratório de Sistemas Inteligentes e Robótica
 *      SirSoccer - Sistema dedicado a categoria IEEE Very Small Size Soccer
 *
 *      Orientadores: Alberto Angonese e Eduardo Krempser
 *      Membros (2014): Johnathan Fercher, Oscar Neiva, Lucas Borsatto, Lucas Marques e Hebert Luiz.
 *      Membros (2015): Johnathan Fercher, Oscar Neiva, Lucas Borsatto, Hebert Luiz, Felipe Amaral, Manoel Stilpen e Samantha Vilaça.
 */
 
#ifndef CALIBRATION_H_
#define CALIBRATION_H_

#include "Headers.h"

class Calibration{
private:
    CRUD crud;
    Mat inputImage, convertImage, outputImage;
    VideoCapture cam;

    int calibrationStage;
    bool done;
    bool device;
    int idCam;
    string imagePath;

    static void callbackMouseClickColor(int evt, int x, int y, int flags, void* param);
    static void callbackMouseClickCut(int evt, int x, int y, int flags, void* param);
    static void callbackHueMin(int value, void *data);
    static void callbackValueMin(int value, void *data);
    static void callbackSaturationMin(int value, void *data);
    static void callbackHueMax(int value, void *data);
    static void callbackValueMax(int value, void *data);
    static void callbackSaturationMax(int value, void *data);

    void draw();
    void saveHSV();
    void saveRGB();
    void handleHSV(Pixel &p);
    void loadColors1();
    void loadColors2();

    void applyFilters();
    void applyRotation();
    void calibrationVisionColor();
    void calibrationRotation();
    void calibrationCut();
    
public:
    Calibration();

    void init();
    void setDevice(bool camera);
    void setImagePath(string path);
    void setCalibrationStage(int stage);
    void setID(int id);
};

#endif
