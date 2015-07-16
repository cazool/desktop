#include "common.h"
#include "desktop.h"


int main(int argc, char *argv[])
{

    qsrand(time(NULL));

    QApplication a(argc, argv);

    Desktop d;
    d.show();

    return a.exec();
}
