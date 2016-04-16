/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
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
