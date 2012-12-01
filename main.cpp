#include <QtGui/QApplication>
#include "ugolkigui.h"
#include "ugolkimodel.h"
#include "ugolkinetwork.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    UgolkiGUI gui;
    UgolkiModel model;
    UgolkiNetwork network;


    return a.exec();
}
