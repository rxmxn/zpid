#include <QtGui/QApplication>
#include "xcontrolador.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    xControlador w;
    w.show();

    return a.exec();
}
