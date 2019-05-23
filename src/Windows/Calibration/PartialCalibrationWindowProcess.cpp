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

void CalibrationWindow::receiveNewFrame(cv::Mat image){
    processFrame(image.clone());
    
    mutexFPS.lock();
        timeHelper.calculateFramesPerSecond();
    mutexFPS.unlock();
}

bool CalibrationWindow::emitUpdateGtkImage(){
    dispatcher_update_gtkmm_frame.emit();
    return true;
}

void CalibrationWindow::updateGtkImage(){
    mutexFrame.lock();
        cv::Mat image = frame.clone();
    mutexFrame.unlock();

    screenImage->setImage(image);

    mutexFPS.lock();
        updateLabel(timeHelper.getFramesPerSecond());
    mutexFPS.unlock();
}

void CalibrationWindow::processFrame(cv::Mat image) {
    mutexCalibration.lock();
        Calibration _calibration = calibration;
    mutexCalibration.unlock();

    if (not perspectiveMatrix.empty())
        image = changePerspective(image, perspectiveMatrix);

    colorRecognizer->processImage(image, 3);

    if(showBinaryImage){
       mutexFrame.lock();
           frame = colorRecognizer->getBinaryImage().clone();
       mutexFrame.unlock();

   } else {
       image = drawRectangle(image, colorRecognizer->getRectangles());

       mutexFrame.lock();
           frame = image.clone();
       mutexFrame.unlock();
   }
}
