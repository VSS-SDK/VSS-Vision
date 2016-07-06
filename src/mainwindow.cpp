/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

const int ROWS = 2;
const int COLUMNS = 3;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    calib_vs_vision = false;

    sql = new SQLite("../data/main.db", "passwd");

    for(int i = 0 ; i < 8 ; i++){
        colors.push_back(0);
    }

    image = new QCustomLabel();
    image->setMouseTracking(true);
    QObject::connect(image, SIGNAL(Mouse_Pos()), this, SLOT(mouseCurrentPos()));
    QObject::connect(image, SIGNAL(Mouse_Left_Pressed()), this, SLOT(mouseLeftPressed()));
    QObject::connect(image, SIGNAL(Mouse_Right_Pressed()), this, SLOT(mouseRightPressed()));

    ui->layoutH2->addWidget(image);

    QObject::connect(&calib, SIGNAL(finished()), this, SLOT(quit()));
    calib.alloc_label_input(image);
    calib.alloc_calibration(&_calib);

    QObject::connect(&vi, SIGNAL(finished()), this, SLOT(quit()));
    vi.alloc_label_input(image);
    vi.alloc_calibration(&_calib);
    vi.alloc_state(&state);
    vi.alloc_colors(&colors);
    vi.alloc_execution_config(&execConfig);

    calib.start();
    vi.start();

    image->show();


    coordinate_mouse = new QLabel("M(0, 0)");

    mainItem = new QTreeWidgetItem;

    cmbCameraIds = new QComboBox();
    cmbSavedImages = new QComboBox();
    cmbSavedVideos = new QComboBox();

    checkUseCamera = new QCheckBox();
    checkUseImage = new QCheckBox();
    checkUseVideo = new QCheckBox();

    cmbColors = new QComboBox();
    cmbBallColors = new QComboBox();
    cmbMainColors_1 = new QComboBox();
    cmbMainColors_2 = new QComboBox();
    cmbSecColors_1 = new QComboBox();
    cmbSecColors_2 = new QComboBox();
    cmbSecColors_3 = new QComboBox();
    cmbSecColors_4 = new QComboBox();
    cmbSecColors_5 = new QComboBox();
    cmbSecColors_6 = new QComboBox();

    btnDoColorCalib = new QPushButton("Do", this);
    btnRunVision = new QPushButton("Run", this);

    blockdevice = QIcon(":icons/blockdevice.png");
    ksame = QIcon(":icons/ksame.png");
    kdf = QIcon(":icons/kdf.png");
    package = QIcon(":icons/package.png");

    getAllDevices();
    buildTrees();

    if(devices.size() < 1){
        checkUseCamera->setChecked(false);
        checkUseImage->setChecked(true);
        checkUseVideo->setChecked(false);
        cmbCameraIds->setDisabled(true);

    }else{
        checkUseCamera->setChecked(true);
        checkUseImage->setChecked(false);
        checkUseVideo->setChecked(false);
    }

    for(int i = 0 ; i < 3 ; i++){
        lblHeadersHSV.push_back(new QLabel("(0 - N)"));
        lblHeadersHSV.at(i)->setStyleSheet("QLabel {qproperty-alignment: AlignCenter; font-weight: bold;}");
    }

    lbl_val = new QLabel("Pos\nVel\nKPos\nKVel");

    val_ball = new QLabel("Ball");
    val_robot1 = new QLabel("Robot 1");
    val_robot2 = new QLabel("Robot 2");
    val_robot3 = new QLabel("Robot 3");
    val_robot4 = new QLabel("Robot 4");
    val_robot5 = new QLabel("Robot 5");
    val_robot6 = new QLabel("Robot 6");

    h_val_ball = new QLabel("000, 000, 0.00\n000, 000, 0.00\n000, 000, 0.00\n000, 000, 0.00\n");
    h_val_robot1 = new QLabel("000, 000, 0.00\n000, 000, 0.00\n000, 000, 0.00\n000, 000, 0.00\n");
    h_val_robot2 = new QLabel("000, 000, 0.00\n000, 000, 0.00\n000, 000, 0.00\n000, 000, 0.00\n");
    h_val_robot3 = new QLabel("000, 000, 0.00\n000, 000, 0.00\n000, 000, 0.00\n000, 000, 0.00\n");
    h_val_robot4 = new QLabel("000, 000, 0.00\n000, 000, 0.00\n000, 000, 0.00\n000, 000, 0.00\n");
    h_val_robot5 = new QLabel("000, 000, 0.00\n000, 000, 0.00\n000, 000, 0.00\n000, 000, 0.00\n");
    h_val_robot6 = new QLabel("000, 000, 0.00\n000, 000, 0.00\n000, 000, 0.00\n000, 000, 0.00\n");

    lbl_val->setStyleSheet("QLabel {qproperty-alignment: AlignCenter; font-size: 14px; background: white; border: 1px solid #bbb;");

    h_val_ball->setStyleSheet("QLabel {qproperty-alignment: AlignCenter; font-size: 14px; background: white; border: 1px solid #bbb;}");
    h_val_robot1->setStyleSheet("QLabel {qproperty-alignment: AlignCenter; font-size: 14px; background: white; border: 1px solid #bbb;}");
    h_val_robot2->setStyleSheet("QLabel {qproperty-alignment: AlignCenter; font-size: 14px; background: white; border: 1px solid #bbb;}");
    h_val_robot3->setStyleSheet("QLabel {qproperty-alignment: AlignCenter; font-size: 14px; background: white; border: 1px solid #bbb;}");
    h_val_robot4->setStyleSheet("QLabel {qproperty-alignment: AlignCenter; font-size: 14px; background: white; border: 1px solid #bbb;}");
    h_val_robot5->setStyleSheet("QLabel {qproperty-alignment: AlignCenter; font-size: 14px; background: white; border: 1px solid #bbb;}");
    h_val_robot6->setStyleSheet("QLabel {qproperty-alignment: AlignCenter; font-size: 14px; background: white; border: 1px solid #bbb;}");

    for(int i = 0 ; i < 6 ; i++){
        sliderHSV.push_back(new QSlider(Qt::Orientation(VerticalTabs)));
        sliderHSV.at(i)->setMinimumHeight(130);
    }

    sliderHSV.at(hmin)->setMaximum(179);
    sliderHSV.at(smin)->setMaximum(254);
    sliderHSV.at(vmin)->setMaximum(254);
    sliderHSV.at(hmax)->setMaximum(180);
    sliderHSV.at(smax)->setMaximum(255);
    sliderHSV.at(vmax)->setMaximum(255);

    sliderHSV.at(hmin)->setMinimum(0);
    sliderHSV.at(smin)->setMinimum(0);
    sliderHSV.at(vmin)->setMinimum(0);
    sliderHSV.at(hmax)->setMinimum(1);
    sliderHSV.at(smax)->setMinimum(1);
    sliderHSV.at(vmax)->setMinimum(1);

    sliderHSV.at(hmin)->setValue(_calib.colors.at(0).min.rgb[h]);
    sliderHSV.at(smin)->setValue(_calib.colors.at(0).min.rgb[s]);
    sliderHSV.at(vmin)->setValue(_calib.colors.at(0).min.rgb[v]);
    sliderHSV.at(hmax)->setValue(_calib.colors.at(0).max.rgb[h]);
    sliderHSV.at(smax)->setValue(_calib.colors.at(0).max.rgb[s]);
    sliderHSV.at(hmax)->setValue(_calib.colors.at(0).max.rgb[v]);

    connect(sliderHSV.at(hmin), SIGNAL(valueChanged(int)), this, SLOT(updateHmin(int)));
    connect(sliderHSV.at(smin), SIGNAL(valueChanged(int)), this, SLOT(updateSmin(int)));
    connect(sliderHSV.at(vmin), SIGNAL(valueChanged(int)), this, SLOT(updateVmin(int)));
    connect(sliderHSV.at(hmax), SIGNAL(valueChanged(int)), this, SLOT(updateHmax(int)));
    connect(sliderHSV.at(smax), SIGNAL(valueChanged(int)), this, SLOT(updateSmax(int)));
    connect(sliderHSV.at(vmax), SIGNAL(valueChanged(int)), this, SLOT(updateVmax(int)));

    updateValuesHSV();
    update_hsv_s();

    sliderHSV.at(hmax)->setStyleSheet("QSlider{ background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0.0 #00f, stop: 0.167 #f0f, stop: 0.334 #f00, stop: 0.501 #ff0, stop: 0.668 #0f0, stop: 0.835 #0ff, stop: 1.0 #00f)}");
    sliderHSV.at(hmin)->setStyleSheet("QSlider{ background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0.0 #00f, stop: 0.167 #f0f, stop: 0.334 #f00, stop: 0.501 #ff0, stop: 0.668 #0f0, stop: 0.835 #0ff, stop: 1.0 #00f)}");
    sliderHSV.at(vmax)->setStyleSheet("QSlider{ background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #fff, stop: 1 #000)}");
    sliderHSV.at(vmin)->setStyleSheet("QSlider{ background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #fff, stop: 1 #000)}");

    ui->layoutH3->setContentsMargins(2, 0, 2, 0);
    ui->layoutH4->setContentsMargins(2, 0, 2, 0);
    ui->layoutH5->setContentsMargins(2, 0, 2, 0);
    ui->layoutH6->setContentsMargins(2, 0, 2, 0);
    ui->layoutH7->setContentsMargins(2, 0, 2, 0);
    ui->layoutH8->setContentsMargins(2, 0, 2, 0);
    ui->layoutH9->setContentsMargins(2, 0, 2, 0);
    ui->layoutH10->setContentsMargins(2, 0, 2, 0);
}

void MainWindow::getAllDevices(){
    devices.clear();

    string response = cmdTerminal("find /dev/ -name video*");
    string sp = "";

    for(int i = 0 ; i < response.size() ; i++){
        if(response[i] == '\n'){
            devices.push_back(sp);
            sp = "";
        }else{
            sp += response.at(i);
        }
    }
}

void MainWindow::addMainItem(){
    mainItem->setIcon(0, package);
    mainItem->setText(0, "Vision System");

    ui->treeMain->addTopLevelItem(mainItem);
}

void MainWindow::addInputDataItem(){
    int qtd = 7;
    for(int i = 0 ; i < qtd ; i++){
        inputData.append(new QTreeWidgetItem);
    }

    inputData.at(0)->setIcon(0, blockdevice);
    inputData.at(0)->setText(0, "Input Data");

    inputData.at(1)->setIcon(0, ksame);
    inputData.at(1)->setText(0, "USB Camera");

    inputData.at(2)->setIcon(0, ksame);
    inputData.at(2)->setText(0, "Saved Images");

    inputData.at(3)->setIcon(0, ksame);
    inputData.at(3)->setText(0, "Saved Videos");

    inputData.at(4)->setIcon(0, ksame);
    inputData.at(4)->setText(0, "Use Camera");

    inputData.at(5)->setIcon(0, ksame);
    inputData.at(5)->setText(0, "Use Image");

    inputData.at(6)->setIcon(0, ksame);
    inputData.at(6)->setText(0, "Use Video");

    mainItem->addChild(inputData.at(0));
    for(int i = 1 ; i < qtd ; i++){
        inputData.at(0)->addChild(inputData.at(i));
    }

    ui->treeMain->insertTopLevelItems(0, inputData);

    cmbCameraIds->setMaximumHeight(20);
    for(int i = 0 ; i < devices.size() ; i++){
        cmbCameraIds->addItem(QString(devices.at(i).c_str()));
    }

    // TODO: add isso como opção verdadeira
    cmbSavedImages->setMaximumHeight(20);
    cmbSavedImages->addItem("/model1.jpg");

    // TODO: add isso como opção verdadeira
    cmbSavedVideos->setMaximumHeight(20);
    cmbSavedVideos->addItem("/ball_move.mp4");


    checkUseCamera->setMaximumHeight(20);
    connect(checkUseCamera, SIGNAL(stateChanged(int)), this, SLOT(checkboxCamera(int)));

    checkUseImage->setMaximumHeight(20);
    connect(checkUseImage, SIGNAL(stateChanged(int)), this, SLOT(checkboxImage(int)));

    checkUseVideo->setMaximumHeight(20);
    connect(checkUseVideo, SIGNAL(stateChanged(int)), this, SLOT(checkboxVideo(int)));

    ui->treeMain->setItemWidget(inputData.value(1), 1, cmbCameraIds);
    ui->treeMain->setItemWidget(inputData.value(2), 1, cmbSavedImages);
    ui->treeMain->setItemWidget(inputData.value(3), 1, cmbSavedVideos);
    ui->treeMain->setItemWidget(inputData.value(4), 1, checkUseCamera);
    ui->treeMain->setItemWidget(inputData.value(5), 1, checkUseImage);
    ui->treeMain->setItemWidget(inputData.value(6), 1, checkUseVideo);
}

void MainWindow::addCameraCalibrationItem(){
    int qtd = 3;
    for(int i = 0 ; i < qtd ; i++){
        cameraCalibration.append(new QTreeWidgetItem);
    }

    cameraCalibration.at(0)->setIcon(0, blockdevice);
    cameraCalibration.at(0)->setText(0, "Camera Calibration");

    cameraCalibration.at(1)->setIcon(0, ksame);
    cameraCalibration.at(1)->setText(0, "Rotation");

    cameraCalibration.at(2)->setIcon(0, ksame);
    cameraCalibration.at(2)->setText(0, "Bounds");

    mainItem->addChild(cameraCalibration.at(0));
    for(int i = 1 ; i < qtd ; i++){
        cameraCalibration.at(0)->addChild(cameraCalibration.at(i));
    }

    ui->treeMain->insertTopLevelItems(0, cameraCalibration);
}

void MainWindow::addBlobFindingItem(){
    int qtd = 5;
    for(int i = 0 ; i < qtd ; i++){
        blobFinding.append(new QTreeWidgetItem);
    }

    blobFinding.at(0)->setIcon(0, blockdevice);
    blobFinding.at(0)->setText(0, "Blob Finding");

    blobFinding.at(1)->setIcon(0, ksame);
    blobFinding.at(1)->setText(0, "Area Min");

    blobFinding.at(2)->setIcon(0, ksame);
    blobFinding.at(2)->setText(0, "Area Max");

    blobFinding.at(3)->setIcon(0, ksame);
    blobFinding.at(3)->setText(0, "Enable Min");

    blobFinding.at(4)->setIcon(0, ksame);
    blobFinding.at(4)->setText(0, "Enable Max");

    mainItem->addChild(blobFinding.at(0));
    for(int i = 1 ; i < qtd ; i++){
        blobFinding.at(0)->addChild(blobFinding.at(i));
    }

    ui->treeMain->insertTopLevelItems(0, blobFinding);
}

void MainWindow::addVisualizationItem(){
    int qtd = 4;
    for(int i = 0 ; i < qtd ; i++){
        visualization.append(new QTreeWidgetItem);
    }

    visualization.at(0)->setIcon(0, blockdevice);
    visualization.at(0)->setText(0, "Visualization");

    visualization.at(1)->setIcon(0, ksame);
    visualization.at(1)->setText(0, "Enable");

    visualization.at(2)->setIcon(0, ksame);
    visualization.at(2)->setText(0, "Grayscale");

    visualization.at(3)->setIcon(0, ksame);
    visualization.at(3)->setText(0, "Bounds");

    mainItem->addChild(visualization.at(0));
    for(int i = 1 ; i < qtd ; i++){
        visualization.at(0)->addChild(visualization.at(i));
    }

    ui->treeMain->insertTopLevelItems(0, visualization);
}

void MainWindow::addDefinePatternsItem(){
    int qtd = 5;
    for(int i = 0 ; i < qtd ; i++){
        definePatterns.append(new QTreeWidgetItem);
    }

    definePatterns.at(0)->setIcon(0, blockdevice);
    definePatterns.at(0)->setText(0, "Define Patterns");

    definePatterns.at(1)->setIcon(0, kdf);
    definePatterns.at(1)->setText(0, "Team 1");

    definePatterns.at(2)->setIcon(0, ksame);
    definePatterns.at(2)->setText(0, "Patterns List");

    definePatterns.at(3)->setIcon(0, kdf);
    definePatterns.at(3)->setText(0, "Team 2");

    definePatterns.at(4)->setIcon(0, ksame);
    definePatterns.at(4)->setText(0, "Patterns List");

    mainItem->addChild(definePatterns.at(0));
        definePatterns.at(0)->addChild(definePatterns.at(1));
            definePatterns.at(1)->addChild(definePatterns.at(2));
        definePatterns.at(0)->addChild(definePatterns.at(3));
            definePatterns.at(3)->addChild(definePatterns.at(4));


    ui->treeMain->insertTopLevelItems(0, definePatterns);
}

void MainWindow::addExecutionConfig(){
    int qtd = 12;
    for(int i = 0 ; i < qtd ; i++){
        defineExecutionConfig.append(new QTreeWidgetItem);
    }

    defineExecutionConfig.at(0)->setIcon(0, blockdevice);
    defineExecutionConfig.at(0)->setText(0, "Execution Config");

    defineExecutionConfig.at(1)->setIcon(0, kdf);
    defineExecutionConfig.at(1)->setText(0, "Team 1");

    defineExecutionConfig.at(2)->setIcon(0, ksame);
    defineExecutionConfig.at(2)->setText(0, "Main Color");

    defineExecutionConfig.at(3)->setIcon(0, ksame);
    defineExecutionConfig.at(3)->setText(0, "Color_r 1");

    defineExecutionConfig.at(4)->setIcon(0, ksame);
    defineExecutionConfig.at(4)->setText(0, "Color_r 2");

    defineExecutionConfig.at(5)->setIcon(0, ksame);
    defineExecutionConfig.at(5)->setText(0, "Color_r 3");

    defineExecutionConfig.at(6)->setIcon(0, kdf);
    defineExecutionConfig.at(6)->setText(0, "Team 2");

    defineExecutionConfig.at(7)->setIcon(0, ksame);
    defineExecutionConfig.at(7)->setText(0, "Main Color");

    defineExecutionConfig.at(8)->setIcon(0, ksame);
    defineExecutionConfig.at(8)->setText(0, "Color_r 1");

    defineExecutionConfig.at(9)->setIcon(0, ksame);
    defineExecutionConfig.at(9)->setText(0, "Color_r 2");

    defineExecutionConfig.at(10)->setIcon(0, ksame);
    defineExecutionConfig.at(10)->setText(0, "Color_r 3");

    defineExecutionConfig.at(11)->setIcon(0, ksame);
    defineExecutionConfig.at(11)->setText(0, "Ball Color");



    mainItem->addChild(defineExecutionConfig.at(0));
        defineExecutionConfig.at(0)->addChild(defineExecutionConfig.at(1));
            defineExecutionConfig.at(1)->addChild(defineExecutionConfig.at(2));
            defineExecutionConfig.at(1)->addChild(defineExecutionConfig.at(3));
            defineExecutionConfig.at(1)->addChild(defineExecutionConfig.at(4));
            defineExecutionConfig.at(1)->addChild(defineExecutionConfig.at(5));
        defineExecutionConfig.at(0)->addChild(defineExecutionConfig.at(6));
            defineExecutionConfig.at(6)->addChild(defineExecutionConfig.at(7));
            defineExecutionConfig.at(6)->addChild(defineExecutionConfig.at(8));
            defineExecutionConfig.at(6)->addChild(defineExecutionConfig.at(9));
            defineExecutionConfig.at(6)->addChild(defineExecutionConfig.at(10));
        defineExecutionConfig.at(0)->addChild(defineExecutionConfig.at(11));

        //*cmbMainColors_1, *cmbMainColors_2, *cmdSecColors_1, *cmdSecColors_2
        // fazer disso um vector
        cmbBallColors->setMaximumHeight(20);
        cmbBallColors->addItem("Orange");

        cmbMainColors_1->setMaximumHeight(20);
        cmbMainColors_1->addItem("Blue");
        cmbMainColors_1->addItem("Yellow");

        cmbMainColors_2->setMaximumHeight(20);
        cmbMainColors_2->addItem("Blue");
        cmbMainColors_2->addItem("Yellow");

        cmbSecColors_1->setMaximumHeight(20);
        cmbSecColors_1->addItem("Red");
        cmbSecColors_1->addItem("Pink");
        cmbSecColors_1->addItem("Purple");
        cmbSecColors_1->addItem("Green");
        cmbSecColors_1->addItem("Brown");
        cmbSecColors_1->addItem("None");

        cmbSecColors_2->setMaximumHeight(20);
        cmbSecColors_2->addItem("Red");
        cmbSecColors_2->addItem("Pink");
        cmbSecColors_2->addItem("Purple");
        cmbSecColors_2->addItem("Green");
        cmbSecColors_2->addItem("Brown");
        cmbSecColors_2->addItem("None");

        cmbSecColors_3->setMaximumHeight(20);
        cmbSecColors_3->addItem("Red");
        cmbSecColors_3->addItem("Pink");
        cmbSecColors_3->addItem("Purple");
        cmbSecColors_3->addItem("Green");
        cmbSecColors_3->addItem("Brown");
        cmbSecColors_3->addItem("None");

        cmbSecColors_4->setMaximumHeight(20);
        cmbSecColors_4->addItem("Red");
        cmbSecColors_4->addItem("Pink");
        cmbSecColors_4->addItem("Purple");
        cmbSecColors_4->addItem("Green");
        cmbSecColors_4->addItem("Brown");
        cmbSecColors_4->addItem("None");

        cmbSecColors_5->setMaximumHeight(20);
        cmbSecColors_5->addItem("Red");
        cmbSecColors_5->addItem("Pink");
        cmbSecColors_5->addItem("Purple");
        cmbSecColors_5->addItem("Green");
        cmbSecColors_5->addItem("Brown");
        cmbSecColors_5->addItem("None");

        cmbSecColors_6->setMaximumHeight(20);
        cmbSecColors_6->addItem("Red");
        cmbSecColors_6->addItem("Pink");
        cmbSecColors_6->addItem("Purple");
        cmbSecColors_6->addItem("Green");
        cmbSecColors_6->addItem("Brown");
        cmbSecColors_6->addItem("None");

        ui->treeMain->setItemWidget(defineExecutionConfig.value(2), 1, cmbMainColors_1);
        ui->treeMain->setItemWidget(defineExecutionConfig.value(3), 1, cmbSecColors_1);
        ui->treeMain->setItemWidget(defineExecutionConfig.value(4), 1, cmbSecColors_2);
        ui->treeMain->setItemWidget(defineExecutionConfig.value(5), 1, cmbSecColors_3);
        ui->treeMain->setItemWidget(defineExecutionConfig.value(7), 1, cmbMainColors_2);
        ui->treeMain->setItemWidget(defineExecutionConfig.value(8), 1, cmbSecColors_4);
        ui->treeMain->setItemWidget(defineExecutionConfig.value(9), 1, cmbSecColors_5);
        ui->treeMain->setItemWidget(defineExecutionConfig.value(10), 1, cmbSecColors_6);
        ui->treeMain->setItemWidget(defineExecutionConfig.value(11), 1, cmbBallColors);

    ui->treeMain->insertTopLevelItems(0, defineExecutionConfig);

    cmbMainColors_2->setCurrentIndex(1);

    cmbSecColors_1->setCurrentIndex(0);
    cmbSecColors_2->setCurrentIndex(1);
    cmbSecColors_3->setCurrentIndex(3);

    cmbSecColors_4->setCurrentIndex(5);
    cmbSecColors_5->setCurrentIndex(5);
    cmbSecColors_6->setCurrentIndex(5);
}

void MainWindow::addCalibrateColors(){
    int qtd = 3;
    for(int i = 0 ; i < qtd ; i++){
        calibrateColors.append(new QTreeWidgetItem);
    }

    calibrateColors.at(0)->setIcon(0, blockdevice);
    calibrateColors.at(0)->setText(0, "Calibrate Colors");

    calibrateColors.at(1)->setIcon(0, ksame);
    calibrateColors.at(1)->setText(0, "Colors List");

    calibrateColors.at(2)->setIcon(0, ksame);
    calibrateColors.at(2)->setText(0, "Calibrate");

    mainItem->addChild(calibrateColors.at(0));
        calibrateColors.at(0)->addChild(calibrateColors.at(1));
        calibrateColors.at(0)->addChild(calibrateColors.at(2));

    cmbColors->setMaximumHeight(20);
    cmbColors->addItem("Orange");
    cmbColors->addItem("Blue");
    cmbColors->addItem("Yellow");
    cmbColors->addItem("Red");
    cmbColors->addItem("Pink");
    cmbColors->addItem("Purple");
    cmbColors->addItem("Green");
    cmbColors->addItem("Brown");


    btnDoColorCalib->setMaximumHeight(20);
    connect(btnDoColorCalib, SIGNAL (clicked()), this, SLOT (evtCalibration()));

    ui->treeMain->setItemWidget(calibrateColors.value(1), 1, cmbColors);
    ui->treeMain->setItemWidget(calibrateColors.value(2), 1, btnDoColorCalib);
}

void MainWindow::addVisionOptions(){
    int qtd = 3;
    for(int i = 0 ; i < qtd ; i++){
        visionOptions.append(new QTreeWidgetItem);
    }

    visionOptions.at(0)->setIcon(0, blockdevice);
    visionOptions.at(0)->setText(0, "Vision Options");

    visionOptions.at(1)->setIcon(0, ksame);
    visionOptions.at(1)->setText(0, "Optimization");

    visionOptions.at(2)->setIcon(0, ksame);
    visionOptions.at(2)->setText(0, "Kalman Filter");

    mainItem->addChild(visionOptions.at(0));
    for(int i = 1 ; i < qtd ; i++){
        visionOptions.at(0)->addChild(visionOptions.at(i));
    }

    ui->treeMain->insertTopLevelItems(0, visionOptions);
}

void MainWindow::addNetOptions(){
    int qtd = 3;
    for(int i = 0 ; i < qtd ; i++){
        netOptions.append(new QTreeWidgetItem);
    }

    netOptions.at(0)->setIcon(0, blockdevice);
    netOptions.at(0)->setText(0, "Net Options");

    netOptions.at(1)->setIcon(0, ksame);
    netOptions.at(1)->setText(0, "Ip");

    netOptions.at(2)->setIcon(0, ksame);
    netOptions.at(2)->setText(0, "Port");

    mainItem->addChild(netOptions.at(0));
    for(int i = 1 ; i < qtd ; i++){
        netOptions.at(0)->addChild(netOptions.at(i));
    }

    ui->treeMain->insertTopLevelItems(0, netOptions);
}

void MainWindow::addExecutionOptions(){
    int qtd = 2;
    for(int i = 0 ; i < qtd ; i++){
        executionOptions.append(new QTreeWidgetItem);
    }

    executionOptions.at(0)->setIcon(0, blockdevice);
    executionOptions.at(0)->setText(0, "Execution");

    executionOptions.at(1)->setIcon(0, ksame);
    executionOptions.at(1)->setText(0, "Run");

    /*executionOptions.at(2)->setIcon(0, ksame);
    executionOptions.at(2)->setText(0, "Img off");

    executionOptions.at(3)->setIcon(0, ksame);
    executionOptions.at(3)->setText(0, "Report");*/

    btnRunVision->setMaximumHeight(20);
    connect(btnRunVision, SIGNAL (clicked()), this, SLOT (evtVision()));


    mainItem->addChild(executionOptions.at(0));
    for(int i = 1 ; i < qtd ; i++){
        executionOptions.at(0)->addChild(executionOptions.at(i));
    }

    ui->treeMain->setItemWidget(executionOptions.value(1), 1, btnRunVision);
    ui->treeMain->insertTopLevelItems(0, executionOptions);
}

void MainWindow::checkboxCamera(int a){
    if(checkUseCamera->isChecked()){
        checkUseImage->setChecked(false);
        checkUseVideo->setChecked(false);
    }
}

void MainWindow::checkboxImage(int a){
    if(checkUseImage->isChecked()){
        checkUseCamera->setChecked(false);
        checkUseVideo->setChecked(false);
    }
}

void MainWindow::checkboxVideo(int a){
    if(checkUseVideo->isChecked()){
        checkUseImage->setChecked(false);
        checkUseCamera->setChecked(false);
    }
}

void MainWindow::buildTrees(){
    QStringList headers;

    headers.append("Variable");
    headers.append("Value");

    addMainItem();
    addInputDataItem();
    //addCameraCalibrationItem();
    //addBlobFindingItem();
    //addVisualizationItem();
    //addDefinePatternsItem();
    addCalibrateColors();
    addExecutionConfig();
    //addVisionOptions();
    //addNetOptions();
    addExecutionOptions();

    ui->treeMain->setColumnCount(2);
    ui->treeMain->setHeaderLabels(headers);
    ui->treeMain->setColumnWidth(0, 220);
    ui->treeMain->expandItem(mainItem);
}

void MainWindow::mouseCurrentPos(){
    clearSS(ss);
    ss << "M(" << image->x << ", " << image->y << ")";
    coordinate_mouse->setText(QString(ss.str().c_str()));
}

void MainWindow::mouseLeftPressed(){
    calib.set_mouse_click_left(calib.get_mouse_click_left()+1);
}

void MainWindow::mouseRightPressed(){
    calib.set_mouse_click_right(calib.get_mouse_click_right()+1);
}

void MainWindow::mouseReleased(){

}

void MainWindow::mouseLeave(){

}

/*void MainWindow::mouseScroll(){
    clearSS(ss);
    ss << "Zoom " << image->delta << "%";
    zoom_image->setText(QString(ss.str().c_str()));
}*/

void MainWindow::keyPressed(){

}

void MainWindow::evtCalibration(){
    if(!calib.get_vision_reception()){
        if(checkUseCamera->isChecked()){
            calib.set_device(CAMERA);
            calib.set_id_camera(0);
        }else
        if(checkUseImage->isChecked()){
            calib.set_device(IMAGE);
        }else
        if(checkUseVideo->isChecked()){
            calib.set_device(VIDEO);

        }

        calib.set_id_color(cmbColors->currentIndex());
        calib.set_vision_reception(true);

        btnDoColorCalib->setText("Done");

        cmbColors->setDisabled(true);
        cmbCameraIds->setDisabled(true);
        cmbSavedImages->setDisabled(true);
        cmbSavedVideos->setDisabled(true);

        checkUseCamera->setDisabled(true);
        checkUseImage->setDisabled(true);
        checkUseVideo->setDisabled(true);

        updateValuesHSV();
        initCalibrationColors();
        ui->layoutH9H->addWidget(coordinate_mouse);
        coordinate_mouse->show();
        btnRunVision->setDisabled(true);
    }else{
        btnDoColorCalib->setText("Do");

        cmbColors->setDisabled(false);
        cmbCameraIds->setDisabled(false);
        cmbSavedImages->setDisabled(false);
        cmbSavedVideos->setDisabled(false);

        checkUseCamera->setDisabled(false);
        checkUseImage->setDisabled(false);
        checkUseVideo->setDisabled(false);

        btnRunVision->setDisabled(false);

        calib.set_vision_reception(false);

        finishCalibrationColors();
        ui->layoutH9H->removeWidget(coordinate_mouse);
        coordinate_mouse->hide();
    }
}

void MainWindow::evtVision(){
    if(!vi.get_vision_reception()){
        if(checkUseCamera->isChecked()){
            vi.set_device(CAMERA);
            vi.set_id_camera(0);
        }else
        if(checkUseImage->isChecked()){
            vi.set_device(IMAGE);
        }else
        if(checkUseVideo->isChecked()){
            vi.set_device(VIDEO);
        }

        btnRunVision->setText("Pause");
        cmbColors->setDisabled(true);
        checkUseCamera->setDisabled(true);
        checkUseImage->setDisabled(true);
        cmbCameraIds->setDisabled(true);
        cmbSavedImages->setDisabled(true);
        vi.set_vision_reception(true);

        defineColors();
        btnDoColorCalib->setDisabled(true);
        initPlotValues();
    }else{
        btnRunVision->setText("Run");

        cmbColors->setDisabled(false);
        checkUseCamera->setDisabled(false);
        checkUseImage->setDisabled(false);
        cmbCameraIds->setDisabled(false);
        cmbSavedImages->setDisabled(false);
        btnDoColorCalib->setDisabled(false);

        vi.set_vision_reception(false);
        finishPlotValues();
    }
}

void MainWindow::initCalibrationColors(){
    ui->layoutH3->addWidget(sliderHSV.at(hmin));
    ui->layoutH3->addWidget(sliderHSV.at(hmax));
    ui->layoutH4->addWidget(sliderHSV.at(smin));
    ui->layoutH4->addWidget(sliderHSV.at(smax));
    ui->layoutH5->addWidget(sliderHSV.at(vmin));
    ui->layoutH5->addWidget(sliderHSV.at(vmax));

    for(int i = 0 ; i < 6 ; i++)
        sliderHSV.at(i)->show();

    ui->layoutH3H->addWidget(lblHeadersHSV.at(h));
    ui->layoutH4H->addWidget(lblHeadersHSV.at(s));
    ui->layoutH5H->addWidget(lblHeadersHSV.at(v));

    for(int i = 0 ; i < 3 ; i++)
        lblHeadersHSV.at(i)->show();

    update_hsv_s();
}

void MainWindow::finishCalibrationColors(){
    ui->layoutH3->removeWidget(sliderHSV.at(hmin));
    ui->layoutH3->removeWidget(sliderHSV.at(hmax));
    ui->layoutH4->removeWidget(sliderHSV.at(smin));
    ui->layoutH4->removeWidget(sliderHSV.at(smax));
    ui->layoutH5->removeWidget(sliderHSV.at(vmin));
    ui->layoutH5->removeWidget(sliderHSV.at(vmax));

    for(int i = 0 ; i < 6 ; i++)
        sliderHSV.at(i)->hide();

    ui->layoutH3H->removeWidget(lblHeadersHSV.at(h));
    ui->layoutH4H->removeWidget(lblHeadersHSV.at(s));
    ui->layoutH5H->removeWidget(lblHeadersHSV.at(v));

    for(int i = 0 ; i < 3 ; i++)
        lblHeadersHSV.at(i)->hide();

     update_hsv_s();
}

void MainWindow::initPlotValues(){
    val_ball->setStyleSheet("QLabel {qproperty-alignment: AlignCenter; font-weight: bold; color: #d40;}");

    if(execConfig.team_color[0] == BLUE){
        val_robot1->setStyleSheet("QLabel {qproperty-alignment: AlignCenter; font-weight: bold; color: #00d;}");
        val_robot2->setStyleSheet("QLabel {qproperty-alignment: AlignCenter; font-weight: bold; color: #00d;}");
        val_robot3->setStyleSheet("QLabel {qproperty-alignment: AlignCenter; font-weight: bold; color: #00d;}");
        val_robot4->setStyleSheet("QLabel {qproperty-alignment: AlignCenter; font-weight: bold; color: #f90;}");
        val_robot5->setStyleSheet("QLabel {qproperty-alignment: AlignCenter; font-weight: bold; color: #f90;}");
        val_robot6->setStyleSheet("QLabel {qproperty-alignment: AlignCenter; font-weight: bold; color: #f90;}");
    }else{
        val_robot1->setStyleSheet("QLabel {qproperty-alignment: AlignCenter; font-weight: bold; color: #f90;}");
        val_robot2->setStyleSheet("QLabel {qproperty-alignment: AlignCenter; font-weight: bold; color: #f90;}");
        val_robot3->setStyleSheet("QLabel {qproperty-alignment: AlignCenter; font-weight: bold; color: #f90;}");
        val_robot4->setStyleSheet("QLabel {qproperty-alignment: AlignCenter; font-weight: bold; color: #00d;}");
        val_robot5->setStyleSheet("QLabel {qproperty-alignment: AlignCenter; font-weight: bold; color: #00d;}");
        val_robot6->setStyleSheet("QLabel {qproperty-alignment: AlignCenter; font-weight: bold; color: #00d;}");
    }

    ui->layoutH10->addWidget(lbl_val);
    lbl_val->show();

    ui->layoutH9H->addWidget(val_ball);
    ui->layoutH3H->addWidget(val_robot1);
    ui->layoutH4H->addWidget(val_robot2);
    ui->layoutH5H->addWidget(val_robot3);
    ui->layoutH6H->addWidget(val_robot4);
    ui->layoutH7H->addWidget(val_robot5);
    ui->layoutH8H->addWidget(val_robot6);

    val_ball->show();
    val_robot1->show();
    val_robot2->show();
    val_robot3->show();
    val_robot4->show();
    val_robot5->show();
    val_robot6->show();

    ui->layoutH3->addWidget(h_val_ball);
    ui->layoutH4->addWidget(h_val_robot1);
    ui->layoutH5->addWidget(h_val_robot2);
    ui->layoutH6->addWidget(h_val_robot3);
    ui->layoutH7->addWidget(h_val_robot4);
    ui->layoutH8->addWidget(h_val_robot5);
    ui->layoutH9->addWidget(h_val_robot6);

    h_val_ball->show();
    h_val_robot1->show();
    h_val_robot2->show();
    h_val_robot3->show();
    h_val_robot4->show();
    h_val_robot5->show();
    h_val_robot6->show();
}

void MainWindow::finishPlotValues(){
    ui->layoutH10->removeWidget(lbl_val);
    lbl_val->hide();

    ui->layoutH9H->removeWidget(val_ball);
    ui->layoutH3H->removeWidget(val_robot1);
    ui->layoutH4H->removeWidget(val_robot2);
    ui->layoutH5H->removeWidget(val_robot3);
    ui->layoutH6H->removeWidget(val_robot4);
    ui->layoutH7H->removeWidget(val_robot5);
    ui->layoutH8H->removeWidget(val_robot6);

    val_ball->hide();
    val_robot1->hide();
    val_robot2->hide();
    val_robot3->hide();
    val_robot4->hide();
    val_robot5->hide();
    val_robot6->hide();

    ui->layoutH3->removeWidget(h_val_ball);
    ui->layoutH4->removeWidget(h_val_robot1);
    ui->layoutH5->removeWidget(h_val_robot2);
    ui->layoutH6->removeWidget(h_val_robot3);
    ui->layoutH7->removeWidget(h_val_robot4);
    ui->layoutH8->removeWidget(h_val_robot5);
    ui->layoutH9->removeWidget(h_val_robot6);

    h_val_ball->hide();
    h_val_robot1->hide();
    h_val_robot2->hide();
    h_val_robot3->hide();
    h_val_robot4->hide();
    h_val_robot5->hide();
    h_val_robot6->hide();
}

void MainWindow::updateValuesHSV(){
    updateHmin((int)_calib.colors.at(cmbColors->currentIndex()).min.rgb[h]);
    updateSmin((int)_calib.colors.at(cmbColors->currentIndex()).min.rgb[s]);
    updateVmin((int)_calib.colors.at(cmbColors->currentIndex()).min.rgb[v]);
    updateHmax((int)_calib.colors.at(cmbColors->currentIndex()).max.rgb[h]);
    updateSmax((int)_calib.colors.at(cmbColors->currentIndex()).max.rgb[s]);
    updateVmax((int)_calib.colors.at(cmbColors->currentIndex()).max.rgb[v]);
}

void MainWindow::updateHmin(int value){
    _calib.colors.at(cmbColors->currentIndex()).min.rgb[h] = value;
    sliderHSV.at(hmin)->setValue(_calib.colors.at(cmbColors->currentIndex()).min.rgb[h]);

    /*if(value >= _calib.colors.at(cmbColors->currentIndex()).max.rgb[h]){
        sliderHmax->setValue(_calib.colors.at(cmbColors->currentIndex()).max.rgb[h] + 1);
    }*/

    clearSS(ss);
    ss << "H(" << sliderHSV.at(hmin)->value() << ", " << sliderHSV.at(hmax)->value() << ")";
    lblHeadersHSV.at(h)->setText(QString(ss.str().c_str()));

    //update_hsv_s();

    //sliderHmin->show();
}

void MainWindow::updateSmin(int value){
    _calib.colors.at(cmbColors->currentIndex()).min.rgb[s] = value;
    sliderHSV.at(smin)->setValue(_calib.colors.at(cmbColors->currentIndex()).min.rgb[s]);

    /*if(value >= _calib.colors.at(cmbColors->currentIndex()).max.rgb[s]){
        sliderSmax->setValue(_calib.colors.at(cmbColors->currentIndex()).max.rgb[s] + 1);
    }*/

    clearSS(ss);
    ss << "S(" << sliderHSV.at(smin)->value() << ", " << sliderHSV.at(smax)->value() << ")";
    lblHeadersHSV.at(s)->setText(QString(ss.str().c_str()));

    //sliderSmin->show();
}

void MainWindow::updateVmin(int value){
    _calib.colors.at(cmbColors->currentIndex()).min.rgb[v] = value;
    sliderHSV.at(vmin)->setValue(_calib.colors.at(cmbColors->currentIndex()).min.rgb[v]);

    /*if(value >= _calib.colors.at(cmbColors->currentIndex()).max.rgb[v]){
        sliderVmax->setValue(_calib.colors.at(cmbColors->currentIndex()).max.rgb[v] + 1);
    }*/

    clearSS(ss);
    ss << "V(" << sliderHSV.at(vmin)->value() << ", " << sliderHSV.at(vmax)->value() << ")";
    lblHeadersHSV.at(v)->setText(QString(ss.str().c_str()));

    //sliderVmin->show();
}

void MainWindow::updateHmax(int value){
    _calib.colors.at(cmbColors->currentIndex()).max.rgb[h] = value;
    sliderHSV.at(hmax)->setValue(_calib.colors.at(cmbColors->currentIndex()).max.rgb[h]);

    /*if(value <= _calib.colors.at(cmbColors->currentIndex()).min.rgb[h]){
        sliderHmin->setValue(_calib.colors.at(cmbColors->currentIndex()).max.rgb[h] - 1);
    }*/

    clearSS(ss);
    ss << "H(" << sliderHSV.at(hmin)->value() << ", " << sliderHSV.at(hmax)->value() << ")";
    lblHeadersHSV.at(h)->setText(QString(ss.str().c_str()));

    //update_hsv_s();

    //sliderHmax->show();
}

void MainWindow::updateSmax(int value){
    _calib.colors.at(cmbColors->currentIndex()).max.rgb[s] = value;
    sliderHSV.at(smax)->setValue(_calib.colors.at(cmbColors->currentIndex()).max.rgb[s]);

    /*if(value <= _calib.colors.at(cmbColors->currentIndex()).min.rgb[s]){
        sliderSmin->setValue(_calib.colors.at(cmbColors->currentIndex()).max.rgb[s] - 1);
    }*/

    clearSS(ss);
    ss << "S(" << sliderHSV.at(smin)->value() << ", " << sliderHSV.at(smax)->value() << ")";
    lblHeadersHSV.at(s)->setText(QString(ss.str().c_str()));

    //sliderSmax->show();
}

void MainWindow::updateVmax(int value){
    _calib.colors.at(cmbColors->currentIndex()).max.rgb[v] = value;
    sliderHSV.at(vmax)->setValue(_calib.colors.at(cmbColors->currentIndex()).max.rgb[v]);

    /*if(value <= _calib.colors.at(cmbColors->currentIndex()).min.rgb[v]){
        sliderVmin->setValue(_calib.colors.at(cmbColors->currentIndex()).max.rgb[v] - 1);
    }*/

    clearSS(ss);
    ss << "V(" << sliderHSV.at(vmin)->value() << ", " << sliderHSV.at(vmax)->value() << ")";
    lblHeadersHSV.at(v)->setText(QString(ss.str().c_str()));

    //sliderVmax->show();
}

void MainWindow::update_hsv_s(){
    switch(cmbColors->currentIndex()){
        case ORANGE:{
            hsv_s = "QSlider{ background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #fa1, stop: 1 #000)}";
        }break;
        case BLUE:{
            hsv_s = "QSlider{ background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #00f, stop: 1 #000)}";
        }break;
        case YELLOW:{
            hsv_s = "QSlider{ background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ff0, stop: 1 #000)}";
        }break;
        case RED:{
            hsv_s = "QSlider{ background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #f00, stop: 1 #000)}";
        }break;
        case GREEN:{
            hsv_s = "QSlider{ background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #0f0, stop: 1 #000)}";
        }break;
        case PURPLE:{
            hsv_s = "QSlider{ background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #71c, stop: 1 #000)}";
        }break;
        case PINK:{
            hsv_s = "QSlider{ background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #f87, stop: 1 #000)}";
        }break;
        case BROWN:{
            hsv_s = "QSlider{ background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #603, stop: 1 #000)}";
        }break;
    }

    sliderHSV.at(smax)->setStyleSheet(QString(hsv_s.c_str()));
    sliderHSV.at(smin)->setStyleSheet(QString(hsv_s.c_str()));
}

void MainWindow::defineColors(){
    int c;
    for(int i = 0 ; i < 8 ; i++){
        colors.at(i) = 0;
    }

    c = translateColor(cmbBallColors->currentText());
    if(c != UNKNOWN){
        colors.at(c)++;
        execConfig.ball_color = c;
    }

    c = translateColor(cmbMainColors_1->currentText());
    if(c != UNKNOWN){
        colors.at(c)++;
        execConfig.team_color[0] = c;
    }

    c = translateColor(cmbMainColors_2->currentText());
    if(c != UNKNOWN){
        colors.at(c)++;
        execConfig.team_color[1] = c;
    }

    c = translateColor(cmbSecColors_1->currentText());
    if(c != UNKNOWN){
        colors.at(c)++;
        execConfig.secundary_color_1[0] = c;
    }

    c = translateColor(cmbSecColors_2->currentText());
    if(c != UNKNOWN){
        colors.at(c)++;
        execConfig.secundary_color_1[1] = c;
    }

    c = translateColor(cmbSecColors_3->currentText());
    if(c != UNKNOWN){
        colors.at(c)++;
        execConfig.secundary_color_1[2] = c;
    }

    c = translateColor(cmbSecColors_4->currentText());
    if(c != UNKNOWN){
        colors.at(c)++;
        execConfig.secundary_color_2[0] = c;
    }

    c = translateColor(cmbSecColors_5->currentText());
    if(c != UNKNOWN){
        colors.at(c)++;
        execConfig.secundary_color_2[1] = c;
    }

    c = translateColor(cmbSecColors_6->currentText());
    if(c != UNKNOWN){
        colors.at(c)++;
        execConfig.secundary_color_2[2] = c;
    }

}

int MainWindow::translateColor(QString s){
    int c;

    if(s == "Orange"){
        c = ORANGE;
    }else
    if(s == "Blue"){
        c = BLUE;
    }else
    if(s == "Yellow"){
        c = YELLOW;
    }else
    if(s == "Purple"){
        c = PURPLE;
    }else
    if(s == "Pink"){
        c = PINK;
    }else
    if(s == "Green"){
        c = GREEN;
    }else
    if(s == "Brown"){
        c = BROWN;
    }else
    if(s == "Red"){
        c = RED;
    }else{
        c = UNKNOWN;
    }

    return c;
}


MainWindow::~MainWindow()
{
    calib.finish();
    vi.finish();
    delete ui;
}
