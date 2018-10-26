//
// Created by paulo on 19/10/18.
//

#include "RobotTeamKalmanFilter.h"

RobotTeamKalmanFilter::RobotTeamKalmanFilter() {
    notFoundCount = 0;
    maxNotFoundCount = 100;
    foundDelayFlag = false;
    foundFlag = false;
    init();
}

void RobotTeamKalmanFilter::init() {
    int stateSize = 6; // Variable states: [X , Y, ANGLE, XSPEED, YSPEED, ANGLESPEED]
    int measSize = 3; // Measure vector: [X, Y, ANGLE]
    int contrSize = 0; // No control

    unsigned int type = CV_32F;

    cv::KalmanFilter kf(stateSize, measSize, contrSize, type);
    kalmanFilter = kf;

    cv::Mat state(stateSize, 1, type); //[x, y, as, xs, ys, as]
    this->state = state;
    cv::Mat measure(measSize, 1, type); //[x , y, a]
    this->measure = measure;

    // Transition State Matrix A
    // Note: set deltaTime (dT) at each processing step!
    // [ 1 0 0 dT  0 0 ]
    // [ 0 1 0  0 dT 0 ]
    // [ 0 0 1  0  0 dT]
    // [ 0 0 0  1  0 0 ]
    // [ 0 0 0  0  1 0 ]
    // [ 0 0 0  0  0 1 ]
    cv::setIdentity(kalmanFilter.transitionMatrix);

    // Measure Matrix H
    // [ 1 0 0 0 0 0 ]
    // [ 0 1 0 0 0 0 ]
    // [ 0 0 1 0 0 0 ]
    kalmanFilter.measurementMatrix = cv::Mat::zeros(measSize, stateSize, type);
    kalmanFilter.measurementMatrix.at<float>(0) = 1.0f;
    kalmanFilter.measurementMatrix.at<float>(7) = 1.0f;
    kalmanFilter.measurementMatrix.at<float>(14) = 1.0f;

    // Process Noise Covariance Matrix Q
    // [ Ex   0   0     0     0      0 ]
    // [ 0    Ey  0     0     0      0 ]
    // [ 0    0   Eangle  0   0      0 ]
    // [ 0    0   0     Es_x  0      0 ]
    // [ 0    0   0     0     Es_y   0 ]
    // [ 0    0   0     0     0    Es_a]

    kalmanFilter.processNoiseCov.at<float>(0) = 1e-2;
    kalmanFilter.processNoiseCov.at<float>(7) = 1e-2;
    kalmanFilter.processNoiseCov.at<float>(14) = 1e-2;
    kalmanFilter.processNoiseCov.at<float>(21) = 5.0f;
    kalmanFilter.processNoiseCov.at<float>(28) = 5.0f;
    kalmanFilter.processNoiseCov.at<float>(35) = 5.0f;

    // Measures Noise Covariance Matrix R
    cv::setIdentity(kalmanFilter.measurementNoiseCov, cv::Scalar(1e-1));
}

void RobotTeamKalmanFilter::predict() {

    if (foundDelayFlag) {
        // >>>> Matrix A
        kalmanFilter.transitionMatrix.at<float>(3) = deltaTime;
        kalmanFilter.transitionMatrix.at<float>(10) = deltaTime;
        kalmanFilter.transitionMatrix.at<float>(17) = deltaTime;

        state = kalmanFilter.predict();

        robotPredicted.x = state.at<float>(0);
        robotPredicted.y = state.at<float>(1);
        robotPredicted.angle = state.at<float>(2);

        robotPredicted.speedX = state.at<float>(3);
        robotPredicted.speedY = state.at<float>(4);
        robotPredicted.speedAngle = state.at<float>(5);

        //std::cout<<"Predição do robo:"<<std::endl;
        //std::cout<<"( "<<state.at<float>(0)<<" , "<<state.at<float>(1)<<" , "<<state.at<float>(2)<<" , "<<state.at<float>(3)<<" , "<<state.at<float>(4)<<" , "<<state.at<float>(5)<<")"<<std::endl;
    }
}

void RobotTeamKalmanFilter::update() {
    if (!foundFlag) {
        notFoundCount++;
        //std::cout << "notFoundCount:" << notFoundCount << std::endl;
        if (notFoundCount >= maxNotFoundCount) {
            foundDelayFlag = false;
            // std::cout<<"Saiu"<<std::endl;
        }
    } else {
        notFoundCount = 0;

        measure.at<float>(0) = robotMesured.x;
        measure.at<float>(1) = robotMesured.y;
        measure.at<float>(2) = robotMesured.angle;

        if (!foundDelayFlag) {
            // >>>> Initialization
            kalmanFilter.errorCovPre.at<float>(0) = 1; // px
            kalmanFilter.errorCovPre.at<float>(7) = 1; // px
            kalmanFilter.errorCovPre.at<float>(14) = 1;
            kalmanFilter.errorCovPre.at<float>(21) = 1;
            kalmanFilter.errorCovPre.at<float>(28) = 1; // px
            kalmanFilter.errorCovPre.at<float>(35) = 1; // px

            //std::cout<<"ENtro"<<std::endl;

            state.at<float>(0) = measure.at<float>(0);
            state.at<float>(1) = measure.at<float>(1);
            state.at<float>(2) = measure.at<float>(2);
            state.at<float>(3) = 0;
            state.at<float>(4) = 0;
            state.at<float>(5) = 0;
            // <<<< Initialization

            kalmanFilter.statePost = state;

            foundDelayFlag = true;
        } else {
            kalmanFilter.correct(measure); // Kalman Correction
        }

        //std::cout<<"Medição da bola:"<<std::endl;
        // std::cout<<"( "<<measure.at<float>(0)<<" , "<<measure.at<float>(1)<<" )"<<std::endl;
    }
}

void RobotTeamKalmanFilter::setRobot(vss::Robot robot) {
    robotMesured = robot;
}

void RobotTeamKalmanFilter::setDeltaTime(double deltaTime) {
    this->deltaTime = deltaTime;
}

void RobotTeamKalmanFilter::setFoundFlag(bool flag) {
    foundFlag = flag;
}

vss::Robot RobotTeamKalmanFilter::getRobot() {
    return robotPredicted;
}