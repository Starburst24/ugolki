#ifndef UGOLKIGUI_H
#define UGOLKIGUI_H

#include <QGridLayout>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QList>
#include <QPushButton>
#include <QResizeEvent>
#include <QSignalMapper>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QWidget>

#include "ugolkimodel.h"
#include "variables.h"


class UgolkiGUI : public QWidget
{
    Q_OBJECT
public:
    explicit UgolkiGUI(UgolkiModel *modelRef, UgolkiNetwork *network, QWidget *parent = 0);

private:

    UgolkiModel *model;
    UgolkiNetwork *network;
    bool pieceSelected;
    int selectedPiece;
    int gameMode;

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

    void infoPrint(QString);
    void sendMessageButtonClicked();

    const QString getStyleSheet(int playerId, bool isWhiteCell, bool isSelected = false, bool isReselectable = false);



signals:

public slots:

};

#endif // UGOLKIGUI_H
