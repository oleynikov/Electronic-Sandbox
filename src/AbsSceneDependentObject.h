#ifndef ABSSCENEDEPENDENTOBJECT_H
#define ABSSCENEDEPENDENTOBJECT_H

#include <QGraphicsObject>
#include <QGraphicsScene>

class AbsSceneDependentObject : public QGraphicsObject
{

    Q_OBJECT

    protected:
        virtual QVariant    itemChange(GraphicsItemChange change, const QVariant &value)
        {

            if (change == QGraphicsItem::ItemSceneHasChanged)
            {

                QObject::connect(this->scene(),SIGNAL(sceneRectChanged(QRectF)),this,SLOT(sceneRectChanged(QRectF)));
                this->sceneRectChanged(QRectF());

            }

            return QGraphicsItem::itemChange(change, value);

        }

    protected slots:
        virtual void        sceneRectChanged(QRectF) = 0;

};

#endif // ABSSCENEDEPENDENTOBJECT_H
