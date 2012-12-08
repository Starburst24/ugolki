#ifndef UGOLKIAI_H
#define UGOLKIAI_H

#include <QObject>
#include "ugolkiframe.h"

class UgolkiAI : public QObject
{
    Q_OBJECT
public:
    explicit UgolkiAI(QObject *parent = 0);
    
signals:
    void botTurnReady(int oldPosRow, int oldPosColumn, int newPosRow, int newPosColumn);
    
public slots:
    void calculateBestMove(UgolkiFrame* frame);
};

#endif // UGOLKIAI_H
