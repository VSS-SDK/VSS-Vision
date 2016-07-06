/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef CALIBRATION_H
#define CALIBRATION_H

#include "QtCore"
#include "QString"
#include "QObject"
#include "QImage"
#include "QLabel"
#include "QPixmap"
#include "qcustomlabel.h"
#include "QDebug"

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "iostream"
#include "vector"
#include "unistd.h"

#include "QtOpenCV.h"
#include "common.h"

using namespace std;
using namespace cv;
using namespace QtOcv;
using namespace common;

class calibration : public QThread{
protected:
    // Control
    bool run_it;
    int device_used;
    bool vision_reception;
    bool start_finish;
    int id_camera;
    string path_image;
    string path_video;
    int mouse_click_left, mouse_click_right;
    int id_calib;
    Point zoom_blob;

    // OpenCV
    Mat in, out, saved, raw_in, raw_out, storage;
    Point size;
    VideoCapture cap;
    vector<vector<Point> > labels;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    // Qt
    QImage img;
    QCustomLabel *lbl_input;


    // common
    Calibration *_calib;
    TableColor table_color;

public:
    calibration();

    void run();
    void finish();

    void applyFilters();
    void zoom();
    void paint_output();

    void set_device(int);
    void set_id_camera(int);
    void set_path_image(string);
    void set_path_video(string);
    void set_vision_reception(bool);
    void set_id_color(int);
    void set_mouse_click_left(int);
    void set_mouse_click_right(int);

    int get_device();
    int get_id_camera();
    string get_path_image();
    bool get_vision_reception();
    int get_id_color();
    int get_mouse_click_left();
    int get_mouse_click_right();

    void alloc_label_input(QCustomLabel*);
    void alloc_calibration(Calibration*);
};

#endif // VISION_H
