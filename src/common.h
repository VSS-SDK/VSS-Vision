/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef COMMON_H_
#define COMMON_H_

#include "iostream"                     // C++
#include "math.h"                       // C

#include "qdebug.h"                     // Qt
#include "qprocess.h"
#include "qimage.h"
#include "qstring.h"

#include <opencv2/highgui/highgui.hpp>	// OpenCV Visão Computacional
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/video/video.hpp>

#include "VSS-Interface/cpp/interface.h"    // VSS

#define FIELD_LENGHT            150.0              // 150.0 cm
#define FIELD_WIDTH             130.0              // 130.0 cm
#define FIELD_HEIGHT            2.5                // 2.5 cm

#define GOAL_LENGHT             40.0               // 40.0 cm
#define GOAL_WIDTH              10.0               // 10.0 cm

#define TRIANGLE_CORNER_SIDE    7.5                // 7.5 cm

#define TOTAL_LENGHT            (FIELD_LENGHT + GOAL_WIDTH + GOAL_WIDTH)
#define TOTAL_WIDTH             FIELD_WIDTH

using namespace std;
using namespace cv;

//! This namespace is responsible to implement all global functions and custom datatypes used in the software, like: ENUMS, btVector3, Pixel, TableColor, VisionColor, ExecConfiguration, Calibration, Robot and State
namespace common{
    //! This enum implements a abstraction of a RGB array.
    enum{ r = 0, g = 1, b = 2 };

    //! This enum implements a abstraction of a range of RGB array.
    enum{ rmin = 0, gmin = 1, bmin = 2, rmax = 3, gmax = 4, bmax = 5};

    //! This enum implements a abstraction of a HSV array.
    enum{ h = 0, s = 1, v = 2 };

    //! This enum implements a abstraction of a range of  HSV array.
    enum{ hmin = 0, smin = 1, vmin = 2, hmax = 3, smax = 4, vmax = 5};

    //! This enum implements a abstraction of teams.
    enum{ OUR_TEAM = 0, ADVERSARY_TEAM = 1 };

    ///! This enum represents all data that can be calibrated.
    enum{ ORANGE = 0, BLUE = 1, YELLOW = 2, RED = 3, PINK = 4, PURPLE = 5, GREEN = 6, BROWN = 7, ROTATION = 8, CUT = 9 };

    //! This enum represents all types of blob that can be used.
    enum{ SQUARES = 0, RECTANGLES = 1, CIRCLES = 2 };   

    //! This enum represents all unknown things.
    enum{ UNKNOWN = -1 };

    //! This enum represents all types of input datas.
    enum { CAMERA = 0, IMAGE = 1, VIDEO = 2 };

    //! This enum represents all objects in a State
    enum { BALL = 0, TEAM1_ROBOT1 = 1, TEAM1_ROBOT2 = 2, TEAM1_ROBOT3 = 3, TEAM2_ROBOT1 = 4, TEAM2_ROBOT2 = 5, TEAM2_ROBOT3 = 6 };

    //! This struct represents a Vector in R^3.
    struct btVector3{
        //! Data: x, y, z.
        float x, y, z;
        //! Default constructor: btVector3 bt3;
        btVector3(){
            x = y = z = 0;
        };
        //! Construtor XYZ: btVector3 bt3(x, y, z);
        btVector3(float x, float y, float z){
            this->x = x;
            this->y = y;
            this->z = z;
        };
        //! Constructor copy: btVector3 bt3(btVector3(x, y, z));
        btVector3(btVector3 *b){
            x = b->x;
            y = b->y;
            z = b->z;
        };
        //! Constructor parse of point: btVector3 bt3(Point(x, y));
        btVector3(Point *b){
            x = b->x;
            y = b->y;
            z = 0;
        };
        //! Default function: prints all variables.
        void show(){
            printf("btVector3(%f, %f, %f)\n", x, y, z);
        };
    };

    //! This struct represents a Pixel, can be: RGB and HSV. It's used float because is possible to represent color in systems, like: 0 to 1, and 0 to 255.
    struct Pixel{
        //! Data: array[3] of RGB.
        float rgb[3];
        //! Constructor default: Pixel p;
        Pixel(){
            rgb[0] = 0;
            rgb[1] = 0;
            rgb[2] = 0;
        };
        //! Constructor RGB1: Pixel p(r, g, b);
        Pixel(float r, float g, float b){
            rgb[0] = r;
            rgb[1] = g;
            rgb[2] = b;
        };
        //! Constructor RGB2: Pixel p(rgb[3]);
        Pixel(float rgb[3]){
            for(int i = 0 ; i < 3 ; i++){
                this->rgb[i] = rgb[i];
            }
        };
        //! Constructor copy: Pixel p(Pixel(r, g, b));
        Pixel(Pixel *p){
            for(int i = 0 ; i < 3 ; i++){
                rgb[i] = p->rgb[i];
            }
        };
        //! Constructor btVector3: Pixel p(btVector(r, g, b));
        Pixel(btVector3 *p){
            rgb[0] = p->x;
            rgb[1] = p->y;
            rgb[2] = p->z;
        };
        //! Default function: prints all variables.
        void show(){
            printf("Pixel(%.2f, %.2f, %.2f)\n", rgb[0], rgb[1], rgb[2]);
        };
    };

    //! This struct represents all colors in RGB that can be used.
    struct TableColor{
        //! Data: vector of Pixel.
        vector<Pixel> colors;
        //! Default constructor: TableColor tb;
        TableColor(){
            colors.push_back(Pixel(255, 128, 0));       // ORANGE = 0
            colors.push_back(Pixel(0, 0, 255));         // BLUE = 1
            colors.push_back(Pixel(255, 255, 0));       // YELLOW = 2
            colors.push_back(Pixel(255, 0, 0));         // RED = 3
            colors.push_back(Pixel(255, 51, 255));      // PINK = 4
            colors.push_back(Pixel(127, 0, 255));       // PURPLE = 5
            colors.push_back(Pixel(0, 255, 0));         // GREEN = 6
            colors.push_back(Pixel(153, 76, 0));        // BROWN = 7
        };
    };

    //! This struct represents a Color that can be calibrated: made by 2 Pixels that represents a range of color, Bottom Pixel Limit and Top Pixel Limit.
    struct VisionColor{
        //! Data: Bottom Pixel Limit 
        Pixel min;
        //! Data: Top Pixel Limit 
        Pixel max;

        //! Constructor default: VisionColor c;
        VisionColor(){
            min = Pixel(0, 0, 0);
            max = Pixel(255, 255, 255);
        };

        //! Constructor Pixels: VisionColor c( Pixel (r, g, b), Pixel (r, g, b));
        VisionColor(Pixel min, Pixel max){
            this->min = min;
            this->max = max;
        };

        //! Constructor copy: VisionColor c( VisionColor );
        VisionColor(VisionColor *color){
            min = color->min;
            max = color->max;
        };

        //! Default function: prints all variables.
        void show(){
            printf("VisionColor\nMin");
            min.show();
            printf("Max");
            max.show();
        }
    };

    //! This struct represents a configuration of colors of objects in workspace.
    struct ExecConfiguration{
        //! Data: comment of configuration. used to save in db
        string comment;
        //! Data: ENUM id_color
        int ball_color;
        //! Data: ENUM id_color
        int team_color[2];
        //! Data: ENUM id_color
        int secundary_color_1[3];
        //! Data: ENUM id_color
        int secundary_color_2[3];

        string data;

        //! Default constructor: ExecConfiguration exex;
        ExecConfiguration(){
            comment = "";

            ball_color = ORANGE;

            team_color[0] = YELLOW;

            team_color[1] = BLUE;

            for(int i = 0 ; i < 3 ; i++){
                secundary_color_1[i] = UNKNOWN;
                secundary_color_2[i] = UNKNOWN;
            }
        };

        //! Constructor copy: ExexConfiguration exex(ExecConfiguration());
        ExecConfiguration(ExecConfiguration *g){
            comment = g->comment;

            ball_color = g->ball_color;

            team_color[0] = g->team_color[0];

            team_color[1] = g->team_color[1];

            for(int i = 0 ; i < 3 ; i++){
                secundary_color_1[i] = UNKNOWN;
                secundary_color_2[i] = UNKNOWN;
            }
        };

        //! Default function: prints all variables.
        void show(){
            printf("ExecConfiguration:\n");
            //printf("Comment: %s\n", comment);
            printf("Ball_color: %d\n", ball_color);
            printf("Team_color_1: %d\n", team_color[0]);
            printf("Team_color_2: %d\n", team_color[1]);
            for(int i = 0 ; i < 3 ; i++){
                printf("Secundary_color_team_1: %d\n", secundary_color_1[i]);
                printf("Secundary_color_team_2: %d\n", secundary_color_2[i]);
            }
        }
    };

    //! This struct represents a calibration of colors
    struct Calibration{
        //! Data: comment of calibration. used to save in db
        string comment;
        //! Data: vector of VisionColor
        vector<VisionColor> colors;
        //! Data: vector of Point
        vector<Point> cut;
        //! Data: value of rotation i Z
        float rotation;
        //! Data: day of calibration. used ti save in db
        string data;

        //! Default constructor: Calibration c; initialize the vector with range of colors in HSV to track the objects with Saved Video and Saved Image. 
        Calibration(){
            comment = "lorem";

            colors.push_back(VisionColor(Pixel(104, 128 , 118), Pixel(122, 255, 255))); // ORANGE = 0
            colors.push_back(VisionColor(Pixel(0, 34, 71), Pixel(28, 255, 255)));       // BLUE = 1
            colors.push_back(VisionColor(Pixel(74, 66, 117), Pixel(104, 255, 255)));    // YELLOW = 2
            colors.push_back(VisionColor(Pixel(120, 165, 61), Pixel(156, 255, 255)));   // RED = 3
            colors.push_back(VisionColor(Pixel(119, 66, 145), Pixel(180, 174, 255)));   // PINK = 4
            colors.push_back(VisionColor(Pixel(125, 40, 112), Pixel(180, 255, 255)));   // PURPLE = 5
            colors.push_back(VisionColor(Pixel(21, 46, 120), Pixel(85, 255, 255)));     // GREEN = 6
            colors.push_back(VisionColor(Pixel(87, 150, 46), Pixel(107, 229, 60)));     // BROWN = 7


            cut.push_back(Point(0, 0));
            cut.push_back(Point(0, 0));

            rotation = 0.0;

            data = "0000-00-00";
        };
        //! Constructor copy: Calibration c(Calibration());
        Calibration(Calibration *c){
            comment = c->comment;
            colors = c->colors;
            cut = c->cut;
            rotation = c->rotation;
            data = c->data;
        };

        //! Default function: prints all variables.
        void show(){
            printf("Calibration:\n");
            cout << comment << endl;
            for(int i = 0 ; i < colors.size() ; i++){
                colors.at(i).show();
            }
            printf("Cut\n");
            for(int i = 0 ; i < cut.size() ; i++){
                printf("Point(%d, %d)\n", cut.at(i).x, cut.at(i).y);
            }
            printf("Rotation: %f\n", rotation);
            cout << data << endl;
        };
    };

    //! This strcut represets the pose that one robot can handle. Pos and Vel.
    struct Robot{
        //! Data: Pose
        btVector3 pose;
        //! Data: V_Pose
        btVector3 v_pose;

        //! Default constructor: Robot t;
        Robot(){
            pose = btVector3(0, 0, 0);
            v_pose = btVector3(0, 0, 0);
        };

        //! Constructor 2: Robot t(btVector3(x, y, yaw), btVector3(x, y, yaw))
        Robot(btVector3 pose, btVector3 v_pose){
            this->pose = pose;
            this->v_pose = v_pose;
        };

        //! Constructor copy: Robot t(Robot());
        Robot(Robot *r){
            pose = r->pose;
            v_pose = r->v_pose;
        };

        //! Default function: prints all variables.
        void show(){
            printf("Robot:\n");
            printf("Pose:\n");
            pose.show();
            printf("V_Pose:\n");
            v_pose.show();
        }
    };

    //! This struct represents the state that the workspace can handle.
    struct State{
        //! All robots by vision
        Robot robots[6];
        //! All robots by kalman
        Robot robots_kalman[6];
        //! Pos ball by vision
        btVector3 ball;
        //! Vel ball by vision
        btVector3 v_ball;
        //! Pos ball by kalman
        btVector3 ball_kalman;
        //! Vel ball by kalman
        btVector3 v_ball_kalman;
        //! Default constructor: State s;
        State(){};
        /* TODO: outros construtores*/
        //! Default function: prints all variables.
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

    //! This function clean a stringstream 
    void clearSS(stringstream &ss);

    //! Get int and convert to string.
    string toString(int a);

    //! Get float and convert to string.
    string toString(float a);

    //! Get double and convert to string.
    string toString(double a);

    //! Get long long int and convert to string.
    string toString(long long int a);

    //! Get boolean and convert to string.
    string toString(bool a);

    //! Get string and convert to Int.
    int toInt(string a);

    //! Get string and convert to float.
    float toFloat(string a);

    //! Get string and convert to double.
    double toDouble(string a);

    //! Get string and convert to long long int.
    long long int toLongLongInt(string a);

    //! Get string and convert to bool.
    bool toBool(string a);

    //! Send string to terminal and get the returned value.
    string cmdTerminal(string s);

    //! Estimate distance between a set of points.
    double distancePoint(btVector3, btVector3);

    //! Estimate distance between two points.
    double distancePoint(Point, Point);

    //! Estimate midpoint between two points.
    Point midpoint(Point, Point);

    //! Estimate gravity center in a quadrilateral.
    Point midpoint(Rect);

    //! Estimate midpoint between a set of points.
    btVector3 midpoint(btVector3, btVector3);

    //! Estimate angle between two straight lines.
    float angulation(Point, Point);

    //! Estimate angle between two straight lines in radian.
    double radian(Point, Point);

    vss_state::Global_State State2Global_State(State, ExecConfiguration);
}

#endif
