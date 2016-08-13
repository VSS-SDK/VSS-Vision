/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef KALMAN_H
#define KALMAN_H

#include "common.h"

class kalman{
protected:
    int stateSize;
    int measSize;
    int contrSize;
    unsigned int type;

    KalmanFilter kf;
    Mat state, meas;
public:
    kalman();

    void init();
};

#endif // KALMAN_H
