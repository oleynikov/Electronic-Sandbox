#ifndef AGRAPHICSSANDBOX_H
#define AGRAPHICSSANDBOX_H

#include <AInteractiveScene.h>
#include <AGraphicsController.h>

class AGraphicsSandbox : public QObject
{

    Q_OBJECT

    public:
                                AGraphicsSandbox()
        {

            this->graphicsScene = new AInteractiveScene();
            this->controller = new AGraphicsController();

            QObject::connect(this->graphicsScene,SIGNAL(newEvent(QEvent*)),this,SLOT(newEvent(QEvent*)));

        }
        QGraphicsScene*         getScene(void) const
        {

            return this->graphicsScene;

        }
        AGraphicsController*    getController(void) const
        {

            return this->controller;

        }
        void                    addItem(QGraphicsItem* item)
        {

            if (this->controller->addItem(item))
            {

                this->graphicsScene->addItem(item);

            }

        }
        void                    removeItem(QGraphicsItem* item)
        {

            this->controller->removeItem(item);

        }

    protected:
        AInteractiveScene*      graphicsScene;
        AGraphicsController*    controller;

    protected slots:
        virtual void            newEvent(QEvent*)
        {

        }

};

#endif // AGRAPHICSSANDBOX_H
