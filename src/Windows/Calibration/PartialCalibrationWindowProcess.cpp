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
    TimeHelper t;
    processFrame(_frame.clone());
    cout << t.getElapsedTime() << endl;
    dispatcher_update_gtkmm_frame.emit();
}

void CalibrationWindow::updateGtkImage(){
    mtx.lock();
        cv::Mat _frame = frame.clone();
    mtx.unlock();

    screenImage->set_image(_frame, showBinaryImage);
    updateFpsLabel( timeHelper.framesPerSecond() );
}

void CalibrationWindow::processFrame(cv::Mat _frame) {
    mtx.lock();
        Calibration _calibration = calibration;
    mtx.unlock();

    changeRotation(_frame, _calibration.rotation);

    if(_calibration.shouldCropImage) {
        cropImage(_frame, _calibration.cut[0], _calibration.cut[1]);
    }

    colorRecognizer->processImage(_frame);

    if(showBinaryImage){
        return colorRecognizer->getBinaryFrame();
    }

    drawRectangle(_frame, colorRecognizer->getRectangles());

    mtx.lock();
        frame = _frame.clone();
    mtx.unlock();
}
