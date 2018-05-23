/*
* This file is part of the VSS-Vision project.
*
* This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
* v. 3.0. If a copy of the GPL was not distributed with this
* file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
*/

#include <Windows/Vision/VisionWindow.h>

void VisionWindow::setNewFrame(){
  processFrame();
  screenImage->set_image(frame);
  colorRecognizer = new ColorRecognizer();

}

void VisionWindow::receiveNewFrame(cv::Mat _frame){
  frame = _frame;
  signal_set_new_frame.emit();
}

void VisionWindow::processFrame() {
  //cv::warpAffine(frame, frame, cv::getRotationMatrix2D(cv::Point2f(frame.cols/2, frame.rows/2), calibration.rotation, 1.0), frame.size());

  if (calibration.colorsRange.size() > 0) {
    colorRecognizer->setColorRange(calibration.colorsRange.at(0));
    colorRecognizer->processImage(frame);

    auto rectangles = colorRecognizer->getRectangles();
    for(unsigned int i = 0 ; i < rectangles.size() ; i++){
      cv::rectangle(frame, rectangles.at(i), cv::Scalar(255, 255, 255), 1, 1, 0);
    }
  }
}
