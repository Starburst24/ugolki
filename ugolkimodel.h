#ifndef UGOLKIMODEL_H
#define UGOLKIMODEL_H

#include <QObject>
#include <ugolkiframe.h>

class UgolkiModel : public QObject
{
    Q_OBJECT
public:
    explicit UgolkiModel(QObject *parent = 0);

signals:
    void gameOver(QString reason);

public:
    UgolkiFrame currentFrame;

private slots:
    void gameOverHandler();
    void turnHandler(int oldPosRow, int oldPosColumn,
                     int newPosRow, int newPosColumn);


public slots:
    void calculatePossibleMoves(UgolkiFrame *someFrame);


};

#endif // UGOLKIMODEL_H
