#ifndef _ABOUTWINDOW_H
#define _ABOUTWINDOW_H

#include <QDialog>
#include "ui_WindowAbout.h"

class AboutWindow : public QDialog
{

    public:
        AboutWindow(QWidget* parent) : QDialog(parent)
        {

            this->ui.setupUi(this);

        }

    private:
        Ui::AboutWindow ui;

};

#endif // _ABOUTWINDOW_H
