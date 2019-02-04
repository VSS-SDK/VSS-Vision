/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "GImage.h"

GImage::GImage(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder) : Gtk::DrawingArea(cobject) {
    add_events(Gdk::BUTTON_PRESS_MASK);
    add_events(Gdk::BUTTON_MOTION_MASK);
    add_events(Gdk::BUTTON_RELEASE_MASK);
    add_events(Gdk::POINTER_MOTION_MASK);

    clicked_point.resize(4);

    current_point = 0;

    cut_mode = false;

    cv_image = cv::Mat::zeros(1, 1, CV_64F);

    set_size_request(250,200);
}

GImage::~GImage(){
}


bool GImage::on_draw(const Cairo::RefPtr<Cairo::Context>& c) {

    try{
        Glib::RefPtr<Gdk::Window> window = get_window();

        Glib::RefPtr<Gdk::Pixbuf> pixbuf =  Gdk::Pixbuf::create_from_data( cv_image.data, Gdk::COLORSPACE_RGB, false, 8, cv_image.cols, cv_image.rows, cv_image.step);
        Gdk::Cairo::set_source_pixbuf(c, pixbuf);
        c->paint();

        if (cut_mode) {

            for (unsigned int i = 0; i < clicked_point.size(); i++) {
                if (clicked_point[i].x != 0 and clicked_point[i].y != 0) {
                    c->save();
                    c->arc(clicked_point[i].x, clicked_point[i].y, 5.0, 0.0, 2.0 * M_PI);
                    c->set_source_rgba(1.0, 0.0, 0.0, 1.0);
                    c->fill_preserve();
                    c->restore();
                    c->stroke();
                }
            }
        }

    } catch(const std::exception& ex) {
        std::cout << "EXCEPTION: " << ex.what() << "in GImage:on_draw " << std::endl;
    }

    return true;
}


bool GImage::on_button_press_event (GdkEventButton* event){
    if (event->button == 1 && cut_mode) {
        clicked_point[current_point] = {int(event->x), int(event->y)};

        current_point++;
        if (current_point > 3) current_point = 0;
    }

    return true;
}


void GImage::processImage(cv::Mat image) {

    if(image.type() != 0) {
        cv_image = changeColorSpace(image, cv::COLOR_BGR2RGB);
    } else {
        cv_image = changeColorSpace(image, cv::COLOR_GRAY2RGB);
    }

    width_original_image = cv_image.cols;
    height_original_image = cv_image.rows;

    width_image  = get_allocation().get_width();
    height_image = get_allocation().get_height();

    if (width_original_image > width_image || height_original_image > height_image) {
        do {
            float ratio = float(width_image) / float(cv_image.cols);

            width_image = width_image - 1;
            height_image = cv_image.rows * ratio;

        } while (height_image > get_allocation().get_height());

        cv_image = resizeImage(cv_image, cv::Point(width_image, height_image));
    }

    queue_draw();
}

cv::Point GImage::checkPointInsideImage(cv::Point point) {
    if (point.x < 0) point.x = 0;
    if (point.y < 0) point.y = 0;
    if (point.x > width_image) point.x = width_image;
    if (point.y > height_image) point.y = height_image;
    return point;
}

void GImage::setImage(cv::Mat _cv_image){
    if (!_cv_image.empty()) processImage(_cv_image);
}

void GImage::setCutMode(bool _cut_mode){
    cut_mode = _cut_mode;
}

std::vector<cv::Point> GImage::getPoints(){
    std::vector<cv::Point> aux(4);

    for (unsigned int i = 0; i < 4; i++) {
        aux[i].x = (clicked_point[i].x * width_original_image) / cv_image.cols;
        aux[i].y = (clicked_point[i].y * height_original_image) / cv_image.rows;
    }

    return aux;
}