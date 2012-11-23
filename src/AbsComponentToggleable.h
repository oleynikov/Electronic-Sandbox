#ifndef ABSCOMPONENTTOGGLEABLE_H
#define ABSCOMPONENTTOGGLEABLE_H

#include "AbsComponentElectronic.h"

class AbsComponentToggleable : public AbsComponentElectronic
{

    Q_OBJECT

    public:
                AbsComponentToggleable      (
                                                QString         iconName = "AbsComponentToggleable",
                                                ComponentType   logicType = COMPONENT_TYPE_LOGICAL,
                                                int             width = 60,
                                                int             height = 60,
                                                bool            bordered = false,
                                                bool            dragable = true,
                                                bool            isToggled = false
                                            )
                                            :   AbsComponentElectronic(iconName,logicType,width,height,bordered,dragable)
        {

            this->setToggled(isToggled);

        }
        bool    getToggled() const
        {

            return this->isToggled;

        }
        void    setToggled(bool toggled)
        {

            if(toggled)
                this->iconPath = ":/images/resources/images/sprites/" + this->iconName + "Enabled.png";
            else
                this->iconPath = ":/images/resources/images/sprites/" + this->iconName + "Disabled.png";

            this->isToggled = toggled;
            this->update(this->boundingRect());
            emit this->toggled(this->isToggled);

        }
        void    toggle(void)
        {

            this->setToggled(!this->isToggled);

        }

    protected:
        bool    isToggled;

    signals:
        void    toggled(bool);

};

#endif // ABSCOMPONENTTOGGLEABLE_H
