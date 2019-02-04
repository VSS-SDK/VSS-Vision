//
// Created by manoel on 11/06/18.
//

#include <Helpers/TimeHelper.h>

TimeHelper::TimeHelper() {
    contFrame = 0;
    numberFrame = 0;
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

void TimeHelper::calculateFramesPerSecond(){
    if (getElapsedTime() >= 1000) {
        numberFrame = numberFrame * 0.7 + contFrame * 0.3;
        contFrame = 0;
        restartCounting();

    } else {
        contFrame++;
    }
}

int TimeHelper::getFramesPerSecond() {
    return numberFrame;
}
