#ifndef ABSWIRE_H
#define ABSWIRE_H

#include <QGraphicsObject>
#include "stdlib.h"
#include "AbsPin.h"
#include "AbsComponent.h"
#include "AbsPathFinder.h"

#include <QDebug>

class AbsWire : public QGraphicsObject
{

    Q_OBJECT

    public:
                                AbsWire(AbsPin* foo, AbsPin* bar)
        {

            pins[0] = foo;
            pins[1] = bar;

            this->pathUpdate();
            this->setZValue(-1);

            QObject::connect(foo,SIGNAL(poweredChange()),this,SLOT(pinPowered()));
            QObject::connect(bar,SIGNAL(poweredChange()),this,SLOT(pinPowered()));

            QObject::connect(foo->getHost(),SIGNAL(dragged()),this,SLOT(pinDragged()));
            QObject::connect(bar->getHost(),SIGNAL(dragged()),this,SLOT(pinDragged()));

        }
        AbsPin*                 pin(int id)const
        {

            return this->pins[id];

        }
        virtual QPainterPath    shape()const
        {

            return this->wireShape;

        }
        virtual QRectF          boundingRect()const
        {

            return this->wireRect;

        }
        virtual void            paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
        {

            QPen pen;
            pen.setWidth(3);

            this->pins[1]->getPowered()
                ?   pen.setColor(QColor(72,174,4))
                :   pen.setColor(QColor(167,194,252));

            painter->setPen(pen);
            painter->drawPolyline(this->points.constData(),this->points.size());

        }
        virtual void            mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
        {

            if (event->button() == Qt::RightButton)
            {

                emit this->deleted(this);

            }

        }

    private:
        AbsPin*                 pins[2];
        QVector<QPointF>        points;
        QRectF                  wireRect;
        QPainterPath            wireShape;
        void                    pathUpdate()
        {

            AbsPin *pinOut, *pinIn;
            if (this->pins[0]->getDirection() == PIN_DIRECTION_OUTPUT)
            {
                pinOut = this->pins[0];
                pinIn = this->pins[1];
            }
            else
            {
                pinOut = this->pins[1];
                pinIn = this->pins[0];
            }

            QVector<QPointF> blocked;
            blocked += AbsPathFinder::getRectPoints(this->pins[0]->getHost()->sceneBoundingRect());
            blocked += AbsPathFinder::getRectPoints(this->pins[1]->getHost()->sceneBoundingRect());

            this->points.clear();
            this->points.push_back(pinOut->scenePos());
            this->points += AbsPathFinder::pathFindAStar(pinOut->scenePos()+QPointF(10,0),pinIn->scenePos()-QPointF(10,0),blocked);
            this->points.push_back(pinIn->scenePos());

            this->rectUpdate();
            this->shapeUpdate();
            this->prepareGeometryChange();
            this->update(this->boundingRect());

        }
        void                    rectUpdate()
        {

            QPointF topLeft = this->points.first();
            QPointF bottomRight = this->points.first();
            QVector<QPointF>::iterator pointItr;

            for (pointItr=this->points.begin() ; pointItr!=this->points.end() ; ++pointItr)
            {

                QPointF point = *pointItr;
                if (point.x()<topLeft.x())              topLeft.rx() = point.x();
                else if (point.x()>bottomRight.x())     bottomRight.rx() = point.x();
                if (point.y()<topLeft.y())              topLeft.ry() = point.y();
                else if (point.y()>bottomRight.y())     bottomRight.ry() = point.y();

            }

            this->wireRect = QRectF(topLeft,bottomRight);

            if (this->wireRect.width() == 0) this->wireRect.setWidth(1);
            if (this->wireRect.height() == 0) this->wireRect.setHeight(1);

        }
        void                    shapeUpdate()
        {

            QVector<QPointF>::iterator pointsItr;
            QPainterPath shape;
            int wWidth = 20;

            for (pointsItr=this->points.begin()+1 ; pointsItr!=points.end() ; ++pointsItr)
            {

                QPointF pPrev = *(pointsItr-1);
                QPointF pNext = *pointsItr;

                if(pPrev.x() > pNext.x() || pPrev.y() > pNext.y())
                {
                    QPointF pTemp = pPrev;
                    pPrev = pNext;
                    pNext = pTemp;

                }

                QRectF rect(pPrev.x()-wWidth/2,pPrev.y()-wWidth/2,(pNext-pPrev).x()+wWidth,(pNext-pPrev).y()+wWidth);
                shape.addRect(rect);

            }

            this->wireShape = shape;

        }

    private slots:
        void                    pinDragged()
        {

            this->pathUpdate();

        }
        void                    pinPowered()
        {

            this->update(this->boundingRect());

        }

    signals:
        void                    deleted(AbsWire*);

};

#endif // ABSWIRE_H
