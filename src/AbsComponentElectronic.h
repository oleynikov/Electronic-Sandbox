#ifndef ABSCOMPONENTELECTRONIC_H
#define ABSCOMPONENTELECTRONIC_H

#include <QMap>
#include "AbsComponent.h"
#include "LogicPin.h"

enum ComponentType
{

    COMPONENT_TYPE_ANALOG,
    COMPONENT_TYPE_LOGICAL

};

class AbsComponentElectronic : public AbsComponent
{

    Q_OBJECT

    public:
                            AbsComponentElectronic  (
                                                        QString         iconName = "AbsComponentElectronic",
                                                        ComponentType   logicType = COMPONENT_TYPE_LOGICAL,
                                                        int             width = 60,
                                                        int             height = 60,
                                                        bool            bordered = false,
                                                        bool            dragable = true
                                                    )
                                                    :   AbsComponent(width,height,iconName,bordered,dragable),
                                                        logicType(logicType)
        {

        }
        AbsPin*             pin(int pinId)
        {

            QMap<int,AbsPin*>::iterator pinItr = this->absPins.find(pinId);

            if (pinItr != this->absPins.end())
            {

                return this->absPins.find(pinId).value();

            }

            return NULL;

        }
        QMap<int,AbsPin*>   pins(void)const
        {

            return this->absPins;

        }

    protected:
        void                pinCreate(int id, QPointF position, PinDirection direction)
        {

            //  If pin id is not specified or is already used, looking for an unused one
            if (id < 0 || this->absPins.contains(id))
            {
                id = 0;
                while (this->absPins.contains(id))
                    id++;
            }

            AbsPin* pin = NULL;

            switch(this->logicType)
            {
                case COMPONENT_TYPE_LOGICAL: pin = new LogicPin(this,direction); break;
                case COMPONENT_TYPE_ANALOG: break;
            }

            pin->setPos(position);
            this->absPins.insert(id,pin);

            QObject::connect(pin,SIGNAL(pinSelect(AbsPin*)),this,SIGNAL(pinSelect(AbsPin*)));

            if (direction == PIN_DIRECTION_INPUT)
                QObject::connect(pin,SIGNAL(pinSwitch()),this,SLOT(pinsUpdate()));
            else if (direction == PIN_DIRECTION_OUTPUT)
                this->pinsUpdate();

        }

    protected slots:
        virtual void        pinsUpdate()
        {

        }

    private:
        QMap<int,AbsPin*>   absPins;
        ComponentType       logicType;

    signals:
        void                pinSelect(AbsPin*);

};

#endif // ABSCOMPONENTELECTRONIC_H
