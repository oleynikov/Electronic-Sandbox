#ifndef LOGICALBICONDITIONAL_H
#define LOGICALBICONDITIONAL_H

#include "AbsComponentElectronic.h"

class LogicBiconditional : public AbsComponentElectronic
{

    Q_OBJECT

    public:
        LogicBiconditional() : AbsComponentElectronic("LogicalBiconditional")
        {

            this->pinCreate(0,QPointF(0,15),PIN_DIRECTION_INPUT);
            this->pinCreate(1,QPointF(0,45),PIN_DIRECTION_INPUT);
            this->pinCreate(2,QPointF(60,30),PIN_DIRECTION_OUTPUT);

        }

    protected slots:
        void pinsUpdate()
        {

            if (this->pin(0)->getPowered() == this->pin(1)->getPowered())
            {

                this->pin(2)->setPowered(true);

            }

            else
            {

                this->pin(2)->setPowered(false);

            }

        }

};

#endif // LOGICALBICONDITIONAL_H
