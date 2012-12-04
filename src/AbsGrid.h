#ifndef GRID_H
#define GRID_H

#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QColor>

#include "_Configuration.h"
#include "AbsSceneDependentObject.h"

class AbsGrid : public AbsSceneDependentObject
{

    Q_OBJECT

    public:
                            AbsGrid()
        {

            this->setZValue(-2);
            this->stepSize = Configuration::parameter("grid_step_size").toInt();

        }
        virtual QRectF      boundingRect() const
        {

            return this->sceneRect;

        }
        virtual void        paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0)
        {

            QPen pen;
            pen.setColor(QColor(235,235,235));
            painter->setPen(pen);

            for (unsigned int i=0 ; i<this->linesVer ; ++i)
                painter->drawLine(this->stepSize*i,0,this->stepSize*i,this->sceneRect.height());

            for (unsigned int j=0 ; j<this->linesHor ; ++j)
                painter->drawLine(0,this->stepSize*j,this->sceneRect.width(),this->stepSize*j);
        }

    protected slots:
        virtual void        sceneRectChangeHandler()
        {

            linesVer = this->sceneRect.width() / this->stepSize + 1;
            linesHor = this->sceneRect.height() / this->stepSize + 1;

            this->prepareGeometryChange();
            this->update(this->boundingRect());

        }

    private:
        int                 stepSize;
        unsigned int        linesHor;
        unsigned int        linesVer;

};

#endif // GRID_H
