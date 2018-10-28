//
// Created by paulo on 20/10/18.
//

#include "RobotOpponentKalmanFilter.h"

RobotOpponentKalmanFilter::RobotOpponentKalmanFilter() {
    notFoundCount = 0;
    maxNotFoundCount = 100;
    foundDelayFlag = false;
    foundFlag = false;
    init();
}

void RobotOpponentKalmanFilter::init() {
    int stateSize = 4; // Variable states: [X,Y XSPEED, YSPEED]
    int measSize = 2; // Measure vector: [X, Y]
    int contrSize = 0; // No control

    unsigned int type = CV_32F;

    cv::KalmanFilter kf(stateSize, measSize, contrSize, type);
    kalmanFilter = kf;

    cv::Mat state(stateSize, 1, type); //[x,y,xs,ys]
    this->state = state;
    cv::Mat measure(measSize, 1, type); //[x,y]
    this->measure = measure;

    // Transition State Matrix A
    // Note: set deltaTime (dT) at each processing step!
    // [ 1 0 dT 0  ]
    // [ 0 1 0  dT ]
    // [ 0 0 1  0  ]
    // [ 0 0 0  1  ]
    cv::setIdentity(kalmanFilter.transitionMatrix);

    // Measure Matrix H
    // [ 1 0 0 0 ]
    // [ 0 1 0 0 ]
    kalmanFilter.measurementMatrix = cv::Mat::zeros(measSize, stateSize, type);
    kalmanFilter.measurementMatrix.at<float>(0) = 1.0f;
    kalmanFilter.measurementMatrix.at<float>(5) = 1.0f;

    // Process Noise Covariance Matrix Q
    // [ Ex   0   0     0     ]
    // [ 0    Ey  0     0     ]
    // [ 0    0   Ev_x  0     ]
    // [ 0    0   0     Ev_y  ]
    kalmanFilter.processNoiseCov.at<float>(0) = 1e-2;
    kalmanFilter.processNoiseCov.at<float>(5) = 1e-2;
    kalmanFilter.processNoiseCov.at<float>(10) = 5.0f;
    kalmanFilter.processNoiseCov.at<float>(15) = 5.0f;

    // Measures Noise Covariance Matrix R
    cv::setIdentity(kalmanFilter.measurementNoiseCov, cv::Scalar(1e-1));
}

void RobotOpponentKalmanFilter::predict() {

    if (foundDelayFlag) {
        // >>>> Matrix A
        kalmanFilter.transitionMatrix.at<float>(2) = deltaTime;
        kalmanFilter.transitionMatrix.at<float>(7) = deltaTime;

        state = kalmanFilter.predict();

        robotPredicted.x = state.at<float>(0);
        robotPredicted.y = state.at<float>(1);
        robotPredicted.angle = robotMesured.angle;
        robotPredicted.speedX = state.at<float>(2);
        robotPredicted.speedY = state.at<float>(3);

        //std::cout<<"Predição da bola:"<<std::endl;
        //std::cout<<"( "<<state.at<float>(0)<<" , "<<state.at<float>(1)<<" , "<<state.at<float>(2)<<" , "<<state.at<float>(3)<<std::endl;
    }
}

void RobotOpponentKalmanFilter::update() {
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

        if (!foundDelayFlag) {
            // >>>> Initialization
            kalmanFilter.errorCovPre.at<float>(0) = 1; // px
            kalmanFilter.errorCovPre.at<float>(5) = 1; // px
            kalmanFilter.errorCovPre.at<float>(10) = 1;
            kalmanFilter.errorCovPre.at<float>(15) = 1;

            //std::cout<<"ENtro"<<std::endl;

            state.at<float>(0) = measure.at<float>(0);
            state.at<float>(1) = measure.at<float>(1);
            state.at<float>(2) = 0;
            state.at<float>(3) = 0;
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

void RobotOpponentKalmanFilter::setRobot(vss::Robot robot) {
    robotMesured = robot;
}

void RobotOpponentKalmanFilter::setDeltaTime(double deltaTime) {
    this->deltaTime = deltaTime;
}

void RobotOpponentKalmanFilter::setFoundFlag(bool flag) {
    foundFlag = flag;
}

vss::Robot RobotOpponentKalmanFilter::getRobot() {
    return robotPredicted;
}