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
    processFrame(_frame.clone());
    dispatcher_update_gtkmm_frame.emit();
}

void CalibrationWindow::updateGtkImage(){
    mtxUpdateFrame.lock();
        cv::Mat _frame = frame.clone();
    mtxUpdateFrame.unlock();

    screenImage->set_image(_frame, showBinaryImage);
    updateFpsLabel( timeHelper.framesPerSecond() );
}

void CalibrationWindow::processFrame(cv::Mat _frame) {
//    mtx.lock();
        Calibration _calibration = calibration;
//    mtx.unlock();

    changeRotation(_frame, _calibration.rotation);

    if(_calibration.shouldCropImage) {
        cropImage(_frame, _calibration.cut[0], _calibration.cut[1]);
    }

    colorRecognizer->processImage(_frame, 3);

    cutPosition[ colorRecognizer->getColor() ] = colorRecognizer->getRectangles();

    if(showBinaryImage){
       mtxUpdateFrame.lock();
           frame =  colorRecognizer->getBinaryFrame().clone();
       mtxUpdateFrame.unlock();

   } else {
       drawRectangle(_frame, colorRecognizer->getRectangles());
       mtxUpdateFrame.lock();
           frame = _frame.clone();
       mtxUpdateFrame.unlock();
   }
}
