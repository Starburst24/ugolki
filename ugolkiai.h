#ifndef UGOLKIAI_H
#define UGOLKIAI_H

#include <QObject>
#include "ugolkiframe.h"
#include "variables.h"


class UgolkiAI : public QObject
{
    Q_OBJECT
public:
    explicit UgolkiAI(QObject *parent = 0);
    
signals:
    void turnTask(UgolkiFrame *frame);
    void calculatePossibleMovesTask(UgolkiFrame *frame);
    void botTurnReady(int oldPosRow, int oldPosColumn, int newPosRow, int newPosColumn);

private slots:
    double bestMove(UgolkiFrame *frame, int depth);
    double criteriaDistanceToHouse(UgolkiFrame *frame);
    double criteriaPiecesInHouse(UgolkiFrame *frame);
    double criteriaHousePunishment(UgolkiFrame *frame);

    double distance(int i, int j, int k, int l);

public slots:
    void calculateBestMove(UgolkiFrame* frame);
};

#endif // UGOLKIAI_H
