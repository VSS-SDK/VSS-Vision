/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */
 
#ifndef HEADERS_H_
#define HEADERS_H_

#define CALIBRATION

#define PATHSAVE			"../Data/"

#include <iostream>
#include <cstdlib>
#include "string"
#include <sstream>
#include <fstream>
#include "unistd.h"
#include "vector"

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "../Utils/Commons/Commons.h"
 
using namespace std;
using namespace cv;
using namespace common;

#include "../Utils/CRUD/CRUD.h"
#include "Calibration.h"

#endif
