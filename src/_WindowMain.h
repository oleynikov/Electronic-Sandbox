#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QTranslator>
#include <QVector>
#include <QLocale>
#include <QSystemLocale>

#include "_Configuration.h"
#include "_WindowAbout.h"
#include "ui_WindowMain.h"
#include "AbsGrid.h"
#include "AbsWire.h"
#include "LogicSource.h"
#include "LogicIndicator.h"
#include "LogicConjunction.h"
#include "LogicDisjunction.h"
#include "LogicNegation.h"
#include "LogicImplication.h"
#include "LogicBiconditional.h"
#include "LogicSplitter.h"

class GameWindow : public QWidget
{

    Q_OBJECT

    public:
        GameWindow() : pinActive(NULL)
        {

            if (Configuration::load())
            {

                this->ui.setupUi(this);

                this->setLanguage(QSystemLocale().fallbackLocale().bcp47Name().section('-',0,0));

                this->graphicsScene.setParent(this);
                this->ui.GraphicsView->setScene(&this->graphicsScene);

                this->grid = new AbsGrid();
                this->graphicsScene.addItem(this->grid);

                QObject::connect(this->ui.LogicSource,SIGNAL(clicked()),this,SLOT(componentCreate()));
                QObject::connect(this->ui.LogicTautology1,SIGNAL(clicked()),this,SLOT(componentCreate()));
                QObject::connect(this->ui.LogicTautology2,SIGNAL(clicked()),this,SLOT(componentCreate()));
                QObject::connect(this->ui.LogicTautology3,SIGNAL(clicked()),this,SLOT(componentCreate()));
                QObject::connect(this->ui.LogicConjunction,SIGNAL(clicked()),this,SLOT(componentCreate()));
                QObject::connect(this->ui.LogicDisjunction,SIGNAL(clicked()),this,SLOT(componentCreate()));
                QObject::connect(this->ui.LogicNegation,SIGNAL(clicked()),this,SLOT(componentCreate()));
                QObject::connect(this->ui.LogicImplication,SIGNAL(clicked()),this,SLOT(componentCreate()));
                QObject::connect(this->ui.LogicBiconditional,SIGNAL(clicked()),this,SLOT(componentCreate()));
                QObject::connect(this->ui.LogicIndicator,SIGNAL(clicked()),this,SLOT(componentCreate()));

                QObject::connect(this->ui.SetLanguageEnglish,SIGNAL(clicked()),this,SLOT(languageSwitch()));
                QObject::connect(this->ui.SetLanguageRussian,SIGNAL(clicked()),this,SLOT(languageSwitch()));
                QObject::connect(this->ui.SetLanguageDeutsch,SIGNAL(clicked()),this,SLOT(languageSwitch()));
                QObject::connect(this->ui.SetLanguageFrench,SIGNAL(clicked()),this,SLOT(languageSwitch()));

                QObject::connect(this->ui.InformationAbout,SIGNAL(clicked()),this,SLOT(windowAboutShow()));

            }

        }
        ~GameWindow()
        {

        }

    protected:
        virtual void                resizeEvent(QResizeEvent* event)
        {

            this->graphicsScene.setSceneRect(this->ui.GraphicsView->rect());

        }

    private:
        Ui::WindowMain              ui;
        AboutWindow*                windowAbout;
        QGraphicsScene              graphicsScene;
        AbsGrid*                    grid;
        AbsPin*                     pinActive;
        QVector<AbsComponent*>      components;
        QVector<AbsWire*>           wires;

        void                        connectionEstablish(AbsPin* foo, AbsPin* bar)
        {

            //  foo & bar must belong to different componnets
            if (foo->getDirection()!=bar->getDirection() && foo->getHost() != bar->getHost())
            {

                //  Destroying old connections
                AbsWire* wireOld = NULL;
                wireOld = this->getWire(foo);
                if (wireOld)
                    this->connectionRemove(wireOld);
                wireOld = this->getWire(bar);
                if (wireOld)
                    this->connectionRemove(wireOld);

                //  Establishing a new connection

                AbsPin::connect(foo,bar);
                AbsWire* wire = new AbsWire(foo,bar);
                this->wires.push_back(wire);
                this->graphicsScene.addItem(wire);
                foo->setSelected(false);
                bar->setSelected(false);
                this->pinActive = NULL;

                QObject::connect(wire,SIGNAL(deleted(AbsWire*)),this,SLOT(wireRemove(AbsWire*)));

            }

            //  if not, reseting them
            else
            {

                foo->setSelected(false);
                bar->setSelected(false);
                this->pinActive = NULL;

            }

        }
        void                        connectionRemove(AbsWire* wire)
        {

            AbsPin* pinFoo = wire->pin(0);
            AbsPin* pinBar = wire->pin(1);
            AbsPin::disconnect(pinFoo,pinBar);

            int wireId = this->wires.lastIndexOf(wire);
            this->wires.remove(wireId);
            delete wire;

        }
        AbsWire*                    getWire(AbsPin *pin)
        {

            QVector<AbsWire*>::iterator wireItr;

            for(wireItr=this->wires.begin() ; wireItr!=this->wires.end() ; ++wireItr)
            {

                if((*wireItr)->pin(0)==pin || (*wireItr)->pin(1)==pin)
                {

                    return *wireItr;

                }

            }

            return NULL;

        }
        void                        setLanguage(QString language)
        {

            QTranslator translator;
            translator.load("BooleanSandbox_"+language,"translations");
            qApp->installTranslator(&translator);

            this->ui.retranslateUi(this);

        }

    private slots:
        void                        componentCreate()
        {

            QObject* sender = QObject::sender();
            AbsComponent* component = NULL;

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

            if (component)
            {

                this->graphicsScene.addItem(component);
                this->components.push_back(component);
                QObject::connect(component,SIGNAL(componentRemove()),this,SLOT(componentRemove()));
                QObject::connect(component,SIGNAL(pinSelect(AbsPin*)),this,SLOT(pinSelect(AbsPin*)));

            }

        }
        void                        componentRemove()
        {

            AbsComponentElectronic* component = static_cast<AbsComponentElectronic*>(QObject::sender());

            QMap<int,AbsPin*> pins = component->pins();
            QMap<int,AbsPin*>::iterator pinsItr;

            for (pinsItr=pins.begin() ; pinsItr!=pins.end() ; ++pinsItr)
            {

                AbsWire* wire = this->getWire(pinsItr.value());
                if (wire)
                {

                    this->connectionRemove(wire);

                }

            }

            int componentId = this->components.lastIndexOf(component);
            delete component;
            this->components.remove(componentId);

        }
        void                        pinSelect(AbsPin* pin)
        {

            //  If pin was activated
            if (pin->getSelected())
            {

                //  And there already is an activated one
                if (this->pinActive)
                {

                    //  Establish connection
                    this->connectionEstablish(this->pinActive,pin);

                }

                //  And no pin was previously activated
                else
                {

                    //  Set an active pin
                    this->pinActive = pin;

                }
            }

            //  If pin is deactivated
            else
            {

                //  Reset the active pin
                this->pinActive = NULL;

            }

        }
        void                        wireRemove(AbsWire* wire)
        {

            this->connectionRemove(wire);

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

};

#endif // GAMEWINDOW_H
