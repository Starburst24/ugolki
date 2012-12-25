#ifndef UGOLKIAI_H
#define UGOLKIAI_H

#include <QObject>
#include <QHash>
#include "ugolkiframe.h"
#include "stdlib.h"
#include "variables.h"

class UgolkiAI : public QObject
{
    Q_OBJECT
public:
    explicit UgolkiAI(QObject *parent = 0);
    
private:
    QHash<QByteArray, UgolkiFrame*> *frameCache;

signals:
    void turnTask(UgolkiFrame *frame);
    void calculatePossibleMovesTask(UgolkiFrame *frame);
    void botTurnReady(int oldPosRow, int oldPosColumn, int newPosRow, int newPosColumn);

private slots:
    double alphaBetaPruning(UgolkiFrame *rootFrame, int depth, double alpha, double beta, int playerId, int opponentId);
    double heuristicValue(UgolkiFrame *frame, int playerId, int opponentId);
    bool isPlayerInHouse(UgolkiFrame *frame, int playerId, int opponentId);

public slots:
    void calculateBestMove(UgolkiFrame* frame);
};

#endif // UGOLKIAI_H
