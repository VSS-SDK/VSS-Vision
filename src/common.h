/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef COMMON_H_
#define COMMON_H_

#include "iostream"
#include "math.h"
#include "qdebug.h"
#include "qprocess.h"
#include "qstring.h"
#include <opencv2/highgui/highgui.hpp>	// Visão Computacional
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/video/video.hpp>

using namespace std;
using namespace cv;

namespace common{
    enum{ r = 0, g = 1, b = 2 };
    enum{ rmin = 0, gmin = 1, bmin = 2, rmax = 3, gmax = 4, bmax = 5};

    enum{ h = 0, s = 1, v = 2 };
    enum{ hmin = 0, smin = 1, vmin = 2, hmax = 3, smax = 4, vmax = 5};

    /*
        Estados pelo qual um processo pode estar passando (Máquina Simples de Estados)

        STOPPED (Estado de não iniciado)
            * STOPPED -> STARTING
            * STOPPED -> PAUSING
            * STOPPED -> CRASHED

        STARTING (Estado de iniciando)
            * STARTING -> RUNNING
            * STARTING -> PAUSING
            * STARTING -> ENDING
            * STARTING -> CRASHED

        RUNNING (Estado de rodando)
            * RUNNING -> PAUSING
            * RUNNING -> ENDING
            * RUNNING -> CRASHED

        PAUSING (Estado de iniciando uma pausa)
            * PAUSING -> PAUSED
            * PAUSING -> CRASHED

        PAUSED (Estado de pausado)
            * PAUSED -> STARTING
            * PAUSED -> ENDING
            * PAUSED -> CRASHED

        ENDING (Estado de terminando)
            * ENDING -> FINISHED
            * ENDING -> CRASHED

        FINISHED (Estado de terminado)
            * FINISHED -> STOPPED
            * FINISHED -> CRASHED
    */
    enum{ STOPPED = 0, STARTING = 1, RUNNING = 2, PAUSING = 3, PAUSED = 4, ENDING = 5, FINISHED = 6, CRASHED = -1 };

    // Times
    enum{ OUR_TEAM = 0, ADVERSARY_TEAM = 1 };

    // Possiveis coisas para se calibrar na visão computacional
    enum{ ORANGE = 0, BLUE = 1, YELLOW = 2, RED = 3, PINK = 4, PURPLE = 5, GREEN = 6, BROWN = 7, ROTATION = 8, CUT = 9 };

    // Possiveis formatos de label
    enum{ SQUARES = 0, RECTANGLES = 1, CIRCLES = 2 };

    // Default error
    enum{ UNKNOWN = -1 };

    // Input of data
    enum { CAMERA = 0, IMAGE = 1, VIDEO = 2 };

    enum { BALL = 0, TEAM1_ROBOT1 = 1, TEAM1_ROBOT2 = 2, TEAM1_ROBOT3 = 3, TEAM2_ROBOT1 = 4, TEAM2_ROBOT2 = 5, TEAM2_ROBOT3 = 6 };

    struct btVector3{
        float x, y, z;
        btVector3(){
            x = y = z = 0;
        };
        btVector3(float x, float y, float z){
            this->x = x;
            this->y = y;
            this->z = z;
        };
        btVector3(btVector3 *b){
            x = b->x;
            y = b->y;
            z = b->z;
        };
        btVector3(Point *b){
            x = b->x;
            y = b->y;
            z = 0;
        };
        void show(){
            printf("btVector3(%f, %f, %f)\n", x, y, z);
        };
    };

    struct Pixel{
        float rgb[3];
        Pixel(){
            rgb[0] = 0;
            rgb[1] = 0;
            rgb[2] = 0;
        };
        Pixel(float r, float g, float b){
            rgb[0] = r;
            rgb[1] = g;
            rgb[2] = b;
        };
        Pixel(float rgb[3]){
            for(int i = 0 ; i < 3 ; i++){
                this->rgb[i] = rgb[i];
            }
        };
        Pixel(Pixel *p){
            for(int i = 0 ; i < 3 ; i++){
                rgb[i] = p->rgb[i];
            }
        };
        Pixel(btVector3 *p){
            rgb[0] = p->x;
            rgb[1] = p->y;
            rgb[2] = p->z;
        };
        void show(){
            printf("Pixel(%.2f, %.2f, %.2f)\n", rgb[0], rgb[1], rgb[2]);
        };
    };

    struct TableColor{
        vector<Pixel> colors;
        TableColor(){
            colors.push_back(Pixel(255, 128, 0));
            colors.push_back(Pixel(0, 0, 255));
            colors.push_back(Pixel(255, 255, 0));
            colors.push_back(Pixel(255, 0, 0));
            colors.push_back(Pixel(255, 51, 255));
            colors.push_back(Pixel(127, 0, 255));
            colors.push_back(Pixel(0, 255, 0));
            colors.push_back(Pixel(153, 76, 0));
        };
    };

    struct VisionColor{
        Pixel min;
        Pixel max;

        VisionColor(){
            min = Pixel(0, 0, 0);
            max = Pixel(255, 255, 255);
        };
        VisionColor(Pixel min, Pixel max){
            this->min = min;
            this->max = max;
        };
        VisionColor(VisionColor *color){
            min = color->min;
            max = color->max;
        };
        void show(){
            printf("VisionColor\nMin");
            min.show();
            printf("Max");
            max.show();
        }
    };

    struct ExecConfiguration{
        string comment;
        int ball_color;
        int team_color[2];
        int config_labels[2];
        int secundary_color_1[3];
        int secundary_color_2[3];

        ExecConfiguration(){
            comment = "";

            ball_color = ORANGE;

            team_color[0] = BLUE;
            config_labels[0] = SQUARES;

            team_color[1] = YELLOW;
            config_labels[1] = SQUARES;

            for(int i = 0 ; i < 3 ; i++){
                secundary_color_1[i] = UNKNOWN;
                secundary_color_2[i] = UNKNOWN;
            }
        };
        ExecConfiguration(ExecConfiguration *g){
            comment = g->comment;

            ball_color = g->ball_color;

            team_color[0] = g->team_color[0];
            config_labels[0] = g->config_labels[0];

            team_color[1] = g->team_color[1];
            config_labels[0] = g->config_labels[0];

            for(int i = 0 ; i < 3 ; i++){
                secundary_color_1[i] = UNKNOWN;
                secundary_color_2[i] = UNKNOWN;
            }
        };
        void show(){
            printf("ExecConfiguration:\n");
            //printf("Comment: %s\n", comment);
            printf("Ball_color: %d\n", ball_color);
            printf("Team_color_1: %d\n", team_color[0]);
            printf("Config_labels_1: %d\n", config_labels[0]);
            printf("Team_color_2: %d\n", team_color[1]);
            printf("Config_labels_2: %d\n", config_labels[1]);
            for(int i = 0 ; i < 3 ; i++){
                printf("Secundary_color_team_1: %d\n", secundary_color_1[i]);
                printf("Secundary_color_team_2: %d\n", secundary_color_2[i]);
            }
        }
    };

    struct Calibration{
        string comment;
        vector<VisionColor> colors;
        vector<Point> cut;
        string data;

        Calibration(){
            comment = "";

            colors.push_back(VisionColor(Pixel(104, 128 , 118), Pixel(122, 255, 255)));
            colors.push_back(VisionColor(Pixel(0, 34, 71), Pixel(28, 255, 255)));
            colors.push_back(VisionColor(Pixel(74, 66, 117), Pixel(104, 255, 255)));
            colors.push_back(VisionColor(Pixel(120, 165, 61), Pixel(156, 255, 255)));
            colors.push_back(VisionColor(Pixel(119, 66, 145), Pixel(180, 174, 255)));
            colors.push_back(VisionColor(Pixel(125, 40, 112), Pixel(180, 255, 255)));
            colors.push_back(VisionColor(Pixel(21, 46, 120), Pixel(85, 255, 255)));
            colors.push_back(VisionColor(Pixel(87, 150, 46), Pixel(107, 229, 60)));


            cut.push_back(Point(0, 0));
            cut.push_back(Point(0, 0));

            data = "2016-12-30";
        };
        Calibration(Calibration *c){
            comment = c->comment;
            colors = c->colors;
            cut = c->cut;
            data = c->data;
        };
        void show(){
            printf("Calibration:\n");
            //printf("Comment: %s", comment);
            for(int i = 0 ; i < colors.size() ; i++){
                colors.at(i).show();
            }
            printf("Cut");
            for(int i = 0 ; i < cut.size() ; i++){
                printf("Point(%d, %d)", cut.at(i).x, cut.at(i).y);
            }
            //printf("Data: %s", data);
        };
    };

    struct Robot{
        btVector3 pose;
        btVector3 v_pose;
        Robot(){
            pose = btVector3(0, 0, 0);
            v_pose = btVector3(0, 0, 0);
        };
        Robot(btVector3 pose, btVector3 v_pose){
            this->pose = pose;
            this->v_pose = v_pose;
        };
        Robot(Robot *r){
            pose = r->pose;
            v_pose = r->v_pose;
        };
        void show(){
            printf("Robot:\n");
            printf("Pose:\n");
            pose.show();
            printf("V_Pose:\n");
            v_pose.show();
        }
    };

    struct State{
        Robot robots[6];
        Robot robots_kalman[6];
        btVector3 ball;
        btVector3 v_ball;
        btVector3 ball_kalman;
        btVector3 v_ball_kalman;
        State(){};
        /* TODO: outros construtores*/
        void show(){
            cout << "Robots Team 1:" << endl;
            for(int i = 0 ; i < 3 ; i++){
                robots[i].show();
            }
            cout << "Robots Team 1 Kalman:" << endl;
            for(int i = 0 ; i < 3 ; i++){
                robots_kalman[i].show();
            }
            cout << "Robots Team 2:" << endl;
            for(int i = 3 ; i < 6 ; i++){
                robots[i].show();
            }
            cout << "Robots Team 2 Kalman" << endl;
            for(int i = 3 ; i < 6 ; i++){
                robots_kalman[i].show();
            }
            cout << "Ball:" << endl;
            ball.show();
            ball_kalman.show();
        };
    };

    void clearSS(stringstream &ss);

    string toString(int a);
    string toString(float a);
    string toString(double a);
    string toString(long long int a);
    string toString(bool a);

    int toInt(string a);
    float toFloat(string a);
    double toDouble(string a);
    long long int toLongLongInt(string a);
    bool toBool(string a);

    string cmdTerminal(string s);

    double distancePoint(btVector3, btVector3);
    double distancePoint(Point, Point);

    Point midpoint(Point, Point);
    Point midpoint(Rect);
    btVector3 midpoint(btVector3, btVector3);

    float angulation(Point, Point);
    double radian(Point, Point);
}

#endif
