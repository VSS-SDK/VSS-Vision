//
// Created by manoel on 11/06/18.
//

#include <Helpers/TimeHelper.h>

TimeHelper::TimeHelper() {
    countFrame = 0;
    framesPerSecond = 0;
    startTime = std::chrono::high_resolution_clock::now();
}

void TimeHelper::startCounting() {
    startTime = std::chrono::high_resolution_clock::now();
}

void TimeHelper::restartCounting() {
    startCounting();
}

double TimeHelper::getElapsedTime() {

    auto finish = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> elapsed = finish - startTime;

    return elapsed.count();
}

bool TimeHelper::timeOut(int i) {
    if (getElapsedTime() >= i) {
        restartCounting();
        return true;

    } else {
        return false;
    }
}

int TimeHelper::fps(){
    if (getElapsedTime() >= 1000) {
        framesPerSecond = countFrame;
        countFrame = 0;
        restartCounting();

    } else {
        countFrame++;
    }
    return framesPerSecond;
}
