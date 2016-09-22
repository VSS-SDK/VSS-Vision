/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "common.h"

namespace common{
    void clearSS(stringstream &ss){
        ss.str(string());
        ss.clear();
    }

    string toString(int a){
        stringstream ss;
        ss << a;
        return ss.str();
    }

    string toString(float a){
        stringstream ss;
        ss << a;
        return ss.str();
    }

    string toString(double a){
        stringstream ss;
        ss << a;
        return ss.str();
    }

    string toString(long long int a){
        stringstream ss;
        ss << a;
        return ss.str();
    }

    string toString(bool a){
        string s;
        if(a) s = "1";
        else s = "0";
        return s;
    }

    int toInt(string a){
        int aa;
        stringstream ss;
        ss << a;
        ss >> aa;
        return aa;
    }

    float toFloat(string a){
        float aa;
        stringstream ss;
        ss << a;
        ss >> aa;
        return aa;
    }

    double toDouble(string a){
        double aa;
        stringstream ss;
        ss << a;
        ss >> aa;
        return aa;
    }

    long long int toLongLongInt(string a){
        long long int aa;
        stringstream ss;
        ss << a;
        ss >> aa;
        return aa;
    }

    bool toBool(string a){
        string b = "0";
        if(a.compare(b) == 0) return false;
        else return true;
    }

    string cmdTerminal(string s){
        QProcess process;
        process.start(s.c_str());
        process.waitForFinished(-1); // will wait forever until finished

        QString stdout = process.readAllStandardOutput();
        string result = stdout.toUtf8().constData();
        return result;
    }

    double distancePoint(btVector3 a, btVector3 b){
        return sqrt(((a.x - b.x)*(a.x - b.x)) + ((a.y - b.y)*(a.y - b.y)));
    }

    double distancePoint(Point a, Point b){
        return sqrt(((a.x - b.x)*(a.x - b.x)) + ((a.y - b.y)*(a.y - b.y)));
    }

    Point midpoint(Point a, Point b){
        return Point(((a.x + b.x) / 2.0), ((a.y + b.y) / 2.0));
    }

    Point midpoint(Rect testLabel){
        return Point(testLabel.x + (testLabel.width/2.0), testLabel.y  + (testLabel.height/2.0));
    }

    //! Addendum
    //! --------
    //! 
    float angulation(Point a, Point b){
        //! > Estimate angle between two straight lines. 
        //! > One line formed by the two points in the function and 
        //! > the other line is formed by the point in the center of
        //! > the robot (estimated using midpoint() function) and for
        //! > a point in the pitch where the line must form a ninety 
        //! > degree angle with the pitch side.
        return (atan2(a.y - b.y, a.x - b.x) * (180/CV_PI));
    }

    double radian(Point a, Point b){
        return atan2(a.y - b.y, a.x - b.x);
    }

    vss_state::Global_State State2Global_State(State state, ExecConfiguration exec){
        vss_state::Global_State global_state;
        TableColor c;

        global_state = vss_state::Global_State();
        global_state.set_id(0);
	    global_state.set_situation(0);
        global_state.set_origin(true);

        vss_state::Ball_State *ball_s = global_state.add_balls();
        ball_s->mutable_pose()->set_x(state.ball.x);
        ball_s->mutable_pose()->set_y(state.ball.y);

        ball_s->mutable_v_pose()->set_x(state.v_ball.x);
        ball_s->mutable_v_pose()->set_y(state.v_ball.y);

        ball_s->mutable_k_pose()->set_x(state.ball_kalman.x);
        ball_s->mutable_k_pose()->set_y(state.ball_kalman.y);

        ball_s->mutable_k_v_pose()->set_x(state.v_ball_kalman.x);
        ball_s->mutable_k_v_pose()->set_y(state.v_ball_kalman.y);

        switch(exec.team_color[0]){
            case YELLOW:{
                for(int i = 0 ; i < 3 ; i++){
                    vss_state::Robot_State *robot_s = global_state.add_robots_blue();

                    robot_s->mutable_pose()->set_x(state.robots[i+3].pose.x);
                    robot_s->mutable_pose()->set_y(state.robots[i+3].pose.y);
                    robot_s->mutable_pose()->set_yaw(state.robots[i+3].pose.z);

                    robot_s->mutable_v_pose()->set_x(state.robots[i+3].v_pose.x);
                    robot_s->mutable_v_pose()->set_y(state.robots[i+3].v_pose.y);
                    robot_s->mutable_v_pose()->set_yaw(state.robots[i+3].v_pose.z);

                    robot_s->mutable_k_pose()->set_x(state.robots_kalman[i+3].pose.x);
                    robot_s->mutable_k_pose()->set_y(state.robots_kalman[i+3].pose.y);
                    robot_s->mutable_k_pose()->set_yaw(state.robots_kalman[i+3].pose.z);

                    robot_s->mutable_k_v_pose()->set_x(state.robots_kalman[i+3].v_pose.x);
                    robot_s->mutable_k_v_pose()->set_y(state.robots_kalman[i+3].v_pose.y);
                    robot_s->mutable_k_v_pose()->set_yaw(state.robots_kalman[i+3].v_pose.z);

                    if(i == 0 && exec.secundary_color_2[0] != UNKNOWN){
                        robot_s->mutable_color()->set_r(c.colors.at(exec.secundary_color_2[0]).rgb[0]);
                        robot_s->mutable_color()->set_g(c.colors.at(exec.secundary_color_2[0]).rgb[1]);
                        robot_s->mutable_color()->set_b(c.colors.at(exec.secundary_color_2[0]).rgb[2]);

                        //qDebug() << exec.secundary_color_1[0];
                    }

                    if(i == 1 && exec.secundary_color_2[1] != UNKNOWN){
                        robot_s->mutable_color()->set_r(c.colors.at(exec.secundary_color_2[1]).rgb[0]);
                        robot_s->mutable_color()->set_g(c.colors.at(exec.secundary_color_2[1]).rgb[1]);
                        robot_s->mutable_color()->set_b(c.colors.at(exec.secundary_color_2[1]).rgb[2]);

                        //qDebug() << exec.secundary_color_1[1];
                    }

                    if(i == 2 && exec.secundary_color_2[2] != UNKNOWN){
                        robot_s->mutable_color()->set_r(c.colors.at(exec.secundary_color_2[2]).rgb[0]);
                        robot_s->mutable_color()->set_g(c.colors.at(exec.secundary_color_2[2]).rgb[1]);
                        robot_s->mutable_color()->set_b(c.colors.at(exec.secundary_color_2[2]).rgb[2]);

                        //c.colors.at(exec.secundary_color_1[2]).show();
                    }
                }

                for(int i = 0 ; i < 3 ; i++){
                    vss_state::Robot_State *robot_s = global_state.add_robots_yellow();

                    robot_s->mutable_pose()->set_x(state.robots[i].pose.x);
                    robot_s->mutable_pose()->set_y(state.robots[i].pose.y);
                    robot_s->mutable_pose()->set_yaw(state.robots[i].pose.z);

                    robot_s->mutable_v_pose()->set_x(state.robots[i].v_pose.x);
                    robot_s->mutable_v_pose()->set_y(state.robots[i].v_pose.y);
                    robot_s->mutable_v_pose()->set_yaw(state.robots[i].v_pose.z);

                    robot_s->mutable_k_pose()->set_x(state.robots_kalman[i].pose.x);
                    robot_s->mutable_k_pose()->set_y(state.robots_kalman[i].pose.y);
                    robot_s->mutable_k_pose()->set_yaw(state.robots_kalman[i].pose.z);

                    robot_s->mutable_k_v_pose()->set_x(state.robots_kalman[i].v_pose.x);
                    robot_s->mutable_k_v_pose()->set_y(state.robots_kalman[i].v_pose.y);
                    robot_s->mutable_k_v_pose()->set_yaw(state.robots_kalman[i].v_pose.z);

                    if(i == 0 && exec.secundary_color_1[0] != UNKNOWN){
                        robot_s->mutable_color()->set_r(c.colors.at(exec.secundary_color_1[0]).rgb[0]);
                        robot_s->mutable_color()->set_g(c.colors.at(exec.secundary_color_1[0]).rgb[1]);
                        robot_s->mutable_color()->set_b(c.colors.at(exec.secundary_color_1[0]).rgb[2]);
                    }

                    if(i == 1 && exec.secundary_color_1[1] != UNKNOWN){
                        robot_s->mutable_color()->set_r(c.colors.at(exec.secundary_color_1[1]).rgb[0]);
                        robot_s->mutable_color()->set_g(c.colors.at(exec.secundary_color_1[1]).rgb[1]);
                        robot_s->mutable_color()->set_b(c.colors.at(exec.secundary_color_1[1]).rgb[2]);
                    }

                    if(i == 2 && exec.secundary_color_1[2] != UNKNOWN){
                        robot_s->mutable_color()->set_r(c.colors.at(exec.secundary_color_1[2]).rgb[0]);
                        robot_s->mutable_color()->set_g(c.colors.at(exec.secundary_color_1[2]).rgb[1]);
                        robot_s->mutable_color()->set_b(c.colors.at(exec.secundary_color_1[2]).rgb[2]);
                    }
                }
            }break;
            case BLUE:{
                for(int i = 0 ; i < 3 ; i++){
                    vss_state::Robot_State *robot_s = global_state.add_robots_blue();

                    robot_s->mutable_pose()->set_x(state.robots[i].pose.x);
                    robot_s->mutable_pose()->set_y(state.robots[i].pose.y);
                    robot_s->mutable_pose()->set_yaw(state.robots[i].pose.z);

                    robot_s->mutable_v_pose()->set_x(state.robots[i].v_pose.x);
                    robot_s->mutable_v_pose()->set_y(state.robots[i].v_pose.y);
                    robot_s->mutable_v_pose()->set_yaw(state.robots[i].v_pose.z);

                    robot_s->mutable_k_pose()->set_x(state.robots_kalman[i].pose.x);
                    robot_s->mutable_k_pose()->set_y(state.robots_kalman[i].pose.y);
                    robot_s->mutable_k_pose()->set_yaw(state.robots_kalman[i].pose.z);

                    robot_s->mutable_k_v_pose()->set_x(state.robots_kalman[i].v_pose.x);
                    robot_s->mutable_k_v_pose()->set_y(state.robots_kalman[i].v_pose.y);
                    robot_s->mutable_k_v_pose()->set_yaw(state.robots_kalman[i].v_pose.z);

                    if(i == 0 && exec.secundary_color_1[0] != UNKNOWN){
                        robot_s->mutable_color()->set_r(c.colors.at(exec.secundary_color_1[0]).rgb[0]);
                        robot_s->mutable_color()->set_g(c.colors.at(exec.secundary_color_1[0]).rgb[1]);
                        robot_s->mutable_color()->set_b(c.colors.at(exec.secundary_color_1[0]).rgb[2]);

                        //qDebug() << exec.secundary_color_1[0];
                    }

                    if(i == 1 && exec.secundary_color_1[1] != UNKNOWN){
                        robot_s->mutable_color()->set_r(c.colors.at(exec.secundary_color_1[1]).rgb[0]);
                        robot_s->mutable_color()->set_g(c.colors.at(exec.secundary_color_1[1]).rgb[1]);
                        robot_s->mutable_color()->set_b(c.colors.at(exec.secundary_color_1[1]).rgb[2]);

                        //qDebug() << exec.secundary_color_1[1];
                    }

                    if(i == 2 && exec.secundary_color_1[2] != UNKNOWN){
                        robot_s->mutable_color()->set_r(c.colors.at(exec.secundary_color_1[2]).rgb[0]);
                        robot_s->mutable_color()->set_g(c.colors.at(exec.secundary_color_1[2]).rgb[1]);
                        robot_s->mutable_color()->set_b(c.colors.at(exec.secundary_color_1[2]).rgb[2]);

                        //c.colors.at(exec.secundary_color_1[2]).show();
                    }
                }

                for(int i = 0 ; i < 3 ; i++){
                    vss_state::Robot_State *robot_s = global_state.add_robots_yellow();

                    robot_s->mutable_pose()->set_x(state.robots[i+3].pose.x);
                    robot_s->mutable_pose()->set_y(state.robots[i+3].pose.y);
                    robot_s->mutable_pose()->set_yaw(state.robots[i+3].pose.z);

                    robot_s->mutable_v_pose()->set_x(state.robots[i+3].v_pose.x);
                    robot_s->mutable_v_pose()->set_y(state.robots[i+3].v_pose.y);
                    robot_s->mutable_v_pose()->set_yaw(state.robots[i+3].v_pose.z);

                    robot_s->mutable_k_pose()->set_x(state.robots_kalman[i+3].pose.x);
                    robot_s->mutable_k_pose()->set_y(state.robots_kalman[i+3].pose.y);
                    robot_s->mutable_k_pose()->set_yaw(state.robots_kalman[i+3].pose.z);

                    robot_s->mutable_k_v_pose()->set_x(state.robots_kalman[i+3].v_pose.x);
                    robot_s->mutable_k_v_pose()->set_y(state.robots_kalman[i+3].v_pose.y);
                    robot_s->mutable_k_v_pose()->set_yaw(state.robots_kalman[i+3].v_pose.z);

                    if(i == 0 && exec.secundary_color_2[0] != UNKNOWN){
                        robot_s->mutable_color()->set_r(c.colors.at(exec.secundary_color_2[0]).rgb[0]);
                        robot_s->mutable_color()->set_g(c.colors.at(exec.secundary_color_2[0]).rgb[1]);
                        robot_s->mutable_color()->set_b(c.colors.at(exec.secundary_color_2[0]).rgb[2]);
                    }

                    if(i == 1 && exec.secundary_color_2[1] != UNKNOWN){
                        robot_s->mutable_color()->set_r(c.colors.at(exec.secundary_color_2[1]).rgb[0]);
                        robot_s->mutable_color()->set_g(c.colors.at(exec.secundary_color_2[1]).rgb[1]);
                        robot_s->mutable_color()->set_b(c.colors.at(exec.secundary_color_2[1]).rgb[2]);
                    }

                    if(i == 2 && exec.secundary_color_2[2] != UNKNOWN){
                        robot_s->mutable_color()->set_r(c.colors.at(exec.secundary_color_2[2]).rgb[0]);
                        robot_s->mutable_color()->set_g(c.colors.at(exec.secundary_color_2[2]).rgb[1]);
                        robot_s->mutable_color()->set_b(c.colors.at(exec.secundary_color_2[2]).rgb[2]);
                    }
                }
            }break;
        }

        return global_state;
    }
}