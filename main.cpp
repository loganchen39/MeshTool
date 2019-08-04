#include <QtGui/QApplication>

#include "meshtool.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MeshTool w;
    w.show();
    a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
    return a.exec();
}
