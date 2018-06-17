/*
* This file is part of the VSS-Vision project.
*
* This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
* v. 3.0. If a copy of the GPL was not distributed with this
* file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
*/

#include <Repositories/CalibrationRepository.h>
#include <CameraReader.h>
#include <Windows/Calibration/CalibrationWindow.h>

void CalibrationWindow::receiveNewFrame(cv::Mat _frame){
    frame = _frame;
    processFrame();

    dispatcher_update_gtkmm_frame.emit();
}

void CalibrationWindow::updateGtkImage(){
    screenImage->set_image(frame);
    updateFpsLabel( timeHelper.fps() );
}

void CalibrationWindow::processFrame() {
    changeRotation(frame, calibration.rotation);

    if(calibration.shouldCropImage) {
        cropImage(frame, calibration.cut[0], calibration.cut[1]);
    }

    if (timerOptimization.timeOut(1000)) {
        colorRecognizer->processImage(frame);

    } else {
        colorRecognizer->processImageInsideSectors(frame, cutPosition[ colorRecognizer->getColor() ] , 20);
    }

    std::cout << "Numbers of square: " << colorRecognizer->getRectangles().size() << std::endl;

    cutPosition[ colorRecognizer->getColor() ] = colorRecognizer->getRectangles();

    applyRectangleToFrame();
}

void CalibrationWindow::applyRectangleToFrame(){
    auto rectangles = colorRecognizer->getRectangles();
    for(unsigned int i = 0 ; i < rectangles.size() ; i++){
        cv::rectangle(frame, rectangles.at(i), cv::Scalar(255, 255, 255), 1, 1, 0);
    }
}
