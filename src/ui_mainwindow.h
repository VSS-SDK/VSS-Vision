/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *layoutH1;
    QTreeWidget *treeMain;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *layoutH2;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *layoutH3;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *layoutH3H;
    QWidget *horizontalLayoutWidget_5;
    QHBoxLayout *layoutH4H;
    QWidget *horizontalLayoutWidget_6;
    QHBoxLayout *layoutH5H;
    QWidget *horizontalLayoutWidget_7;
    QHBoxLayout *layoutH9H;
    QWidget *horizontalLayoutWidget_8;
    QHBoxLayout *layoutH6H;
    QWidget *horizontalLayoutWidget_9;
    QHBoxLayout *layoutH7H;
    QWidget *horizontalLayoutWidget_10;
    QHBoxLayout *layoutH8H;
    QWidget *horizontalLayoutWidget_11;
    QHBoxLayout *layoutH4;
    QWidget *horizontalLayoutWidget_12;
    QHBoxLayout *layoutH5;
    QWidget *horizontalLayoutWidget_13;
    QHBoxLayout *layoutH6;
    QWidget *horizontalLayoutWidget_14;
    QHBoxLayout *layoutH7;
    QWidget *horizontalLayoutWidget_15;
    QHBoxLayout *layoutH8;
    QWidget *horizontalLayoutWidget_16;
    QHBoxLayout *layoutH9;
    QWidget *horizontalLayoutWidget_17;
    QHBoxLayout *layoutH10H;
    QWidget *horizontalLayoutWidget_18;
    QHBoxLayout *layoutH10;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1119, 730);
        MainWindow->setMinimumSize(QSize(1119, 730));
        MainWindow->setMaximumSize(QSize(1119, 730));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 341, 661));
        layoutH1 = new QHBoxLayout(horizontalLayoutWidget);
        layoutH1->setSpacing(5);
        layoutH1->setContentsMargins(11, 11, 11, 11);
        layoutH1->setObjectName(QStringLiteral("layoutH1"));
        layoutH1->setContentsMargins(5, 5, 5, 0);
        treeMain = new QTreeWidget(horizontalLayoutWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeMain->setHeaderItem(__qtreewidgetitem);
        treeMain->setObjectName(QStringLiteral("treeMain"));

        layoutH1->addWidget(treeMain);

        horizontalLayoutWidget_2 = new QWidget(centralWidget);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(340, 0, 771, 491));
        layoutH2 = new QHBoxLayout(horizontalLayoutWidget_2);
        layoutH2->setSpacing(6);
        layoutH2->setContentsMargins(11, 11, 11, 11);
        layoutH2->setObjectName(QStringLiteral("layoutH2"));
        layoutH2->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget_3 = new QWidget(centralWidget);
        horizontalLayoutWidget_3->setObjectName(QStringLiteral("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(410, 520, 100, 141));
        layoutH3 = new QHBoxLayout(horizontalLayoutWidget_3);
        layoutH3->setSpacing(6);
        layoutH3->setContentsMargins(11, 11, 11, 11);
        layoutH3->setObjectName(QStringLiteral("layoutH3"));
        layoutH3->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget_4 = new QWidget(centralWidget);
        horizontalLayoutWidget_4->setObjectName(QStringLiteral("horizontalLayoutWidget_4"));
        horizontalLayoutWidget_4->setGeometry(QRect(410, 490, 100, 31));
        layoutH3H = new QHBoxLayout(horizontalLayoutWidget_4);
        layoutH3H->setSpacing(6);
        layoutH3H->setContentsMargins(11, 11, 11, 11);
        layoutH3H->setObjectName(QStringLiteral("layoutH3H"));
        layoutH3H->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget_5 = new QWidget(centralWidget);
        horizontalLayoutWidget_5->setObjectName(QStringLiteral("horizontalLayoutWidget_5"));
        horizontalLayoutWidget_5->setGeometry(QRect(510, 490, 100, 31));
        layoutH4H = new QHBoxLayout(horizontalLayoutWidget_5);
        layoutH4H->setSpacing(6);
        layoutH4H->setContentsMargins(11, 11, 11, 11);
        layoutH4H->setObjectName(QStringLiteral("layoutH4H"));
        layoutH4H->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget_6 = new QWidget(centralWidget);
        horizontalLayoutWidget_6->setObjectName(QStringLiteral("horizontalLayoutWidget_6"));
        horizontalLayoutWidget_6->setGeometry(QRect(610, 490, 100, 31));
        layoutH5H = new QHBoxLayout(horizontalLayoutWidget_6);
        layoutH5H->setSpacing(6);
        layoutH5H->setContentsMargins(11, 11, 11, 11);
        layoutH5H->setObjectName(QStringLiteral("layoutH5H"));
        layoutH5H->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget_7 = new QWidget(centralWidget);
        horizontalLayoutWidget_7->setObjectName(QStringLiteral("horizontalLayoutWidget_7"));
        horizontalLayoutWidget_7->setGeometry(QRect(1010, 490, 100, 31));
        layoutH9H = new QHBoxLayout(horizontalLayoutWidget_7);
        layoutH9H->setSpacing(6);
        layoutH9H->setContentsMargins(11, 11, 11, 11);
        layoutH9H->setObjectName(QStringLiteral("layoutH9H"));
        layoutH9H->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget_8 = new QWidget(centralWidget);
        horizontalLayoutWidget_8->setObjectName(QStringLiteral("horizontalLayoutWidget_8"));
        horizontalLayoutWidget_8->setGeometry(QRect(710, 490, 100, 31));
        layoutH6H = new QHBoxLayout(horizontalLayoutWidget_8);
        layoutH6H->setSpacing(6);
        layoutH6H->setContentsMargins(11, 11, 11, 11);
        layoutH6H->setObjectName(QStringLiteral("layoutH6H"));
        layoutH6H->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget_9 = new QWidget(centralWidget);
        horizontalLayoutWidget_9->setObjectName(QStringLiteral("horizontalLayoutWidget_9"));
        horizontalLayoutWidget_9->setGeometry(QRect(810, 490, 100, 31));
        layoutH7H = new QHBoxLayout(horizontalLayoutWidget_9);
        layoutH7H->setSpacing(6);
        layoutH7H->setContentsMargins(11, 11, 11, 11);
        layoutH7H->setObjectName(QStringLiteral("layoutH7H"));
        layoutH7H->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget_10 = new QWidget(centralWidget);
        horizontalLayoutWidget_10->setObjectName(QStringLiteral("horizontalLayoutWidget_10"));
        horizontalLayoutWidget_10->setGeometry(QRect(910, 490, 100, 31));
        layoutH8H = new QHBoxLayout(horizontalLayoutWidget_10);
        layoutH8H->setSpacing(6);
        layoutH8H->setContentsMargins(11, 11, 11, 11);
        layoutH8H->setObjectName(QStringLiteral("layoutH8H"));
        layoutH8H->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget_11 = new QWidget(centralWidget);
        horizontalLayoutWidget_11->setObjectName(QStringLiteral("horizontalLayoutWidget_11"));
        horizontalLayoutWidget_11->setGeometry(QRect(510, 520, 100, 141));
        layoutH4 = new QHBoxLayout(horizontalLayoutWidget_11);
        layoutH4->setSpacing(6);
        layoutH4->setContentsMargins(11, 11, 11, 11);
        layoutH4->setObjectName(QStringLiteral("layoutH4"));
        layoutH4->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget_12 = new QWidget(centralWidget);
        horizontalLayoutWidget_12->setObjectName(QStringLiteral("horizontalLayoutWidget_12"));
        horizontalLayoutWidget_12->setGeometry(QRect(610, 520, 100, 141));
        layoutH5 = new QHBoxLayout(horizontalLayoutWidget_12);
        layoutH5->setSpacing(6);
        layoutH5->setContentsMargins(11, 11, 11, 11);
        layoutH5->setObjectName(QStringLiteral("layoutH5"));
        layoutH5->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget_13 = new QWidget(centralWidget);
        horizontalLayoutWidget_13->setObjectName(QStringLiteral("horizontalLayoutWidget_13"));
        horizontalLayoutWidget_13->setGeometry(QRect(710, 520, 100, 141));
        layoutH6 = new QHBoxLayout(horizontalLayoutWidget_13);
        layoutH6->setSpacing(6);
        layoutH6->setContentsMargins(11, 11, 11, 11);
        layoutH6->setObjectName(QStringLiteral("layoutH6"));
        layoutH6->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget_14 = new QWidget(centralWidget);
        horizontalLayoutWidget_14->setObjectName(QStringLiteral("horizontalLayoutWidget_14"));
        horizontalLayoutWidget_14->setGeometry(QRect(810, 520, 100, 141));
        layoutH7 = new QHBoxLayout(horizontalLayoutWidget_14);
        layoutH7->setSpacing(6);
        layoutH7->setContentsMargins(11, 11, 11, 11);
        layoutH7->setObjectName(QStringLiteral("layoutH7"));
        layoutH7->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget_15 = new QWidget(centralWidget);
        horizontalLayoutWidget_15->setObjectName(QStringLiteral("horizontalLayoutWidget_15"));
        horizontalLayoutWidget_15->setGeometry(QRect(910, 520, 100, 141));
        layoutH8 = new QHBoxLayout(horizontalLayoutWidget_15);
        layoutH8->setSpacing(6);
        layoutH8->setContentsMargins(11, 11, 11, 11);
        layoutH8->setObjectName(QStringLiteral("layoutH8"));
        layoutH8->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget_16 = new QWidget(centralWidget);
        horizontalLayoutWidget_16->setObjectName(QStringLiteral("horizontalLayoutWidget_16"));
        horizontalLayoutWidget_16->setGeometry(QRect(1010, 520, 100, 141));
        layoutH9 = new QHBoxLayout(horizontalLayoutWidget_16);
        layoutH9->setSpacing(6);
        layoutH9->setContentsMargins(11, 11, 11, 11);
        layoutH9->setObjectName(QStringLiteral("layoutH9"));
        layoutH9->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget_17 = new QWidget(centralWidget);
        horizontalLayoutWidget_17->setObjectName(QStringLiteral("horizontalLayoutWidget_17"));
        horizontalLayoutWidget_17->setGeometry(QRect(340, 490, 70, 31));
        layoutH10H = new QHBoxLayout(horizontalLayoutWidget_17);
        layoutH10H->setSpacing(6);
        layoutH10H->setContentsMargins(11, 11, 11, 11);
        layoutH10H->setObjectName(QStringLiteral("layoutH10H"));
        layoutH10H->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget_18 = new QWidget(centralWidget);
        horizontalLayoutWidget_18->setObjectName(QStringLiteral("horizontalLayoutWidget_18"));
        horizontalLayoutWidget_18->setGeometry(QRect(340, 520, 70, 140));
        layoutH10 = new QHBoxLayout(horizontalLayoutWidget_18);
        layoutH10->setSpacing(6);
        layoutH10->setContentsMargins(11, 11, 11, 11);
        layoutH10->setObjectName(QStringLiteral("layoutH10"));
        layoutH10->setContentsMargins(0, 0, 0, 0);
        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1119, 25));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "VSS-Vision", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
