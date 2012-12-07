#ifndef ABSCOMPONENTSANDBOX_H
#define ABSCOMPONENTSANDBOX_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <AbsGrid.h>

#include <QDebug>

class AbsComponentSandbox : public QObject
{

    Q_OBJECT

    public:
                                    AbsComponentSandbox()
        {

            this->graphicsScene.installEventFilter(this);
            this->graphicsScene.addItem(&this->graphicsGrid);
            QObject::connect(&this->graphicsGrid,SIGNAL(select(QRectF)),this,SIGNAL(select(QRectF)));

        }
        QGraphicsScene*             getGraphicsScene(void) const
        {

            return &this->graphicsScene;

        }
        virtual bool                eventFilter(QObject*, QEvent* event)
        {

            QEvent::Type eventType = event->type();

            if (eventType == QEvent::GraphicsSceneMousePress || eventType == QEvent::GraphicsSceneMouseMove)
            {

                QGraphicsSceneMouseEvent* sceneEvent = static_cast<QGraphicsSceneMouseEvent*>(event);

                if (sceneEvent->buttons() == Qt::LeftButton)
                {

                    QGraphicsItem* item = this->graphicsScene.itemAt(sceneEvent->scenePos());

                    switch (eventType)
                    {

                        case QEvent::GraphicsSceneMousePress:
                        {
                            emit this->mouseDown(sceneEvent->buttonDownScenePos(Qt::LeftButton));

                            if (item && item != &this->graphicsGrid)
                            {

                                emit this->itemSelect(item);

                            }

                            break;
                        }

                        case QEvent::GraphicsSceneMouseMove:
                        {

                            if (item && item != &this->graphicsGrid)
                            {

                                emit this->mouseMove(sceneEvent->scenePos());
                                break;

                            }

                        }

                        default: break;

                    }

                }

            }

            return false;

        }

    public slots:
        void                        resize(QRectF rect)
        {

            this->graphicsScene.setSceneRect(rect);

        }
        void                        graphicsItemAdded(QGraphicsItem* item)
        {

            this->graphicsScene.addItem(item);

        }
        void                        graphicsItemRemoved(QGraphicsItem* item)
        {

            this->graphicsScene.removeItem(item);

        }

    protected:
        mutable QGraphicsScene      graphicsScene;
        AbsGrid                     graphicsGrid;

    signals:
        void                        select(QRectF);
        void                        mouseDown(QPointF);
        void                        mouseMove(QPointF);
        void                        itemSelect(QGraphicsItem*);

};

#endif // ABSCOMPONENTSANDBOX_H
