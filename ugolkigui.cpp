#include "ugolkigui.h"
#include "styles.h"

UgolkiGUI::UgolkiGUI(UgolkiModel *modelRef, UgolkiNetwork *networkRef, QWidget *parent) :
    QWidget(parent)
{

    model = modelRef;
    network = networkRef;

    /* ************************************************************* */
    // настраиваем окно уведомления
    QFont notificationFont;

    notificationLayout.addWidget(&notificationLabel);
    notificationLayout.addWidget(&notificationButton);    

    notificationFont.setPixelSize(NOTIFICATION_FONT_SIZE_PIXEL);
    notificationLabel.setFont(notificationFont);
    notificationButton.setText(STRING_BACK_TO_MENU);
    notificationWidget.setLayout(&notificationLayout);
    notificationWidget.setWindowTitle(STRING_APPLICATION_NAME
                                      " - " STRING_NOTIFICATION);

    // при завершении игры открываем окно уведомлений
    connect(model, SIGNAL(gameOver(QString)), SLOT(showNotification(QString)));
    connect(&notificationButton, SIGNAL(clicked()), SLOT(showMenu()));

    /* ************************************************************* */
    // настраиваем главное меню
    QFont menuButtonsFont;

    menuButtonsSignalMapper = new QSignalMapper();

    // для каждого режима нужно создать кнопку и прикрутить ее к карте кнопок
    // а также к вертикальному лейауту
    menuButtonsFont.setPixelSize(MENU_BUTTONS_FONT_SIZE_PIXEL);

    // для всех кнопок режима
    for (int buttonId = 0; buttonId < UGOLKI_MODES; buttonId++) {
        // создаем новую кнопку режима и заносим ее в список кнопок меню
        menuButtons << new QPushButton;

        menuButtons[buttonId]->setFont(menuButtonsFont);
        menuButtons[buttonId]->setFixedHeight(MENU_BUTTONS_HEIGHT_FOR_FONT_MULTIPLICATOR *
                                              MENU_BUTTONS_FONT_SIZE_PIXEL);
        // соединяем её с картой кнопок меню
        connect(menuButtons[buttonId], SIGNAL(clicked()), menuButtonsSignalMapper, SLOT(map()));
        menuButtonsSignalMapper->setMapping(menuButtons[buttonId], buttonId);

        // добавляем кнопку в вертикальную сетку меню для отображения
        menuLayout.addWidget(menuButtons[buttonId]);
    }

    // называем и настраиваем кнопки
    menuButtons[UGOLKI_MODE_AI]->setText(STRING_MODE_AI);
    menuButtons[UGOLKI_MODE_NETWORK]->setText(STRING_MODE_NETWORK);
    menuButtons[UGOLKI_MODE_MULTIPLAYER]->setText(STRING_MODE_MULTIPLAYER);

    // карта кнопок соединяется с обработчиком нажатий. обработчик в зависимости от
    // нажатия организует нужный режим
    connect(menuButtonsSignalMapper, SIGNAL(mapped(const int &)),
            this, SLOT(menuButtonClicked(const int &)));

    // устанавливаем наш лейаут в виджет меню
    menuWidget.setLayout(&menuLayout);
    menuWidget.setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    menuWidget.setWindowTitle(STRING_APPLICATION_NAME " - " STRING_MAIN_MENU);

    /* ************************************************************* */
    // настраиваем доску
    deskWidget = this;
    deskWidget->setFixedSize(0, 0);
    deskButtonsSignalMapper = new QSignalMapper();

    // создаем кнопки игрового поля и прикручиваем их к карте кнопок
    // а также к сеточному лейауту

    // для всех кнопок игрового поля
    for (int buttonId = 0; buttonId < DESK_SIZE * DESK_SIZE; buttonId++) {

        // создаем новую кнопку поля и заносим ее в список
        deskButtons << new QPushButton;
        deskButtons[buttonId]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

        // соединяем её с картой кнопок игрового поля
        connect(deskButtons[buttonId], SIGNAL(clicked()), deskButtonsSignalMapper, SLOT(map()));
        deskButtonsSignalMapper->setMapping(deskButtons[buttonId], buttonId);

        // Добавляем кнопку в сетку меню для отображения
        deskLayout.addWidget(deskButtons[buttonId],
                             buttonId / DESK_SIZE,
                             buttonId % DESK_SIZE);
    }

    // Карта кнопок соединяется с обработчиком нажатий
    connect(deskButtonsSignalMapper, SIGNAL(mapped(const int &)),
            this, SLOT(deskButtonClicked(const int &)));

    deskLayout.setSpacing(0);
    deskVerticalLayout.insertLayout(0, &deskLayout);

    /* ************************************************************* */
    // настраиваем информационное поле
    informationTextEdit.setReadOnly(true);
    informationTextEdit.setMaximumHeight(DESK_INFORMATION_TABLE_PIXEL_HEIGHT);

    QHBoxLayout *messageLayout = new QHBoxLayout;
    messageLayout->addWidget(&messageEdit);
    messageLayout->addWidget(&okButton);
    okButton.setText(STRING_BUTTON_SEND);

    connect(&okButton, SIGNAL(clicked()), SLOT(sendMessageButtonClicked()));
    connect(model, SIGNAL(modelMessage(QString)), SLOT(infoPrint(QString)));

    deskVerticalLayout.insertWidget(1, &informationTextEdit);
    deskVerticalLayout.insertLayout(2, messageLayout);
    deskWidget->setLayout(&deskVerticalLayout);

    connect(&model->currentFrame,
            SIGNAL(frameChanged(UgolkiFrame*)),
            SLOT(drawFrame(UgolkiFrame*)));

    // Запускаем главное меню
    showMenu();
}

void UgolkiGUI::showNotification(QString message)
{
    // показываем сообщение
    notificationLabel.setText(message);
    // закрываем главное окно, показываем окно уведомлений
    menuWidget.hide();
    deskWidget->setEnabled(false);
    notificationWidget.show();
}

void UgolkiGUI::drawFrame(UgolkiFrame *frame)
{
    // настройка шрифтов
    QFont font;
    font.setPixelSize(DESK_CELL_FONT_PIXEL_SIZE);
    int cellSize = DESK_SIZE_PIXEL / DESK_SIZE;

    for (int i = 0; i < DESK_SIZE; i++) {
        // делаем нерастяжимыми клетки поля
        deskLayout.setColumnStretch(i, 1);
        deskLayout.setRowStretch(i, 1);
        for (int j = 0; j < DESK_SIZE; j++) {
            // id игрока камня текущей клетки
            int playerPieceOnCurrentCell = frame->matrix[i][j];
            // свойства клетки i,j по умолчанию
            bool isSelected = false;
            bool isSelectable = false;
            bool isReselectable = false;

            if (pieceSelected == true &&
                    model->currentFrame.matrix[i][j] == model->currentFrame.currentPlayersTurnId &&
                    !model->currentFrame.possibleMoves[i][j].isEmpty())
                isReselectable = isSelectable = true;

            if (pieceSelected == true && selectedPiece == i * DESK_SIZE + j)
                isSelected = true;
            // на клетку можно нажать, т.к. у неё есть ходы
            if (pieceSelected == false && !model->currentFrame.possibleMoves[i][j].isEmpty())
                isReselectable = isSelectable = true;

            // на клетку можно нажать т.к. в неё можно сходить
            if (pieceSelected == true && model->currentFrame.possibleMoves
                    [selectedPiece / DESK_SIZE][selectedPiece % DESK_SIZE].contains(QPair<int,int>(i,j)))
                isSelectable = true;

            // запрет на нажатие камней бота
            if (gameMode == UGOLKI_MODE_AI &&
                    model->currentFrame.currentPlayersTurnId != UGOLKI_PLAYER_1) {
                isSelected = isReselectable = false;
            }

            deskButtons[i * DESK_SIZE + j]->setFont(font);
            deskButtons[i * DESK_SIZE + j]->setFixedSize(cellSize, cellSize);
            deskButtons[i * DESK_SIZE + j]->setEnabled(isSelectable);
            // применение стилей оформления
            QString styleSheet = getStyleSheet(playerPieceOnCurrentCell, ((j + i) % 2), isSelected, isReselectable);
            deskButtons[i * DESK_SIZE + j]->setStyleSheet(styleSheet);
            // отрисовка камней на доске
            if (playerPieceOnCurrentCell != UGOLKI_PLAYER_EMPTY)
                deskButtons[i * DESK_SIZE + j]->setText(QString::fromUtf8("●"));
            else
                deskButtons[i * DESK_SIZE + j]->setText(QString::fromUtf8(""));
        }
    }
}

void UgolkiGUI::showMenu()
{
    notificationWidget.hide();
    deskWidget->hide();
    menuWidget.show();
    deskWidget->setEnabled(true);
}

void UgolkiGUI::deskButtonClicked(const int &clickedButtonId)
{
    // выбираем фишку для хода если не выбрана
    if (!pieceSelected) {
        selectedPiece = clickedButtonId;

        pieceSelected = !pieceSelected;
        drawFrame(&model->currentFrame);
        return;
    }

    // выбираем другую фишку для хода если уже была выбрана другая
    if (model->currentFrame.matrix[clickedButtonId / DESK_SIZE][clickedButtonId % DESK_SIZE]
            == model->currentFrame.currentPlayersTurnId) {
        selectedPiece = clickedButtonId;
        drawFrame(&model->currentFrame);
        return;
    }

    // нашли куда сходить - и ходим
    pieceSelected = !pieceSelected;
    model->turnHandler(selectedPiece / DESK_SIZE,
                       selectedPiece % DESK_SIZE,
                       clickedButtonId / DESK_SIZE,
                       clickedButtonId % DESK_SIZE);
}
// выбор режима игры
void UgolkiGUI::menuButtonClicked(const int &clickedButtonId) {

    menuWidget.hide();
    // установка режима в модели
    gameMode = clickedButtonId;
    model->gameMode = gameMode;

    pieceSelected = false;
    informationTextEdit.clear();

    okButton.hide();
    messageEdit.hide();

    switch (clickedButtonId) {
    // игра против искусственного интеллекта
    case UGOLKI_MODE_AI:
        deskWidget->setWindowTitle(STRING_APPLICATION_NAME " - " STRING_MODE_AI);
        model->currentFrame.resetFrame();
        deskWidget->show();
        break;
    // два человека на одном компьютере
    case UGOLKI_MODE_MULTIPLAYER:
        deskWidget->setWindowTitle(STRING_APPLICATION_NAME " - " STRING_MODE_MULTIPLAYER);
        model->currentFrame.resetFrame();
        deskWidget->show();
        break;
    // игра по сети (не реализована - стоит заглушка)
    case UGOLKI_MODE_NETWORK:
        deskWidget->setWindowTitle(STRING_APPLICATION_NAME " - " STRING_MODE_NETWORK);
        showNotification(STRING_NOT_IMPLEMENTED);
        okButton.show();
        messageEdit.show();
        break;
    }
}

// список стилей для камней и клеток
const QString UgolkiGUI::getStyleSheet(int playerId, bool isWhiteCell, bool isSelected, bool isReselectable)
{
    QString pieceColor, pressedPieceColor;
    switch (playerId) {
    default:
    // первый игрок
    case 0:
        pressedPieceColor = COLOR_PRESSED_PLAYER_1;
        pieceColor = COLOR_PLAYER_1;
        break;
    // второй игрок
    case 1:
        pressedPieceColor = COLOR_PRESSED_PLAYER_2;
        pieceColor = COLOR_PLAYER_2;
        break;
    }

    QString cellColor;
    if (isWhiteCell)
        cellColor = COLOR_BLACK;
    else
        cellColor = COLOR_WHITE;

    if (isReselectable) {
        cellColor = COLOR_CELL_RESELECTABLE;
    }
    if (isSelected) {
        cellColor = COLOR_CELL_SELECTED;
    }

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
    informationTextEdit.appendPlainText(tr("%1").arg(string));
}
