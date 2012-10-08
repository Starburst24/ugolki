#include <QtGui/QApplication>
#include "ugolkigui.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    UgolkiGUI gui;
    gui.setFixedHeight(490);
    gui.setFixedWidth(650);
    gui.show();



    return a.exec();
}
