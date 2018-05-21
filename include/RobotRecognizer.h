//
// Created by manoel on 14/05/18/.
//

#ifndef VSS_VISION_ROBOTRECOGNIZER_H
#define VSS_VISION_ROBOTRECOGNIZER_H

#include "Interfaces/IRobotRecognizer.h"

class RobotRecognizer : public IRobotRecognizer {
	
public:

    void recognizeRobots(std::map<WhoseName,ColorPosition>) override;
    std::vector<vss::Robot> getRobots() override;

private:

    std::vector<vss::Robot> robots;


};

#endif
