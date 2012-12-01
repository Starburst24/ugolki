#ifndef UGOLKIGUI_H
#define UGOLKIGUI_H

#include <QGridLayout>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QResizeEvent>
#include <QSignalMapper>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QWidget>

#include <ugolkimodel.h>
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
    QWidget *deskWidget;
    QList<QPushButton*> deskButtons; // list of all buttons
    QSignalMapper *deskButtonsSignalMapper;
    QVBoxLayout deskVerticalLayout;
    QGridLayout deskLayout;
    QPlainTextEdit informationTextEdit;
    QLineEdit messageEdit;
    QPushButton okButton;
    QList<const QString*> styleDarkForPlayer;
    QList<const QString*> styleBrightForPlayer;
    UgolkiModel model;


    /* Notification items */
    QWidget notificationWidget;
    QPushButton notificationButton;
    QLabel notificationLabel;
    QVBoxLayout notificationLayout;

private slots:
    void drawFrame(UgolkiFrame*);
    void showMenu();
    void showNotification(QString);
    void menuButtonClicked(const int &);
    void deskButtonClicked(const int &);

    void resizeEvent(QResizeEvent *);



signals:

public slots:

};

#endif // UGOLKIGUI_H
