/********************************************************************************
** Form generated from reading UI file 'AboutWindow.ui'
**
** Created: Sat 24. Nov 23:55:16 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTWINDOW_H
#define UI_ABOUTWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AboutWindow
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;

    void setupUi(QWidget *AboutWindow)
    {
        if (AboutWindow->objectName().isEmpty())
            AboutWindow->setObjectName(QString::fromUtf8("AboutWindow"));
        AboutWindow->resize(400, 240);
        AboutWindow->setMinimumSize(QSize(400, 240));
        AboutWindow->setMaximumSize(QSize(400, 240));
        label = new QLabel(AboutWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 205, 131, 16));
        label_2 = new QLabel(AboutWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(0, 60, 401, 91));
        QFont font;
        font.setFamily(QString::fromUtf8("Calibri"));
        font.setPointSize(36);
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(AboutWindow);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(348, 220, 46, 13));
        label_4 = new QLabel(AboutWindow);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 220, 131, 16));

        retranslateUi(AboutWindow);

        QMetaObject::connectSlotsByName(AboutWindow);
    } // setupUi

    void retranslateUi(QWidget *AboutWindow)
    {
        AboutWindow->setWindowTitle(QApplication::translate("AboutWindow", "About", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("AboutWindow", "\302\251 Oleynikov Nikolay - 2012", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("AboutWindow", "Boolean Sandbox", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("AboutWindow", "v. 1.3.12", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("AboutWindow", "OleynikovNY@mail.ru", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AboutWindow: public Ui_AboutWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTWINDOW_H
