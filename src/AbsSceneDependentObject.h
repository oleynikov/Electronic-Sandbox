#ifndef ABSSCENEDEPENDENTOBJECT_H
#define ABSSCENEDEPENDENTOBJECT_H

#include <QGraphicsObject>
#include <QGraphicsScene>
#include <QRectF>

class AbsSceneDependentObject : public QGraphicsObject
{

    Q_OBJECT

    protected:
        QRectF              sceneRect;
        virtual void        sceneRectChangeHandler()
        {

        }
        virtual QVariant    itemChange(GraphicsItemChange change, const QVariant &value)
        {

            if (change == QGraphicsItem::ItemSceneHasChanged)
            {

                this->sceneRectChanged(this->scene()->sceneRect());
                QObject::connect(this->scene(),SIGNAL(sceneRectChanged(QRectF)),this,SLOT(sceneRectChanged(QRectF)));

            }

            return QGraphicsItem::itemChange(change, value);

        }

    protected slots:
        virtual void        sceneRectChanged(QRectF sceneRect)
        {

            this->sceneRect = sceneRect;
            this->sceneRectChangeHandler();
        }

};

#endif // ABSSCENEDEPENDENTOBJECT_H
