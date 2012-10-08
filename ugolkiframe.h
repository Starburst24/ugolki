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

    char table[DESK_HEIGHT][DESK_WIDTH];

signals:

public slots:

};

#endif // UGOLKIFRAME_H
