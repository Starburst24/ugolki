#include "ugolkigui.h"

UgolkiGUI::UgolkiGUI(QWidget *parent) :
    QWidget(parent)
{
    scene = new QGraphicsScene(0, 0, SCENE_WIDTH, SCENE_HEIGHT);
    view = new QGraphicsView(scene, this);

    view->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    scene->addEllipse(0,0,100,100);
    scene->addText("HI");
    drawDesk();
    view->show();
}

void UgolkiGUI::drawFrame(UgolkiFrame *frame){

}

void UgolkiGUI::drawDesk(){

    QBrush black, white;
    black.setColor(Qt::black);
    white.setColor(Qt::white);
    QPen pen;
    pen.setColor(Qt::red);

    scene->addRect(0,0, 100, 100, pen, black);


    for (int i = 0; i < DESK_SIZE; i++)
        for (int j = 0; j < DESK_SIZE; j++){
            scene->addRect(DESK_HORIZONTAL_OFFSET_PIXELS +      //Cell start X
                           j * DESK_SIZE_PIXEL / DESK_SIZE,
                           DESK_VERTICAL_OFFSET_PIXELS +        //Cell start Y
                           i * DESK_SIZE_PIXEL / DESK_SIZE,
                           DESK_SIZE_PIXEL / DESK_SIZE,       //Cell WIDTH
                           DESK_SIZE_PIXEL / DESK_SIZE,     //Cell Height
                           pen, (i * DESK_SIZE + j) % 2 == 0 ? black : white
                          );
        }

}
