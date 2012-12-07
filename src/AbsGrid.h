#ifndef GRID_H
#define GRID_H

#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QColor>
#include <QGraphicsSceneMouseEvent>
#include <stdlib.h>

#include "_Configuration.h"
#include "AbsSceneDependentObject.h"

#include <QDebug>

class AbsGrid : public AbsSceneDependentObject
{

    Q_OBJECT

    public:
                            AbsGrid()
        {

            this->setZValue(-2);
            this->stepSize = Configuration::parameter("grid_step_size").toInt();
            this->lineSize = Configuration::parameter("grid_line_size").toInt();


        }
        virtual QRectF      boundingRect() const
        {

            return this->sceneRect;

        }
        virtual void        paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0)
        {

            QPen pen;
            pen.setColor(QColor(235,235,235));
            pen.setWidth(this->lineSize);
            painter->setPen(pen);

            QBrush brush;
            brush.setStyle(Qt::SolidPattern);
            brush.setColor(QColor(225,225,225));
            painter->setBrush(brush);

            painter->drawRect(this->selection);

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
        virtual void        mousePressEvent(QGraphicsSceneMouseEvent*)
        {

        }
        virtual void        mouseMoveEvent(QGraphicsSceneMouseEvent* event)
        {

            if (event->buttons() == Qt::LeftButton)
            {

                QPointF pBegin = event->buttonDownScenePos(Qt::LeftButton);
                QPointF pEnd(event->scenePos());
                QPointF pTopLeft;
                QPointF pBottomRight;

                pTopLeft.rx() = pBegin.x()<pEnd.x() ? pBegin.x() : pEnd.x();
                pTopLeft.ry() = pBegin.y()<pEnd.y() ? pBegin.y() : pEnd.y();
                pBottomRight.rx() = pBegin.x()>pEnd.x() ? pBegin.x() : pEnd.x();
                pBottomRight.ry() = pBegin.y()>pEnd.y() ? pBegin.y() : pEnd.y();

                pTopLeft.rx() = (int)pTopLeft.x() / this->stepSize * this->stepSize;
                pTopLeft.ry() = (int)pTopLeft.y() / this->stepSize * this->stepSize;
                pBottomRight.rx() = (int)pBottomRight.x() / this->stepSize * this->stepSize + this->stepSize;
                pBottomRight.ry() = (int)pBottomRight.y() / this->stepSize * this->stepSize + this->stepSize;

                this->selection = QRectF(pTopLeft,pBottomRight);

                this->update(this->boundingRect());

            }

        }
        virtual void        mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
        {

            if (this->selection.size().width() != 0)
            {

                emit this->select(this->selection);

                this->selection = QRectF(0,0,0,0);
                this->update(this->boundingRect());

            }

            else
            {

                emit this->select(this->selection);

            }

        }

    private:
        int                 lineSize;
        QColor              lineColor;
        QColor              selectionColor;
        int                 stepSize;
        unsigned int        linesHor;
        unsigned int        linesVer;
        QPointF             selectionBegin;
        QRectF              selection;

    signals:
        void                select(QRectF);

};

#endif // GRID_H
