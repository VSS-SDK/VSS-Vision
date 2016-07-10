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
#include "QThread"
#include "QDir"

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

//! This class is responsible for calibrate all common::VisionColor, cut points and rotation
class calibration : public QThread{
     Q_OBJECT
public:
    Mat in, out, saved, raw_in, raw_out, storage, last_in;
protected:
    // Control
    bool run_it;
    int device_used;
    bool vision_reception;
    bool start_finish;
    int id_camera;
    string user_path;
    string path_image;
    string path_video;
    int mouse_click_left, mouse_click_right;
    int id_calib;
    bool type_calibration;
    

    // OpenCV
    Point size;
    VideoCapture cap;
    vector<vector<Point> > labels;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    Point zoom_blob;

    // Qt
    QImage img;
    QCustomLabel *lbl_input;


    // common
    Calibration *_calib;
    TableColor table_color;

public:
    //! Default constructor: calibration c;
    explicit calibration(QObject *parent = 0);

    //! Virtual method from QThread, MainWindow call this method in a CONNECT
    void run();

    //! Virtual method from QThread, MainWindow call this method in its destrcutor
    void finish();

    //! Apply all filters needed to find one blob
    void applyFilters();

    //! Apply Zoom on image, if needed
    void zoom();

    //! rotate image
    void rotate_image();

    //! cur image
    void cut_image();

    //! Paint the blob founded
    void paint_output();

    //! Set the device time used, common::IMAGE, common::CAMERA or common::VIDEO
    void set_device(int);

    //! Set the id from camera used
    void set_id_camera(int);

    //! Set the path of image used
    void set_path_image(string);

    //! Set the path of video used
    void set_path_video(string);

    //! Turn ON and OFF the vision reception and calcs
    void set_vision_reception(bool);

    //! Set the id_color to calibrate, like: common::ORANGE, common::YELLOW ...
    void set_id_color(int);

    //! Set the qtd of left clicks
    void set_mouse_click_left(int);

    //! Set the qtd of right clicks
    void set_mouse_click_right(int);

    //! Set the type of calibration, COLORS = true, CAM = false;
    void set_type_calibration(bool);

    //! get the device used
    int get_device();

    //! get the id from camera used
    int get_id_camera();

    //! get the path of image used
    string get_path_image();

    //! get the path of video used
    bool get_vision_reception();

    //! get the id color calibrate
    int get_id_color();

    //! get the qtd of left clicks
    int get_mouse_click_left();

    //! get the qtd of right clicks
    int get_mouse_click_right();

    //! get the type of calibraiton, COLORS = true, CAM = false;
    bool get_type_calibration();

    //! alloc the label of input image, image from VideoCapture
    void alloc_label_input(QCustomLabel*);

    //! alloc the labels of pose from objects in workspace
    void alloc_calibration(Calibration*);

signals:
    void has_new_image();
};

#endif // VISION_H
