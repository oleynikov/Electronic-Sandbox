#ifndef ABSPINLOGICAL_H
#define ABSPINLOGICAL_H

#include "AbsPin.h"

class LogicPin : public AbsPin
{

    public:
        LogicPin (AbsComponent* host, PinDirection direction) : AbsPin(host,direction)
        {

        }

};

#endif // ABSPINLOGICAL_H
