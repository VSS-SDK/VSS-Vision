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
    int getFramesPerSecond();

    void calculateFramesPerSecond();
    bool timeOut(int);

private:
    std::chrono::system_clock::time_point startTime;
    int contFrame;
    int numberFrame;
};

#endif //VSS_VISION_TIMEHELPER_H
