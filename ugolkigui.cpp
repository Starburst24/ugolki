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


    for (int i = 0; i < DESK_HEIGHT; i++)
        for (int j = 0; j < DESK_WIDTH; j++){
            scene->addRect(DESK_HORIZONTAL_OFFSET_PIXELS +      //Cell start X
                           j * DESK_PIXEL_WIDTH / DESK_WIDTH,
                           DESK_VERTICAL_OFFSET_PIXELS +        //Cell start Y
                           i * DESK_PIXEL_HEIGHT / DESK_HEIGHT,
                           DESK_PIXEL_WIDTH / DESK_WIDTH,       //Cell WIDTH
                           DESK_PIXEL_HEIGHT / DESK_HEIGHT,     //Cell Height
                           pen, (i * DESK_WIDTH + j) % 2 == 0 ? black : white
                          );
        }

}
