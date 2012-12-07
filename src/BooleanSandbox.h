#ifndef BOOLEANSANDBOX_H
#define BOOLEANSANDBOX_H

#include <AGraphicsSandbox.h>
#include <BooleanEventFilter.h>

#include <QDebug>

class BooleanSandbox : public AGraphicsSandbox
{

    public:
        BooleanSandbox()
        {

            this->graphicsScene->addFilter(new BooleanEventFilter());

        }

    protected slots:
        void newEvent(QEvent* event)
        {

            qDebug() << event->type();

        }

};

#endif // BOOLEANSANDBOX_H
