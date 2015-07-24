#include "common.h"
#include "desktop.h"


int main(int argc, char *argv[])
{

    qsrand(time(NULL));

    QApplication a(argc, argv);

    QGraphicsView view;

    Desktop *desktop = new Desktop(&view);
    desktop->showScene();

    return a.exec();
}
