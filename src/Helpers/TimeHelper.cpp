//
// Created by manoel on 11/06/18.
//

#include <Helpers/TimeHelper.h>

TimeHelper::TimeHelper() {
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