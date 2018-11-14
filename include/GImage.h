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
#include <iostream>
#include "FrameHelper.h"

#include "opencv2/imgproc/imgproc.hpp"

class GImage : public Gtk::DrawingArea {
public:
    GImage(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
    virtual ~GImage();
    
    void setCutMode(bool);
    void setImage(cv::Mat);
    cv::Point getCutPoint1();
    cv::Point getCutPoint2();

    void setCutPoint1(cv::Point);
    void setCutPoint2(cv::Point);
    void processImage(cv::Mat);


protected:
    //bool on_expose_event(GdkEventExpose* event) override;
    bool on_button_press_event(GdkEventButton* event) override;
    bool on_motion_notify_event(GdkEventMotion* event) override;
    bool on_button_release_event(GdkEventButton* event) override;

private:

    cv::Point checkPointInsideImage(cv::Point);

    cv::Mat cv_image;

    cv::Point cut_point_1;
    cv::Point cut_point_2;

    bool cut_mode;
    bool cut_move;
    bool cut_move_adjust;

    int width_image;
    int height_image;
    int width_original_image;
    int height_original_image;
};

#endif