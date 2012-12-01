#include "ugolkigui.h"
#include "styles.h"

UgolkiGUI::UgolkiGUI(QWidget *parent) :
    QWidget(parent)
{

    /* ************************************************************* */
    /* Настраиваемокно уведомления */

    notificationLayout.addWidget(&notificationLabel);
    notificationLayout.addWidget(&notificationButton);

    notificationButton.setText("Back to menu");

    notificationWidget.setLayout(&notificationLayout);
    notificationWidget.setWindowTitle("Ugolki - Notification");

    connect(&notificationButton, SIGNAL(clicked()), SLOT(showMenu()));
    /* Закончили настраивать окно уведомления */
    /* ************************************************************* */


    /* ************************************************************* */
    /* Настраиваем главное меню */
    menuButtonsSignalMapper = new QSignalMapper();

    /* Для каждого режима нужно создать кнопку и прикрутить ее к карте кнопок */
    /* а также к вертикальному лейауту */

    /* Для всех кнопок режима */
    for (int buttonId = 0; buttonId < UGOLKI_MODES; buttonId++){

        /* Создаем новую кнопку режима и заносим ее в список кнопок меню */
        menuButtons << new QPushButton;

        /* Соединяем её с картой кнопок меню */
        connect(menuButtons[buttonId], SIGNAL(clicked()), menuButtonsSignalMapper, SLOT(map()));
        menuButtonsSignalMapper->setMapping(menuButtons[buttonId], buttonId);

        /* Добавляем кнопку в вертикальную сетку меню для отображения */
        menuLayout.addWidget(menuButtons[buttonId]);

    }

    /* Называем и настраиваем кнопки */
    menuButtons[UGOLKI_MODE_AI]->setText("Game with A.I.");
    menuButtons[UGOLKI_MODE_NETWORK]->setText("Network game");
    menuButtons[UGOLKI_MODE_MULTIPLAYER]->setText("Two-players game");
    for (int buttonId = 0; buttonId < UGOLKI_MODES; buttonId++){
        menuButtons[buttonId]->setFixedSize(300, 100);
    }

    /* Карта кнопок соединяется с обработчиком нажатий. Обработчик в зависимости от */
    /* нажатия организует нужный режим */
    connect(menuButtonsSignalMapper, SIGNAL(mapped(const int &)),
            this, SLOT(menuButtonClicked(const int &)));

    /* Устанавливаем наш лейаут в виджет меню */
    menuWidget.setLayout(&menuLayout);
    menuWidget.setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    menuWidget.setWindowTitle("Ugolki - Main Menu");
    /* Закончили настраивать главное меню */
    /* ************************************************************* */


    /* ************************************************************* */
    /* Настраиваем доску */
    deskWidget = this;

    deskWidget->sizePolicy().setHeightForWidth(true);
    deskButtonsSignalMapper = new QSignalMapper();

    /* Создаем кнопки игрового поля и прикручиваем их к карте кнопок */
    /* а также к сеточному лейауту */

    /* Для всех кнопок игрового поля */
    for (int buttonId = 0; buttonId < DESK_SIZE * DESK_SIZE; buttonId++){

        /* Создаем новую кнопку поля и заносим ее в список */
        deskButtons << new QPushButton;

        deskButtons[buttonId]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

        /* Соединяем её с картой кнопок игрового поля */
        connect(deskButtons[buttonId], SIGNAL(clicked()), deskButtonsSignalMapper, SLOT(map()));
        deskButtonsSignalMapper->setMapping(deskButtons[buttonId], buttonId);

        /* Добавляем кнопку в сетку меню для отображения */
        deskLayout.addWidget(deskButtons[buttonId],
                             buttonId / DESK_SIZE,
                             buttonId % DESK_SIZE);
    }

    /* Карта кнопок соединяется с обработчиком нажатий */
    connect(deskButtonsSignalMapper, SIGNAL(mapped(const int &)),
            this, SLOT(deskButtonClicked(const int &)));

    styleDarkForPlayer << &styleDarkPlayer1;
    styleDarkForPlayer << &styleDarkPlayer2;
    styleBrightForPlayer << &styleBrightPlayer1;
    styleBrightForPlayer << &styleBrightPlayer2;


    deskLayout.setSpacing(0);

    deskWidget->sizePolicy().setHeightForWidth(true);


    deskVerticalLayout.insertLayout(0, &deskLayout);

    informationTextEdit.setEnabled(false);
    informationTextEdit.setMaximumHeight(70);
    QHBoxLayout *messageLayout = new QHBoxLayout;
    messageLayout->addWidget(&messageEdit);
    messageLayout->addWidget(&okButton);
    okButton.setText("Send");


    deskVerticalLayout.insertWidget(1, &informationTextEdit);
    deskVerticalLayout.insertLayout(2, messageLayout);
    deskWidget->setLayout(&deskVerticalLayout);
    /* Закончили настраивать доску */
    /* ************************************************************* */


    /* Запускаем главное меню */
    showMenu();

}

void UgolkiGUI::resizeEvent(QResizeEvent *event){



}

void UgolkiGUI::showNotification(QString message){

    notificationLabel.setText(message);

    deskWidget->hide();
    menuWidget.hide();
    notificationWidget.show();


}


void UgolkiGUI::drawFrame(UgolkiFrame *frame){


    for (int i = 0; i < DESK_SIZE; i++)
        for (int j = 0; j < DESK_SIZE; j++){
            int playerPieceOnCurrentCell = frame->matrix[i][j];
            if (playerPieceOnCurrentCell == -1){
                if ((j + i)%2 == 0)
                    deskButtons[i * DESK_SIZE + j]->setStyleSheet(*styleBrightForPlayer.first());
                else
                    deskButtons[i * DESK_SIZE + j]->setStyleSheet(*styleDarkForPlayer.first());
                continue;
            }

            deskButtons[i * DESK_SIZE + j]->setText("0");

            if ((j + i)%2 == 0)
                deskButtons[i * DESK_SIZE + j]->setStyleSheet(*styleBrightForPlayer[playerPieceOnCurrentCell]);
            else
                deskButtons[i * DESK_SIZE + j]->setStyleSheet(*styleDarkForPlayer[playerPieceOnCurrentCell]);
        }

}


void UgolkiGUI::showMenu(){
    notificationWidget.hide();
    deskWidget->hide();
    menuWidget.show();
}

void UgolkiGUI::deskButtonClicked(const int &clickedButtonId){

    showNotification("Game over");
    menuWidget.hide();
    deskWidget->hide();
}

void UgolkiGUI::menuButtonClicked(const int &clickedButtonId){
    menuWidget.hide();
    switch (clickedButtonId){


    case UGOLKI_MODE_AI: /* Artificial Intelligence mode */
        showNotification("Not implemented yet");
        break;


    case UGOLKI_MODE_MULTIPLAYER:   /* Multiplayer mode */

        deskWidget->show();
        model.currentFrame.resetFrame();
        drawFrame(&model.currentFrame);
        break;


    case UGOLKI_MODE_NETWORK: /* Network mode */

        showNotification("Not implemented yet");
        break;
    }



}
