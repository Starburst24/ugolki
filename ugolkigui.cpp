#include "ugolkigui.h"

UgolkiGUI::UgolkiGUI(QWidget *parent) :
    QWidget(parent)
{
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
    deskButtonsSignalMapper = new QSignalMapper();

    /* Создаем кнопки игрового поля и прикручиваем их к карте кнопок */
    /* а также к сеточному лейауту */

    /* Для всех кнопок игрового поля */
    for (int buttonId = 0; buttonId < DESK_SIZE * DESK_SIZE; buttonId++){

        /* Создаем новую кнопку поля и заносим ее в список */
        deskButtons << new QPushButton;

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

    deskVerticalLayout.insertLayout(0, &deskLayout);
    deskWidget.setLayout(&deskVerticalLayout);
    /* Закончили настраивать доску */
    /* ************************************************************* */


    /* Запускаем главное меню */
    showMenu();

}

void UgolkiGUI::drawFrame(UgolkiFrame *frame){

}

void UgolkiGUI::showDesk(int gameMode){

    switch (gameMode){


    case UGOLKI_MODE_AI: /* Artificial Intelligence mode */
        deskWidget.setWindowTitle("Ugolki - Artificial Intelligence Mode");
        break;


    case UGOLKI_MODE_MULTIPLAYER:   /* Multiplayer mode */

        deskWidget.setWindowTitle("Ugolki - Multiplayer Mode");
        break;


    case UGOLKI_MODE_NETWORK: /* Network mode */

        deskWidget.setWindowTitle("Ugolki - Network Mode");
        break;
    }


    deskWidget.show();
    menuWidget.hide();
}

void UgolkiGUI::showMenu(){
    deskWidget.hide();
    menuWidget.show();
}

void UgolkiGUI::deskButtonClicked(const int &clickedButtonId){

    menuWidget.show();
    deskWidget.hide();
}

void UgolkiGUI::menuButtonClicked(const int &clickedButtonId){
    switch (clickedButtonId){


    case UGOLKI_MODE_AI: /* Artificial Intelligence mode */

        break;


    case UGOLKI_MODE_MULTIPLAYER:   /* Multiplayer mode */


        break;


    case UGOLKI_MODE_NETWORK: /* Network mode */


        break;
    }
    showDesk(clickedButtonId);
    menuWidget.hide();

}
