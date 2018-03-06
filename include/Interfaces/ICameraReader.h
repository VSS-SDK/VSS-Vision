//
// Created by johnathan on 01/03/18.
//

#ifndef VSS_VISION_ICAMERAREADER_H
#define VSS_VISION_ICAMERAREADER_H

#include <vector>
#include <cxcore.h>
#include <sigc++/sigc++.h>

class ICameraReader{
public:
    virtual void initializeCapture() = 0;
    virtual std::vector<int> getAllCamerasIndex() = 0;
    virtual void setCameraIndex(int) = 0;
    virtual cv::Mat getActualFrame() = 0;
    virtual void pause() = 0;
    virtual void start() = 0;
    virtual void close() = 0;

    sigc::signal <void, cv::Mat> signal_update_frame;
};

#endif //VSS_VISION_ICAMERAREADER_H
