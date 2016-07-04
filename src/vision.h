#ifndef VISION_H
#define VISION_H

#include "QtCore"
#include "QLabel"
#include "qcustomlabel.h"

#include "common.h"
#include "QtOpenCV.h"

using namespace common;
using namespace QtOcv;

class vision : public QThread{
protected:
    bool run_it;
    bool start_finish;
    int device_used;
    int id_camera;
    bool vision_reception;
    string path_image;
    string path_video;

    // Parameters
    int side_cut;
    float area_min, area_max, distc_min, distc_max, propc_min, propc_max;

    Calibration *calib;
    State *state;
    ExecConfiguration *exec_config;
    TableColor table_color;

    Mat in, out, saved, raw_out, raw_in, storage;
    VideoCapture cap;

    // Optimization
    vector< vector<Point> > coordinate_old;
    vector<vector<Point> > labels;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    vector<Point> vol_coordinate;

    vector<int> *colors;
    bool find_old_labels[13];

    KalmanFilter kfs[13];

    QCustomLabel *lbl_input;

    vector<Rect> orderByArea(vector<Rect>);

    Rect expandRect(Point);
    bool itsALabel(Rect);
    bool itsAwayFromLimits(Point);
    void recognizeObjects();
    bool isValidPoint(Point);

public:
    vision();
    void run();
    void search_color(int);

    void alloc_calibration(Calibration*);
    void alloc_state(State*);
    void alloc_label_input(QCustomLabel*);
    void alloc_colors(vector<int>*);
    void alloc_execution_config(ExecConfiguration*);

    void set_device(int);
    void set_id_camera(int);
    void set_path_image(string);
    void set_vision_reception(bool);
    void set_path_video(string);

    int get_device();
    int get_id_camera();
    string get_path_image();
    bool get_vision_reception();
    string get_path_video();
    void finish();

};

#endif // VISION_H