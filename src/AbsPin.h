#ifndef ABSPIN_H
#define ABSPIN_H

#include <QGraphicsObject>
#include <QPainter>
#include <QPointF>
#include <QPen>
#include <QBrush>
#include <QColor>
#include <AbsComponent.h>
#include "_Configuration.h"

enum PinDirection
{

    PIN_DIRECTION_INPUT,
    PIN_DIRECTION_OUTPUT

};

class AbsPin : public QGraphicsObject
{

    Q_OBJECT

    public:
                            AbsPin  (
                                        AbsComponent*   host,
                                        PinDirection    direction,
                                        bool            powered = false,
                                        bool            selected = false,
                                        AbsPin*         ally = NULL
                                    )
                                    :   QGraphicsObject(host),
                                        host(host),
                                        direction(direction),
                                        powered(powered),
                                        selected(selected)
        {

            this->setAlly(ally);

            this->sizeDefault = Configuration::parameter("pin_size_default").toInt();
            this->sizeSelected = Configuration::parameter("pin_size_selected").toInt();
            QString cEnbStr = Configuration::parameter("pin_color_enabled");
            QString cDisStr = Configuration::parameter("pin_color_disabled");
            this->colorEnabled = qRgb(cEnbStr.mid(0,3).toInt(),cEnbStr.mid(3,3).toInt(),cEnbStr.mid(6,3).toInt());
            this->colorDisabled = qRgb(cDisStr.mid(0,3).toInt(),cDisStr.mid(3,3).toInt(),cDisStr.mid(6,3).toInt());

        }
        AbsComponent*       getHost(void)const
        {

            return this->host;

        }
        PinDirection        getDirection(void)const
        {

            return this->direction;

        }
        AbsPin*             getAlly(void)const
        {

            return this->ally;

        }
        bool                getPowered(void)const
        {

            return this->powered;

        }
        bool                getSelected(void)const
        {

            return this->selected;

        }
        void                setDirection(PinDirection direction)
        {

            this->direction = direction;

        }
        void                setAlly(AbsPin* ally)
        {

            this->ally = ally;
            this->stateUpdate();

            if(ally)
            {

                QObject::connect(ally,SIGNAL(poweredChange()),this,SLOT(allyStateChanged()));

            }

        }
        void                setPowered(bool powered)
        {

            this->powered = powered;
            this->update(this->boundingRect());
            emit this->poweredChange();

        }
        void                setSelected(bool active)
        {

            this->selected = active;
            this->prepareGeometryChange();
            this->update(this->boundingRect());
            emit this->selectedChange(this);

        }

    protected:
        AbsComponent*       host;
        PinDirection        direction;
        AbsPin*             ally;
        bool                powered;
        bool                selected;
        void                stateUpdate(void)
        {

            if (this->getDirection() == PIN_DIRECTION_INPUT)
            {

                if(this->getAlly())
                {

                    this->setPowered(this->getAlly()->getPowered());

                }

                else
                {

                    this->setPowered(false);

                }

            }

        }
        virtual void        mousePressEvent(QGraphicsSceneMouseEvent* event)
        {

            Qt::MouseButton mouseButton = event->button();

            if (mouseButton == Qt::LeftButton)
            {

                this->setSelected(!this->getSelected());

            }

        }
        virtual void        paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
        {

            QPen pen(QBrush(Qt::NoBrush),0);
            QBrush brush(Qt::SolidPattern);

            this->getPowered()
                ?   brush.setColor(this->colorEnabled)
                :   brush.setColor(this->colorDisabled);

            int circleRadius;
            this->getSelected()
                ?   circleRadius = this->sizeSelected
                :   circleRadius = this->sizeDefault;

            painter->setPen(pen);
            painter->setBrush(brush);
            painter->drawEllipse(QPointF(0,0),circleRadius,circleRadius);

        }
        virtual QRectF      boundingRect() const
        {

            if (this->getSelected())
                return QRectF(-10,-10,20,20);
            else
                return QRectF(-5,-5,10,10);

        }

    protected slots:
        void                allyStateChanged()
        {

            this->stateUpdate();

        }

    private:
        int                 sizeDefault;
        int                 sizeSelected;
        QColor              colorEnabled;
        QColor              colorDisabled;

    signals:
        void                poweredChange();
        void                selectedChange(AbsPin*);

};

#endif // ABSPIN_H
