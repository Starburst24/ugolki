#ifndef UGOLKIGUI_H
#define UGOLKIGUI_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <ugolkiframe.h>
#include "variables.h"

class UgolkiGUI : public QWidget
{
    Q_OBJECT
public:
    explicit UgolkiGUI(QWidget *parent = 0);

private:
    QGraphicsView *view;
    QGraphicsScene *scene;

private slots:
    void drawFrame(UgolkiFrame*);
    void drawDesk();

signals:

public slots:

};

#endif // UGOLKIGUI_H
