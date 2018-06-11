//
// Created by manoel on 11/06/18.
//

#ifndef VSS_VISION_TIMEHELPER_H
#define VSS_VISION_TIMEHELPER_H

#include <chrono>

class TimeHelper {

public:

    TimeHelper();
    void startCounting();
    void restartCounting();
    double getElapsedTime();

private:

    std::chrono::system_clock::time_point startTime;
};

#endif //VSS_VISION_TIMEHELPER_H
