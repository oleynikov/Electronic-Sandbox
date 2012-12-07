#ifndef AGRAPHICSCONTROLLER_H
#define AGRAPHICSCONTROLLER_H

#include <QList>
#include <QGraphicsItem>

typedef QList<QGraphicsItem*>       GraphicItems;
typedef GraphicItems::iterator      ItemItr;

class AGraphicsController
{

    public:
        bool addItem(QGraphicsItem* item)
        {

            if (!this->items.contains(item))
            {

                this->items.push_back(item);
                return true;

            }

            return false;

        }
        bool removeItem(QGraphicsItem* item)
        {

            if (this->items.contains(item))
            {

                this->items.removeOne(item);
                delete item;

                return true;

            }

            return false;

        }

    protected:
        GraphicItems items;

};

#endif // AGRAPHICSCONTROLLER_H
