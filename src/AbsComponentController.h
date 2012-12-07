#ifndef ABSCOMPONENTCONTROLLER_H
#define ABSCOMPONENTCONTROLLER_H

#include <QList>
#include <QObject>
#include <math.h>

#include <AbsComponent.h>
#include <AbsComponentElectronic.h>
#include <AbsComponentSandbox.h>
#include <AbsPin.h>
#include <AbsWire.h>
#include "LogicSource.h"
#include "LogicIndicator.h"
#include "LogicConjunction.h"
#include "LogicDisjunction.h"
#include "LogicNegation.h"
#include "LogicImplication.h"
#include "LogicBiconditional.h"
#include "LogicSplitter.h"

#include <QDebug>

typedef QList<AbsComponentElectronic*> Components;
typedef Components::iterator ComponentItr;
typedef QList<AbsWire*> Wires;
typedef Wires::iterator WireItr;

class AbsComponentController : public QObject
{

    Q_OBJECT

    public:
                                    AbsComponentController() : pinActive(NULL)
        {

        }
                                    ~AbsComponentController()
        {

            ComponentItr componentItr;

            for (componentItr=this->components.begin() ; componentItr!=this->components.end() ; componentItr++)
            {

                this->componentRemove(*componentItr);

            }

        }
                                    template <typename ComponentType>
        void                        componentCreate(int parameter = 0)
        {

            ComponentType* component = new ComponentType(parameter);
            this->componentAdd(component);

        }
        void                        setComponentSandbox(AbsComponentSandbox* componentSandbox)
        {

            QObject::connect(this,SIGNAL(graphicsItemAdded(QGraphicsItem*)),componentSandbox,SLOT(graphicsItemAdded(QGraphicsItem*)));
            QObject::connect(this,SIGNAL(graphicsItemRemoved(QGraphicsItem*)),componentSandbox,SLOT(graphicsItemRemoved(QGraphicsItem*)));
            QObject::connect(componentSandbox,SIGNAL(itemSelect(QGraphicsItem*)),this,SLOT(itemSelect(QGraphicsItem*)));
            QObject::connect(componentSandbox,SIGNAL(mouseDown(QPointF)),this,SLOT(mouseDown(QPointF)));
            QObject::connect(componentSandbox,SIGNAL(mouseMove(QPointF)),this,SLOT(mouseMove(QPointF)));
            QObject::connect(componentSandbox,SIGNAL(select(QRectF)),this,SLOT(componentsSelectInRect(QRectF)));

        }

    public slots:
        void                        componentAdd(AbsComponentElectronic* component)
        {

            if (component)
            {

                this->components.push_back(component);
                QObject::connect(component,SIGNAL(pinSelect(AbsPin*)),this,SLOT(pinSelect(AbsPin*)));
                QObject::connect(component,SIGNAL(componentRemove(AbsComponent*)),this,SLOT(componentRemove(AbsComponent*)));

                emit this->graphicsItemAdded(component);

            }

        }
        void                        componentsSelectInRect(QRectF selection)
        {

            ComponentItr componentItr;

            for (componentItr=this->components.begin() ; componentItr!=this->components.end() ; ++componentItr)
            {

                AbsComponent* component = *componentItr;
                component->setSelected(selection.contains(component->sceneBoundingRect())?true:false);

            }

        }
        void                        componentRemove(AbsComponent* component)
        {

            AbsComponentElectronic* componenElectronic = static_cast<AbsComponentElectronic*>(component);

            Pins pinsAll = componenElectronic->pins();
            PinItr pinItr;

            for (pinItr=pinsAll.begin() ; pinItr!=pinsAll.end() ; ++pinItr)
            {

                AbsWire* wire = this->getWire(pinItr.value());
                if (wire)
                {

                    this->componentsDisconnect(wire);

                }

            }

            int componentId = this->components.lastIndexOf(componenElectronic);
            this->components.removeAt(componentId);

            delete componenElectronic;

        }
        void                        componentsRemoveSelected(void)
        {

            Components componentsSelected = this->getComponentsSelected();
            ComponentItr componentItr;

            for (componentItr=componentsSelected.begin() ; componentItr!=componentsSelected.end() ; componentItr++)
            {

                this->componentRemove(*componentItr);

            }

        }
        void                        componentsRemoveAll(void)
        {

            while (!this->components.empty())
            {

                this->componentRemove(this->components.last());

            }

        }

    protected:
        Components                  components;
        Wires                       wires;
        AbsPin*                     pinActive;
        QPointF                     buttonDown;
        AbsWire*                    getWire(AbsPin* pin)
        {

            WireItr wireItr;

            for(wireItr=this->wires.begin() ; wireItr!=this->wires.end() ; ++wireItr)
            {

                if((*wireItr)->pin(0)==pin || (*wireItr)->pin(1)==pin)
                {

                    return *wireItr;

                }

            }

            return NULL;

        }
        Components                  getComponentsSelected(void)
        {
            Components componentsSelected;
            ComponentItr componentItr;

            for (componentItr=this->components.begin() ; componentItr!=this->components.end() ; componentItr++)
            {

                if ((*componentItr)->getSelected())
                {

                    componentsSelected.push_back(*componentItr);

                }

            }

            return componentsSelected;

        }

    protected slots:
        void                        componentsConnect(AbsPin* foo, AbsPin* bar)
        {

            //  foo & bar must belong to different componnets
            if (foo->getDirection()!=bar->getDirection() && foo->getHost() != bar->getHost())
            {

                //  Destroying old connections
                AbsWire* wireOld = NULL;
                wireOld = this->getWire(foo);
                if (wireOld)
                    this->componentsDisconnect(wireOld);
                wireOld = this->getWire(bar);
                if (wireOld)
                    this->componentsDisconnect(wireOld);

                //  Establishing a new connection

                AbsPin::connect(foo,bar);
                AbsWire* wire = new AbsWire(foo,bar);
                this->wires.push_back(wire);
                foo->setSelected(false);
                bar->setSelected(false);
                this->pinActive = NULL;

                QObject::connect(wire,SIGNAL(deleted(AbsWire*)),this,SLOT(componentsDisconnect(AbsWire*)));

                emit this->graphicsItemAdded(wire);

            }

            //  if not, reseting them
            else
            {

                foo->setSelected(false);
                bar->setSelected(false);
                this->pinActive = NULL;

            }

        }
        void                        componentsDisconnect(AbsWire* wire)
        {

            AbsPin* pinFoo = wire->pin(0);
            AbsPin* pinBar = wire->pin(1);
            AbsPin::disconnect(pinFoo,pinBar);

            int wireId = this->wires.lastIndexOf(wire);
            this->wires.removeAt(wireId);

            delete wire;

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
                    this->componentsConnect(this->pinActive,pin);

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
        void                        itemSelect(QGraphicsItem* item)
        {

            AbsComponentElectronic* component = static_cast<AbsComponentElectronic*>(item);
            component->setSelected(true);

        }
        void                        mouseDown(QPointF point)
        {

            this->buttonDown = point;

        }
        void                        mouseMove(QPointF point)
        {

            QPointF dragDelta = point - this->buttonDown;

            if (abs(dragDelta.x()) >= 15)
            {

                int dragDeltaStepsX = dragDelta.x() / 15;
                int dragDeltaX = 15 * dragDeltaStepsX * ( point.x()>=0 ? 1 : -1 );

                qDebug() << dragDeltaX;

                Components componentsSelected = this->getComponentsSelected();
                ComponentItr componentItr;

                for (componentItr=componentsSelected.begin() ; componentItr!=componentsSelected.end() ; componentItr++)
                {

                    (*componentItr)->moveBy(dragDeltaX,0);

                }

                this->buttonDown.rx() = point.x();

            }

        }

    signals:
        void                        graphicsItemAdded(QGraphicsItem*);
        void                        graphicsItemRemoved(QGraphicsItem*);

};

#endif // ABSCOMPONENTCONTROLLER_H
