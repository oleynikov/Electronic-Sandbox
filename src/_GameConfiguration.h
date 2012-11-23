#ifndef GAMECONFIGURATION_H
#define GAMECONFIGURATION_H

#include <QColor>

class GameConfiguration
{

    public:
        static const int WINDOW_WIDTH = 640;
        static const int WINDOW_HEIGHT = 480;
        static const int GRID_STEP = 10;
        static const int GRID_LINE_WIDTH = 1;
        static const QColor wireFalseColor;
        static const QColor wireTrueColor;

};

#endif // GAMECONFIGURATION_H
