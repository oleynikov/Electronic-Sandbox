#ifndef LOGICALNEGATION_H
#define LOGICALNEGATION_H

#include "AbsComponentElectronic.h"

class LogicNegation : public AbsComponentElectronic
{

    Q_OBJECT

    public:
        LogicNegation() : AbsComponentElectronic("LogicalNegation")
        {

            this->pinCreate(0,QPointF(0,30),PIN_DIRECTION_INPUT);
            this->pinCreate(1,QPointF(60,30),PIN_DIRECTION_OUTPUT);

        }

    protected slots:
        virtual void pinsUpdate()
        {

            this->pin(1)->setPowered(!this->pin(0)->getPowered());

        }

};

#endif // LOGICALNEGATION_H
