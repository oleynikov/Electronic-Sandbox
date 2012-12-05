#ifndef ABSCOMPONENTTOGGLEABLEMANUALEF_H
#define ABSCOMPONENTTOGGLEABLEMANUALEF_H

#include <QObject>
#include <QEvent>
#include <QGraphicsSceneMouseEvent>

class AbsComponentToggleableManualEF : public QObject
{

    Q_OBJECT

    protected:
        bool eventFilter(QObject* object, QEvent* event)
        {

            QEvent::Type eventType = event->type();


            switch(eventType)
            {

                case QEvent::GraphicsSceneMouseRelease:
                {

                    QGraphicsSceneMouseEvent* gEvent = static_cast<QGraphicsSceneMouseEvent*>(event);

                    if (gEvent->button()==Qt::LeftButton && gEvent->scenePos()==gEvent->buttonDownScenePos(Qt::LeftButton))
                    {

                        emit mouseRelease();

                    }

                    break;

                }

                default:
                {

                    break;

                }

            }

            return false;

        }

    signals:
        void mouseMove();
        void mouseRelease();

};

#endif // ABSCOMPONENTTOGGLEABLEMANUALEF_H
