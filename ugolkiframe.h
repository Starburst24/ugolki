#ifndef UGOLKIFRAME_H
#define UGOLKIFRAME_H

#include <QList>
#include <QPair>
#include "variables.h"
#include <QObject>

class UgolkiFrame : public QObject
{
    Q_OBJECT
public:
    explicit UgolkiFrame(QObject *parent = 0);
    QList< QPair<int,int> > possibleMoves[ DESK_SIZE ][ DESK_SIZE ];

    char currentPlayersTurnId;
    char matrix[ DESK_SIZE ][ DESK_SIZE ];
    int turnCount;

private:



signals:
    void frameChanged(UgolkiFrame* thisFrame);

public slots:
    void resetFrame();
    void movePiece(int oldPosRow, int oldPosColumn, int newPosRow, int newPosColumn);
    bool validateMove(int oldPosRow, int oldPosColumn, int newPosRow, int newPosColumn);

};

#endif // UGOLKIFRAME_H
