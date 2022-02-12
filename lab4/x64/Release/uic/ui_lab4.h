/********************************************************************************
** Form generated from reading UI file 'lab4.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAB4_H
#define UI_LAB4_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_lab4Class
{
public:
    QWidget *centralWidget;
    QToolBar *toolbar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *lab4Class)
    {
        if (lab4Class->objectName().isEmpty())
            lab4Class->setObjectName(QString::fromUtf8("lab4Class"));
        lab4Class->resize(600, 400);
        centralWidget = new QWidget(lab4Class);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        lab4Class->setCentralWidget(centralWidget);
        toolbar = new QToolBar(lab4Class);
        toolbar->setObjectName(QString::fromUtf8("toolbar"));
        lab4Class->addToolBar(Qt::TopToolBarArea, toolbar);
        statusBar = new QStatusBar(lab4Class);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        lab4Class->setStatusBar(statusBar);

        retranslateUi(lab4Class);

        QMetaObject::connectSlotsByName(lab4Class);
    } // setupUi

    void retranslateUi(QMainWindow *lab4Class)
    {
        lab4Class->setWindowTitle(QApplication::translate("lab4Class", "lab4", nullptr));
    } // retranslateUi

};

namespace Ui {
    class lab4Class: public Ui_lab4Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAB4_H
