#ifndef UGOLKIMODEL_H
#define UGOLKIMODEL_H

#include <QObject>
#include "ugolkiframe.h"
#include "ugolkiai.h"
#include "ugolkinetwork.h"



class UgolkiModel : public QObject
{
    Q_OBJECT
public:
    explicit UgolkiModel(UgolkiNetwork *network, UgolkiAI *ai, QObject *parent = 0);
    int gameMode;

private:
    UgolkiNetwork *network;
    UgolkiAI *ai;

signals:
    void gameOver(QString reason);
    void modelMessage(QString message);

public:
    UgolkiFrame currentFrame;

private slots:
    void gameOverHandler();
    bool checkBoundsOfSquare(int currentRow, int currentColumn);
    void watchNeighboringSquares(int currentRow, int currentColumn, UgolkiFrame *currentFrame);
    void searchForJumps(int currentRow,
                        int currentColumn,
                        UgolkiFrame *currentFrame,
                        bool visitedSquares[DESK_SIZE][DESK_SIZE],
                        int *firstSquare);

public slots:
    void calculatePossibleMoves(UgolkiFrame *currentFrame);
    void turnHandler(int oldPosRow, int oldPosColumn,
                     int newPosRow, int newPosColumn);


};

#endif // UGOLKIMODEL_H
