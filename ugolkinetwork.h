#ifndef UGOLKINETWORK_H
#define UGOLKINETWORK_H

#include <QObject>
#include <QString>

class UgolkiNetwork : public QObject
{
    Q_OBJECT
public:
    explicit UgolkiNetwork(QObject *parent = 0);

signals:
    void networkMessage(QString message);

public slots:

};

#endif // UGOLKINETWORK_H
