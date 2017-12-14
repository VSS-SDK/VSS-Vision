/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "GImage.h"

GImage::GImage()app{
    add_events(Gdk::BUTTON_PRESS_MASK);
    add_events(Gdk::BUTTON_MOTION_MASK);
    add_events(Gdk::BUTTON_RELEASE_MASK);
    add_events(Gdk::POINTER_MOTION_MASK);

    opencv_image = cv::Mat::zeros(1, 1, CV_64F);

    cut_mode = false;
    move_first_cut = false;
    move_adjust_cut = false;
}

bool GImage::on_draw (const Cairo::RefPtr<Cairo::Context> &c){

    try{
        cairo_image_size.x = get_allocation().get_width();
        cairo_image_size.y = get_allocation().get_height();

        if (opencv_image.rows != 0 && opencv_image.cols != 0){

            cv::resize(opencv_image, opencv_image, cairo_image_size, 0, 0, cv::INTER_LINEAR);
            
            Glib::RefPtr<Gdk::Pixbuf> pixbuf =  Gdk::Pixbuf::create_from_data( opencv_image.data, Gdk::COLORSPACE_RGB, false, 8, opencv_image.cols, opencv_image.rows, opencv_image.step);
            Gdk::Cairo::set_source_pixbuf(c, pixbuf);
            
            c->paint();
            c->move_to(cut_point.first.x , cut_point.first.y);
            c->line_to(cut_point.second.x, cut_point.first.y);
            c->line_to(cut_point.second.x, cut_point.second.y);
            c->line_to(cut_point.first.x , cut_point.second.y);
            c->close_path();

            std::vector<double> dashes = {50.0, 10.0, 10.0, 10.0};
            double offset = -50.0;

            c->set_dash(dashes, offset);
            c->set_source_rgba(1, 1, 1, 1);
            c->set_line_width(4.0);
            c->stroke();
        }

    } catch(const std::exception& ex) {
        std::cout << "EXCEPTION: " << ex.what() << "in GImage:on_draw " << std::endl;
    }
    
    return true;
}

bool GImage::on_button_press_event (GdkEventButton* event){
    if(event->button == GDK_BUTTON_SECONDARY && cut_mode) {
        cut_point.first = {int(event->x), int(event->y)};
        cut_point.second = {int(event->x), int(event->y)};
        move_first_cut = true;
    } 

    if(event->button == GDK_BUTTON_PRIMARY && cut_mode) {
        move_adjust_cut = true;
    }

    return true;
}

bool GImage::on_button_release_event (GdkEventButton* event){
    if(event->button == GDK_BUTTON_SECONDARY && cut_mode) {
        move_first_cut = false;
    }

    if(event->button == GDK_BUTTON_PRIMARY && cut_mode) {
        move_adjust_cut = false;
    }

    return true;
}

bool GImage::on_motion_notify_event (GdkEventMotion* event){
    if(move_first_cut && cut_mode) {
        cut_point.second = {int(event->x) , int(event->y)};
        queue_draw();
    
    } else if (move_adjust_cut && cut_mode) {

        int dist1 = abs(int(event->x) - cut_point.first.x);
        int dist2 = abs(int(event->x) - cut_point.second.x);
        int dist3 = abs(int(event->y) - cut_point.second.y);
        int dist4 = abs(int(event->y) - cut_point.first.y);

        if (dist1 < dist2 && dist1 < dist3 && dist1 < dist4){
            cut_point.first.x = int(event->x);
        } else if (dist2 < dist1 && dist2 < dist3 && dist2 < dist4){
            cut_point.second.x = int(event->x);
        } else if (dist3 < dist1 && dist3 < dist2 && dist3 < dist4){
            cut_point.second.y = int(event->y);
        } else if (dist4 < dist1 && dist4 < dist2 && dist4 < dist3){
            cut_point.first.y = int(event->y);
        }
        
        queue_draw();
    }
    return true;
}

void GImage::setImage(cv::Mat image){
    opencv_image = image;
    queue_draw();
}

void GImage::setCutMode(bool b){
    cut_mode = b;
}

void GImage::setRectangleInvisible(){
    cut_point.first  = {0,0};
    cut_point.second = {0,0};
}

cv::Point GImage::getCairoImageSize(){
    return cairo_image_size;
}

PointCut GImage::getCutPoint(){
    return cut_point;
}