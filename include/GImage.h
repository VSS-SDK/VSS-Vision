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
#include <vector>
#include "FrameHelper.h"

#include "opencv2/imgproc/imgproc.hpp"

class GImage : public Gtk::DrawingArea {
public:
    GImage(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
    virtual ~GImage();

    void processImage(cv::Mat);

    void setCutMode(bool);
    void setImage(cv::Mat);

    std::vector<cv::Point> getPoints();

    std::vector<cv::Point> clicked_point;
protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

    bool on_button_press_event(GdkEventButton* event) override;

private:
    int current_point;

    cv::Point checkPointInsideImage(cv::Point);

    cv::Mat cv_image;

    bool cut_mode;

    int width_image;
    int height_image;
    int width_original_image;
    int height_original_image;
};

#endif