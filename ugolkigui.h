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

    // элементы меню
    QWidget menuWidget;
    // кнопки меню
    QList<QPushButton*> menuButtons;
    QSignalMapper *menuButtonsSignalMapper;
    QVBoxLayout menuLayout;

    // элементы игрового поля
    QWidget *deskWidget;
    // кнопки поля - клетки
    QList<QPushButton*> deskButtons;
    QSignalMapper *deskButtonsSignalMapper;
    QVBoxLayout deskVerticalLayout;
    QGridLayout deskLayout;
    QPlainTextEdit informationTextEdit;
    QLineEdit messageEdit;
    QPushButton okButton;
    QList<const QString*> styleDarkForPlayer;
    QList<const QString*> styleBrightForPlayer;

    // элементы окна уведомлений
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
