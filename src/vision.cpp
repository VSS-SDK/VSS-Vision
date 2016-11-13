/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "vision.h"

vision::vision(QObject *parent) : QThread(parent){
    side_cut = 20;     // inversamente proporcional a taxa de atualização da camera e proporcional a velocidade dos objetos
    area_min = 30;
    area_max = 700;
    distc_min = 5;
    distc_max = 50;
    propc_min = 0;
    propc_max = 0;
    init_camera = 0;

    run_it = true;
    device_used = IMAGE;
    vision_reception = false;
    id_camera = 0;
    start_finish = false;

    path_image = "/images/model.jpg";
    path_video = "/videos/ball_move.mp4";

    user_path = QCoreApplication::applicationDirPath().toUtf8().constData();

    path_image = user_path + path_image;
    path_video = user_path + path_video;

    frames_renew = 0;
}

void vision::run(){
    saved = imread(path_image.c_str());
    in = saved.clone();

    lbl_input->setPixmap(QPixmap::fromImage(mat2Image( Mat(480, 770, CV_8UC3, Scalar(130, 70, 40)) )));

    while(run_it){
        //cout << id_camera << endl;
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

            if(in.rows > 0 && init_camera > 30){                        // Qt it's assync, and is possible this loop exec something after the GUI send a sign to stop, and this crash the software.;
                
                applyRotation();
                cutImage();

                raw_in = in.clone();
                updatePlot();
                
                cvtColor(in, in, COLOR_RGB2HSV);

                save = coordinate_old;
                coordinate_old.clear();

                frames_renew++;
                if(frames_renew > 15){
                    frames_renew = 0;
                    for(int i = 0 ; i < 13 ; i++){
                        find_old_labels[i] = false;
                    }
                }

                for(int i = 0 ; i < 6 ; i++){
                    //cout << "i: " << i << endl;
                    search_color(colors_by_list[i], i); 
                }
                cout << endl;

                // Filtro de Kalman AQUI
                
                recognizeObjects();
                
            }else{
                raw_in = in.clone();
                init_camera++;
            }

            emit has_new_state();
        }else{
            if(start_finish){
                start_finish = false;
                lbl_input->setPixmap(QPixmap::fromImage(mat2Image( Mat(480, 770, CV_8UC3, Scalar(130, 70, 40)) )));
                init_camera = 0;
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

void vision::cutImage(){
   	// TODO: Pensar em uma regras melhor, pois pode existir uma config x ou y 0
	if(calib->cut.at(0).x != 0 || calib->cut.at(0).y != 0 || calib->cut.at(1).x != 0 || calib->cut.at(1).y != 0){
		Mat rep, rep2;

		rep = in(Rect(calib->cut.at(0), calib->cut.at(1)));
		
		//resize(rep, rep2, Size(640, 480), 0, 0, 0);
		in = rep.clone();
	}
}

void vision::applyRotation(){
    Mat aux;
	warpAffine(in, aux, getRotationMatrix2D(Point2f(in.cols/2, in.rows/2), calib->rotation, 1.0), in.size());
	in = aux;
}

void vision::updatePlot(){
    stringstream ss;
    int ang;

    for(int i = 0 ; i < 3 ; i++){
        clearSS(ss);
        ang = state->robots[i].pose.z*180/M_PI;
        ss << (int)state->robots[i].pose.x << ", " << (int)state->robots[i].pose.y << ", " << ang << "°" << endl;

        ang = state->robots[i].v_pose.z*180/M_PI;
        ss << (int)state->robots[i].v_pose.x << ", " << (int)state->robots[i].v_pose.y << ", " << ang << "°" << endl;

        ang = state->robots_kalman[i].pose.z*180/M_PI;
        ss << (int)state->robots_kalman[i].pose.x << ", " << (int)state->robots_kalman[i].pose.y << ", " << ang << "°" << endl;

        ang = state->robots_kalman[i].v_pose.z*180/M_PI;
        ss << state->robots_kalman[i].v_pose.x << ", " << state->robots_kalman[i].v_pose.y << ", " << ang << "°";
        lbl_plots->at(i)->setText(ss.str().c_str());
    }

    for(int i = 0 ; i < 3 ; i++){
        clearSS(ss);
        ang = state->robots[i+3].pose.z*180/M_PI;
        ss << (int)state->robots[i+3].pose.x << ", " << (int)state->robots[i+3].pose.y << ", " << ang << "°" << endl;

        ang = state->robots[i+3].v_pose.z*180/M_PI;
        ss << (int)state->robots[i+3].v_pose.x << ", " << (int)state->robots[i+3].v_pose.y << ", " << ang << "°" << endl;

        ang = state->robots_kalman[i+3].pose.z*180/M_PI;
        ss << (int)state->robots_kalman[i+3].pose.x << ", " << (int)state->robots_kalman[i+3].pose.y << ", " << ang << "°" << endl;

        ang = state->robots_kalman[i+3].v_pose.z*180/M_PI;
        ss << (int)state->robots_kalman[i+3].v_pose.x << ", " << (int)state->robots_kalman[i+3].v_pose.y << ", " << ang << "°";
        lbl_plots->at(i+3)->setText(ss.str().c_str());
    }

    clearSS(ss);
    ss << (int)state->ball.x << ", " << (int)state->ball.y << endl;
    ss << (int)state->v_ball.x << ", " << (int)state->v_ball.y << endl;
    ss << (int)state->ball_kalman.x << ", " << (int)state->ball_kalman.y << endl;
    ss << (int)state->v_ball_kalman.x << ", " << (int)state->v_ball_kalman.y;

    lbl_plots->at(6)->setText(ss.str().c_str());
}

void vision::search_color(int id_color, int id_for){
    labels.clear();
    contours.clear();
    hierarchy.clear();
    vol_coordinate.clear();

    //if(!find_old_labels[id_color]){
        inRange(in,
                Scalar(calib->colors.at(id_color).min.rgb[h], calib->colors.at(id_color).min.rgb[s], calib->colors.at(id_color).min.rgb[v]),
                Scalar(calib->colors.at(id_color).max.rgb[h], calib->colors.at(id_color).max.rgb[s], calib->colors.at(id_color).max.rgb[v]),
                out);

        //medianBlur(out, out, 3);

        findContours(out, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

        vector<vector<Point> > contours_poly( contours.size() );
        vector<Rect> boundRect( contours.size() );

        for( int i = 0; i < contours.size(); i++ ){
            approxPolyDP( Mat(contours[i]), contours_poly[i], 0, true );
            boundRect[i] = boundingRect( Mat(contours_poly[i]) );
        }

        for( int i = 0; i < contours.size(); i++ ){
            if(itsALabel(boundRect[i])){
                vol_coordinate.push_back(midpoint(boundRect[i]));
                rectangle(raw_in, Rect(Point(boundRect[i].x, boundRect[i].y), Point(boundRect[i].x + boundRect[i].width, boundRect[i].y + boundRect[i].height)), Scalar(table_color.colors.at(id_color).rgb[b], table_color.colors.at(id_color).rgb[g], table_color.colors.at(id_color).rgb[r]), 1, 1, 0);
            }
        }

        if(id_color == exec_config->ball_color){
            if(vol_coordinate.size() >= 1){
                //cout << "ok" << endl;
                find_old_labels[id_color] = true;
            }else{
                //cout << "nok" << endl;
                find_old_labels[id_color] = false;
            }
        }

        if(id_color == exec_config->team_color[0] || id_color == exec_config->team_color[1]){
            if(vol_coordinate.size() >= 3){
                find_old_labels[id_color] = true;
            }else{
                find_old_labels[id_color] = false;
            }
        }

        vol_coordinate.push_back(Point(-1, -1));
        vol_coordinate.push_back(Point(-1, -1));
        vol_coordinate.push_back(Point(-1, -1));

        coordinate_old.push_back(vol_coordinate);
    /*}else{
        Point aux;
        find_old_labels[id_color] = true;

        cout << "id_color: " << id_color << endl;
        cout << "id_for: " << id_for << endl;
        cout << "save_size: " << save.size() << endl;

        for(int i = 0 ; i < save.at(id_for).size() ; i++){
            if(isValidPoint(save.at(id_for).at(i))){  
                Mat volM = in(expandRect( save.at(id_for).at(i) )).clone();
                /*Mat volN;

                cvtColor(volM, volN, COLOR_HSV2RGB);

                stringstream ss;
                ss << "id_color:" << id_color << "id:" << i << endl;
                imshow(ss.str().c_str(), volN);

                inRange(volM,
                        Scalar(calib->colors.at(id_color).min.rgb[h], calib->colors.at(id_color).min.rgb[s], calib->colors.at(id_color).min.rgb[v]),
                        Scalar(calib->colors.at(id_color).max.rgb[h], calib->colors.at(id_color).max.rgb[s], calib->colors.at(id_color).max.rgb[v]),
                        out);

                //medianBlur(out, out, 3);

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

                Point vol_coord = midpoint(testLabel);
                Point vol_sum;

                vol_sum.x = save.at(id_color).at(i).x + vol_coord.x - (side_cut);
                vol_sum.y = save.at(id_color).at(i).y + vol_coord.y - (side_cut);

                if(itsAwayFromLimits(Point(vol_sum))){
                    aux.x = vol_sum.x;
                    aux.y = vol_sum.y;

                    rectangle(raw_in, Rect(Point(aux.x - 8, aux.y - 8), Point(aux.x + 8, aux.y + 8)), Scalar(table_color.colors.at(id_color).rgb[b], table_color.colors.at(id_color).rgb[g], table_color.colors.at(id_color).rgb[r]), 1, 1, 0);
                    vol_coordinate.push_back(aux);
                }else{
                    find_old_labels[id_color] = false;
                }
            }
        }

        //find_old_labels[id_color] = false;

        vol_coordinate.push_back(Point(-1, -1));
        vol_coordinate.push_back(Point(-1, -1));
        vol_coordinate.push_back(Point(-1, -1));

        coordinate_old.push_back(vol_coordinate);
    }*/
}

void vision::recognizeObjects(){
    // Filtro de Kalman AQUI

    int dist_min;
    int j_min;
    int i_min;

    /*for(int i = 0 ; i < coordinate_old.size() ; i++){
        for(int j = 0 ; j < coordinate_old.at(i).size() ; j++){
            cout << "i: " << i << ", j: " << j << endl;
            cout << "( " << coordinate_old.at(i).at(j).x << ", " << coordinate_old.at(i).at(j).y << ")" << endl;
        }
        cout << endl;
    }*/
    for(int i = 0 ; i < coordinate_old.at(0).size() ; i++){
        btVector3 test;
        test.x = coordinate_old.at(0).at(i).x * TOTAL_LENGHT /(float)in.cols;
        test.y = coordinate_old.at(0).at(i).y * TOTAL_WIDTH /(float)in.rows;

        if(isValidPoint(coordinate_old.at(0).at(i))/* && distancePoint(state->ball, test)*/){
            state->ball = test;
        }
    }

    int max = 0;
    for(int i = 0 ; i < coordinate_old.at(2).size() && max < 3; i++){
        if(isValidPoint(coordinate_old.at(2).at(i))){
            //stringstream ss;
            //ss << i+1;
            state->robots[i+3].pose.x = coordinate_old.at(2).at(i).x  * TOTAL_LENGHT/(float)in.cols;
            state->robots[i+3].pose.y = coordinate_old.at(2).at(i).y * TOTAL_WIDTH/(float)in.rows;
            state->robots[i+3].pose.z = 0;
            max++;

            //state->robots[i+3].show();
            //putText(raw_in, ss.str().c_str(), Point(state->robots[i+3].pose.x + 15, state->robots[i+3].pose.y + 25), 1, 1, Scalar(255, 255, 255), 1, 1, false);
        }
    }

    for(int k = 3 ; k < 6 ; k++){
        dist_min = 1024;
        i_min = j_min = -1;

        //cout << "RECOGNIZE ROBOTS: " << k << endl;
        //cout << "size: " << coordinate_old.at(exec_config->secundary_color_1[k]).size() << endl;
        //cout << "robot: " << k << endl;
        //cout << "a" << endl;

        for(int i = 0 ; i < coordinate_old.at(k).size(); i++){
            //cout << coordinate_old.at(exec_config->secundary_color_1[k]).at(i) << endl;
            if(isValidPoint(coordinate_old.at(k).at(i))){
                for(int j = 0 ; j < coordinate_old.at(1).size() ; j++){
                    if(isValidPoint(coordinate_old.at(1).at(j))){
                        float dist = distancePoint( coordinate_old.at(1).at(j) , coordinate_old.at(k).at(i) );
                        if(dist < dist_min && dist <= distc_max && dist >= distc_min){
                            dist_min = dist;
                            j_min = j;
                            i_min = i;
                        }

                    }
                }
            }
        }

       // cout << "b" << endl;

        //cout << endl;

        if(i_min >= 0 && j_min >= 0){
            stringstream ss;
            double radius = 8;
            Point center = midpoint(coordinate_old.at(k).at(i_min), coordinate_old.at(1).at(j_min));
            double radians = radian(coordinate_old.at(k).at(i_min), coordinate_old.at(1).at(j_min)) - 0.785;

            ss << k-2;
            line(raw_in, Point(center.x + radius*cos(radians), center.y + radius*sin(radians)), Point(center.x - radius*cos(radians), center.y - radius*sin(radians)), Scalar(255, 255, 255), 1, 1, 0);
            putText(raw_in, ss.str().c_str(), Point(center.x + 10, center.y + 20), 1, 1, Scalar(255, 255, 255), 1, 1, false);

            state->robots[k-3].pose.x = center.x * TOTAL_LENGHT/(float)in.cols;
            state->robots[k-3].pose.y = center.y * TOTAL_WIDTH/(float)in.rows;
            state->robots[k-3].pose.z = radians;
        }

       // cout << "c" << endl;
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
    Point up, down;

    if(coordinate.x - side_cut < 0){
        down.x = 0;
    }else{
        down.x = coordinate.x - side_cut;
    }

    if(coordinate.x + side_cut > in.cols){
        up.x = in.cols;
    }else{
        up.x = coordinate.x + side_cut;
    }

    if(coordinate.y - side_cut < 0){
        down.y = 0;
    }else{
        down.y = coordinate.y - side_cut;
    }

    if(coordinate.y + side_cut > in.rows){
        up.y = in.rows;
    }else{
        up.y = coordinate.y + side_cut;
    }

    return Rect(down, up);
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

    if(a.x < 0 && a.y < 0)
        isValid = false;

    return isValid;
}

void vision::set_device(int device_used){
    this->device_used = device_used;
}

void vision::set_id_camera(int id_camera){
    this->id_camera = id_camera;
}

void vision::set_path_image(string path_image){
    this->path_image = path_image;
}

void vision::set_vision_reception(bool s){
    colors_by_list[0] = exec_config->ball_color; 
    colors_by_list[1] = exec_config->team_color[0];           // TEAM 1 ALWAYS BE "OUR" TEAM 
    colors_by_list[2] = exec_config->team_color[1]; 
    colors_by_list[3] = exec_config->secundary_color_1[0]; 
    colors_by_list[4] = exec_config->secundary_color_1[1]; 
    colors_by_list[5] = exec_config->secundary_color_1[2];

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

