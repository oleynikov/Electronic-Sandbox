#ifndef LOGICALSOURCE_H
#define LOGICALSOURCE_H

#include "AbsComponentToggleableManual.h"

class LogicSource : public AbsComponentToggleableManual
{

    Q_OBJECT

    public:
        LogicSource()
        {

            this->pinCreate(0,QPointF(60,30),PIN_DIRECTION_OUTPUT);

            QObject::connect(this,SIGNAL(toggled(bool)),this,SLOT(toggled(bool)));

        }

    private slots:
        void toggled(bool toggled)
        {

            this->pin(0)->setPowered(toggled);

        }


};

#endif // LOGICALSOURCE_H
