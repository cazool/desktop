#include "common.h"
#include "desktop.h"


int main(int argc, char *argv[])
{

    qsrand(time(NULL));
    QApplication a(argc, argv);

    qApp->setOrganizationName("o2mation");
    qApp->setOrganizationDomain("o2mation.org");
    qApp->setApplicationName("o2-desktop");

    QGraphicsView view;


//    view.setAttribute(Qt::WA_TranslucentBackground);
//    view.setAttribute(Qt::WA_DeleteOnClose);
//    view.setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnBottomHint);
//    view.setWindowState(Qt::WindowMaximized);
//    view.setGeometry(qApp->desktop()->availableGeometry());


    Desktop *desktop = new Desktop(&view);
    desktop->showScene();

    return a.exec();
}
