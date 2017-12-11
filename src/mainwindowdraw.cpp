#include "mainwindowdraw.h"

MainWindowDraw::MainWindowDraw(){
    add_events(Gdk::BUTTON_PRESS_MASK);
    add_events(Gdk::BUTTON_MOTION_MASK);
    add_events(Gdk::BUTTON_RELEASE_MASK);
    add_events(Gdk::POINTER_MOTION_MASK);

    opencv_image = cv::Mat::zeros(1, 1, CV_64F);

    cut_mode = false;
    move_first_cut = false;
    move_adjust_cut = false;
}

bool MainWindowDraw::on_draw (const Cairo::RefPtr<Cairo::Context> &cairo_draw){

    try{
        Gtk::Allocation allocation = get_allocation();
            cairo_image_size.x = allocation.get_width();
            cairo_image_size.y = allocation.get_height();
            opencv_image_size  = opencv_image.size();

        if (opencv_image_size.x != 0 && opencv_image_size.y != 0){
            cv::Mat opencv_image_resize;
            cv::resize(opencv_image, opencv_image_resize, cairo_image_size, 0, 0, cv::INTER_LINEAR);
            
            Glib::RefPtr<Gdk::Pixbuf> pixbuf =  Gdk::Pixbuf::create_from_data( opencv_image_resize.data, Gdk::COLORSPACE_RGB, false, 8, opencv_image_resize.cols, opencv_image_resize.rows, opencv_image_resize.step);
            Gdk::Cairo::set_source_pixbuf(cairo_draw, pixbuf);
            cairo_draw->paint();

            cairo_draw->move_to(cut_point.first.x,  cut_point.first.y);
            cairo_draw->line_to(cut_point.second.x, cut_point.first.y);
            cairo_draw->line_to(cut_point.second.x, cut_point.second.y);
            cairo_draw->line_to(cut_point.first.x, cut_point.second.y);
            cairo_draw->close_path();

            std::vector<double> dashes = {50.0, 10.0, 10.0, 10.0};
            double offset = -50.0;

            cairo_draw->set_dash(dashes, offset);
            cairo_draw->set_source_rgba(1, 1, 1, 1);
            cairo_draw->set_line_width(4.0);
            cairo_draw->stroke();
        }

    } catch(const std::exception& ex) {
        std::cout << "EXCEPTION: " << ex.what() << "in MainWindowDraw:on_draw " << std::endl;
    }
    
    return true;
}

bool MainWindowDraw::on_button_press_event (GdkEventButton* event){
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

bool MainWindowDraw::on_button_release_event (GdkEventButton* event){
    if(event->button == GDK_BUTTON_SECONDARY && cut_mode) {
        move_first_cut = false;
    }

    if(event->button == GDK_BUTTON_PRIMARY && cut_mode) {
        move_adjust_cut = false;
    }

    return true;
}

bool MainWindowDraw::on_motion_notify_event (GdkEventMotion* event){
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

void MainWindowDraw::setImage(cv::Mat image){
    opencv_image = image;
    queue_draw();
}

void MainWindowDraw::setCutMode(bool b){
    cut_mode = b;
}

void MainWindowDraw::setRectangleInvisible(){
    cut_point.first  = {0,0};
    cut_point.second = {0,0};
}

cv::Point MainWindowDraw::getCairoImageSize(){
    return cairo_image_size;
}

PointCut MainWindowDraw::getCutPoint(){
    return cut_point;
}