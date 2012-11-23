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

                case QEvent::GraphicsSceneMouseMove:
                {

                    emit mouseMove();
                    break;

                }

                case QEvent::GraphicsSceneMouseRelease:
                {

                    if (static_cast<QGraphicsSceneMouseEvent*>(event)->button() == Qt::LeftButton)
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
