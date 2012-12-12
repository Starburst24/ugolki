#include <QtGui/QApplication>
#include "ugolkigui.h"
#include "ugolkimodel.h"
#include "ugolkinetwork.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    UgolkiNetwork network;
    UgolkiAI ai;
    UgolkiModel model(&network, &ai);
    UgolkiGUI gui(&model, &network);

    return a.exec();
}
