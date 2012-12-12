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
    //todo: separate criterias into one function
    double criteriaDistanceToOpponentsHouse(UgolkiFrame *frame, bool invert = false);
    double criteriaPiecesInHouse(UgolkiFrame *frame, bool invert = false);
    double criteriaHousePunishment(UgolkiFrame *frame, bool invert = false);

public slots:
    void calculateBestMove(UgolkiFrame* frame);
};

#endif // UGOLKIAI_H
