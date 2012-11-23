#ifndef ABSPINSCONNECTOR_H
#define ABSPINSCONNECTOR_H

#include "AbsPin.h"

class AbsPinsConnector
{

    public:
        static void pinsConnect(AbsPin* foo, AbsPin* bar)
        {

            foo->setAlly(bar);
            bar->setAlly(foo);

        }

        static void pinsDisconnect(AbsPin* foo, AbsPin* bar)
        {

            foo->setAlly(NULL);
            bar->setAlly(NULL);

        }

    private:
        AbsPinsConnector()
        {

        }

};

#endif // ABSPINSCONNECTOR_H
