/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "unistd.h"

#include "vector"
#include "iostream"
#include "sstream"

#include <QMainWindow>
#include <QTreeView>
#include <QStandardItemModel>
#include <QStringListModel>
#include "QAbstractItemModel"
#include "QStringList"
#include <QStandardItem>
#include "QModelIndex"
#include "QIcon"
#include "QStyle"
#include "QMessageBox"
#include "QComboBox"
#include "QSize"
#include "QPushButton"
#include "QTreeWidgetItem"
#include "QCheckBox"
#include "QSignalMapper"
#include "QThread"
#include "QLabel"
#include "QTableView"
#include "QWidget"
#include "QPixmap"
#include "QSignalMapper"
#include "QSlider"
#include "QAbstractSlider"
#include "qcustomlabel.h"
#include "qtextstream.h"

#include "common.h"
#include "calibration.h"
#include "vision.h"
#include "sqlite.h"
#include "QtOpenCV.h"
#include "VSS-Interface/cpp/interface.h"

using namespace common;
using namespace QtOcv;

namespace Ui {


class MainWindow;
}

using namespace std;

//! This class is the main window of the software
class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    // QCustomLabel
    //! Method that get the signal from move the mouse inside QCustomLabel input image
    void mouseCurrentPos();

    //! Method that get the signal from left click inside QCustomLabel input image
    void mouseLeftPressed();

    //! Method that get the signal from right click inside QCustomLabel input image
    void mouseRightPressed();

    //! Method that get the signal from release left click inside QCustomLabel input image
    void mouseReleased();

    //! Method that get the signal from release the mouse from QCustomLabel input image
    void mouseLeave();


    // QPushButtons
    //! Method that get the signal from click on QPushButton Do Calibration Colors
    void evtCalibrationColors();

    //! Method that get the signal from click on QPushButton Run Vision
    void evtVision();

    //! Method that get the signal from click on QPushButton Do Calibration Camera
    void evtCalibrationCam();

    void evtSaveConfig();

    void evtSaveCalib();

    void evtLoadConfig();

    void evtLoadCalib();

    void evtDatabaseList();

    // QCheckboxs
    //! Method that get the signal from click on QCheckbox of use camera
    void checkboxCamera(int);

    //! Method that get the signal from click on QCheckbox of use image
    void checkboxImage(int);

    //! Method that get the signal from click on QCheckbox of use video
    void checkboxVideo(int);


    // QSliders
    //! Method that get the signal from slide on HSV-Hmin
    void updateHmin(int);

    //! Method that get the signal from slide on HSV-SMin
    void updateSmin(int);

    //! Method that get the signal from slide on HSV-Vmin
    void updateVmin(int);

    //! Method that get the signal from slide on HSV-Hmax
    void updateHmax(int);

    //! Method that get the signal from slide on HSV-Smax
    void updateSmax(int);

    //! Method that get the signal from slide on HSV-Vmax
    void updateVmax(int);

    //! Method that get the signal from slide on Rotation
    void updateRotation(int);

    // QThreads
    //! Method that get the signal has_new_image() from calibration
    void getNewImageCalib();

    //! Method that get the signal has_new_state() from vision
    void getNewStateVision();

protected:
    string user_path;
    Interface interface;
    calibration *calib;
    vision *vi;
    SQLite *sql;
    Ui::MainWindow *ui;
    vss_state::Global_State global_state;
    QIcon blockdevice, ksame, kdf, package, database;

    // QTree
    //! Method responsible for build all the left tab
    void buildTrees();

    //! Method responsible for add the main item "Yellow box"
    void addMainItem();

    //! Method responsible for add the list item "Yellow box"
    void addListItem();

    //! Method responsible for add the item of choose input data
    void addInputDataItem();

    //! Method reponsible for add the item of calibrate camera, cut points and rotation
    void addCameraCalibrationItem();

    //! Method responsible for add the item of set parameters of vision, like for blobs: area-min, area-max, proportion-max, proportion-min
    void addBlobFindingItem();

    //! Method responsible for add the item of set visualization (DEPRECATED)
    void addVisualizationItem();

    //! Method responsible for add the item that defines the type of pattern of colors (TODO)
    void addDefinePatternsItem();

    //! Method responsible for add the item of define the configuration of colors of each team 
    void addExecutionConfig();

    //! Method responsible for add the item of calibration of colors
    void addCalibrateColors();

    void addVisionOptions();
    
    //! Method responsible for add the item of define IP and PORT for interface
    void addNetOptions();

    //! Method reponsible form add the item of initializes the vision tracking
    void addExecutionOptions();

    void addDatabaseOptions();

    QTreeWidgetItem *mainItem, *listItem;
    QList<QTreeWidgetItem*> inputData;
    QList<QTreeWidgetItem*> databaseList;
    QList<QTreeWidgetItem*> cameraCalibration;
    QList<QTreeWidgetItem*> databaseOptions;
    QList<QTreeWidgetItem*> blobFinding;
    QList<QTreeWidgetItem*> visualization;
    QList<QTreeWidgetItem*> definePatterns;
    QList<QTreeWidgetItem*> defineExecutionConfig;
    QList<QTreeWidgetItem*> calibrateColors;
    QList<QTreeWidgetItem*> visionOptions;
    QList<QTreeWidgetItem*> netOptions;
    QList<QTreeWidgetItem*> executionOptions;

    QComboBox *cmbCameraIds, *cmbSavedImages, *cmbSavedVideos;
    QComboBox *cmbColors, *cmbMainColors_1, *cmbMainColors_2, *cmbSecColors_1, *cmbSecColors_2, *cmbSecColors_3, *cmbSecColors_4, *cmbSecColors_5, *cmbSecColors_6, *cmbBallColors;
    QCheckBox *checkUseCamera, *checkUseImage, *checkUseVideo;

    QPushButton *btnDoColorCalib, *btnRunVision, *btnDoCameraCalib;

    QWidget *contLayoutH3;
    vector<QLabel*> lblHeadersHSV;
    vector<QSlider*> slidersHSV;
    vector<QLabel*> lblHeadersPlot;
    vector<QLabel*> lblPlots;
    QLabel *lbl_val;

    QSlider *sliderRotation;
    QLabel *lbl_h_rotation;

    QCustomLabel *image;
    QLabel *coordinate_mouse, *zoom_image;

    //! Method responsible for update the layout for turn on the calibration
    void initCalibrationColors();

    //! Method responsible for update the layout for turn off the calibration
    void finishCalibrationColors();

    void initCalibrationCamera();

    void finishCalibrationCamera();

    //! Method responsible for update the layout for turn on the vision
    void initPlotValues();

    //! Method responsible for update the layout for turn off the vision
    void finishPlotValues();

    //! Method responsible for update de commom::VisionColor of calibration, depends of id_color in common::TableColor
    void updateValuesHSV();

    //! Method responsible for update the slide HSV-Smin and HSV-Smax, with the id_color in common::TableColor
    void update_hsv_s();

    QImage *in;

    //! Method responsible for get all cameras on PC
    void getAllDevices();

    //! Method responsible for define the colors that gonna be used on vision
    void defineColors();

    //! Method responsible for translate the colors on QCheckbox to vector
    int translateColor(QString);

    void sql_log();

    vector<string> devices;
    vector<int> devices_id;
    vector<int> colors;
    Calibration _calib;
    vector<Calibration> calibrations;
    State state;
    ExecConfiguration execConfig;
    stringstream ss;
    string hsv_s;
    bool calib_vs_vision;
    bool init;
    bool has_a_camera;
};

#endif // MAINWINDOW_H
