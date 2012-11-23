#ifndef ABSCOMPONENT_H
#define ABSCOMPONENT_H

#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QBrush>
#include <QString>
#include "math.h"

#include "_GameConfiguration.h"
#include "AbsSceneDependentObject.h"

#include <QDebug>

class AbsComponent : public AbsSceneDependentObject
{
    Q_OBJECT

    public:
                        AbsComponent    (
                                            int     width = 50,
                                            int     height = 60,
                                            QString iconName = "AbsComponent",
                                            bool    bordered = false,
                                            bool    dragable = true
                                        )
                                        :   width(width),
                                            height(height),
                                            iconName(iconName),
                                            bordered(bordered),
                                            dragable(dragable),
                                            mouseDown(false)
        {

            this->iconUpdate();

        }
        void            setIcon(QString iconName)
        {

            this->iconName = iconName;
            this->iconUpdate();

        }
        bool            setBordered(bool bordered)
        {

            if (this->bordered != bordered)
            {

                this->bordered = bordered;
                return true;

            }

            return false;

        }
        bool            setDragable(bool dragable)
        {

            if (this->dragable != dragable)
            {

                this->dragable = dragable;
                return true;

            }

            return false;

        }
        bool            getBordered(void) const
        {

           return this->bordered;

        }
        bool            getDragable(void) const
        {

            return this->dragable;

        }
        virtual void    mousePressEvent(QGraphicsSceneMouseEvent* event)
        {

            if (event->button() == Qt::LeftButton)
            {

                this->mouseDown = true;

                if (this->getDragable())
                {

                    this->mouseDownPoint = event->pos();

                }

            }

        }
        virtual void    mouseMoveEvent(QGraphicsSceneMouseEvent* event)
        {

            if (this->dragable && this->mouseDown)
            {

                QPointF positionNew = event->scenePos()-this->mouseDownPoint;
                QPointF positionDelta = positionNew - this->scenePos();

                if (abs(positionDelta.x()) >= GameConfiguration::GRID_STEP)
                {

                    if (positionNew.x() < 0)
                        positionNew.setX(0);
                    else if (positionNew.x() > this->pointMax.x())
                        positionNew.setX(this->pointMax.x());
                    else
                    {
                        int xDelta = positionDelta.x()/GameConfiguration::GRID_STEP;
                        positionNew.setX(this->pos().x()+xDelta*GameConfiguration::GRID_STEP);
                    }

                    this->setX(positionNew.x());
                    emit dragged();

                }

                if (abs(positionDelta.y()) >= GameConfiguration::GRID_STEP)
                {

                    if (positionNew.y() < 0)
                        positionNew.setY(0);
                    else if (positionNew.y() > this->pointMax.y())
                        positionNew.setY(this->pointMax.y());
                    else
                    {
                        int yDelta = positionDelta.y()/GameConfiguration::GRID_STEP;
                        positionNew.setY(this->pos().y()+yDelta*GameConfiguration::GRID_STEP);
                    }

                    this->setY(positionNew.y());
                    emit dragged();

                }

            }

        }
        virtual void    mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
        {

            /*

                Mouse released on the sprite

            */


            if (this->mouseDown)
            {

                this->mouseDown = false;

            }

        }
        virtual void    mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
        {

            if (event->button() == Qt::RightButton)
            {

                emit this->deleted();

            }

        }
        virtual QRectF  boundingRect() const
        {

            return QRectF(0,0,this->width,this->height);

        }
        virtual void    paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0)
        {

            QPixmap spritePixmap(this->iconPath);
            QBrush spriteBrush(spritePixmap);

            if (!bordered)
            {

                painter->setPen(Qt::NoPen);

            }

            painter->setBrush(spriteBrush);
            painter->drawRect(0,0,this->width,this->height);

        }

    protected:
        const int       width;
        const int       height;
        QString         iconName;
        QString         iconPath;
        bool            bordered;
        bool            dragable;
        QPointF         pointMax;
        bool            mouseDown;
        QPointF         mouseDownPoint;
        void            reDraw(void)
        {

            this->update(this->boundingRect());

        }

    protected slots:
        virtual void    sceneRectChanged(QRectF)
        {

            QRectF sceneRect = this->scene()->sceneRect();

            this->pointMax.setX(sceneRect.right()-fmod(sceneRect.right(),GameConfiguration::GRID_STEP)-this->width);
            this->pointMax.setY(sceneRect.bottom()-fmod(sceneRect.bottom(),GameConfiguration::GRID_STEP)-this->height);

        }

    private:
        void            iconUpdate()
        {

            this->iconPath = ":/images/resources/images/sprites/" + this->iconName + ".png";
            this->reDraw();

        }

    signals:
        void            dragged();
        void            deleted();

};

#endif // ABSCOMPONENT_H
