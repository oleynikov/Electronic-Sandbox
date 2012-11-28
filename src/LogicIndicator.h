#ifndef LOGICALINDICATOR_H
#define LOGICALINDICATOR_H

#include "AbsComponentToggleable.h"

class LogicIndicator : public AbsComponentToggleable
{

    Q_OBJECT

    public:
        LogicIndicator() : AbsComponentToggleable("AbsComponentToggleablePin")
        {

            this->pinCreate(0,QPointF(0,30),PIN_DIRECTION_INPUT);

        }

    private slots:
        void pinInChanged()
        {

            this->setToggled(this->pin(0)->getPowered());

        }

};

#endif // ABSLOGICALINDICATOR_H
