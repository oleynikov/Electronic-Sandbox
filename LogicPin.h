#ifndef ABSPINLOGICAL_H
#define ABSPINLOGICAL_H

#include "AbsPin.h"

class LogicPin : public AbsPin
{

    public:
        LogicPin    (
                        AbsComponent*   host,
                        PinDirection    direction,
                        bool            powered = false,
                        bool            selected = false,
                        AbsPin*         ally = NULL
                    )
                    :   AbsPin(host,direction,powered,selected,ally)
        {



        }

};

#endif // ABSPINLOGICAL_H
