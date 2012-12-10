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

    bool checkBoundsOfSquare(int currentRow, int currentColumn);
    void clearVisited(bool visitedSquares[DESK_SIZE][DESK_SIZE]);
    void watchNeighboringSquares(int currentRow, int currentColumn, UgolkiFrame *currentFrame);
    void searchForJumps(int currentRow,
                        int currentColumn,
                        UgolkiFrame *currentFrame,
                        bool visitedSquares[DESK_SIZE][DESK_SIZE],
                        int *firstSquare);


signals:
    void gameOver(QString reason);

public:
    UgolkiFrame currentFrame;

private slots:
    void gameOverHandler();



public slots:
    void calculatePossibleMoves(UgolkiFrame *currentFrame);
    void turnHandler(int oldPosRow, int oldPosColumn,
                     int newPosRow, int newPosColumn);


};

#endif // UGOLKIMODEL_H
