#ifndef UGOLKIFRAME_H
#define UGOLKIFRAME_H

#include <QList>
#include <QPair>
#include "variables.h"
//#include "math.h"
#include <cmath>
#include <QObject>

class UgolkiFrame : public QObject
{
    Q_OBJECT
public:
    explicit UgolkiFrame(QObject *parent = 0);
    explicit UgolkiFrame(const UgolkiFrame *frameToClone);

    QList< QPair<int,int> > possibleMoves[ DESK_SIZE ][ DESK_SIZE ];
    char currentPlayersTurnId;
    char matrix[ DESK_SIZE ][ DESK_SIZE ];
    int turnCount;
    QPair<int, int> playerHouse[ UGOLKI_MAXPLAYERS ];

    //criterions
    double averageDistanceToOpponentsHouse[ UGOLKI_MAXPLAYERS ];



private:

signals:
    void frameChanged(UgolkiFrame* thisFrame);

public slots:

    void resetFrame();
    void movePiece(int oldPosRow, int oldPosColumn, int newPosRow, int newPosColumn);
    bool validateMove(int oldPosRow, int oldPosColumn, int newPosRow, int newPosColumn);

    double distance(int i, int j, int k, int l);
    double distanceToHouse(int row, int column, int playersHouseId);



    bool isInHouse(int row, int column, int playersHouseId);

    int playerOpponent(int player);



};

#endif // UGOLKIFRAME_H
