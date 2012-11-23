#include <QApplication>

#include "_WindowMain.h"

int main(int argc, char* argv[])
{

    QApplication application(argc,argv);

    GameWindow window;
    window.show();

    return application.exec();

}
