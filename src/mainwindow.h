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

using namespace common;

namespace Ui {

class MainWindow;
}

using namespace std;


class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    // QCustomLabel
    void mouseCurrentPos();
    void mouseLeftPressed();
    void mouseRightPressed();
    void mouseReleased();
    void mouseLeave();
    //void mouseScroll();
    void keyPressed();

    // QPushButtons
    void evtCalibration();
    void evtVision();

    // QCheckboxs
    void checkboxCamera(int);
    void checkboxImage(int);
    void checkboxVideo(int);

    // QSliders
    void updateHmin(int);
    void updateSmin(int);
    void updateVmin(int);
    void updateHmax(int);
    void updateSmax(int);
    void updateVmax(int);

private:
    calibration calib;
    vision vi;
    SQLite *sql;
    Ui::MainWindow *ui;
    QIcon blockdevice, ksame, kdf, package;

    // QTree
    void buildTrees();
    void addMainItem();
    void addInputDataItem();
    void addCameraCalibrationItem();
    void addBlobFindingItem();
    void addVisualizationItem();
    void addDefinePatternsItem();
    void addExecutionConfig();
    void addCalibrateColors();
    void addVisionOptions();
    void addNetOptions();
    void addExecutionOptions();

    QTreeWidgetItem* mainItem;
    QList<QTreeWidgetItem*> inputData;
    QList<QTreeWidgetItem*> cameraCalibration;
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

    QPushButton *btnDoColorCalib, *btnRunVision;

    QWidget *contLayoutH3;
    vector<QLabel*> lblHeadersHSV;
    vector<QSlider*> slidersHSV;
    vector<QLabel*> lblHeadersPlot;
    vector<QLabel*> lblPlots;
    QLabel *lbl_val;

    QCustomLabel *image;
    QLabel *coordinate_mouse, *zoom_image;

    void initCalibrationColors();
    void finishCalibrationColors();
    void initPlotValues();
    void finishPlotValues();
    void updateValuesHSV();
    void update_hsv_s();
    char calcHex(float);

    QImage *in;

    // Others
    void getAllDevices();
    void defineColors();
    int translateColor(QString);

    vector<string> devices;
    vector<int> colors;
    Calibration _calib;
    State state;
    ExecConfiguration execConfig;
    stringstream ss;
    string hsv_s;
    bool calib_vs_vision;
    bool init;
};

#endif // MAINWINDOW_H
