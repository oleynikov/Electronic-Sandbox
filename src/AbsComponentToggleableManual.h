#ifndef ABSCOMPONENTTOGGLEABLEMANUAL_H
#define ABSCOMPONENTTOGGLEABLEMANUAL_H

#include "AbsComponentToggleable.h"
#include "AbsComponentToggleableManualEF.h"

class AbsComponentToggleableManual : public AbsComponentToggleable
{

    Q_OBJECT

    public:
        AbsComponentToggleableManual    (
                                            QString         iconName = "AbsComponentToggleableManual",
                                            ComponentType   logicType = COMPONENT_TYPE_LOGICAL,
                                            int             width = 60,
                                            int             height = 60,
                                            bool            bordered = false,
                                            bool            dragable = true,
                                            bool            isToggled = false
                                        )
                                        :   AbsComponentToggleable(iconName,logicType,width,height,bordered,dragable,isToggled)
        {

            this->installEventFilter(&eventFilter);
            QObject::connect(&this->eventFilter,SIGNAL(mouseMove()),this,SLOT(mouseMove()));
            QObject::connect(&this->eventFilter,SIGNAL(mouseRelease()),this,SLOT(mouseRelease()));

        }

    private slots:
        void                            mouseMove()
        {

            if (this->mouseDown)
            {

                this->mouseMoved = true;

            }

        }
        void                            mouseRelease()
        {

            if (this->mouseMoved)
            {

                this->mouseMoved = false;
                return;

            }

            this->toggle();

        }

    private:
        AbsComponentToggleableManualEF  eventFilter;
        bool                            enabled;
        bool                            mouseMoved;

};

#endif // ABSCOMPONENTTOGGLEABLEMANUAL_H
