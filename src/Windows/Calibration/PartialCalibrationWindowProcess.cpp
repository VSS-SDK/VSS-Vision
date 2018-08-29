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
    dispatcher_update_gtkmm_frame.emit();
}

void CalibrationWindow::updateGtkImage(){
    mtxUpdateFrame.lock();
        cv::Mat image = frame.clone();
    mtxUpdateFrame.unlock();

    screenImage->set_image(image, showBinaryImage);
    updateFpsLabel( timeHelper.framesPerSecond() );
}

void CalibrationWindow::processFrame(cv::Mat image) {
//    mtx.lock();
        Calibration _calibration = calibration;
//    mtx.unlock();

    image = changeRotation(image, _calibration.rotation);

    if(_calibration.shouldCropImage) {
        image = cropImage(image, _calibration.cut[0], _calibration.cut[1]);
    }

    teamRecognizer->processImage(image);

    cutPosition[ teamRecognizer->getColor() ] = teamRecognizer->getRectangles();

    if(showBinaryImage){
       mtxUpdateFrame.lock();
           frame = teamRecognizer->getBinaryImage().clone();
       mtxUpdateFrame.unlock();

   } else {
       image = drawRectangle(image, teamRecognizer->getRectangles());
       mtxUpdateFrame.lock();
           frame = image.clone();
       mtxUpdateFrame.unlock();
   }
}
