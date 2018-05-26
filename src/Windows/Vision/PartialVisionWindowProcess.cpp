/*
* This file is part of the VSS-Vision project.
*
* This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
* v. 3.0. If a copy of the GPL was not distributed with this
* file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
*/

#include <Windows/Vision/VisionWindow.h>

void VisionWindow::setNewFrame() {
    processFrame();
    screenImage->set_image(frame);
}

void VisionWindow::receiveNewFrame(cv::Mat _frame) {
    frame = _frame;
    signal_set_new_frame.emit();
}

void VisionWindow::processFrame() {
    //cv::warpAffine(frame, frame, cv::getRotationMatrix2D(cv::Point2f(frame.cols/2, frame.rows/2), calibration.rotation, 1.0), frame.size());
    map<WhoseName, ColorPosition> positions = getColorPosition();

    robotRecognizer->recognizeRobots(positions);

    auto robots = robotRecognizer->getRobots();
    auto ball = robotRecognizer->getBall();

//    for(auto r : robots){
//        cout << "robot " << r.x << " " << r.y << endl;
//    }
//
//    cout << ball.x << " " << ball.y << " " << ball.speedX << " " << ball.speedY << endl;

    // should it be here?
    sendState(robots, ball);
}

std::map<WhoseName, ColorPosition> VisionWindow::getColorPosition() {
    map<WhoseName, ColorPosition> whosePosition;

    for (auto colorRange : calibration.colorsRange) {
        WhoseName objectName = whoseColor[colorRange.colorType];

        if (objectName != WhoseName::Unknown) {
            colorRecognizer->setColorRange(colorRange);
            colorRecognizer->processImage(frame);

            ColorPosition colorPosition;
            colorPosition.color = colorRange.colorType;
            colorPosition.points = colorRecognizer->getCenters();

            whosePosition[objectName] = colorPosition;

            /* TO DRAW IN IMAGE */
            auto rectangles = colorRecognizer->getRectangles();
            for (unsigned int i = 0; i < rectangles.size(); i++) {
                cv::rectangle(frame, rectangles.at(i), cv::Scalar(255, 255, 255), 1, 1, 0);
            }
        }
    }

    return whosePosition;
}

void VisionWindow::sendState(std::vector<vss::Robot> robots, vss::Ball ball) {
    for (unsigned int i = 0; i < robots.size()/2; i++) {
        vss_state::Robot_State *robot_s = global_state.add_robots_blue();

        robot_s->mutable_pose()->set_x(robots[i + 3].x);
        robot_s->mutable_pose()->set_y(robots[i + 3].y);
        robot_s->mutable_pose()->set_yaw(robots[i + 3].angle);

        robot_s->mutable_v_pose()->set_x(robots[i + 3].speedX);
        robot_s->mutable_v_pose()->set_y(robots[i + 3].speedY);
        robot_s->mutable_v_pose()->set_yaw(0);

        robot_s->mutable_k_pose()->set_x(0);
        robot_s->mutable_k_pose()->set_y(0);
        robot_s->mutable_k_pose()->set_yaw(0);

        robot_s->mutable_k_v_pose()->set_x(0);
        robot_s->mutable_k_v_pose()->set_y(0);
        robot_s->mutable_k_v_pose()->set_yaw(0);
    }

    for (unsigned int i = 0; i < robots.size()/2; i++) {
        vss_state::Robot_State *robot_s = global_state.add_robots_yellow();

        robot_s->mutable_pose()->set_x(robots[i].x);
        robot_s->mutable_pose()->set_y(robots[i].y);
        robot_s->mutable_pose()->set_yaw(robots[i].angle);

        robot_s->mutable_v_pose()->set_x(robots[i].speedX);
        robot_s->mutable_v_pose()->set_y(robots[i].speedY);
        robot_s->mutable_v_pose()->set_yaw(0);

        robot_s->mutable_k_pose()->set_x(0);
        robot_s->mutable_k_pose()->set_y(0);
        robot_s->mutable_k_pose()->set_yaw(0);

        robot_s->mutable_k_v_pose()->set_x(0);
        robot_s->mutable_k_v_pose()->set_y(0);
        robot_s->mutable_k_v_pose()->set_yaw(0);
    }

    vss_state::Ball_State *ball_s = global_state.add_balls();
    ball_s->mutable_pose()->set_x(ball.x);
    ball_s->mutable_pose()->set_y(ball.y);
    ball_s->mutable_v_pose()->set_x(ball.speedX);
    ball_s->mutable_v_pose()->set_y(ball.speedY);

    ball_s->mutable_k_pose()->set_x(0);
    ball_s->mutable_k_pose()->set_y(0);

    ball_s->mutable_k_v_pose()->set_x(0);
    ball_s->mutable_k_v_pose()->set_y(0);

    interface.sendState();
}
