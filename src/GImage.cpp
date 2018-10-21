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

    cut_mode = false;
    cut_move = false;
    cut_move_adjust = false;

    cv_image = cv::Mat::zeros(1, 1, CV_64F);

    set_size_request(250,200);
}

GImage::~GImage(){
}

bool GImage::on_expose_event(GdkEventExpose* event) {

    try{
        Glib::RefPtr<Gdk::Window> window = get_window();

        Cairo::RefPtr<Cairo::Context> c = window->create_cairo_context();

        Glib::RefPtr<Gdk::Pixbuf> pixbuf =  Gdk::Pixbuf::create_from_data( cv_image.data, Gdk::COLORSPACE_RGB, false, 8, cv_image.cols, cv_image.rows, cv_image.step);
        Gdk::Cairo::set_source_pixbuf(c, pixbuf);
        c->paint();

        if (cut_mode) {
            c->move_to(cut_point_1.x , cut_point_1.y);
            c->line_to(cut_point_2.x , cut_point_1.y);
            c->line_to(cut_point_2.x , cut_point_2.y);
            c->line_to(cut_point_1.x , cut_point_2.y);
            c->close_path();

            std::vector<double> dash = {20.0, 20.0};
            c->set_dash(dash, 1);
            c->set_source_rgba(1, 0, 0, 1);
            c->set_line_width(2.0);
            c->stroke();
        }

    } catch(const std::exception& ex) {
        std::cout << "EXCEPTION: " << ex.what() << "in GImage:on_draw " << std::endl;
    }

    return true;
}

bool GImage::on_button_press_event (GdkEventButton* event){
    if (event->button == 1 && cut_mode) {
        cut_move_adjust = true;
    }

    if (event->button == 3 && cut_mode) {
        cut_point_1 = {int(event->x), int(event->y)};
        cut_point_2 = {int(event->x), int(event->y)};
        cut_move = true;
    }

    return true;
}

bool GImage::on_button_release_event (GdkEventButton* event){
    if (event->button == 1 && cut_mode) {
        cut_move_adjust = false;
    }

    if (event->button == 3 && cut_mode) {
        cut_move = false;
    }

    return true;
}

bool GImage::on_motion_notify_event (GdkEventMotion* event){
    if (cut_move && cut_mode) {
        cut_point_2 = {int(event->x) , int(event->y)};
        queue_draw();

    } else if (cut_move_adjust && cut_mode) {

        int dist1 = abs(int(event->x) - cut_point_1.x);
        int dist2 = abs(int(event->x) - cut_point_2.x);
        int dist3 = abs(int(event->y) - cut_point_2.y);
        int dist4 = abs(int(event->y) - cut_point_1.y);

        if (dist1 < dist2 && dist1 < dist3 && dist1 < dist4){
            cut_point_1.x = int(event->x);
        } else if (dist2 < dist1 && dist2 < dist3 && dist2 < dist4){
            cut_point_2.x = int(event->x);
        } else if (dist3 < dist1 && dist3 < dist2 && dist3 < dist4){
            cut_point_2.y = int(event->y);
        } else if (dist4 < dist1 && dist4 < dist2 && dist4 < dist3){
            cut_point_1.y = int(event->y);
        }

        queue_draw();
    }

    cut_point_1 = checkPointInsideImage(cut_point_1);
    cut_point_2 = checkPointInsideImage(cut_point_2);

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

    do {
        float ratio = float(width_image) / float(cv_image.cols);

        width_image  = width_image - 1;
        height_image = cv_image.rows * ratio;

    } while (height_image > get_allocation().get_height());

    cv_image = resizeImage(cv_image, cv::Point(width_image , height_image));

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

cv::Point GImage::getCutPoint1(){
    cv::Point aux;
    aux.x = (cut_point_1.x * width_original_image) / cv_image.cols;
    aux.y = (cut_point_1.y * height_original_image) / cv_image.rows;
    return aux;
}

cv::Point GImage::getCutPoint2(){
    cv::Point aux;
    aux.x = (cut_point_2.x * width_original_image) / cv_image.cols;
    aux.y = (cut_point_2.y * height_original_image) / cv_image.rows;
    return aux;
}

void GImage::setCutPoint1(cv::Point p) {
    p = checkPointInsideImage(p);
    cut_point_1 = p;

}

void GImage::setCutPoint2(cv::Point p) {
    p = checkPointInsideImage(p);
    cut_point_2 = p;
}
