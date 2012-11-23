#ifndef GRID_H
#define GRID_H

#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QColor>

#include "_GameConfiguration.h"
#include "AbsSceneDependentObject.h"

class AbsGrid : public AbsSceneDependentObject
{

    Q_OBJECT

    public:
                            AbsGrid()
        {

            this->setZValue(-2);

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
                painter->drawLine(GameConfiguration::GRID_STEP*i,0,GameConfiguration::GRID_STEP*i,this->sceneRect.height());

            for (unsigned int j=0 ; j<this->linesHor ; ++j)
                painter->drawLine(0,GameConfiguration::GRID_STEP*j,this->sceneRect.width(),GameConfiguration::GRID_STEP*j);
        }

    protected slots:
        virtual void        sceneRectChanged(QRectF)
        {

            this->sceneRect = this->scene()->sceneRect();

            linesVer = this->sceneRect.width() / GameConfiguration::GRID_STEP + 1;
            linesHor = this->sceneRect.height() / GameConfiguration::GRID_STEP + 1;

            this->prepareGeometryChange();
            this->update(this->boundingRect());

        }

    private:
        QRectF              sceneRect;
        unsigned int        linesHor;
        unsigned int        linesVer;
        static const int    PEN_WIDTH = 10;

};

#endif // GRID_H
