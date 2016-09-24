/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

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

//! This class is a modification of QLabel, QCustomLabel handle events like: mouse click, mouse move, scrool wheel move and etc.
class QCustomLabel : public QLabel
{
    Q_OBJECT
public:
    explicit QCustomLabel(QLabel *parent = 0);

    //! This method make some adds modificationsin at the Qt method Mouse_Pos().
    void mouseMoveEvent(QMouseEvent *ev);
    //! This method make some adds modificationsin at the Qt method Mouse_Right_Pressed() and Mouse_Left_Pressed().
    void mousePressEvent(QMouseEvent *ev);
    //! This method make some adds modificationsin at the Qt method Mouse_Release().
    void mouseReleaseEvent(QMouseEvent *ev);
    //! This method make some adds modificationsin at the Qt method Mouse_Left().
    void leaveEvent(QEvent *ev);
    //! This method make some adds modificationsin at the Qt method Mouse_Scroll().
    void wheelEvent(QWheelEvent *ev);
    //! This method make some adds modificationsin at the Qt method Key_Pressed().
    void keyPressEvent(QKeyEvent *ev);

    int x, y, delta, volatil;
    int last_left_click_x, last_left_click_y;
    int last_right_click_x, last_right_click_y;

signals:
    //! Send signal of the mouse movement.
    void Mouse_Pos();
    //! Send signal of the mouse left key pressed.
    void Mouse_Left_Pressed();
    //! Send signal of the mouse right key pressed.
    void Mouse_Right_Pressed();
    //! Send signal of the mouse in/out of the label area
    void Mouse_Release();
    //! Send signal asking if the mouse left button is pressed.
    void Mouse_Left();
    //! Send signal of the mouse scroll rolled.
    void Mouse_Scroll();
    //! Send signal of the mouse scroll pressed
    void Key_Pressed();

public slots:
};

#endif // QCUSTOMLABEL_H
