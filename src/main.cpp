/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "mainwindow.h"
#include <QApplication>
#include <QtCore>
#include "calibration.h"
#include "common.h"

using namespace common;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();

    /*SQLite sqlite("../data/main.db", "passwd");
    Calibration c;
    c.comment = "debug";
    sqlite.insert_calibration(c);

    cout << "query.str()" << endl;

    return 0;*/
}
