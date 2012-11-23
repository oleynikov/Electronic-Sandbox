#ifndef LOGICALSPLITTER_H
#define LOGICALSPLITTER_H

#include "AbsComponentElectronic.h"

class LogicSplitter : public AbsComponentElectronic
{

    Q_OBJECT

    public:
        LogicSplitter(int pinsCount=0)
        {

            (pinsCount>3 || pinsCount<1) ? this->pinsCount=1 : this->pinsCount=pinsCount;

            this->pinCreate(0,QPointF(0,30),PIN_DIRECTION_INPUT);

            for (int key=1 ; key<=this->pinsCount ; ++key)
            {

                this->pinCreate(key,QPointF(50,10+20*(key-1)),PIN_DIRECTION_OUTPUT);

            }

            switch (this->pinsCount)
            {

                case 1: this->pin(1)->setY(30); break;
                case 2: this->pin(1)->setY(10); this->pin(2)->setY(50); break;
                case 3: this->pin(1)->setY(10); this->pin(2)->setY(50); this->pin(3)->setY(30); break;

            }

            QObject::connect(this->pin(0),SIGNAL(poweredChange()),this,SLOT(pinInChanged()));

        }

    private:
        int pinsCount;

    private slots:
        void pinInChanged()
        {

            bool inputState = this->pin(0)->getPowered();

            for (int key=1 ; key<=this->pinsCount ; ++key)
            {

                this->pin(key)->setPowered(inputState);

            }

        }

};

#endif // LOGICALSPLITTER_H
