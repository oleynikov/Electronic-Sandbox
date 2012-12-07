#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QTranslator>
#include <QLocale>
#include <QSystemLocale>

#include "_Configuration.h"
#include "_WindowAbout.h"
#include "ui_WindowMain.h"

#include <AbsComponentController.h>
#include <AbsComponentSandbox.h>

#include <QDebug>

class GameWindow : public QWidget
{

    Q_OBJECT

    public:
                                    GameWindow()
        {

            if (Configuration::load())
            {

                this->ui.setupUi(this);
                this->setLanguage(QSystemLocale().fallbackLocale().bcp47Name().section('-',0,0));

                this->componentController = new AbsComponentController();
                this->componentSandbox = new AbsComponentSandbox();
                this->componentController->setComponentSandbox(this->componentSandbox);

                this->ui.GraphicsView->setScene(this->componentSandbox->getGraphicsScene());
                this->ui.GraphicsView->setMouseTracking(true);

                QObject::connect(this,SIGNAL(resize(QRectF)),this->componentSandbox,SLOT(resize(QRectF)));

                QObject::connect(this->ui.LogicSource,SIGNAL(clicked()),this,SLOT(componentAdd()));
                QObject::connect(this->ui.LogicTautology1,SIGNAL(clicked()),this,SLOT(componentAdd()));
                QObject::connect(this->ui.LogicTautology2,SIGNAL(clicked()),this,SLOT(componentAdd()));
                QObject::connect(this->ui.LogicTautology3,SIGNAL(clicked()),this,SLOT(componentAdd()));
                QObject::connect(this->ui.LogicConjunction,SIGNAL(clicked()),this,SLOT(componentAdd()));
                QObject::connect(this->ui.LogicDisjunction,SIGNAL(clicked()),this,SLOT(componentAdd()));
                QObject::connect(this->ui.LogicNegation,SIGNAL(clicked()),this,SLOT(componentAdd()));
                QObject::connect(this->ui.LogicImplication,SIGNAL(clicked()),this,SLOT(componentAdd()));
                QObject::connect(this->ui.LogicBiconditional,SIGNAL(clicked()),this,SLOT(componentAdd()));
                QObject::connect(this->ui.LogicIndicator,SIGNAL(clicked()),this,SLOT(componentAdd()));

                QObject::connect(this->ui.SetLanguageEnglish,SIGNAL(clicked()),this,SLOT(languageSwitch()));
                QObject::connect(this->ui.SetLanguageRussian,SIGNAL(clicked()),this,SLOT(languageSwitch()));
                QObject::connect(this->ui.SetLanguageDeutsch,SIGNAL(clicked()),this,SLOT(languageSwitch()));
                QObject::connect(this->ui.SetLanguageFrench,SIGNAL(clicked()),this,SLOT(languageSwitch()));

                QObject::connect(this->ui.DeleteAll,SIGNAL(clicked()),this->componentController,SLOT(componentsRemoveAll()));
                QObject::connect(this->ui.DeleteSelected,SIGNAL(clicked()),this->componentController,SLOT(componentsRemoveSelected()));
                QObject::connect(this->ui.InformationAbout,SIGNAL(clicked()),this,SLOT(windowAboutShow()));

            }

        }
                                    ~GameWindow()
        {

        }

    protected:
        virtual void                resizeEvent(QResizeEvent*)
        {

            emit this->resize(this->ui.GraphicsView->rect());

        }

    private:
        Ui::WindowMain              ui;
        AboutWindow*                windowAbout;
        AbsComponentController*     componentController;
        AbsComponentSandbox*        componentSandbox;
        void                        setLanguage(QString language)
        {

            QTranslator translator;
            translator.load("BooleanSandbox_"+language,"translations");
            qApp->installTranslator(&translator);
            this->ui.retranslateUi(this);

        }

    private slots:
        void                        componentAdd()
        {

            QObject* sender = QObject::sender();
            AbsComponentElectronic* component = NULL;

            if (sender == this->ui.LogicSource)
                component = new LogicSource();
            else if (sender == this->ui.LogicTautology1)
                component = new LogicSplitter(1);
            else if (sender == this->ui.LogicTautology2)
                component = new LogicSplitter(2);
            else if (sender == this->ui.LogicTautology3)
                component = new LogicSplitter(3);
            else if (sender == this->ui.LogicNegation)
                component = new LogicNegation();
            else if (sender == this->ui.LogicConjunction)
                component = new LogicConjunction();
            else if (sender == this->ui.LogicDisjunction)
                component = new LogicDisjunction();
            else if (sender == this->ui.LogicImplication)
                component = new LogicImplication();
            else if (sender == this->ui.LogicBiconditional)
                component = new LogicBiconditional();
            else if (sender == this->ui.LogicIndicator)
                component = new LogicIndicator();

            this->componentController->componentAdd(component);

        }
        void                        languageSwitch()
        {

            QObject* sender = QObject::sender();
            QString language = "en";

            if (sender == this->ui.SetLanguageRussian)
                language = "ru";
            if (sender == this->ui.SetLanguageEnglish)
                language = "en";
            if (sender == this->ui.SetLanguageDeutsch)
                language = "de";
            if (sender == this->ui.SetLanguageFrench)
                language = "fr";

            this->setLanguage(language);

        }
        void                        windowAboutShow()
        {

            this->windowAbout = new AboutWindow(this);
            this->windowAbout->show();

        }

    signals:
        void                        resize(QRectF);

};

#endif // GAMEWINDOW_H
