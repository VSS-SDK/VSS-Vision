#include "myarea.h"
#include <gtkmm.h>
#include <cairomm/context.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>


MyArea::MyArea()
{
}

MyArea::~MyArea()
{
}

bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr){

    cv::Mat opencv_image = cv::imread("../mock/images/model.jpg");
    std::cout << opencv_image.size() << std::endl;

    Glib::RefPtr<Gdk::Pixbuf> pixbuf =  Gdk::Pixbuf::create_from_data( opencv_image.data, Gdk::COLORSPACE_RGB, false, 8, opencv_image.cols, opencv_image.rows, opencv_image.step);
    Gdk::Cairo::set_source_pixbuf(cr, pixbuf); 

    cr->paint();
        
    return true;
}