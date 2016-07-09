/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "vision.h"

vision::vision(QObject *parent) : QThread(parent){
    /*for(int i = 0 ; i < 13 ; i++){
        find_old_labels[i] = false;
    }*/
    side_cut = 15;     // inversamente proporcional a taxa de atualização da camera e proporcional a velocidade dos objetos
    area_min = 30;
    area_max = 700;
    distc_min = 5;
    distc_max = 50;
    propc_min = 0;
    propc_max = 0;

    run_it = true;
    device_used = IMAGE;
    vision_reception = false;
    id_camera = 0;
    start_finish = false;
    path_image = PATH_IMAGE;
    path_video = PATH_VIDEO;
}

void vision::run(){
    saved = imread(path_image.c_str());
    in = saved.clone();

    lbl_input->setPixmap(QPixmap::fromImage(mat2Image( Mat(480, 770, CV_8UC3, Scalar(130, 70, 40)) )));

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
                    cap >> in;
                }else{
                    cap.release();
                    cap = VideoCapture(path_video);
                    cap >> in;
                }

                if(in.rows < 1)     // Reset video
                    cap.set(0, 0);
                
                usleep(33333);
            }

            raw_in = in.clone();
            updatePlot();

            if(in.rows > 0){                        // Qt it's assync, and is possible this loop exec something after the GUI send a sign to stop, and this crash the software.;
                cvtColor(in, in, COLOR_RGB2HSV);

                coordinate_old.clear();

                for(int i = 0 ; i < 8 ; i++){
                    if(colors->at(i)){
                        search_color(i);
                        //qDebug() << i;
                    }else{
                        vector<Point> a;
                        a.push_back(Point(-1, -1));
                        coordinate_old.push_back(a);
                    }
                }

                // Filtro de Kalman AQUI
                recognizeObjects();
            }

            emit has_new_state();
        }else{
            if(start_finish){
                start_finish = false;
                lbl_input->setPixmap(QPixmap::fromImage(mat2Image( Mat(480, 770, CV_8UC3, Scalar(130, 70, 40)) )));
                cap.release();
            }
            usleep(100000);
        }

    }

    quit();
}

void vision::alloc_calibration(Calibration *calib){
    this->calib = calib;
}

void vision::alloc_state(State *state){
    this->state = state;
}

void vision::alloc_label_input(QCustomLabel *lbl_input){
    this->lbl_input = lbl_input;
}

void vision::alloc_colors(vector<int> *colors){
    this->colors = colors;
}

void vision::alloc_execution_config(ExecConfiguration *exec_config){
    this->exec_config = exec_config;
}

void vision::alloc_label_plots(vector<QLabel*> *lbl_plots){
    this->lbl_plots = lbl_plots;
}

 void vision::updatePlot(){
    stringstream ss;
    int ang;

    for(int i = 0 ; i < 3 ; i++){
        clearSS(ss);
        ang = state->robots[i].pose.z*180/M_PI;
        ss << state->robots[i].pose.x << ", " << state->robots[i].pose.y << ", " << ang << "°" << endl;

        ang = state->robots[i].v_pose.z*180/M_PI;
        ss << state->robots[i].v_pose.x << ", " << state->robots[i].v_pose.y << ", " << ang << "°" << endl;

        ang = state->robots_kalman[i].pose.z*180/M_PI;
        ss << state->robots_kalman[i].pose.x << ", " << state->robots_kalman[i].pose.y << ", " << ang << "°" << endl;

        ang = state->robots_kalman[i].v_pose.z*180/M_PI;
        ss << state->robots_kalman[i].v_pose.x << ", " << state->robots_kalman[i].v_pose.y << ", " << ang << "°";
        lbl_plots->at(i)->setText(ss.str().c_str());
    }

    for(int i = 0 ; i < 3 ; i++){
        clearSS(ss);
        ang = state->robots[i+3].pose.z*180/M_PI;
        ss << state->robots[i+3].pose.x << ", " << state->robots[i+3].pose.y << ", " << ang << "°" << endl;

        ang = state->robots[i+3].v_pose.z*180/M_PI;
        ss << state->robots[i+3].v_pose.x << ", " << state->robots[i+3].v_pose.y << ", " << ang << "°" << endl;

        ang = state->robots_kalman[i+3].pose.z*180/M_PI;
        ss << state->robots_kalman[i+3].pose.x << ", " << state->robots_kalman[i+3].pose.y << ", " << ang << "°" << endl;

        ang = state->robots_kalman[i+3].v_pose.z*180/M_PI;
        ss << state->robots_kalman[i+3].v_pose.x << ", " << state->robots_kalman[i+3].v_pose.y << ", " << ang << "°";
        lbl_plots->at(i+3)->setText(ss.str().c_str());
    }

    clearSS(ss);
    ss << state->ball.x << ", " << state->ball.y << endl;
    ss << state->v_ball.x << ", " << state->v_ball.y << endl;
    ss << state->ball_kalman.x << ", " << state->ball_kalman.y << endl;
    ss << state->v_ball_kalman.x << ", " << state->v_ball_kalman.y;

    lbl_plots->at(6)->setText(ss.str().c_str());
}

void vision::search_color(int id_color){
    labels.clear();
    contours.clear();
    hierarchy.clear();
    vol_coordinate.clear();

    if(!find_old_labels[id_color]){
        inRange(in,
                Scalar(calib->colors.at(id_color).min.rgb[h], calib->colors.at(id_color).min.rgb[s], calib->colors.at(id_color).min.rgb[v]),
                Scalar(calib->colors.at(id_color).max.rgb[h], calib->colors.at(id_color).max.rgb[s], calib->colors.at(id_color).max.rgb[v]),
                out);

        medianBlur(out, out, 3);

        findContours(out, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

        vector<vector<Point> > contours_poly( contours.size() );
        vector<Rect> boundRect( contours.size() );

        for( int i = 0; i < contours.size(); i++ ){
            approxPolyDP( Mat(contours[i]), contours_poly[i], 0, true );
            boundRect[i] = boundingRect( Mat(contours_poly[i]) );
        }

        for( int i = 0; i < contours.size(); i++ ){
            if(itsALabel(boundRect[i])){
                vol_coordinate.push_back(midpoint(boundRect[i]));//.push_back(Rect(Point(boundRect[i].x, boundRect[i].y), Point(boundRect[i].x + boundRect[i].width, boundRect[i].y + boundRect[i].height)));
                rectangle(raw_in, Rect(Point(boundRect[i].x, boundRect[i].y), Point(boundRect[i].x + boundRect[i].width, boundRect[i].y + boundRect[i].height)), Scalar(table_color.colors.at(id_color).rgb[b], table_color.colors.at(id_color).rgb[g], table_color.colors.at(id_color).rgb[r]), 1, 1, 0);
            }
        }

        vol_coordinate.push_back(Point(-1, -1));
        vol_coordinate.push_back(Point(-1, -1));
        vol_coordinate.push_back(Point(-1, -1));

        coordinate_old.push_back(vol_coordinate);

        /*if(id_color == GREEN){
            for(int i = 0 ; i < vol_coordinate.size() ; i++){
                qDebug() << "i = " << i << " " << vol_coordinate.at(i).x << ", " << vol_coordinate.at(i).y ;
            }
            qDebug() << " ";
        }
        usleep(20000);*/
        //vol_label = orderByArea(vol_label);

        /*int comp = 0;
        for(int i = 0 ; i < vol_label.size() ; i++){
            if(itsALabel(vol_label.at(i))){
                //coordinate_old.at(id_color).at(comp) = midpoint(vol_label.at(i));
                //rectangle(in, vol_label.at(i), Scalar(255, 255, 255), 1, 1, 0);
                comp++;
            }
        }*/

        /*Rect testLabel;

        if(vol_label.size() > 0){
            testLabel = vol_label.at(0) ;
        }*/

        /*if(itsALabel(testLabel)){
            Point vol_point = midpoint(testLabel);
            coordinate_old[id_color] = vol_point;
            find_old_labels[id_color] = true;
            if(itsAwayFromLimits(vol_point)){
                find_old_labels[id_color] = true;
            }else{
                find_old_labels[id_color] = false;
            }
        }else{
            find_old_labels[id_color] = false;
        }*/

    }/*else{
        find_old_labels[id_color] = false;
        Mat volM = in(expandRect(coordinate_old[id_color])).clone();

        cvtColor(volM, volM, COLOR_RGB2HSV);
        inRange(volM, Scalar(90, 126, 60), Scalar(132, 255, 255), out);

        medianBlur(out, out, 3);

        findContours(out, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

        vector<vector<Point> > contours_poly( contours.size() );
        vector<Rect> boundRect( contours.size() );

        for( int i = 0; i < contours.size(); i++ ){
            approxPolyDP( Mat(contours[i]), contours_poly[i], 0, true );
            boundRect[i] = boundingRect( Mat(contours_poly[i]) );
        }

        vector<Rect> vol_label;
        for( int i = 0; i< contours.size(); i++ ){
            vol_label.push_back(Rect(Point(boundRect[i].x, boundRect[i].y), Point(boundRect[i].x + boundRect[i].width, boundRect[i].y + boundRect[i].height)));
        }

        vol_label = orderByArea(vol_label);
        Rect testLabel;

        if(vol_label.size() > 0){
            testLabel = vol_label.at(0) ;
        }

        if(itsALabel(testLabel)){
            Point vol_coord = midpoint(testLabel);
            Point vol_sum;

            vol_sum.x = coordinate_old[id_color].x + vol_coord.x - (side_cut);
            vol_sum.y = coordinate_old[id_color].y + vol_coord.y - (side_cut);

            if(itsAwayFromLimits(Point(vol_sum))){
                find_old_labels[id_color] = true;

                coordinate_old[id_color].x += vol_coord.x - (side_cut);
                coordinate_old[id_color].y += vol_coord.y - (side_cut);
            }else{
                find_old_labels[id_color] = false;
            }
        }else{
            find_old_labels[id_color] = false;
        }

        rectangle(in, expandRect(coordinate_old[id_color]), Scalar(255, 0, 0), 1, 1, 0);
    }*/

    //qDebug() << coordinate_old[id_color].x << ", " << coordinate_old[id_color].y;

    /*Mat rep2;
    resize(out, rep2, Size(336, 252), 0, 0, 0);
    out = rep2.clone();*/
}

void vision::recognizeObjects(){
    // Filtro de Kalman AQUI

    int dist_min;
    int j_min;
    int i_min;

    for(int i = 0 ; i < coordinate_old.at(exec_config->ball_color).size() ; i++){
        if(isValidPoint(coordinate_old.at(exec_config->ball_color).at(i))){
            state->ball.x = coordinate_old.at(exec_config->ball_color).at(i).x;
            state->ball.y = coordinate_old.at(exec_config->ball_color).at(i).y;
        }
    }

    int max = 0;
    for(int i = 0 ; i < coordinate_old.at(exec_config->team_color[1]).size() && max < 3; i++){
        if(isValidPoint(coordinate_old.at(exec_config->team_color[1]).at(i))){
            stringstream ss;
            ss << i+1;
            state->robots[i+3].pose.x = coordinate_old.at(exec_config->team_color[1]).at(i).x;
            state->robots[i+3].pose.y = coordinate_old.at(exec_config->team_color[1]).at(i).y;
            max++;
            putText(raw_in, ss.str().c_str(), Point(state->robots[i+3].pose.x + 15, state->robots[i+3].pose.y + 25), 1, 1, Scalar(255, 255, 255), 1, 1, false);
        }
    }

    for(int k = 0 ; k < 3 ; k++){
        dist_min = 1024;
        i_min = j_min = -1;
        for(int i = 0 ; i < coordinate_old.at(exec_config->secundary_color_1[k]).size(); i++){
            if(isValidPoint(coordinate_old.at(exec_config->secundary_color_1[k]).at(i))){
                for(int j = 0 ; j < coordinate_old.at(exec_config->team_color[0]).size() ; j++){
                    if(isValidPoint(coordinate_old.at(exec_config->team_color[0]).at(i))){
                        float dist = distancePoint( coordinate_old.at( exec_config->team_color[0]).at(j) , coordinate_old.at( exec_config->secundary_color_1[k]).at(i) );
                        if(dist < dist_min && dist <= distc_max && dist >= distc_min){
                            dist_min = dist;
                            j_min = j;
                            i_min = i;
                        }
                    }
                }
            }
        }

        if(i_min >= 0 && j_min >= 0){
            stringstream ss;
            double radius = 8;
            Point center = midpoint(coordinate_old.at(exec_config->secundary_color_1[k]).at(i_min), coordinate_old.at(exec_config->team_color[0]).at(j_min));
            double radians = radian(coordinate_old.at(exec_config->secundary_color_1[k]).at(i_min), coordinate_old.at(exec_config->team_color[0]).at(j_min));

            ss << k+1;
            line(raw_in, Point(center.x + radius*cos(radians), center.y + radius*sin(radians)), Point(center.x - radius*cos(radians), center.y - radius*sin(radians)), Scalar(255, 255, 255), 1, 1, 0);
            putText(raw_in, ss.str().c_str(), Point(center.x + 10, center.y + 20), 1, 1, Scalar(255, 255, 255), 1, 1, false);

            state->robots[k].pose.x = center.x;
            state->robots[k].pose.y = center.y;
            state->robots[k].pose.z = radians;
        }
    }
}

vector<Rect> vision::orderByArea(vector<Rect> labels){
    for(int i = 0 ; i < labels.size() ; i++){
        for(int j = i+1 ; j < labels.size() ; j++){
            if(labels.at(i).width * labels.at(i).height < labels.at(j).width * labels.at(j).height){
                Rect l = labels.at(i);
                labels.at(i) = labels.at(j);
                labels.at(j) = l;
            }
        }
    }
    return labels;
}

Rect vision::expandRect(Point coordinate){
    int size_br[2] = {side_cut, side_cut};
    int size_tl[2] = {side_cut, side_cut};
    int new_br[2];
    int new_tl[2];

    if(coordinate.x - size_tl[0] < 0){
        new_tl[0] = 0;
    }else{
        new_tl[0] = coordinate.x - size_tl[0];
    }

    if(coordinate.y - size_tl[1] < 0){
        new_tl[1] = 0;
    }else{
        new_tl[1] = coordinate.y - size_tl[1];
    }

    if(coordinate.x + size_br[0] > in.cols){
        new_br[0] = in.cols;
    }else{
        new_br[0] = coordinate.x + size_br[0];
    }

    if(coordinate.y + size_br[1] > in.rows){
        new_br[1] = in.rows;
    }else{
        new_br[1] = coordinate.y + size_br[1];
    }

    return Rect( Point( new_tl[0], new_tl[1] ) , Point( new_br[0], new_br[1] ) );
}

bool vision::itsALabel(Rect label){
    bool its = false;

    if(label.width * label.height > area_min && label.width * label.height < area_max){
        its = true;
    }

    return its;
}

bool vision::itsAwayFromLimits(Point coordinate){
    bool its = true;

    if(coordinate.x < side_cut || coordinate.x > in.cols - side_cut){
        its = false;
    }

    if(coordinate.y < side_cut || coordinate.y > in.rows - side_cut){
        its = false;
    }

    return its;
}

bool vision::isValidPoint(Point a){
    bool isValid = true;

    if(a.x < 0)
        isValid = false;

    if(a.y < 0)
        isValid = false;

    return isValid;
}

void vision::set_device(int device_used){
    this->device_used = device_used;
}

void vision::set_id_camera(int id_camera){
    this->id_camera;
}

void vision::set_path_image(string path_image){
    this->path_image = path_image;
}

void vision::set_vision_reception(bool s){
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

void vision::set_path_video(string path_video){
    this->path_video = path_video;
}

int vision::get_device(){
    return device_used;
}

int vision::get_id_camera(){
    return id_camera;
}

string vision::get_path_image(){
    return path_image;
}

bool vision::get_vision_reception(){
    return vision_reception;
}

string vision::get_path_video(){
    return path_video;
}

void vision::finish(){
    run_it = false;
}

