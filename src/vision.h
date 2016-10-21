/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef VISION_H
#define VISION_H

#include "QtCore"
#include "QLabel"
#include "QThread"
#include "qcustomlabel.h"

#include "common.h"
#include "QtOpenCV.h"

using namespace common;
using namespace QtOcv;

//! This class is responsible for track all objects in field
class vision : public QThread
{
    Q_OBJECT
public:
    Mat in, out, saved, raw_out, raw_in, storage;
protected:
    bool run_it;
    bool start_finish;
    int device_used;
    int id_camera;
    int init_camera;
    bool vision_reception;
    string path_image;
    string path_video;
    string user_path;
    int frames_renew;

    // Parameters
    int side_cut;
    float area_min, area_max, distc_min, distc_max, propc_min, propc_max;


    Calibration *calib;
    State *state;
    ExecConfiguration *exec_config;
    TableColor table_color;


    VideoCapture cap;

    // Optimization
    vector< vector<Point> > coordinate_old;
    vector< vector<Point> > save;
    vector<vector<Point> > labels;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    vector<Point> vol_coordinate;

    vector<int> *colors;
    bool find_old_labels[13];
    int colors_by_list[6];

    KalmanFilter kfs[13];

    QCustomLabel *lbl_input;
    vector<QLabel*> *lbl_plots;

    vector<Rect> orderByArea(vector<Rect>);

    Rect expandRect(Point);
    bool itsALabel(Rect);
    bool itsAwayFromLimits(Point);
    void recognizeObjects();
    bool isValidPoint(Point);
    void updatePlot();
    void cutImage();
    void applyRotation();
    
public:
    explicit vision(QObject *parent = 0);

    void run();
    void search_color(int, int);

    void alloc_calibration(Calibration*);
    void alloc_state(State*);
    void alloc_label_input(QCustomLabel*);
    void alloc_colors(vector<int>*);
    void alloc_execution_config(ExecConfiguration*);
    void alloc_label_plots(vector<QLabel*>*);

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

signals:
    void has_new_state();
};

#endif // VISION_H
