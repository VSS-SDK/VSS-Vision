/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "calibration.h"

//! Addendum
//! --------
//! 
//! > Initializes all control variables 
calibration::calibration(QObject *parent) : QThread(parent){
    run_it = true;
    device_used = IMAGE;
    vision_reception = false;
    start_finish = false;
    mouse_click_left = mouse_click_right = 0;
    id_camera = 0;

    path_image = "/images/model.jpg";
    path_video = "/videos/ball_move.mp4";

    user_path = QCoreApplication::applicationDirPath().toUtf8().constData();

    path_image = user_path + path_image;
    path_video = user_path + path_video;

    id_calib = -1;
}

//! Addendum
//! --------
//! 
//! > loop from thread calibration
void calibration::run(){
    //! > load the saved image
    saved = imread(path_image);
    //! > default imagem, blue screen
    in = Mat(480, 770, CV_8UC3, Scalar(130, 70, 40));

    //! > set the screen on MainWindow
    lbl_input->setPixmap(QPixmap::fromImage(mat2Image(in)));
    //qDebug() << QCoreApplication::applicationDirPath();
    while(run_it){
        //! > If vision reception must be used
        if(vision_reception){
            //! Check devices and get image from them
            if(device_used == CAMERA){
                if(cap.isOpened()){
                    cap >> in;
                }else{
                    cap.release();
                    cap = VideoCapture(id_camera);
                    cap >> in;
                }
            }else
            if(device_used == IMAGE){
                in = saved.clone();
                //! > if IMAGE it's used, usleep(33333) its needed to limit fps in 30.
                usleep(33333);
            }else
            if(device_used == VIDEO){
                if(cap.isOpened()){
                    if(mouse_click_right < 1){
                        cap >> in;
                        storage = in.clone();
                    }else{
                        in = storage.clone();
                    }

                    //! > if VIDEO it's used, and the video end, we reinititialize it
                    if(in.rows < 1)
                        cap.set(0, 0);
                }else{
                    cap.release();
                    cap = VideoCapture(path_video);
                    cap >> in;
                }


                if(mouse_click_right >= 2)
                    mouse_click_right = 0;
                //! > if VIDEO it's used, usleep(33333) it's needed to limit fps in 30
                usleep(33333);
            }

            size.x = in.cols;
            size.y = in.rows;

            raw_in = in.clone();

            if(type_calibration){
                //! > Apply filters
                applyFilters();
                
                //! > Apply Zoom, if needed
                zoom();
            }else{
                if(raw_in.cols > 0 && raw_in.rows > 0){
                    rotate_image();
                    cut_image();
                }
            }

            //! > emit a signal for MainWindow update its image
            emit has_new_image();
        }else{
            //! > If the vision reception was set false, we set the blue screen and release cv::VideoCapture
            if(start_finish){
                start_finish = false;
                lbl_input->setPixmap(QPixmap::fromImage(mat2Image( Mat(480, 770, CV_8UC3, Scalar(130, 70, 40)) )));
                cap.release();
                mouse_click_right = 0;
            }
            //! > If the vision reception it's false, usleep(100000) to relieve the CPU
            usleep(100000);
        }
    }

    quit();
}

//! Addendum
//! --------
//! 
void calibration::applyFilters(){
    labels.clear();
    contours.clear();
    hierarchy.clear();

    //! > convert image, RGB -> HSV
    cvtColor(in, in, COLOR_RGB2HSV);

    //! > get the blobs
    inRange(in,
            Scalar(_calib->colors.at(id_calib).min.rgb[h], _calib->colors.at(id_calib).min.rgb[s], _calib->colors.at(id_calib).min.rgb[v]),
            Scalar(_calib->colors.at(id_calib).max.rgb[h], _calib->colors.at(id_calib).max.rgb[s], _calib->colors.at(id_calib).max.rgb[v]),
            out);

    //! > filter very small blobs
    medianBlur(out, out, 3);

    if(out.cols > 0){
        //! > find the contour of all blobs
        findContours(out, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

        vector<vector<Point> > contours_poly( contours.size() );
        vector<Rect> boundRect( contours.size() );

        for( int i = 0; i < contours.size(); i++ ){
            approxPolyDP( Mat(contours[i]), contours_poly[i], 0, true );
            boundRect[i] = boundingRect( Mat(contours_poly[i]) );
        }

        //! > paint all blobs
        paint_output();

        //! > Draw a with rectangle on all blobs
        for( int i = 0; i < contours.size(); i++ ){
            rectangle(raw_in, Rect(Point(boundRect[i].x, boundRect[i].y), Point(boundRect[i].x + boundRect[i].width, boundRect[i].y + boundRect[i].height)), Scalar(255, 255, 255), 1, 1, 0);
        }
    }
}

//! Addendum
//! --------
//! 
void calibration::zoom(){
    //! > If the user click one time, the zoom it's turned on
    //! > If the user click one second time, the zoom it's turned off
    if(mouse_click_left == 1){
        zoom_blob = Point(lbl_input->x, lbl_input->y);
        mouse_click_left++;
    }else
    if(mouse_click_left == 2){
        if(raw_in.rows > 0){
            Mat rep2;
            float delta = 75;

            Point bottom, top;
            bool min_x, min_y, max_x, max_y;
            min_x = min_y = max_x = max_y = false;

            //! > security, prevents that the zoom get out of image
            if(zoom_blob.x > delta){
                bottom.x = zoom_blob.x - delta ;
            }else{
                bottom.x = 0;
                min_x = true;
            }

            //! > security, prevents that the zoom get out of image
            if(zoom_blob.y  > delta){
                bottom.y = zoom_blob.y -delta;
            }else{
                bottom.y = 0;
                min_y = true;
            }

            //! > security, prevents that the zoom get out of image
            if(zoom_blob.x < raw_in.cols - delta){
                top.x = zoom_blob.x + delta;
            }else{
                top.x = raw_in.cols;
                max_x = true;
            }

            //! > security, prevents that the zoom get out of image
            if(zoom_blob.y  < raw_in.rows - delta){
                top.y = zoom_blob.y + delta;
            }else{
                top.y = raw_in.rows;
                max_y = true;
            }

            //! > Apply de Zoom
            if(min_x){
                top.x = delta*2.0;
            }else
            if(max_x){
                bottom.x = raw_in.cols - (delta*2.0);
            }else

            if(min_y){
                top.y = delta*2.0;
            }else
            if(max_y){
                bottom.y = raw_in.rows - (delta*2.0);
            }

            if(min_y && min_x){
                top.x = delta*2.0;
                top.y = delta*2.0;
            }

            if(min_y && max_x){
                bottom.x = raw_in.cols - (delta*2.0);
                top.y = delta*2.0;
            }

            if(max_y && min_x){
                top.x = delta*2.0;
                bottom.y = raw_in.rows - (delta*2.0);
            }

            if(max_y && max_x){
                bottom.x = raw_in.cols - (delta*2.0);
                bottom.y = raw_in.rows - (delta*2.0);
            }

            rectangle(raw_in, Rect(bottom, top), Scalar(255, 255, 255), 1, 1, 0);

            raw_in = raw_in( Rect(bottom, top) );
            resize(raw_in, rep2, Size(size.x, size.x), 0, 0, 0);
            raw_in = rep2.clone();
        }
    }else
    if(mouse_click_left >= 3){
        //! > Restart de count of clicks
        mouse_click_left = 0;
    }
}

void calibration::rotate_image(){
    Mat aux;
	warpAffine(raw_in, aux, getRotationMatrix2D(Point2f(raw_in.cols/2, raw_in.rows/2), _calib->rotation, 1.0), raw_in.size());
	raw_in = aux;
}

void calibration::cut_image(){
    rectangle(raw_in, Rect(_calib->cut.at(0), _calib->cut.at(1)), Scalar(255, 255, 255), 1, 1, 0);
}

//! Addendum
//! --------
//! 
void calibration::paint_output(){
    for(int i = 0 ; i < in.cols ; i++){
        for(int j = 0 ; j < in.rows ; j++){
            Vec3b p = in.at<Vec3b>(j, i);
            //! > If the HSV values its on range, paint with color: common::TableColor.
            if(
                (p[0] > _calib->colors.at(id_calib).min.rgb[h] && p[0] < _calib->colors.at(id_calib).max.rgb[h]) &&
                (p[1] > _calib->colors.at(id_calib).min.rgb[s] && p[1] < _calib->colors.at(id_calib).max.rgb[s]) &&
                 p[2] > _calib->colors.at(id_calib).min.rgb[v]
            ){
                p[0] = table_color.colors.at(id_calib).rgb[b];
                p[1] = table_color.colors.at(id_calib).rgb[g];
                p[2] = table_color.colors.at(id_calib).rgb[r];

                raw_in.at<Vec3b>(j, i) = p;
            }
        }
    }
}

void calibration::finish(){
    run_it = false;
}

void calibration::set_device(int deviced_used){
    this->device_used = deviced_used;
}

void calibration::set_id_camera(int id_camera){
    this->id_camera = id_camera;
}

void calibration::set_path_image(string path_image){
    this->path_image = path_image;
}

//! Addendum
//! --------
//! 
void calibration::set_vision_reception(bool){
    start_finish = true;
    vision_reception ? vision_reception = false : vision_reception = true;
    //! > If device_used == common::CAMERA or common::VIDEO, start de VideoCapture
    if(vision_reception){
        if(device_used == CAMERA)
            cap = VideoCapture(id_camera);
        else
        if(device_used == VIDEO)
            cap = VideoCapture(path_video);
    }
}

void calibration::set_id_color(int id_calib){
    this->id_calib = id_calib;
}

void calibration::set_mouse_click_left(int mouse_click_left){
    this->mouse_click_left = mouse_click_left;
}

void calibration::set_mouse_click_right(int mouse_click_right){
    if(device_used == VIDEO)
        this->mouse_click_right = mouse_click_right;
}

void calibration::set_path_video(string path_video){
    this->path_video = path_video;
}

void calibration::set_type_calibration(bool type_calibration){
    this->type_calibration = type_calibration;
}

int calibration::get_device(){
    return device_used;
}

int calibration::get_id_camera(){
    return id_camera;
}

string calibration::get_path_image(){
    return path_image;
}

bool calibration::get_vision_reception(){
    return vision_reception;
}

int calibration::get_id_color(){
    return id_calib;
}

int calibration::get_mouse_click_left(){
    return mouse_click_left;
}

int calibration::get_mouse_click_right(){
    return mouse_click_right;
}

bool calibration::get_type_calibration(){
    return type_calibration;
}

//! Addendum
//! --------
//! 
void calibration::alloc_label_input(QCustomLabel *lbl_input){
    //! > It must be pointer, because calibration it's unrecheable and MainWindow too.
    this->lbl_input = lbl_input;
}

//! Addendum
//! --------
//! 
void calibration::alloc_calibration(Calibration *_calib){
    //! > It must be pointer, because calibration it's unrecheable and MainWindow too.
    this->_calib = _calib;
}
