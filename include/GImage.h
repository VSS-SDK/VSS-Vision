/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef GIMAGE_H_
#define GIMAGE_H_

#include <gtkmm.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

struct PointCut {
	cv::Point2i first;
	cv::Point2i second;

	PointCut (){}

	// initialize making a square area to cut
	PointCut (cv::Point2i point, int side_size){
		first  = cv::Point( point.x - side_size , point.y - side_size );
        second = cv::Point( point.x + side_size , point.y + side_size );
	}
};

class GImage : public Gtk::DrawingArea {

private:
    cv::Mat opencv_image;
    cv::Point cairo_image_size;
    cv::Point pixel_color;
    PointCut cut_point;

    bool cut_mode;
    bool move_first_cut;
    bool move_adjust_cut;

    void drawRectangle(cv::Point, cv::Point);

protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context> &c) override;
    bool on_button_press_event(GdkEventButton* event) override;
    bool on_motion_notify_event(GdkEventMotion* event) override;
    bool on_button_release_event(GdkEventButton* event) override;

public:
	GImage();
    void setCutMode(bool);
    void setImage(cv::Mat);
    void setRectangleInvisible();
    cv::Point getCairoImageSize();
    PointCut getCutPoint();
};

#endif