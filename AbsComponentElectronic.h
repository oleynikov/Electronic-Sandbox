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
                                                        int             width = 50,
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

            QMap<int,AbsPin*>::iterator pinItr = this->pins.find(pinId);

            if (pinItr != this->pins.end())
            {

                return this->pins.find(pinId).value();

            }

            return NULL;

        }
        QMap<int,AbsPin*>   getPins(void)const
        {

            return this->pins;

        }

    protected:
        void                pinCreate(int id, QPointF position, PinDirection direction, bool powered = false, bool selected = false, AbsPin* ally = NULL)
        {

            //  If pin id is not specified or is already used, looking for an unused one
            if (id < 0 || this->pins.contains(id))
            {
                id = 0;
                while (this->pins.contains(id))
                {
                    id++;
                }
            }

            AbsPin* pin = NULL;

            switch(this->logicType)
            {

                case COMPONENT_TYPE_LOGICAL: pin = new LogicPin(this,direction,powered,selected,ally); break;
                case COMPONENT_TYPE_ANALOG: break;

            }

            pin->setPos(position);
            this->pins.insert(id,pin);

            QObject::connect(pin,SIGNAL(selectedChange(AbsPin*)),this,SIGNAL(pinSelected(AbsPin*)));

        }
        void                pinsUpdate(void)
        {

            QMap<int,AbsPin*>::iterator pinItr;

            for (pinItr=this->pins.begin() ; pinItr!=this->pins.end() ; ++pinItr)
            {

                if((*pinItr)->getDirection() == PIN_DIRECTION_INPUT)
                {

                    (*pinItr)->setPowered((*pinItr)->getPowered());

                }

            }

        }

    private:
        QMap<int,AbsPin*>   pins;
        ComponentType       logicType;

    signals:
        void                pinSelected(AbsPin*);

};

#endif // ABSCOMPONENTELECTRONIC_H
