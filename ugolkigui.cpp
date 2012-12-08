#include "ugolkigui.h"
#include "styles.h"

UgolkiGUI::UgolkiGUI(UgolkiModel *modelRef, UgolkiNetwork *networkRef, QWidget *parent) :
    QWidget(parent)
{

    model = modelRef;
    network = networkRef;

    /* ************************************************************* */
    /* Настраиваемокно уведомления */

    notificationLayout.addWidget(&notificationLabel);
    notificationLayout.addWidget(&notificationButton);

    QFont notificationFont;
    notificationFont.setPixelSize(NOTIFICATION_FONT_SIZE_PIXEL);

    //notificationButton.setFont(notificationFont);
    notificationLabel.setFont(notificationFont);

    notificationButton.setText(STRING_BACK_TO_MENU);


    notificationWidget.setLayout(&notificationLayout);
    notificationWidget.setWindowTitle(STRING_APPLICATION_NAME
                                      " - " STRING_NOTIFICATION);

    connect(model, SIGNAL(gameOver(QString)), SLOT(showNotification(QString)));
    connect(&notificationButton, SIGNAL(clicked()), SLOT(showMenu()));
    /* Закончили настраивать окно уведомления */
    /* ************************************************************* */


    /* ************************************************************* */
    /* Настраиваем главное меню */
    menuButtonsSignalMapper = new QSignalMapper();

    /* Для каждого режима нужно создать кнопку и прикрутить ее к карте кнопок */
    /* а также к вертикальному лейауту */


    QFont menuButtonsFont;
    menuButtonsFont.setPixelSize(MENU_BUTTONS_FONT_SIZE_PIXEL);


    /* Для всех кнопок режима */
    for (int buttonId = 0; buttonId < UGOLKI_MODES; buttonId++){

        /* Создаем новую кнопку режима и заносим ее в список кнопок меню */
        menuButtons << new QPushButton;

        menuButtons[buttonId]->setFont(menuButtonsFont);
        menuButtons[buttonId]->setFixedHeight(MENU_BUTTONS_HEIGHT_FOR_FONT_MULTIPLICATOR *
                                              MENU_BUTTONS_FONT_SIZE_PIXEL);
        /* Соединяем её с картой кнопок меню */
        connect(menuButtons[buttonId], SIGNAL(clicked()), menuButtonsSignalMapper, SLOT(map()));
        menuButtonsSignalMapper->setMapping(menuButtons[buttonId], buttonId);

        /* Добавляем кнопку в вертикальную сетку меню для отображения */
        menuLayout.addWidget(menuButtons[buttonId]);

    }

    /* Называем и настраиваем кнопки */
    menuButtons[UGOLKI_MODE_AI]->setText(STRING_MODE_AI);
    menuButtons[UGOLKI_MODE_NETWORK]->setText(STRING_MODE_NETWORK);
    menuButtons[UGOLKI_MODE_MULTIPLAYER]->setText(STRING_MODE_MULTIPLAYER);


    /* Карта кнопок соединяется с обработчиком нажатий. Обработчик в зависимости от */
    /* нажатия организует нужный режим */
    connect(menuButtonsSignalMapper, SIGNAL(mapped(const int &)),
            this, SLOT(menuButtonClicked(const int &)));

    /* Устанавливаем наш лейаут в виджет меню */
    menuWidget.setLayout(&menuLayout);
    menuWidget.setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    menuWidget.setWindowTitle(STRING_APPLICATION_NAME " - " STRING_MAIN_MENU);
    /* Закончили настраивать главное меню */
    /* ************************************************************* */


    /* ************************************************************* */
    /* Настраиваем доску */
    deskWidget = this;

    deskWidget->setFixedSize(0, 0);
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




    //deskLayout.setSpacing(0);

    deskVerticalLayout.insertLayout(0, &deskLayout);

    informationTextEdit.setReadOnly(true);

    informationTextEdit.setMaximumHeight(DESK_INFORMATION_TABLE_PIXEL_HEIGHT);

    QHBoxLayout *messageLayout = new QHBoxLayout;
    messageLayout->addWidget(&messageEdit);
    messageLayout->addWidget(&okButton);
    okButton.setText(STRING_BUTTON_SEND);

    connect(&okButton, SIGNAL(clicked()), SLOT(sendMessageButtonClicked()));


    deskVerticalLayout.insertWidget(1, &informationTextEdit);
    deskVerticalLayout.insertLayout(2, messageLayout);
    deskWidget->setLayout(&deskVerticalLayout);
    /* Закончили настраивать доску */
    /* ************************************************************* */


    /* Запускаем главное меню */
    showMenu();

}

void UgolkiGUI::resizeEvent(QResizeEvent *event){

    //  drawFrame(&model.currentFrame);

}

void UgolkiGUI::showNotification(QString message){

    notificationLabel.setText(message);

    deskWidget->hide();
    menuWidget.hide();
    notificationWidget.show();


}


void UgolkiGUI::drawFrame(UgolkiFrame *frame){

    QFont font;
    font.setPixelSize(DESK_CELL_FONT_PIXEL_SIZE);
    int cellSize = DESK_SIZE_PIXEL / DESK_SIZE;

    for (int i = 0; i < DESK_SIZE; i++){
        deskLayout.setColumnStretch(i, 1);
        deskLayout.setRowStretch(i, 1);
        for (int j = 0; j < DESK_SIZE; j++){
            int playerPieceOnCurrentCell = frame->matrix[i][j];
            bool isSelectable = false;



            if (pieceSelected == false && !model->currentFrame.possibleMoves[i][j].isEmpty() )
                isSelectable = true;

            if (pieceSelected == true && model->currentFrame.possibleMoves[selectedPiece / DESK_SIZE][selectedPiece % DESK_SIZE].contains(QPair<int,int>(i,j)))
                isSelectable = true;

            deskButtons[i * DESK_SIZE + j]->setFont(font);
            deskButtons[i * DESK_SIZE + j]->setFixedSize(cellSize, cellSize);
            deskButtons[i * DESK_SIZE + j]->setEnabled(isSelectable);
            deskButtons[i * DESK_SIZE + j]->setStyleSheet(getStyleSheet(playerPieceOnCurrentCell, ((j + i) % 2), isSelectable));

            if (playerPieceOnCurrentCell != UGOLKI_PLAYER_EMPTY)
                deskButtons[i * DESK_SIZE + j]->setText(QString::fromUtf8("●"));
            else
                deskButtons[i * DESK_SIZE + j]->setText(QString::fromUtf8(""));



        }
    }

}


void UgolkiGUI::showMenu(){
    notificationWidget.hide();
    deskWidget->hide();
    menuWidget.show();
}

void UgolkiGUI::deskButtonClicked(const int &clickedButtonId){

    /* выбираем фишку для зода если не выбрана */
    if (!pieceSelected){
        selectedPiece = clickedButtonId;

        pieceSelected = !pieceSelected;
        drawFrame(&model->currentFrame);
        return;
    }

    /* выбираем другую фишку для хода если уже была выбрана другая */
    if (model->currentFrame.matrix[clickedButtonId / DESK_SIZE][clickedButtonId % DESK_SIZE]
            == model->currentFrame.currentPlayersTurnId) {
        selectedPiece = clickedButtonId;
        drawFrame(&model->currentFrame);
        return;
    }

    /* нашли куда сходить - и ходим */
    pieceSelected = !pieceSelected;
    model->turnHandler(selectedPiece / DESK_SIZE,
                       selectedPiece % DESK_SIZE,
                       clickedButtonId / DESK_SIZE,
                       clickedButtonId % DESK_SIZE);

}

void UgolkiGUI::menuButtonClicked(const int &clickedButtonId) {

    menuWidget.hide();
    gameMode = clickedButtonId;
    pieceSelected = false;

    switch (clickedButtonId) {


    case UGOLKI_MODE_AI: /* Artificial Intelligence mode */
        deskWidget->setWindowTitle(STRING_APPLICATION_NAME " - " STRING_MODE_AI);
        model->currentFrame.resetFrame();
        deskWidget->show();
        break;


    case UGOLKI_MODE_MULTIPLAYER:   /* Multiplayer mode */

        connect(&model->currentFrame,
                SIGNAL(frameChanged(UgolkiFrame*)),
                SLOT(drawFrame(UgolkiFrame*)));
        deskWidget->setWindowTitle(STRING_APPLICATION_NAME " - " STRING_MODE_MULTIPLAYER);
        model->currentFrame.resetFrame();
        deskWidget->show();
        break;


    case UGOLKI_MODE_NETWORK: /* Network mode */
        deskWidget->setWindowTitle(STRING_APPLICATION_NAME " - " STRING_MODE_NETWORK);
        showNotification(STRING_NOT_IMPLEMENTED);
        break;
    }

}

const QString UgolkiGUI::getStyleSheet(int playerId, bool isWhiteCell, bool isSelectable){

    QString pieceColor, pressedPieceColor;
    switch (playerId){

    default:
    case 0:
        pressedPieceColor = COLOR_PRESSED_PLAYER_1;
        pieceColor = COLOR_PLAYER_1;
        break;
    case 1:
        pressedPieceColor = COLOR_PRESSED_PLAYER_2;
        pieceColor = COLOR_PLAYER_2;
        break;

    }

    QString cellColor;

    if (isSelectable) {
        cellColor = COLOR_CELL_SELECTED;
    } else
        if (isWhiteCell)
            cellColor = COLOR_BLACK;
        else
            cellColor = COLOR_WHITE;

    const QString genericStyleSheet ("QPushButton {"
                                     "border: 1px solid #888888;"
                                     "border-radius: 1px;"
                                     "text-align: center;"
                                     "color: " + pieceColor + ";"
                                     "background-color: " + cellColor + ";"
                                     "}"

                                     "QPushButton:pressed {"
                                     "border: 1px solid #888888;"
                                     "border-radius: 1px;"
                                     "color: " + pressedPieceColor + ";"
                                     "background-color: " + cellColor + ";"

                                     "}"

                                     "QPushButton:disabled {"
                                     "border: 1px solid #888888;"
                                     "border-radius: 1px;"
                                     "color: " + pieceColor + ";"
                                     "background-color: " + cellColor + ";"

                                     "}"

                                     "QPushButton:flat {"
                                     "border: none; "
                                     "}");

    return genericStyleSheet;
}

void UgolkiGUI::sendMessageButtonClicked(){
    infoPrint(messageEdit.text() + QString("\n"));
}

void UgolkiGUI::infoPrint(QString string){
    informationTextEdit.insertPlainText(string);
}
