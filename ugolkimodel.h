#ifndef UGOLKIMODEL_H
#define UGOLKIMODEL_H

#include <QObject>
#include "ugolkiframe.h"
#include "ugolkinetwork.h"
#include "ugolkiai.h"


class UgolkiModel : public QObject
{
    Q_OBJECT
public:
    explicit UgolkiModel(UgolkiNetwork *network, UgolkiAI *ai, QObject *parent = 0);

private:
    UgolkiNetwork *network;
    UgolkiAI *ai;

signals:
    void gameOver(QString reason);

public:
    UgolkiFrame currentFrame;

private slots:
    void gameOverHandler();



public slots:
    void calculatePossibleMoves(UgolkiFrame *someFrame);
    void turnHandler(int oldPosRow, int oldPosColumn,
                     int newPosRow, int newPosColumn);


};

#endif // UGOLKIMODEL_H
