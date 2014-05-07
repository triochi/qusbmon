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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QAction *actionStartStop;
    QAction *actionExit;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QSplitter *splitter_2;
    QSplitter *splitter;
    QTreeView *packetsView;
    QTreeWidget *packetTree;
    QTreeView *devicesView;
    QMenuBar *menubar;
    QMenu *menu_Capture;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QStringLiteral("MainWindowClass"));
        MainWindowClass->resize(533, 432);
        actionStartStop = new QAction(MainWindowClass);
        actionStartStop->setObjectName(QStringLiteral("actionStartStop"));
        actionStartStop->setCheckable(true);
        actionExit = new QAction(MainWindowClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        centralwidget = new QWidget(MainWindowClass);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        splitter_2 = new QSplitter(centralwidget);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setOrientation(Qt::Horizontal);
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName(QStringLiteral("splitter"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy);
        splitter->setOrientation(Qt::Vertical);
        packetsView = new QTreeView(splitter);
        packetsView->setObjectName(QStringLiteral("packetsView"));
        packetsView->setRootIsDecorated(false);
        packetsView->setUniformRowHeights(true);
        packetsView->setAnimated(true);
        splitter->addWidget(packetsView);
        packetTree = new QTreeWidget(splitter);
        packetTree->setObjectName(QStringLiteral("packetTree"));
        sizePolicy.setHeightForWidth(packetTree->sizePolicy().hasHeightForWidth());
        packetTree->setSizePolicy(sizePolicy);
        packetTree->setAlternatingRowColors(true);
        packetTree->setHeaderHidden(true);
        packetTree->setColumnCount(0);
        splitter->addWidget(packetTree);
        splitter_2->addWidget(splitter);
        devicesView = new QTreeView(splitter_2);
        devicesView->setObjectName(QStringLiteral("devicesView"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(2);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(devicesView->sizePolicy().hasHeightForWidth());
        devicesView->setSizePolicy(sizePolicy1);
        splitter_2->addWidget(devicesView);

        gridLayout->addWidget(splitter_2, 0, 0, 1, 1);

        MainWindowClass->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindowClass);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 533, 20));
        menu_Capture = new QMenu(menubar);
        menu_Capture->setObjectName(QStringLiteral("menu_Capture"));
        MainWindowClass->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindowClass);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindowClass->setStatusBar(statusbar);

        menubar->addAction(menu_Capture->menuAction());
        menu_Capture->addAction(actionStartStop);
        menu_Capture->addSeparator();
        menu_Capture->addAction(actionExit);

        retranslateUi(MainWindowClass);

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "QUSBMon", 0));
        actionStartStop->setText(QApplication::translate("MainWindowClass", "&Start/Stop", 0));
        actionStartStop->setShortcut(QApplication::translate("MainWindowClass", "Alt+S", 0));
        actionExit->setText(QApplication::translate("MainWindowClass", "E&xit", 0));
        actionExit->setShortcut(QApplication::translate("MainWindowClass", "Alt+X", 0));
#ifndef QT_NO_TOOLTIP
        packetsView->setToolTip(QApplication::translate("MainWindowClass", "packetsview", 0));
#endif // QT_NO_TOOLTIP
        menu_Capture->setTitle(QApplication::translate("MainWindowClass", "&Capture", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
