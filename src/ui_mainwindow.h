/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
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
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
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
    QWidget *horizontalLayoutWidget_19;
    QHBoxLayout *layoutList;
    QTreeWidget *treeList;
    QWidget *horizontalLayoutWidget_20;
    QHBoxLayout *layoutListH;
    QPushButton *btnSave;
    QWidget *horizontalLayoutWidget_21;
    QHBoxLayout *layoutListC;
    QTextBrowser *multiTex;
    QWidget *horizontalLayoutWidget_22;
    QHBoxLayout *layoutListH_2;
    QLineEdit *saveVal;
    QWidget *horizontalLayoutWidget_23;
    QHBoxLayout *layoutBottom;
    QLabel *label;
    QWidget *horizontalLayoutWidget_24;
    QHBoxLayout *layoutBottom_3;
    QWidget *horizontalLayoutWidget_25;
    QHBoxLayout *layoutBottom_4;
    QWidget *horizontalLayoutWidget_26;
    QHBoxLayout *layoutBottom_5;
    QWidget *horizontalLayoutWidget_27;
    QHBoxLayout *layoutListH_3;
    QLineEdit *loadVal;
    QWidget *horizontalLayoutWidget_28;
    QHBoxLayout *layoutListH_4;
    QPushButton *btnLoad;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1248, 730);
        MainWindow->setMinimumSize(QSize(1248, 730));
        MainWindow->setMaximumSize(QSize(1248, 730));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 311, 661));
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
        horizontalLayoutWidget_2->setGeometry(QRect(310, 0, 681, 491));
        layoutH2 = new QHBoxLayout(horizontalLayoutWidget_2);
        layoutH2->setSpacing(6);
        layoutH2->setContentsMargins(11, 11, 11, 11);
        layoutH2->setObjectName(QStringLiteral("layoutH2"));
        layoutH2->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget_3 = new QWidget(centralWidget);
        horizontalLayoutWidget_3->setObjectName(QStringLiteral("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(360, 520, 91, 111));
        layoutH3 = new QHBoxLayout(horizontalLayoutWidget_3);
        layoutH3->setSpacing(6);
        layoutH3->setContentsMargins(11, 11, 11, 11);
        layoutH3->setObjectName(QStringLiteral("layoutH3"));
        layoutH3->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget_4 = new QWidget(centralWidget);
        horizontalLayoutWidget_4->setObjectName(QStringLiteral("horizontalLayoutWidget_4"));
        horizontalLayoutWidget_4->setGeometry(QRect(360, 490, 91, 31));
        layoutH3H = new QHBoxLayout(horizontalLayoutWidget_4);
        layoutH3H->setSpacing(6);
        layoutH3H->setContentsMargins(11, 11, 11, 11);
        layoutH3H->setObjectName(QStringLiteral("layoutH3H"));
        layoutH3H->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget_5 = new QWidget(centralWidget);
        horizontalLayoutWidget_5->setObjectName(QStringLiteral("horizontalLayoutWidget_5"));
        horizontalLayoutWidget_5->setGeometry(QRect(450, 490, 91, 31));
        layoutH4H = new QHBoxLayout(horizontalLayoutWidget_5);
        layoutH4H->setSpacing(6);
        layoutH4H->setContentsMargins(11, 11, 11, 11);
        layoutH4H->setObjectName(QStringLiteral("layoutH4H"));
        layoutH4H->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget_6 = new QWidget(centralWidget);
        horizontalLayoutWidget_6->setObjectName(QStringLiteral("horizontalLayoutWidget_6"));
        horizontalLayoutWidget_6->setGeometry(QRect(540, 490, 91, 31));
        layoutH5H = new QHBoxLayout(horizontalLayoutWidget_6);
        layoutH5H->setSpacing(6);
        layoutH5H->setContentsMargins(11, 11, 11, 11);
        layoutH5H->setObjectName(QStringLiteral("layoutH5H"));
        layoutH5H->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget_7 = new QWidget(centralWidget);
        horizontalLayoutWidget_7->setObjectName(QStringLiteral("horizontalLayoutWidget_7"));
        horizontalLayoutWidget_7->setGeometry(QRect(900, 490, 91, 31));
        layoutH9H = new QHBoxLayout(horizontalLayoutWidget_7);
        layoutH9H->setSpacing(6);
        layoutH9H->setContentsMargins(11, 11, 11, 11);
        layoutH9H->setObjectName(QStringLiteral("layoutH9H"));
        layoutH9H->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget_8 = new QWidget(centralWidget);
        horizontalLayoutWidget_8->setObjectName(QStringLiteral("horizontalLayoutWidget_8"));
        horizontalLayoutWidget_8->setGeometry(QRect(630, 490, 91, 31));
        layoutH6H = new QHBoxLayout(horizontalLayoutWidget_8);
        layoutH6H->setSpacing(6);
        layoutH6H->setContentsMargins(11, 11, 11, 11);
        layoutH6H->setObjectName(QStringLiteral("layoutH6H"));
        layoutH6H->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget_9 = new QWidget(centralWidget);
        horizontalLayoutWidget_9->setObjectName(QStringLiteral("horizontalLayoutWidget_9"));
        horizontalLayoutWidget_9->setGeometry(QRect(720, 490, 91, 31));
        layoutH7H = new QHBoxLayout(horizontalLayoutWidget_9);
        layoutH7H->setSpacing(6);
        layoutH7H->setContentsMargins(11, 11, 11, 11);
        layoutH7H->setObjectName(QStringLiteral("layoutH7H"));
        layoutH7H->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget_10 = new QWidget(centralWidget);
        horizontalLayoutWidget_10->setObjectName(QStringLiteral("horizontalLayoutWidget_10"));
        horizontalLayoutWidget_10->setGeometry(QRect(810, 490, 91, 31));
        layoutH8H = new QHBoxLayout(horizontalLayoutWidget_10);
        layoutH8H->setSpacing(6);
        layoutH8H->setContentsMargins(11, 11, 11, 11);
        layoutH8H->setObjectName(QStringLiteral("layoutH8H"));
        layoutH8H->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget_11 = new QWidget(centralWidget);
        horizontalLayoutWidget_11->setObjectName(QStringLiteral("horizontalLayoutWidget_11"));
        horizontalLayoutWidget_11->setGeometry(QRect(450, 520, 91, 111));
        layoutH4 = new QHBoxLayout(horizontalLayoutWidget_11);
        layoutH4->setSpacing(6);
        layoutH4->setContentsMargins(11, 11, 11, 11);
        layoutH4->setObjectName(QStringLiteral("layoutH4"));
        layoutH4->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget_12 = new QWidget(centralWidget);
        horizontalLayoutWidget_12->setObjectName(QStringLiteral("horizontalLayoutWidget_12"));
        horizontalLayoutWidget_12->setGeometry(QRect(540, 520, 91, 111));
        layoutH5 = new QHBoxLayout(horizontalLayoutWidget_12);
        layoutH5->setSpacing(6);
        layoutH5->setContentsMargins(11, 11, 11, 11);
        layoutH5->setObjectName(QStringLiteral("layoutH5"));
        layoutH5->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget_13 = new QWidget(centralWidget);
        horizontalLayoutWidget_13->setObjectName(QStringLiteral("horizontalLayoutWidget_13"));
        horizontalLayoutWidget_13->setGeometry(QRect(630, 520, 91, 111));
        layoutH6 = new QHBoxLayout(horizontalLayoutWidget_13);
        layoutH6->setSpacing(6);
        layoutH6->setContentsMargins(11, 11, 11, 11);
        layoutH6->setObjectName(QStringLiteral("layoutH6"));
        layoutH6->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget_14 = new QWidget(centralWidget);
        horizontalLayoutWidget_14->setObjectName(QStringLiteral("horizontalLayoutWidget_14"));
        horizontalLayoutWidget_14->setGeometry(QRect(720, 520, 91, 111));
        layoutH7 = new QHBoxLayout(horizontalLayoutWidget_14);
        layoutH7->setSpacing(6);
        layoutH7->setContentsMargins(11, 11, 11, 11);
        layoutH7->setObjectName(QStringLiteral("layoutH7"));
        layoutH7->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget_15 = new QWidget(centralWidget);
        horizontalLayoutWidget_15->setObjectName(QStringLiteral("horizontalLayoutWidget_15"));
        horizontalLayoutWidget_15->setGeometry(QRect(810, 520, 91, 111));
        layoutH8 = new QHBoxLayout(horizontalLayoutWidget_15);
        layoutH8->setSpacing(6);
        layoutH8->setContentsMargins(11, 11, 11, 11);
        layoutH8->setObjectName(QStringLiteral("layoutH8"));
        layoutH8->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget_16 = new QWidget(centralWidget);
        horizontalLayoutWidget_16->setObjectName(QStringLiteral("horizontalLayoutWidget_16"));
        horizontalLayoutWidget_16->setGeometry(QRect(900, 520, 91, 111));
        layoutH9 = new QHBoxLayout(horizontalLayoutWidget_16);
        layoutH9->setSpacing(6);
        layoutH9->setContentsMargins(11, 11, 11, 11);
        layoutH9->setObjectName(QStringLiteral("layoutH9"));
        layoutH9->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget_17 = new QWidget(centralWidget);
        horizontalLayoutWidget_17->setObjectName(QStringLiteral("horizontalLayoutWidget_17"));
        horizontalLayoutWidget_17->setGeometry(QRect(310, 490, 51, 31));
        layoutH10H = new QHBoxLayout(horizontalLayoutWidget_17);
        layoutH10H->setSpacing(6);
        layoutH10H->setContentsMargins(11, 11, 11, 11);
        layoutH10H->setObjectName(QStringLiteral("layoutH10H"));
        layoutH10H->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget_18 = new QWidget(centralWidget);
        horizontalLayoutWidget_18->setObjectName(QStringLiteral("horizontalLayoutWidget_18"));
        horizontalLayoutWidget_18->setGeometry(QRect(310, 520, 51, 111));
        layoutH10 = new QHBoxLayout(horizontalLayoutWidget_18);
        layoutH10->setSpacing(6);
        layoutH10->setContentsMargins(11, 11, 11, 11);
        layoutH10->setObjectName(QStringLiteral("layoutH10"));
        layoutH10->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget_19 = new QWidget(centralWidget);
        horizontalLayoutWidget_19->setObjectName(QStringLiteral("horizontalLayoutWidget_19"));
        horizontalLayoutWidget_19->setGeometry(QRect(990, 0, 251, 486));
        layoutList = new QHBoxLayout(horizontalLayoutWidget_19);
        layoutList->setSpacing(6);
        layoutList->setContentsMargins(11, 11, 11, 11);
        layoutList->setObjectName(QStringLiteral("layoutList"));
        layoutList->setContentsMargins(5, 5, 0, 0);
        treeList = new QTreeWidget(horizontalLayoutWidget_19);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem();
        __qtreewidgetitem1->setText(0, QStringLiteral("1"));
        treeList->setHeaderItem(__qtreewidgetitem1);
        treeList->setObjectName(QStringLiteral("treeList"));
        treeList->setMinimumSize(QSize(0, 480));
        treeList->setMaximumSize(QSize(16777215, 480));

        layoutList->addWidget(treeList);

        horizontalLayoutWidget_20 = new QWidget(centralWidget);
        horizontalLayoutWidget_20->setObjectName(QStringLiteral("horizontalLayoutWidget_20"));
        horizontalLayoutWidget_20->setGeometry(QRect(990, 490, 101, 31));
        layoutListH = new QHBoxLayout(horizontalLayoutWidget_20);
        layoutListH->setSpacing(6);
        layoutListH->setContentsMargins(11, 11, 11, 11);
        layoutListH->setObjectName(QStringLiteral("layoutListH"));
        layoutListH->setContentsMargins(0, 0, 7, 0);
        btnSave = new QPushButton(horizontalLayoutWidget_20);
        btnSave->setObjectName(QStringLiteral("btnSave"));
        btnSave->setMinimumSize(QSize(85, 0));
        btnSave->setMaximumSize(QSize(85, 16777215));

        layoutListH->addWidget(btnSave);

        horizontalLayoutWidget_21 = new QWidget(centralWidget);
        horizontalLayoutWidget_21->setObjectName(QStringLiteral("horizontalLayoutWidget_21"));
        horizontalLayoutWidget_21->setGeometry(QRect(990, 550, 251, 111));
        layoutListC = new QHBoxLayout(horizontalLayoutWidget_21);
        layoutListC->setSpacing(6);
        layoutListC->setContentsMargins(11, 11, 11, 11);
        layoutListC->setObjectName(QStringLiteral("layoutListC"));
        layoutListC->setSizeConstraint(QLayout::SetMinimumSize);
        layoutListC->setContentsMargins(3, 5, 0, 0);
        multiTex = new QTextBrowser(horizontalLayoutWidget_21);
        multiTex->setObjectName(QStringLiteral("multiTex"));
        multiTex->setMinimumSize(QSize(246, 0));
        multiTex->setMaximumSize(QSize(246, 16777215));

        layoutListC->addWidget(multiTex);

        horizontalLayoutWidget_22 = new QWidget(centralWidget);
        horizontalLayoutWidget_22->setObjectName(QStringLiteral("horizontalLayoutWidget_22"));
        horizontalLayoutWidget_22->setGeometry(QRect(1080, 490, 161, 31));
        layoutListH_2 = new QHBoxLayout(horizontalLayoutWidget_22);
        layoutListH_2->setSpacing(6);
        layoutListH_2->setContentsMargins(11, 11, 11, 11);
        layoutListH_2->setObjectName(QStringLiteral("layoutListH_2"));
        layoutListH_2->setContentsMargins(0, 0, 0, 0);
        saveVal = new QLineEdit(horizontalLayoutWidget_22);
        saveVal->setObjectName(QStringLiteral("saveVal"));

        layoutListH_2->addWidget(saveVal);

        horizontalLayoutWidget_23 = new QWidget(centralWidget);
        horizontalLayoutWidget_23->setObjectName(QStringLiteral("horizontalLayoutWidget_23"));
        horizontalLayoutWidget_23->setGeometry(QRect(320, 630, 401, 31));
        layoutBottom = new QHBoxLayout(horizontalLayoutWidget_23);
        layoutBottom->setSpacing(6);
        layoutBottom->setContentsMargins(11, 11, 11, 11);
        layoutBottom->setObjectName(QStringLiteral("layoutBottom"));
        layoutBottom->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(horizontalLayoutWidget_23);
        label->setObjectName(QStringLiteral("label"));

        layoutBottom->addWidget(label);

        horizontalLayoutWidget_24 = new QWidget(centralWidget);
        horizontalLayoutWidget_24->setObjectName(QStringLiteral("horizontalLayoutWidget_24"));
        horizontalLayoutWidget_24->setGeometry(QRect(720, 630, 91, 31));
        layoutBottom_3 = new QHBoxLayout(horizontalLayoutWidget_24);
        layoutBottom_3->setSpacing(6);
        layoutBottom_3->setContentsMargins(11, 11, 11, 11);
        layoutBottom_3->setObjectName(QStringLiteral("layoutBottom_3"));
        layoutBottom_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget_25 = new QWidget(centralWidget);
        horizontalLayoutWidget_25->setObjectName(QStringLiteral("horizontalLayoutWidget_25"));
        horizontalLayoutWidget_25->setGeometry(QRect(810, 630, 91, 31));
        layoutBottom_4 = new QHBoxLayout(horizontalLayoutWidget_25);
        layoutBottom_4->setSpacing(6);
        layoutBottom_4->setContentsMargins(11, 11, 11, 11);
        layoutBottom_4->setObjectName(QStringLiteral("layoutBottom_4"));
        layoutBottom_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget_26 = new QWidget(centralWidget);
        horizontalLayoutWidget_26->setObjectName(QStringLiteral("horizontalLayoutWidget_26"));
        horizontalLayoutWidget_26->setGeometry(QRect(900, 630, 91, 31));
        layoutBottom_5 = new QHBoxLayout(horizontalLayoutWidget_26);
        layoutBottom_5->setSpacing(6);
        layoutBottom_5->setContentsMargins(11, 11, 11, 11);
        layoutBottom_5->setObjectName(QStringLiteral("layoutBottom_5"));
        layoutBottom_5->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget_27 = new QWidget(centralWidget);
        horizontalLayoutWidget_27->setObjectName(QStringLiteral("horizontalLayoutWidget_27"));
        horizontalLayoutWidget_27->setGeometry(QRect(1080, 520, 161, 31));
        layoutListH_3 = new QHBoxLayout(horizontalLayoutWidget_27);
        layoutListH_3->setSpacing(6);
        layoutListH_3->setContentsMargins(11, 11, 11, 11);
        layoutListH_3->setObjectName(QStringLiteral("layoutListH_3"));
        layoutListH_3->setContentsMargins(0, 0, 0, 0);
        loadVal = new QLineEdit(horizontalLayoutWidget_27);
        loadVal->setObjectName(QStringLiteral("loadVal"));

        layoutListH_3->addWidget(loadVal);

        horizontalLayoutWidget_28 = new QWidget(centralWidget);
        horizontalLayoutWidget_28->setObjectName(QStringLiteral("horizontalLayoutWidget_28"));
        horizontalLayoutWidget_28->setGeometry(QRect(990, 520, 101, 31));
        layoutListH_4 = new QHBoxLayout(horizontalLayoutWidget_28);
        layoutListH_4->setSpacing(6);
        layoutListH_4->setContentsMargins(11, 11, 11, 11);
        layoutListH_4->setObjectName(QStringLiteral("layoutListH_4"));
        layoutListH_4->setContentsMargins(0, 0, 7, 0);
        btnLoad = new QPushButton(horizontalLayoutWidget_28);
        btnLoad->setObjectName(QStringLiteral("btnLoad"));
        btnLoad->setMinimumSize(QSize(85, 0));
        btnLoad->setMaximumSize(QSize(85, 16777215));

        layoutListH_4->addWidget(btnLoad);

        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1248, 25));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "VSS-Vision", 0));
        btnSave->setText(QApplication::translate("MainWindow", "Save", 0));
        label->setText(QApplication::translate("MainWindow", "IEEE Very Small Size [Soccer]  -  Computer Vision System", 0));
        btnLoad->setText(QApplication::translate("MainWindow", "Load", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
