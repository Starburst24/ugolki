#ifndef UGOLKIGUI_H
#define UGOLKIGUI_H

#include <QGridLayout>
#include <QLayout>
#include <QPushButton>
#include <QSignalMapper>
#include <QVBoxLayout>
#include <QWidget>
#include <ugolkiframe.h>
#include "variables.h"

class UgolkiGUI : public QWidget
{
    Q_OBJECT
public:
    explicit UgolkiGUI(QWidget *parent = 0);

private:
    /* Menu items */
    QWidget menuWidget;
    QList<QPushButton*> menuButtons; // list of all buttons
    QSignalMapper *menuButtonsSignalMapper;
    QVBoxLayout menuLayout;

    /* Desk items */
    QWidget deskWidget;
    QList<QPushButton*> deskButtons; // list of all buttons
    QSignalMapper *deskButtonsSignalMapper;
    QVBoxLayout deskVerticalLayout;
    QGridLayout deskLayout;


private slots:
    void drawFrame(UgolkiFrame*);
    void showDesk(int gameMode);
    void showMenu();
    void menuButtonClicked(const int &);
    void deskButtonClicked(const int &);
signals:

public slots:

};

#endif // UGOLKIGUI_H
