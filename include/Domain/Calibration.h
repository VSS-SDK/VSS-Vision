/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef CALIBRATION_H
#define CALIBRATION_H

#include "iostream"
#include "vector"

#include "ColorRange.h"
#include "Point2d.h"

class Calibration {
public:
	float rotation;
	float brightness;
	float contrast;
	float saturation;
	float exposure;
	float gain;

	std::vector<ColorRange> colorsRange;
	std::vector<Point2d> cut;

	bool shouldCropImage;

	Calibration();
	Calibration( Calibration *calibration );

	friend std::ostream& operator<<( std::ostream& os, const Calibration& calibration );
};

#endif // CALIBRATION_H
