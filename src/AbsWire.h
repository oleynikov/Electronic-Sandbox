#ifndef ABSWIRE_H
#define ABSWIRE_H

#include <QGraphicsObject>
#include "stdlib.h"
#include "AbsPin.h"
#include "AbsComponent.h"
#include "AbsPathFinder.h"
#include "AbsSceneDependentObject.h"
#include "_Configuration.h"

class AbsWire : public AbsSceneDependentObject
{

    Q_OBJECT

    public:
                                AbsWire(AbsPin* foo, AbsPin* bar)
        {

            pins[0] = foo;
            pins[1] = bar;

            this->setZValue(-1);

            QObject::connect(foo,SIGNAL(pinSwitch()),this,SLOT(pinSwitch()));
            QObject::connect(bar,SIGNAL(pinSwitch()),this,SLOT(pinSwitch()));

            QObject::connect(foo->getHost(),SIGNAL(componentDrag()),this,SLOT(componentDrag()));
            QObject::connect(bar->getHost(),SIGNAL(componentDrag()),this,SLOT(componentDrag()));

            this->pen.setWidth(Configuration::parameter("wire_width_visible").toInt());
            QString cEnbStr = Configuration::parameter("wire_color_enabled");
            QString cDisStr = Configuration::parameter("wire_color_disabled");
            this->colorEnabled = qRgb(cEnbStr.mid(0,3).toInt(),cEnbStr.mid(3,3).toInt(),cEnbStr.mid(6,3).toInt());
            this->colorDisabled = qRgb(cDisStr.mid(0,3).toInt(),cDisStr.mid(3,3).toInt(),cDisStr.mid(6,3).toInt());

            this->pathUpdate();
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

            this->pins[1]->getPowered()
                ?   this->pen.setColor(this->colorEnabled)
                :   this->pen.setColor(this->colorDisabled);

            painter->setPen(this->pen);
            painter->drawPolyline(this->points.constData(),this->points.size());

        }
        virtual void            mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
        {

            if(event->button() == Qt::RightButton)
            {

                emit this->deleted(this);

            }

        }

    protected:
        virtual void            sceneRectChangeHandler()
        {

            this->pathUpdate();

        }

    private:
        AbsPin*                 pins[2];
        QVector<QPointF>        points;
        QRectF                  wireRect;
        QPainterPath            wireShape;
        QPen                    pen;
        QColor                  colorEnabled;
        QColor                  colorDisabled;
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

            int gridStepSize = Configuration::parameter("grid_step_size").toInt();
            QPointF wireBegin = pinOut->scenePos()+QPointF(gridStepSize,0);
            QPointF wireEnd = pinIn->scenePos()-QPointF(gridStepSize,0);
            QVector<QPointF> pointsBlocked;
            QVector<QPointF> pointsAvaliable;

            pointsBlocked += AbsPathFinder::getRectPerimeterPoints(this->pins[0]->getHost()->sceneBoundingRect(),gridStepSize);
            pointsBlocked += AbsPathFinder::getRectPerimeterPoints(this->pins[1]->getHost()->sceneBoundingRect(),gridStepSize);

            QRectF sceneRect = QRectF(this->sceneRect.topLeft()-QPointF(gridStepSize,gridStepSize),this->sceneRect.bottomRight()+QPointF(gridStepSize,gridStepSize));
            pointsAvaliable = AbsPathFinder::getRectInnerPoints(sceneRect,gridStepSize);

            this->points.clear();
            this->points.push_back(pinOut->scenePos());
            this->points += AbsPathFinder::pathFindAStar(wireBegin,wireEnd,pointsAvaliable,pointsBlocked,gridStepSize);
            this->points.push_back(pinIn->scenePos());

            this->rectUpdate();
            this->shapeUpdate();
            this->prepareGeometryChange();
            this->update(this->boundingRect());

        }
        void                    rectUpdate()
        {

            int wWidth = Configuration::parameter("wire_width_total").toInt();
            QPointF topLeft = this->points.first();
            QPointF bottomRight = this->points.first();
            QVector<QPointF>::iterator pointItr;

            for (pointItr=this->points.begin() ; pointItr!=this->points.end() ; ++pointItr)
            {

                QPointF point = *pointItr;

                if (point.x()<topLeft.x())
                    topLeft.rx() = point.x();
                else if (point.x()>bottomRight.x())
                    bottomRight.rx() = point.x();

                if (point.y()<topLeft.y())
                    topLeft.ry() = point.y();
                else if (point.y()>bottomRight.y())
                    bottomRight.ry() = point.y();

            }

            this->wireRect = QRectF(topLeft-QPointF(wWidth/2,wWidth/2),bottomRight+QPointF(wWidth/2,wWidth/2));

            if (this->wireRect.width() == 0) this->wireRect.setWidth(1);
            if (this->wireRect.height() == 0) this->wireRect.setHeight(1);

        }
        void                    shapeUpdate()
        {

            QPainterPath shape;
            QVector<QPointF>::iterator pointsItr;
            int wWidth = Configuration::parameter("wire_width_total").toInt();

            for (pointsItr=this->points.begin()+1 ; pointsItr!=points.end() ; ++pointsItr)
            {

                QPointF pCurr = *pointsItr;
                QPointF pPrev = *(pointsItr-1);

                if(pPrev.x() > pCurr.x() || pPrev.y() > pCurr.y())
                {
                    QPointF pTemp = pPrev;
                    pPrev = pCurr;
                    pCurr = pTemp;

                }

                QPointF topLeft(pPrev.x()-wWidth/2,pPrev.y()-wWidth/2);
                QPointF botRigh(pCurr.x()+wWidth/2,pCurr.y()+wWidth/2);

                shape.addRect(QRectF(topLeft,botRigh));

            }

            this->wireShape = shape;

        }

    private slots:
        void                    componentDrag()
        {

            this->pathUpdate();

        }
        void                    pinSwitch()
        {

            this->update(this->boundingRect());

        }

    signals:
        void                    deleted(AbsWire*);

};

#endif // ABSWIRE_H
