/********************************************************************************
** Form generated from reading UI file 'highlighter.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HIGHLIGHTER_H
#define UI_HIGHLIGHTER_H

#include <QtCore/QVariant>
#include <QtGui/QSyntaxHighlighter>
#include <QtWidgets/QApplication>

QT_BEGIN_NAMESPACE

class Ui_highlighter
{
public:

    void setupUi(QSyntaxHighlighter *highlighter)
    {
        if (highlighter->objectName().isEmpty())
            highlighter->setObjectName(QString::fromUtf8("highlighter"));
        highlighter->resize(400, 300);

        retranslateUi(highlighter);

        QMetaObject::connectSlotsByName(highlighter);
    } // setupUi

    void retranslateUi(QSyntaxHighlighter *highlighter)
    {
        highlighter->setWindowTitle(QApplication::translate("highlighter", "highlighter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class highlighter: public Ui_highlighter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HIGHLIGHTER_H
