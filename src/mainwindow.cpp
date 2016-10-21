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

//! Addendum
//! --------
//! 
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    calib_vs_vision = has_a_camera = false;

    user_path = QCoreApplication::applicationDirPath().toUtf8().constData();

    //! > Define the connection to SQLite
    sql = new SQLite("../data/main.db", "passwd");

    //! Define the interface VSS
    interface.createSocketSendState(&global_state);

    for(int i = 0 ; i < 8 ; i++){
        colors.push_back(0);
    }

    //! > Create all QThings
    coordinate_mouse = new QLabel("M(0, 0)");

    mainItem = new QTreeWidgetItem;
    listItem = new QTreeWidgetItem;

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
    btnDoCameraCalib = new QPushButton("Do", this);
    /*btnSaveCalib = new QPushButton("Save", this);
    btnSaveConfig = new QPushButton("Save", this);
    btnLoadCalib = new QPushButton("Load", this);
    btnLoadConfig = new QPushButton("Load", this);*/

    //! > Define icons used
    blockdevice = QIcon(":icons/blockdevice.png");
    ksame = QIcon(":icons/ksame.png");
    kdf = QIcon(":icons/kdf.png");
    package = QIcon(":icons/package.png");

    string database_path;
    database_path = user_path + "/icons/database.png";
    database = QIcon(QString(database_path.c_str()));

    //! > Get all cameras connected to PC
    getAllDevices();

    sql_log();

    //! > Build the left tab
    buildTrees();

    //! > Disable camera option, if any camera it's connected
    if(devices.size() < 1){
        checkUseCamera->setChecked(false);
        checkUseImage->setChecked(true);
        checkUseVideo->setChecked(false);

        cmbCameraIds->setDisabled(true);
        checkUseCamera->setDisabled(true);
        has_a_camera = false;
    }else{
        checkUseCamera->setChecked(true);
        checkUseImage->setChecked(false);
        checkUseVideo->setChecked(false);
        has_a_camera = true;
    }

    //! > Begin Define styles
    //! *********************
    for(int i = 0 ; i < 3 ; i++){
        lblHeadersHSV.push_back(new QLabel("(0 - N)"));
        lblHeadersHSV.at(i)->setStyleSheet("QLabel {qproperty-alignment: AlignCenter; font-weight: bold;}");
    }

    lbl_val = new QLabel("Pos\nVel\nKPos\nKVel");

    for(int i = 0 ; i < 7 ; i++){
        lblHeadersPlot.push_back(new QLabel("Header"));
        lblHeadersPlot.at(i)->setStyleSheet("QLabel {qproperty-alignment: AlignCenter; font-weight: bold;}");

        lblPlots.push_back(new QLabel("000, 000, 0.00\n000, 000, 0.00\n000, 000, 0.00\n000, 000, 0.00\n"));
        lblPlots.at(i)->setStyleSheet("QLabel {qproperty-alignment: AlignCenter; font-size: 14px; background: white; border: 1px solid #bbb; margin-bottom: 50px; min-height: 100px;}");
    }

    lblHeadersPlot.at(0)->setText("Robot 1A");
    lblHeadersPlot.at(1)->setText("Robot 2A");
    lblHeadersPlot.at(2)->setText("Robot 3A");
    lblHeadersPlot.at(3)->setText("Robot 1B");
    lblHeadersPlot.at(4)->setText("Robot 2B");
    lblHeadersPlot.at(5)->setText("Robot 3B");
    lblHeadersPlot.at(6)->setText("Ball");

    lbl_val->setStyleSheet("QLabel {qproperty-alignment: AlignCenter; font-size: 14px;  margin-bottom: 50px; min-height: 100px;}");

    for(int i = 0 ; i < 6 ; i++){
        slidersHSV.push_back(new QSlider(Qt::Orientation(VerticalTabs)));
        slidersHSV.at(i)->setMinimumHeight(100);
    }

    slidersHSV.at(hmin)->setMaximum(179);
    slidersHSV.at(smin)->setMaximum(254);
    slidersHSV.at(vmin)->setMaximum(254);
    slidersHSV.at(hmax)->setMaximum(180);
    slidersHSV.at(smax)->setMaximum(255);
    slidersHSV.at(vmax)->setMaximum(255);

    slidersHSV.at(hmin)->setMinimum(0);
    slidersHSV.at(smin)->setMinimum(0);
    slidersHSV.at(vmin)->setMinimum(0);
    slidersHSV.at(hmax)->setMinimum(1);
    slidersHSV.at(smax)->setMinimum(1);
    slidersHSV.at(vmax)->setMinimum(1);


    slidersHSV.at(hmin)->setValue(_calib.colors.at(0).min.rgb[h]);
    slidersHSV.at(smin)->setValue(_calib.colors.at(0).min.rgb[s]);
    slidersHSV.at(vmin)->setValue(_calib.colors.at(0).min.rgb[v]);
    slidersHSV.at(hmax)->setValue(_calib.colors.at(0).max.rgb[h]);
    slidersHSV.at(smax)->setValue(_calib.colors.at(0).max.rgb[s]);
    slidersHSV.at(hmax)->setValue(_calib.colors.at(0).max.rgb[v]);

    connect(slidersHSV.at(hmin), SIGNAL(valueChanged(int)), this, SLOT(updateHmin(int)));
    connect(slidersHSV.at(smin), SIGNAL(valueChanged(int)), this, SLOT(updateSmin(int)));
    connect(slidersHSV.at(vmin), SIGNAL(valueChanged(int)), this, SLOT(updateVmin(int)));
    connect(slidersHSV.at(hmax), SIGNAL(valueChanged(int)), this, SLOT(updateHmax(int)));
    connect(slidersHSV.at(smax), SIGNAL(valueChanged(int)), this, SLOT(updateSmax(int)));
    connect(slidersHSV.at(vmax), SIGNAL(valueChanged(int)), this, SLOT(updateVmax(int)));

    updateValuesHSV();
    update_hsv_s();

    slidersHSV.at(hmax)->setStyleSheet("QSlider{ background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0.0 #00f, stop: 0.167 #f0f, stop: 0.334 #f00, stop: 0.501 #ff0, stop: 0.668 #0f0, stop: 0.835 #0ff, stop: 1.0 #00f)}");
    slidersHSV.at(hmin)->setStyleSheet("QSlider{ background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0.0 #00f, stop: 0.167 #f0f, stop: 0.334 #f00, stop: 0.501 #ff0, stop: 0.668 #0f0, stop: 0.835 #0ff, stop: 1.0 #00f)}");
    slidersHSV.at(vmax)->setStyleSheet("QSlider{ background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #fff, stop: 1 #000)}");
    slidersHSV.at(vmin)->setStyleSheet("QSlider{ background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #fff, stop: 1 #000)}");

    ui->layoutH3->setContentsMargins(2, 0, 2, 0);
    ui->layoutH4->setContentsMargins(2, 0, 2, 0);
    ui->layoutH5->setContentsMargins(2, 0, 2, 0);
    ui->layoutH6->setContentsMargins(2, 0, 2, 0);
    ui->layoutH7->setContentsMargins(2, 0, 2, 0);
    ui->layoutH8->setContentsMargins(2, 0, 2, 0);
    ui->layoutH9->setContentsMargins(2, 0, 2, 0);
    ui->layoutH10->setContentsMargins(2, 0, 2, 0);

    image = new QCustomLabel();
    image->setMouseTracking(true);
    QObject::connect(image, SIGNAL(Mouse_Pos()), this, SLOT(mouseCurrentPos()));
    QObject::connect(image, SIGNAL(Mouse_Left_Pressed()), this, SLOT(mouseLeftPressed()));
    QObject::connect(image, SIGNAL(Mouse_Right_Pressed()), this, SLOT(mouseRightPressed()));

    ui->layoutH2->addWidget(image);

    sliderRotation = new QSlider();
    sliderRotation->setMinimumHeight(100);
    sliderRotation->setMaximum(100);
    sliderRotation->setMinimum(-100);
    sliderRotation->setStyleSheet("QSlider {background: white; border: 1px solid #bbb;}");

    lbl_h_rotation = new QLabel("Rotation");
    lbl_h_rotation->setStyleSheet("QLabel {qproperty-alignment: AlignCenter; font-weight: bold;}");
    QObject::connect(sliderRotation, SIGNAL(valueChanged(int)), this, SLOT(updateRotation(int)));


    //! > End Define styles
    //! *******************

    calib = new calibration();

    //! > Initializes the calibration thread
    QObject::connect(calib, SIGNAL(finished()), this, SLOT(quit()));
    QObject::connect(calib, SIGNAL(has_new_image()), this, SLOT(getNewImageCalib()));
    calib->alloc_label_input(image);
    calib->alloc_calibration(&_calib);

    vi = new vision();

    //! Initializes the vision thread
    QObject::connect(vi, SIGNAL(finished()), this, SLOT(quit()));
    QObject::connect(vi, SIGNAL(has_new_state()), this, SLOT(getNewStateVision()));
    vi->alloc_label_input(image);
    vi->alloc_calibration(&_calib);
    vi->alloc_state(&state);
    vi->alloc_colors(&colors);
    vi->alloc_execution_config(&execConfig);
    vi->alloc_label_plots(&lblPlots);

    calib->start();
    vi->start();

    image->show();

    connect(ui->btnSave, SIGNAL (clicked()), this, SLOT (evtSaveCalib()));
    connect(ui->btnLoad, SIGNAL (clicked()), this, SLOT (evtLoadCalib()));
}

//! Addendum
//! --------
//! 
void MainWindow::getAllDevices(){
    devices.clear();
    devices_id.clear();

    string response = cmdTerminal("find /dev/ -name video*");
    string sp = "";

    //! > Trait the exit or common::cmdTerminal();
    for(int i = 0 ; i < response.size() ; i++){
        if(response[i] == '\n'){
            stringstream s_to_i;
            int s_in_i;

            s_to_i << sp[sp.size()-1];
            s_to_i >> s_in_i;

            devices.push_back(sp);
            devices_id.push_back(s_in_i);
            //cout << s_in_i << endl;
            sp = "";
        }else{
            sp += response.at(i);
        }
    }
}

//! Addendum
//! --------
//! 
void MainWindow::addMainItem(){
    //! >  Create the entire tab
    mainItem->setIcon(0, package);
    mainItem->setText(0, "Vision System");

    ui->treeMain->addTopLevelItem(mainItem);
}

//! Addendum
//! --------
//!
void MainWindow::addListItem(){
    //! >  Create the entire tab
    listItem->setIcon(0, database);
    listItem->setText(0, "Database");

    ui->treeList->addTopLevelItem(listItem);
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
    int qtd = 4;
    for(int i = 0 ; i < qtd ; i++){
        cameraCalibration.append(new QTreeWidgetItem);
    }

    cameraCalibration.at(0)->setIcon(0, blockdevice);
    cameraCalibration.at(0)->setText(0, "Camera");

    cameraCalibration.at(1)->setIcon(0, ksame);
    cameraCalibration.at(1)->setText(0, "Rotation");

    cameraCalibration.at(2)->setIcon(0, ksame);
    cameraCalibration.at(2)->setText(0, "Bounds");

    cameraCalibration.at(3)->setIcon(0, ksame);
    cameraCalibration.at(3)->setText(0, "Calibrate");

    mainItem->addChild(cameraCalibration.at(0));
    for(int i = 1 ; i < qtd ; i++){
        cameraCalibration.at(0)->addChild(cameraCalibration.at(i));
    }

    btnDoCameraCalib->setMaximumHeight(20);
    connect(btnDoCameraCalib, SIGNAL (clicked()), this, SLOT (evtCalibrationCam()));

    cameraCalibration.at(1)->setText(1, "0º");        
    cameraCalibration.at(2)->setText(1, "00, 00, 000, 000");
    ui->treeMain->setItemWidget(cameraCalibration.value(3), 1, btnDoCameraCalib);

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
    defineExecutionConfig.at(0)->setText(0, "Configuration");

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

    cmbMainColors_1->setCurrentIndex(1);

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
    calibrateColors.at(0)->setText(0, "Colors");

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
    connect(btnDoColorCalib, SIGNAL (clicked()), this, SLOT (evtCalibrationColors()));

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

    btnRunVision->setMaximumHeight(20);
    connect(btnRunVision, SIGNAL (clicked()), this, SLOT (evtVision()));


    mainItem->addChild(executionOptions.at(0));
    for(int i = 1 ; i < qtd ; i++){
        executionOptions.at(0)->addChild(executionOptions.at(i));
    }

    ui->treeMain->setItemWidget(executionOptions.value(1), 1, btnRunVision);
    ui->treeMain->insertTopLevelItems(0, executionOptions);
}

/*void MainWindow::addDatabaseOptions(){
    int qtd = 5;
    for(int i = 0 ; i < qtd ; i++){
        databaseOptions.append(new QTreeWidgetItem);
    }

    databaseOptions.at(0)->setIcon(0, blockdevice);
    databaseOptions.at(0)->setText(0, "Database");

    databaseOptions.at(1)->setIcon(0, ksame);
    databaseOptions.at(1)->setText(0, "Calibration");

    databaseOptions.at(2)->setIcon(0, ksame);
    databaseOptions.at(2)->setText(0, "Calibration");

    databaseOptions.at(3)->setIcon(0, ksame);
    databaseOptions.at(3)->setText(0, "Configuration");

    databaseOptions.at(4)->setIcon(0, ksame);
    databaseOptions.at(4)->setText(0, "Configuration");

    btnSaveCalib->setMaximumHeight(20);
    btnSaveConfig->setMaximumHeight(20);
    btnLoadCalib->setMaximumHeight(20);
    btnLoadConfig->setMaximumHeight(20);

    connect(btnSaveCalib, SIGNAL (clicked()), this, SLOT (evtSaveCalib()));
    connect(btnSaveConfig, SIGNAL (clicked()), this, SLOT (evtSaveConfig()));
    connect(btnLoadCalib, SIGNAL (clicked()), this, SLOT (evtLoadCalib()));
    connect(btnLoadConfig, SIGNAL (clicked()), this, SLOT (evtLoadConfig()));

    mainItem->addChild(databaseOptions.at(0));
    for(int i = 1 ; i < qtd ; i++){
        databaseOptions.at(0)->addChild(databaseOptions.at(i));
    }

    ui->treeMain->setItemWidget(databaseOptions.value(1), 1, btnSaveCalib);
    ui->treeMain->setItemWidget(databaseOptions.value(2), 1, btnLoadCalib);
    ui->treeMain->setItemWidget(databaseOptions.value(3), 1, btnSaveConfig);
    ui->treeMain->setItemWidget(databaseOptions.value(4), 1, btnLoadConfig);
    ui->treeMain->insertTopLevelItems(0, databaseOptions);
}*/

//! Addendum
//! --------
//! 
void MainWindow::checkboxCamera(int a){
    //> If camera it's true, image and video it's false
    if(checkUseCamera->isChecked()){
        checkUseImage->setChecked(false);
        checkUseVideo->setChecked(false);
    }
}

//! Addendum
//! --------
//! 
void MainWindow::checkboxImage(int a){
    //!> If image it's true, video and camera it's false
    if(checkUseImage->isChecked()){
        checkUseCamera->setChecked(false);
        checkUseVideo->setChecked(false);
    }
}

//! Addendum
//! --------
//! 
void MainWindow::checkboxVideo(int a){
    //! > If video it's true, iamge and camera it's false
    if(checkUseVideo->isChecked()){
        checkUseImage->setChecked(false);
        checkUseCamera->setChecked(false);
    }
}

//! Addendum
//! --------
//! 
void MainWindow::buildTrees(){
    QStringList headers, headers2;

    headers.append("Variable");
    headers.append("Value");

    addMainItem();
    addInputDataItem();
    addCameraCalibrationItem();
    //addBlobFindingItem();
    //addVisualizationItem();
    //addDefinePatternsItem();
    addCalibrateColors();
    addExecutionConfig();
    //addDatabaseOptions();
    //addVisionOptions();
    //addNetOptions();
    addExecutionOptions();

    //! > Set the number os columns and the size of them
    ui->treeMain->setColumnCount(2);
    ui->treeMain->setHeaderLabels(headers);
    ui->treeMain->setColumnWidth(0, 190);
    ui->treeMain->expandItem(mainItem);

    headers2.append("Calibration");
    headers2.append("Date");

    for(int i = 0 ; i < calibrations.size() ; i++){
        databaseList.append(new QTreeWidgetItem);

        databaseList.at(i)->setIcon(0, database);
        databaseList.at(i)->setText(0, QString(calibrations.at(i).comment.c_str()));

        databaseList.at(i)->setText(1, QString(calibrations.at(i).data.c_str()));
    }

    ui->treeList->insertTopLevelItems(0, databaseList);

    ui->treeList->setColumnCount(2);
    ui->treeList->setHeaderLabels(headers2);
    ui->treeList->setColumnWidth(0, 120);
    ui->treeList->expandItem(listItem);


}

//! Addendum
//! --------
//! 
void MainWindow::mouseCurrentPos(){
    //!> Update the plot values on layout
    clearSS(ss);
    ss << "M(" << image->x << ", " << image->y << ")";
    coordinate_mouse->setText(QString(ss.str().c_str()));
}

//! Addendum
//! --------
//! 
void MainWindow::mouseLeftPressed(){
    if(!vi->get_vision_reception()){
        if(calib->get_type_calibration()){
            //! > Update the qtd of left clicks on vision zoom
            calib->set_mouse_click_left(calib->get_mouse_click_left()+1);
        }else{
            _calib.cut.at(0).x = image->x;
            _calib.cut.at(0).y = image->y-10;

            stringstream ss;
            ss << _calib.cut.at(0).x << ", " << _calib.cut.at(0).y << ", " << _calib.cut.at(1).x << ", " << _calib.cut.at(1).y; 
            cameraCalibration.at(2)->setText(1, ss.str().c_str());   
        }
    }
}

//! Addendum
//! --------
//! 
void MainWindow::mouseRightPressed(){
    if(!vi->get_vision_reception()){    
        if(calib->get_type_calibration()){
            //! > Update the qtd of right clicks on vision
            calib->set_mouse_click_right(calib->get_mouse_click_right()+1);
        }else{
            _calib.cut.at(1).x = image->x;
            _calib.cut.at(1).y = image->y-10;

            stringstream ss;
            ss << _calib.cut.at(0).x << ", " << _calib.cut.at(0).y << ", " << _calib.cut.at(1).x << ", " << _calib.cut.at(1).y; 
            cameraCalibration.at(2)->setText(1, ss.str().c_str());  
        }
    }
}

void MainWindow::mouseReleased(){

}

void MainWindow::mouseLeave(){

}

//! Addendum
//! --------
//! 
void MainWindow::evtCalibrationColors(){
    //! > Toggle between ON/OFF calibration
    if(!calib->get_vision_reception()){
        calib->set_type_calibration(true);
        //! > If camera it's used, set device common::CAMERA and its id
        if(checkUseCamera->isChecked()){
            calib->set_device(CAMERA);
            calib->set_id_camera( devices_id.at(cmbCameraIds->currentIndex()) );
        }else
        //! > If image it's used, set device common::IMAGE
        if(checkUseImage->isChecked()){
            calib->set_device(IMAGE);
        }else
        //! > If video it's used, set device common::VIDEO
        if(checkUseVideo->isChecked()){
            calib->set_device(VIDEO);

        }

        //! > Send which color will be calibrate
        calib->set_id_color(cmbColors->currentIndex());
        //! > Turn ON the calibration thread
        calib->set_vision_reception(true);

        //! > Disable options of input data
        cmbColors->setDisabled(true);
        
        cmbSavedImages->setDisabled(true);
        checkUseImage->setDisabled(true);

        cmbSavedVideos->setDisabled(true);
        checkUseVideo->setDisabled(true);

        if(has_a_camera){
            cmbCameraIds->setDisabled(true);
            checkUseCamera->setDisabled(true);
        }
        
        //! > Update the values of HSV that will be plot on sliders
        updateValuesHSV();
        initCalibrationColors();
        ui->layoutH9H->addWidget(coordinate_mouse);
        coordinate_mouse->show();

        btnRunVision->setDisabled(true);
        btnDoCameraCalib->setDisabled(true);
        btnDoColorCalib->setText("Done");

        ui->btnLoad->setDisabled(true);
        ui->btnSave->setDisabled(true);
    }else{
        //! > Enable options of input data
        cmbColors->setDisabled(false);

        if(has_a_camera){
            cmbCameraIds->setDisabled(false);
            checkUseCamera->setDisabled(false);
        }

        cmbSavedImages->setDisabled(false);
        checkUseImage->setDisabled(false);

        cmbSavedVideos->setDisabled(false);
        checkUseVideo->setDisabled(false);

        btnRunVision->setDisabled(false);

        //! > Turn OFF the calibration thread
        calib->set_vision_reception(false);

        finishCalibrationColors();
        ui->layoutH9H->removeWidget(coordinate_mouse);
        coordinate_mouse->hide();

        btnRunVision->setDisabled(false);
        btnDoCameraCalib->setDisabled(false);
        btnDoColorCalib->setText("Do");

        ui->btnLoad->setDisabled(false);
        ui->btnSave->setDisabled(false);
    }
}

//! Addendum
//! --------
//! 
void MainWindow::evtCalibrationCam(){
    //! > Toggle between ON/OFF calibration
    if(!calib->get_vision_reception()){
        initCalibrationCamera();
        calib->set_type_calibration(false);
        //! > If camera it's used, set device common::CAMERA and its id
        if(checkUseCamera->isChecked()){
            calib->set_device(CAMERA);
            calib->set_id_camera( devices_id.at(cmbCameraIds->currentIndex()) );
        }else
        //! > If image it's used, set device common::IMAGE
        if(checkUseImage->isChecked()){
            calib->set_device(IMAGE);
        }else
        //! > If video it's used, set device common::VIDEO
        if(checkUseVideo->isChecked()){
            calib->set_device(VIDEO);

        }

        cmbSavedImages->setDisabled(true);
        checkUseImage->setDisabled(true);

        cmbSavedVideos->setDisabled(true);
        checkUseVideo->setDisabled(true);

        if(has_a_camera){
            cmbCameraIds->setDisabled(true);
            checkUseCamera->setDisabled(true);
        }

        //! > Turn ON the calibration thread
        calib->set_vision_reception(false);

        cmbColors->setDisabled(true);

        btnDoCameraCalib->setText("Done");
        btnDoColorCalib->setDisabled(true);
        btnRunVision->setDisabled(true);

        ui->btnLoad->setDisabled(true);
        ui->btnSave->setDisabled(true);
    }else{
        finishCalibrationCamera();
        //! > Turn OFF the calibration thread
        calib->set_vision_reception(false);

        if(has_a_camera){
            cmbCameraIds->setDisabled(false);
            checkUseCamera->setDisabled(false);
        }

        cmbSavedImages->setDisabled(false);
        checkUseImage->setDisabled(false);

        cmbSavedVideos->setDisabled(false);
        checkUseVideo->setDisabled(false);

        cmbColors->setDisabled(false);
        
        btnDoCameraCalib->setText("Do");
        btnDoColorCalib->setDisabled(false);
        btnRunVision->setDisabled(false);

        ui->btnLoad->setDisabled(false);
        ui->btnSave->setDisabled(false);
    }
}

//! Addendum
//! --------
//! 
void MainWindow::evtVision(){
    //! > Toggle between ON/OFF calibration
    if(!vi->get_vision_reception()){
        //! > If camera it's used, set device common::CAMERA and its id
        if(checkUseCamera->isChecked()){
            vi->set_device(CAMERA);

            vi->set_id_camera( devices_id.at(cmbCameraIds->currentIndex()) );
        }else
        //! > If image it's used, set device common::IMAGE
        if(checkUseImage->isChecked()){
            vi->set_device(IMAGE);
        }else
        //! > If video it's used, set device common::VIDEO
        if(checkUseVideo->isChecked()){
            vi->set_device(VIDEO);
        }

        //! > Disable options of input data
        cmbColors->setDisabled(true);

        cmbSavedImages->setDisabled(true);
        checkUseImage->setDisabled(true);

        cmbSavedVideos->setDisabled(true);
        checkUseVideo->setDisabled(true);

        if(has_a_camera){
            cmbCameraIds->setDisabled(true);
            checkUseCamera->setDisabled(true);
        }  

        defineColors();
        
        //! > Turn ON the vision thread
        vi->set_vision_reception(true);

        
        initPlotValues();

        btnDoCameraCalib->setDisabled(true);
        btnDoColorCalib->setDisabled(true);
        btnRunVision->setText("Pause");

        ui->btnLoad->setDisabled(true);
        ui->btnSave->setDisabled(true);
    }else{
        //! > Enable options of input data
        cmbColors->setDisabled(false);

        if(has_a_camera){
            cmbCameraIds->setDisabled(false);
            checkUseCamera->setDisabled(false);
        }

        cmbSavedImages->setDisabled(false);
        checkUseImage->setDisabled(false);

        cmbSavedVideos->setDisabled(false);
        checkUseVideo->setDisabled(false);

        //! > Turn OFF the vision thread
        vi->set_vision_reception(false);
        finishPlotValues();

        btnDoCameraCalib->setDisabled(false);
        btnDoColorCalib->setDisabled(false);
        btnRunVision->setText("Run");

        ui->btnLoad->setDisabled(false);
        ui->btnSave->setDisabled(false);
    }
}

void MainWindow::evtSaveConfig(){
}

void MainWindow::evtLoadConfig(){
}

void MainWindow::evtSaveCalib(){
    bool ok = false;
    if(ui->saveVal->text().size() > 0){
        _calib.comment = ui->saveVal->text().toUtf8().constData();
        sql->insert_calibration(_calib);
        ok = true;
    }else{
        ui->multiTex->setText("ERROR: You must enter a name to save a new calibration ...");
    }

    if(ok){
        ui->multiTex->setText("SUCCESS: Calibration saved ...");
    }else{
        ui->multiTex->setText("ERROR: Calibration not saved ...");
    }
}

void MainWindow::evtLoadCalib(){
    if(ui->loadVal->text().size() > 0){
        bool ok = false;
        for(int i = 0 ; i < calibrations.size() ; i++){
            if(calibrations.at(i).comment == ui->loadVal->text().toUtf8().constData()){
                //_calib.show();
                _calib = calibrations.at(i);
                //_calib.show();
                ok = true;
                break;
            }
        }
        if(ok){
            ui->multiTex->setText("SUCCESS: Calibration loaded ...");
        }else{
            ui->multiTex->setText("ERROR: Calibration not founded ...");
        }
    }else{
        ui->multiTex->setText("ERROR: You must enter a name to load a calibration ...");
    }
}





void MainWindow::evtDatabaseList(){
    qDebug() << "teste";
}

void MainWindow::initCalibrationColors(){
    ui->layoutH3->addWidget(slidersHSV.at(hmin));
    ui->layoutH3->addWidget(slidersHSV.at(hmax));
    ui->layoutH5->addWidget(slidersHSV.at(smin));
    ui->layoutH5->addWidget(slidersHSV.at(smax));
    ui->layoutH7->addWidget(slidersHSV.at(vmin));
    ui->layoutH7->addWidget(slidersHSV.at(vmax));

    ui->layoutH3H->addWidget(lblHeadersHSV.at(h));
    ui->layoutH5H->addWidget(lblHeadersHSV.at(s));
    ui->layoutH7H->addWidget(lblHeadersHSV.at(v));

    for(int i = 0 ; i < 3 ; i++)
        lblHeadersHSV.at(i)->show();

    for(int i = 0 ; i < 6 ; i++)
        slidersHSV.at(i)->show();

    update_hsv_s();
}

void MainWindow::finishCalibrationColors(){
    ui->layoutH3->removeWidget(slidersHSV.at(hmin));
    ui->layoutH3->removeWidget(slidersHSV.at(hmax));
    ui->layoutH5->removeWidget(slidersHSV.at(smin));
    ui->layoutH5->removeWidget(slidersHSV.at(smax));
    ui->layoutH7->removeWidget(slidersHSV.at(vmin));
    ui->layoutH7->removeWidget(slidersHSV.at(vmax));

    ui->layoutH3H->removeWidget(lblHeadersHSV.at(h));
    ui->layoutH5H->removeWidget(lblHeadersHSV.at(s));
    ui->layoutH7H->removeWidget(lblHeadersHSV.at(v));

    for(int i = 0 ; i < 3 ; i++)
        lblHeadersHSV.at(i)->hide();

    for(int i = 0 ; i < 6 ; i++)
        slidersHSV.at(i)->hide();

    update_hsv_s();
}

void MainWindow::initCalibrationCamera(){
    ui->layoutH3->addWidget(sliderRotation);
    ui->layoutH3H->addWidget(lbl_h_rotation);

    sliderRotation->show();
    lbl_h_rotation->show();
}

void MainWindow::finishCalibrationCamera(){
    ui->layoutH3->removeWidget(sliderRotation);
    ui->layoutH3H->removeWidget(lbl_h_rotation);

    sliderRotation->hide();
    lbl_h_rotation->hide();
}

void MainWindow::initPlotValues(){
    state = State();
    ui->layoutH10->addWidget(lbl_val);
    lbl_val->show();

    ui->layoutH3H->addWidget(lblHeadersPlot.at(0));
    ui->layoutH4H->addWidget(lblHeadersPlot.at(1));
    ui->layoutH5H->addWidget(lblHeadersPlot.at(2));
    ui->layoutH6H->addWidget(lblHeadersPlot.at(3));
    ui->layoutH7H->addWidget(lblHeadersPlot.at(4));
    ui->layoutH8H->addWidget(lblHeadersPlot.at(5));
    ui->layoutH9H->addWidget(lblHeadersPlot.at(6));

    ui->layoutH3->addWidget(lblPlots.at(0));
    ui->layoutH4->addWidget(lblPlots.at(1));
    ui->layoutH5->addWidget(lblPlots.at(2));
    ui->layoutH6->addWidget(lblPlots.at(3));
    ui->layoutH7->addWidget(lblPlots.at(4));
    ui->layoutH8->addWidget(lblPlots.at(5));
    ui->layoutH9->addWidget(lblPlots.at(6));

    for(int i = 0 ; i < 7 ; i++){
        lblPlots.at(i)->show();
        lblHeadersPlot.at(i)->show();
    }
}

void MainWindow::finishPlotValues(){
    ui->layoutH10->removeWidget(lbl_val);
    lbl_val->hide();

    ui->layoutH3H->removeWidget(lblHeadersPlot.at(0));
    ui->layoutH4H->removeWidget(lblHeadersPlot.at(1));
    ui->layoutH5H->removeWidget(lblHeadersPlot.at(2));
    ui->layoutH6H->removeWidget(lblHeadersPlot.at(3));
    ui->layoutH7H->removeWidget(lblHeadersPlot.at(4));
    ui->layoutH8H->removeWidget(lblHeadersPlot.at(5));
    ui->layoutH9H->removeWidget(lblHeadersPlot.at(6));

    ui->layoutH3->removeWidget(lblPlots.at(0));
    ui->layoutH4->removeWidget(lblPlots.at(1));
    ui->layoutH5->removeWidget(lblPlots.at(2));
    ui->layoutH6->removeWidget(lblPlots.at(3));
    ui->layoutH7->removeWidget(lblPlots.at(4));
    ui->layoutH8->removeWidget(lblPlots.at(5));
    ui->layoutH9->removeWidget(lblPlots.at(6));

    for(int i = 0 ; i < 7 ; i++){
        lblPlots.at(i)->hide();
        lblHeadersPlot.at(i)->hide();
    }
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
    slidersHSV.at(hmin)->setValue(_calib.colors.at(cmbColors->currentIndex()).min.rgb[h]);

    /*if(value >= _calib->colors.at(cmbColors->currentIndex()).max.rgb[h]){
        sliderHmax->setValue(_calib->colors.at(cmbColors->currentIndex()).max.rgb[h] + 1);
    }*/

    clearSS(ss);
    ss << "H(" << slidersHSV.at(hmin)->value() << ", " << slidersHSV.at(hmax)->value() << ")";
    lblHeadersHSV.at(h)->setText(QString(ss.str().c_str()));

    //update_hsv_s();

    //sliderHmin->show();
}

void MainWindow::updateSmin(int value){
    _calib.colors.at(cmbColors->currentIndex()).min.rgb[s] = value;
    slidersHSV.at(smin)->setValue(_calib.colors.at(cmbColors->currentIndex()).min.rgb[s]);

    /*if(value >= _calib->colors.at(cmbColors->currentIndex()).max.rgb[s]){
        sliderSmax->setValue(_calib->colors.at(cmbColors->currentIndex()).max.rgb[s] + 1);
    }*/

    clearSS(ss);
    ss << "S(" << slidersHSV.at(smin)->value() << ", " << slidersHSV.at(smax)->value() << ")";
    lblHeadersHSV.at(s)->setText(QString(ss.str().c_str()));

    //sliderSmin->show();
}

void MainWindow::updateVmin(int value){
    _calib.colors.at(cmbColors->currentIndex()).min.rgb[v] = value;
    slidersHSV.at(vmin)->setValue(_calib.colors.at(cmbColors->currentIndex()).min.rgb[v]);

    /*if(value >= _calib->colors.at(cmbColors->currentIndex()).max.rgb[v]){
        sliderVmax->setValue(_calib->colors.at(cmbColors->currentIndex()).max.rgb[v] + 1);
    }*/

    clearSS(ss);
    ss << "V(" << slidersHSV.at(vmin)->value() << ", " << slidersHSV.at(vmax)->value() << ")";
    lblHeadersHSV.at(v)->setText(QString(ss.str().c_str()));

    //sliderVmin->show();
}

void MainWindow::updateHmax(int value){
    _calib.colors.at(cmbColors->currentIndex()).max.rgb[h] = value;
    slidersHSV.at(hmax)->setValue(_calib.colors.at(cmbColors->currentIndex()).max.rgb[h]);

    /*if(value <= _calib->colors.at(cmbColors->currentIndex()).min.rgb[h]){
        sliderHmin->setValue(_calib->colors.at(cmbColors->currentIndex()).max.rgb[h] - 1);
    }*/

    clearSS(ss);
    ss << "H(" << slidersHSV.at(hmin)->value() << ", " << slidersHSV.at(hmax)->value() << ")";
    lblHeadersHSV.at(h)->setText(QString(ss.str().c_str()));

    //update_hsv_s();

    //sliderHmax->show();
}

void MainWindow::updateSmax(int value){
    _calib.colors.at(cmbColors->currentIndex()).max.rgb[s] = value;
    slidersHSV.at(smax)->setValue(_calib.colors.at(cmbColors->currentIndex()).max.rgb[s]);

    /*if(value <= _calib->colors.at(cmbColors->currentIndex()).min.rgb[s]){
        sliderSmin->setValue(_calib->colors.at(cmbColors->currentIndex()).max.rgb[s] - 1);
    }*/

    clearSS(ss);
    ss << "S(" << slidersHSV.at(smin)->value() << ", " << slidersHSV.at(smax)->value() << ")";
    lblHeadersHSV.at(s)->setText(QString(ss.str().c_str()));

    //sliderSmax->show();
}

void MainWindow::updateVmax(int value){
    _calib.colors.at(cmbColors->currentIndex()).max.rgb[v] = value;
    slidersHSV.at(vmax)->setValue(_calib.colors.at(cmbColors->currentIndex()).max.rgb[v]);

    /*if(value <= _calib->colors.at(cmbColors->currentIndex()).min.rgb[v]){
        sliderVmin->setValue(_calib->colors.at(cmbColors->currentIndex()).max.rgb[v] - 1);
    }*/

    clearSS(ss);
    ss << "V(" << slidersHSV.at(vmin)->value() << ", " << slidersHSV.at(vmax)->value() << ")";
    lblHeadersHSV.at(v)->setText(QString(ss.str().c_str()));

    //sliderVmax->show();
}

void MainWindow::updateRotation(int value){
    float new_value = value/10.0;
    sliderRotation->setValue(value);
    _calib.rotation = new_value;

    stringstream ss;
    ss << new_value << "º";
    cameraCalibration.at(1)->setText(1, ss.str().c_str());        
}

void MainWindow::getNewImageCalib(){
    image->setPixmap(QPixmap::fromImage(mat2Image(calib->raw_in)));
}

void MainWindow::getNewStateVision(){
    image->setPixmap(QPixmap::fromImage(mat2Image(vi->raw_in)));
    
    global_state = State2Global_State(state, execConfig);

    interface.sendState();
    //qDebug() << "send state";
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

    slidersHSV.at(smax)->setStyleSheet(QString(hsv_s.c_str()));
    slidersHSV.at(smin)->setStyleSheet(QString(hsv_s.c_str()));
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

void MainWindow::sql_log(){
    calibrations = sql->select_calibration();
}

MainWindow::~MainWindow()
{
    calib->finish();
    vi->finish();
    delete ui;
}
