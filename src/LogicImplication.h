#ifndef LOGICALIMPLICATION_H
#define LOGICALIMPLICATION_H

#include "AbsComponentElectronic.h"

class LogicImplication : public AbsComponentElectronic
{

    Q_OBJECT

    public:
        LogicImplication() : AbsComponentElectronic("LogicalImplication")
        {

            this->pinCreate(0,QPointF(0,15),PIN_DIRECTION_INPUT);
            this->pinCreate(1,QPointF(0,45),PIN_DIRECTION_INPUT);
            this->pinCreate(2,QPointF(60,30),PIN_DIRECTION_OUTPUT);

            QObject::connect(this->pin(0),SIGNAL(poweredChange()),this,SLOT(pinInChanged()));
            QObject::connect(this->pin(1),SIGNAL(poweredChange()),this,SLOT(pinInChanged()));

            this->pinsUpdate();

        }

    private slots:
        void pinInChanged()
        {

            if (this->pin(0)->getPowered() && !this->pin(1)->getPowered())
            {

                this->pin(2)->setPowered(false);

            }

            else
            {

                this->pin(2)->setPowered(true);

            }

        }

};

#endif // LOGICALIMPLICATION_H
