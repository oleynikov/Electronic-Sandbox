#ifndef AINTERACTIVESCENE_H
#define AINTERACTIVESCENE_H

#include <QGraphicsScene>
#include <AEventFilter.h>


#include <QDebug>

class AInteractiveScene : public QGraphicsScene
{

    Q_OBJECT

    public:
                        AInteractiveScene()
        {

            this->installEventFilter(this);

        }
        void            addFilter(AEventFilter* filter)
        {

            if (!this->filters.contains(filter))
            {

                this->filters.push_back(filter);

            }

        }
        void            removeFilter(AEventFilter* filter)
        {

            this->filters.removeOne(filter);

        }
        virtual bool    eventFilter(QObject* watched, QEvent* event)
        {

            if (watched == this && this->applyFilters(event))
            {

                emit this->newEvent(event);

            }

            return false;

        }

    protected:
        Filters         filters;
        bool            applyFilters(QEvent* event)
        {

            FilterItr filterItr;
            bool passed = true;

            for (filterItr=this->filters.begin() ; filterItr!=this->filters.end() ; filterItr++)
            {

                AEventFilter* filter = *filterItr;

                if (!filter->pass(event))
                {

                    passed = false;
                    break;

                }

            }

            return passed;

        }

    signals:
        void            newEvent(QEvent*);

};

#endif // AINTERACTIVESCENE_H
