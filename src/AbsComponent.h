#ifndef ABSCOMPONENT_H
#define ABSCOMPONENT_H

#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QBrush>
#include <QString>
#include "math.h"

#include "_Configuration.h"
#include "AbsSceneDependentObject.h"

class AbsComponent : public AbsSceneDependentObject
{
    Q_OBJECT

    public:
                        AbsComponent    (
                                            int     width = 60,
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
                                            selected(false)
        {

            this->iconUpdate();
            this->gridStep = Configuration::parameter("grid_step_size").toInt();

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
        bool            setSelected(bool selected)
        {

            if (this->selected != selected)
            {

                this->selected = selected;
                this->reDraw();
                return true;

            }

            return false;

        }
        bool            getBordered(void)const
        {

           return this->bordered;

        }
        bool            getDragable(void)const
        {

            return this->dragable;

        }
        bool            getSelected(void)const
        {

            return this->selected;

        }
        QRectF          getRect(void)const
        {

            QRectF rect;

            rect.setTopLeft(this->scenePos());
            rect.setSize(this->boundingRect().size());

            return rect;

        }
        virtual void    mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
        {

            if (event->button() == Qt::RightButton)
            {

                emit this->componentRemove(this);

            }

        }
        virtual QRectF  boundingRect() const
        {

            return QRectF(0,0,this->width,this->height);

        }
        virtual void    paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0)
        {

            QBrush brush;
            QPen pen(Qt::NoPen);

            painter->setPen(pen);

            if (this->selected)
            {

                brush.setStyle(Qt::SolidPattern);
                brush.setColor(QColor(78,100,133));
                painter->setBrush(brush);

                painter->drawRoundRect(0,0,this->width,this->height,10,10);

            }

            QPixmap pixmap(this->iconPath);
            brush.setTexture(pixmap);
            painter->setBrush(brush);

            painter->drawRect(0,0,this->width,this->height);

        }

    protected:
        const int       width;
        const int       height;
        QString         iconName;
        QString         iconPath;
        bool            bordered;
        bool            dragable;
        bool            selected;
        QPointF         pointMax;
        int             gridStep;
        void            reDraw(void)
        {

            this->update(this->boundingRect());

        }
        virtual void    sceneRectChangeHandler()
        {

            int gridStepSize = Configuration::parameter("grid_step_size").toInt();
            this->pointMax.setX(this->sceneRect.right()-fmod(this->sceneRect.right(),gridStepSize)-this->width);
            this->pointMax.setY(this->sceneRect.bottom()-fmod(this->sceneRect.bottom(),gridStepSize)-this->height);

        }

    private:
        void            iconUpdate()
        {

            this->iconPath = ":/images/resources/images/sprites/" + this->iconName + ".png";
            this->reDraw();

        }

    signals:
        void            componentDrag(QPointF);
        void            componentRemove(AbsComponent*);

};

#endif // ABSCOMPONENT_H
