#-------------------------------------------------
#
# Project created by QtCreator 2016-03-10T05:04:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VSS-Vision
TEMPLATE = app

CONFIG += console


INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib \
    -lopencv_core \
    -lopencv_imgproc \
    -lopencv_highgui \
    -lopencv_ml \
    -lopencv_video \
    -lopencv_features2d \
    -lopencv_calib3d \
    -lopencv_objdetect \
    -lopencv_flann \
    -lopencv_shape \
    -lopencv_stitching \
    -lopencv_videostab \
    -lopencv_videoio \
    -lopencv_imgcodecs \
    -lm \
    -l sqlite3 \
    -lprotobuf \
    -pthread \
    -lpthread \
    -lzmq


SOURCES += main.cpp\
        mainwindow.cpp \
    QtOpenCV.cpp \
    common.cpp \
    calibration.cpp \
    sqlite.cpp \
    vision.cpp \
    qcustomlabel.cpp \
    VSS-Interface/cpp/state.pb.cc \
    VSS-Interface/cpp/command.pb.cc \
    VSS-Interface/cpp/interface.cpp \
    kalman.cpp

HEADERS  += mainwindow.h \
    QtOpenCV.h \
    common.h \
    calibration.h \
    sqlite.h \
    vision.h \
    qcustomlabel.h \
    VSS-Interface/cpp/state.pb.h \
    VSS-Interface/cpp/command.pb.h \
    VSS-Interface/cpp/interface.h \
    kalman.h

FORMS    += mainwindow.ui


RESOURCES += \
    resources.qrc

OTHER_FILES += \
    icons/3d.png \
    icons/arrow-left.png \
    icons/arrow-right.png \
    icons/blockdevice.png \
    icons/camera-test.png \
    icons/camera-unmount.png \
    icons/commandprompt.png \
    icons/database.png \
    icons/dialog-error.png \
    icons/dialog-information.png \
    icons/dialog-warning.png \
    icons/document-new.png \
    icons/document-open.png \
    icons/document-properties.png \
    icons/document-save.png \
    icons/kdf.png \
    icons/kllckety.png \
    icons/ksame.png \
    icons/media-playback-pause.png \
    icons/media-playback-start.png \
    icons/media-playback-stop.png \
    icons/media-record.png \
    icons/media-seek-backward.png \
    icons/media-seek-forward.png \
    icons/media-skip-backward.png \
    icons/media-skip-forward.png \
    icons/package.png \
    icons/view-fullscreen.png \
    images/model.jpg

DISTFILES += \
    protos/state.proto \
    protos/protos.make \
    protos/command.proto
