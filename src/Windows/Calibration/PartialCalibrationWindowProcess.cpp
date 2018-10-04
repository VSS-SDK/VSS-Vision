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
    
    mtxFps.lock();
        timeHelper.calculateFramesPerSecond();
    mtxFps.unlock();
}

bool CalibrationWindow::emitUpdateGtkImage(){
    dispatcher_update_gtkmm_frame.emit();
    return true;
}

void CalibrationWindow::updateGtkImage(){
    mtxUpdateFrame.lock();
        cv::Mat image = frame.clone();
    mtxUpdateFrame.unlock();

    screenImage->set_image(image);

    mtxFps.lock();
        updateLabel(timeHelper.getFramesPerSecond());
    mtxFps.unlock();
}

void CalibrationWindow::processFrame(cv::Mat image) {
    mtxCalibration.lock();
        Calibration _calibration = calibration;
    mtxCalibration.unlock();

    //image = changeRotation(image, _calibration.rotation);

    if(_calibration.shouldCropImage) {
        image = cropImage(image, _calibration.cut[0], _calibration.cut[1]);
    }

    colorRecognizer->processImage(image);

    if(showBinaryImage){
       mtxUpdateFrame.lock();
           frame = colorRecognizer->getBinaryImage().clone();
       mtxUpdateFrame.unlock();

   } else {
       image = drawRectangle(image, colorRecognizer->getRectangles());
       
       mtxUpdateFrame.lock();
           frame = image.clone();
       mtxUpdateFrame.unlock();
   }
}
