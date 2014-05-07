/********************************************************************************
** Form generated from reading UI file 'deviceselect.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEVICESELECT_H
#define UI_DEVICESELECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTreeView>

QT_BEGIN_NAMESPACE

class Ui_deviceSelectClass
{
public:
    QGridLayout *gridLayout;
    QTreeView *devicesView;
    QDialogButtonBox *buttons;

    void setupUi(QDialog *deviceSelectClass)
    {
        if (deviceSelectClass->objectName().isEmpty())
            deviceSelectClass->setObjectName(QStringLiteral("deviceSelectClass"));
        deviceSelectClass->setWindowModality(Qt::ApplicationModal);
        deviceSelectClass->resize(355, 489);
        gridLayout = new QGridLayout(deviceSelectClass);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        devicesView = new QTreeView(deviceSelectClass);
        devicesView->setObjectName(QStringLiteral("devicesView"));
        devicesView->setAlternatingRowColors(true);
        devicesView->setUniformRowHeights(true);
        devicesView->setHeaderHidden(true);

        gridLayout->addWidget(devicesView, 0, 0, 1, 1);

        buttons = new QDialogButtonBox(deviceSelectClass);
        buttons->setObjectName(QStringLiteral("buttons"));
        buttons->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttons->setCenterButtons(true);

        gridLayout->addWidget(buttons, 1, 0, 1, 1);


        retranslateUi(deviceSelectClass);
        QObject::connect(buttons, SIGNAL(rejected()), deviceSelectClass, SLOT(reject()));
        QObject::connect(buttons, SIGNAL(accepted()), deviceSelectClass, SLOT(accept()));

        QMetaObject::connectSlotsByName(deviceSelectClass);
    } // setupUi

    void retranslateUi(QDialog *deviceSelectClass)
    {
        deviceSelectClass->setWindowTitle(QApplication::translate("deviceSelectClass", "Select a capture device", 0));
    } // retranslateUi

};

namespace Ui {
    class deviceSelectClass: public Ui_deviceSelectClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEVICESELECT_H
