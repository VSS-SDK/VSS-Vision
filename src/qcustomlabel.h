#ifndef QCUSTOMLABEL_H
#define QCUSTOMLABEL_H

#include "QMouseEvent"
#include "QEvent"
#include "QWheelEvent"
#include "QKeyEvent"
#include "QLabel"
#include "QDebug"

#include "sstream"

using namespace std;

class QCustomLabel : public QLabel
{
    Q_OBJECT
public:
    explicit QCustomLabel(QLabel *parent = 0);

    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void leaveEvent(QEvent *ev);
    void wheelEvent(QWheelEvent *ev);
    void keyPressEvent(QKeyEvent *ev);

    int x, y, delta;
    int last_left_click_x, last_left_click_y;
    int last_right_click_x, last_right_click_y;

signals:
    void Mouse_Pos();
    void Mouse_Left_Pressed();
    void Mouse_Right_Pressed();
    void Mouse_Release();
    void Mouse_Left();
    void Mouse_Scroll();
    void Key_Pressed();

public slots:
};

#endif // QCUSTOMLABEL_H
