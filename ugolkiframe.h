#ifndef UGOLKIFRAME_H
#define UGOLKIFRAME_H

#include <QList>
#include "variables.h"
#include <QObject>

class UgolkiFrame : public QObject
{
    Q_OBJECT
public:
    explicit UgolkiFrame(QObject *parent = 0);


private:
    char currentPlayersTurnId;
    char matrix[DESK_SIZE][DESK_SIZE];
    int turnCount;

signals:

public slots:
    void movePiece(int oldPosRow, int oldPosColumn, int newPosRow, int newPosColumn);

};

#endif // UGOLKIFRAME_H
