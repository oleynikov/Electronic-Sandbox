#ifndef AEVENTFILTER_H
#define AEVENTFILTER_H

#include <QList>
#include <QEvent>

class AEventFilter;

typedef QList<QEvent::Type>     Events;
typedef Events::iterator        EventItr;
typedef QList<AEventFilter*>    Filters;
typedef Filters::iterator       FilterItr;

class AEventFilter
{

    public:
        void    addEvent(QEvent::Type event)
        {

            if (!this->events.contains(event))
            {

                this->events.push_back(event);

            }

        }
        void    removeEvent(QEvent::Type event)
        {

            this->events.removeOne(event);

        }
        bool    pass(QEvent* event)
        {

            QEvent::Type eventType = event->type();

            if (this->events.contains(eventType))
            {

                return true;

            }

            return false;

        }

    protected:
        Events  events;

};

#endif // AEVENTFILTER_H
