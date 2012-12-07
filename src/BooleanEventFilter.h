#ifndef BOOLEANEVENTFILTER_H
#define BOOLEANEVENTFILTER_H

#include <AEventFilter.h>

class BooleanEventFilter : public AEventFilter
{

public:
    BooleanEventFilter()
    {

        this->addEvent(QEvent::GraphicsSceneMouseMove);
        this->addEvent(QEvent::GraphicsSceneMousePress);
        this->addEvent(QEvent::GraphicsSceneMouseRelease);

    }

};

#endif // BOOLEANEVENTFILTER_H
