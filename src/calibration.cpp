/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "calibration.h"

calibration::calibration(){
    run_it = true;
    device_used = IMAGE;
    vision_reception = false;
    start_finish = false;
    mouse_click_left = mouse_click_right = 0;
    id_camera = 0;
    path_image = "/home/johnathan/Repositories/SIRLab/VSS-Vision/src/images/model.jpg";
    path_video = "/home/johnathan/Repositories/SIRLab/VSS-Vision/src/videos/ball_move.mp4";
    id_calib = -1;
}

void calibration::run(){
    saved = imread(path_image);
    in = Mat(480, 770, CV_8UC3, Scalar(130, 70, 40));

    lbl_input->setPixmap(QPixmap::fromImage(mat2Image(in)));

    while(run_it){
        if(vision_reception){
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

                    if(in.rows < 1)
                        cap.set(0, 0);
                }else{
                    cap.release();
                    cap = VideoCapture(path_video);
                    cap >> in;
                }

                if(mouse_click_right >= 2)
                    mouse_click_right = 0;
                usleep(33333);
            }

            size.x = in.cols;
            size.y = in.rows;

            raw_in = in.clone();

            applyFilters();
            zoom();
            lbl_input->setPixmap(QPixmap::fromImage(mat2Image(raw_in)));
        }else{
            if(start_finish){
                start_finish = false;
                lbl_input->setPixmap(QPixmap::fromImage(mat2Image( Mat(480, 770, CV_8UC3, Scalar(130, 70, 40)) )));
                cap.release();
                mouse_click_right = 0;
            }
            usleep(100000);
        }
    }

    quit();
}

void calibration::applyFilters(){
    labels.clear();
    contours.clear();
    hierarchy.clear();

    cvtColor(in, in, COLOR_RGB2HSV);

    inRange(in,
            Scalar(_calib->colors.at(id_calib).min.rgb[h], _calib->colors.at(id_calib).min.rgb[s], _calib->colors.at(id_calib).min.rgb[v]),
            Scalar(_calib->colors.at(id_calib).max.rgb[h], _calib->colors.at(id_calib).max.rgb[s], _calib->colors.at(id_calib).max.rgb[v]),
            out);

    medianBlur(out, out, 3);
    if(out.cols > 0){
        findContours(out, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

        vector<vector<Point> > contours_poly( contours.size() );
        vector<Rect> boundRect( contours.size() );

        for( int i = 0; i < contours.size(); i++ ){
            approxPolyDP( Mat(contours[i]), contours_poly[i], 0, true );
            boundRect[i] = boundingRect( Mat(contours_poly[i]) );
        }

        paint_output();

        for( int i = 0; i < contours.size(); i++ ){
            rectangle(raw_in, Rect(Point(boundRect[i].x, boundRect[i].y), Point(boundRect[i].x + boundRect[i].width, boundRect[i].y + boundRect[i].height)), Scalar(255, 255, 255), 1, 1, 0);
        }
    }
}

void calibration::zoom(){
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

            if(zoom_blob.x > delta){
                bottom.x = zoom_blob.x - delta ;
            }else{
                bottom.x = 0;
                min_x = true;
            }

            if(zoom_blob.y  > delta){
                bottom.y = zoom_blob.y -delta;
            }else{
                bottom.y = 0;
                min_y = true;
            }

            if(zoom_blob.x < raw_in.cols - delta){
                top.x = zoom_blob.x + delta;
            }else{
                top.x = raw_in.cols;
                max_x = true;
            }

            if(zoom_blob.y  < raw_in.rows - delta){
                top.y = zoom_blob.y + delta;
            }else{
                top.y = raw_in.rows;
                max_y = true;
            }

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
        mouse_click_left = 0;
    }
}

void calibration::paint_output(){
    for(int i = 0 ; i < in.cols ; i++){
        for(int j = 0 ; j < in.rows ; j++){
            Vec3b p = in.at<Vec3b>(j, i);
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

void calibration::set_vision_reception(bool){
    start_finish = true;
    vision_reception ? vision_reception = false : vision_reception = true;
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

void calibration::alloc_label_input(QCustomLabel *lbl_input){
    this->lbl_input = lbl_input;
}

void calibration::alloc_calibration(Calibration *_calib){
    this->_calib = _calib;
}
