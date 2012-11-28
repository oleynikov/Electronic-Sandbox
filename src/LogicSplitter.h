#ifndef LOGICALSPLITTER_H
#define LOGICALSPLITTER_H

#include "AbsComponentElectronic.h"
#include <QDebug>

class LogicSplitter : public AbsComponentElectronic
{

    Q_OBJECT

    public:
        LogicSplitter(int pinsCount=0) : AbsComponentElectronic("LogicTautology")
        {

            (pinsCount>3 || pinsCount<1) ? this->pinsCount=1 : this->pinsCount=pinsCount;

            this->pinCreate(0,QPointF(0,30),PIN_DIRECTION_INPUT);

            for (int key=0 ; key<this->pinsCount ; ++key)
            {

                this->pinCreate(key+1,QPointF(60,15+15*(key-1)),PIN_DIRECTION_OUTPUT);

            }

            switch (this->pinsCount)
            {

                case 1: this->pin(1)->setY(30); break;
                case 2: this->pin(1)->setY(15); this->pin(2)->setY(45); break;
                case 3: this->pin(1)->setY(15); this->pin(2)->setY(45); this->pin(3)->setY(30); break;

            }

        }

    protected slots:
        void pinsUpdate()
        {

            bool inputState = this->pin(0)->getPowered();

            for (int key=0 ; key<this->pinsCount ; ++key)
            {

                if (this->pin(key+1))
                {

                    this->pin(key+1)->setPowered(inputState);

                }

            }

        }

    private:
        int pinsCount;

};

#endif // LOGICALSPLITTER_H
