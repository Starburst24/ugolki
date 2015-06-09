# Структуры данных и подсистем #
  * [UgolkiModel](UgolkiModel.md) - абстрактная модель игры
  * [UgolkiFrame](UgolkiFrame.md) - класс фрейма игры
  * [UgolkiGUI](UgolkiGUI.md) - визуальный модуль
  * [UgolkiNetwork](UgolkiNetwork.md) - сетевой модуль
  * [UgolkiAI](UgolkiAI.md) - модуль искусственного интеллекта

# Классы: #
# [UgolkiFrame](UgolkiFrame.md) #
## Методы: ##
  * [void resetFrame()](UgolkiFrame#void_resetFrame().md)
  * [void movePiece(int oldPosRow, int oldPosColumn, int newPosRow, int newPosColumn)](UgolkiFrame#void_movePiece(int_oldPosRow,_int_oldPosColumn,_int_newPosRow,_i.md)
  * [bool validateMove(int oldPosRow, int oldPosColumn, int newPosRow, int newPosColumn)](UgolkiFrame#bool_validateMove(int_oldPosRow,_int_oldPosColumn,_int_newPosRow.md)
## Сигналы: ##
  * [frameChanged(UgolkiFrame \*currentFrame)](UgolkiFrame#frameChanged(__*_currentFrame).md)

---


# [UgolkiNetwork](UgolkiNetwork.md) #
### Методы: ###
  * [void sendPacket(QByteArrayPacket datagram, int descr)](UgolkiNetwork#void_sendPacket(QByteArrayPacket_datagram,_int_descr).md)
  * [void packetHandler(QByteArray datagram)](UgolkiNetwork#void_packetHandler(QByteArray_datagram).md)
  * [void serverStart()](UgolkiNetwork#void_serverStart().md)
  * [void connectToServer(QString address, short port)](UgolkiNetwork#void_connectToServer(QString_address,_short_port).md)
### Сигналы: ###
  * [playerConnected()](UgolkiNetwork#playerConnected().md)
  * [connectionTerminated(QString reason)](UgolkiNetwork#connectionTerminated(QString_reason).md)
  * [opponentTurnReady(int oldPosRow, int oldPosColumn, int newPosRow, int newPosColumn)](UgolkiNetwork#opponentTurnReady(int_oldPosRow,_int_oldPosColumn,_int_newPosRow.md)
  * [networkMessage(QString message)](UgolkiNetwork#networkMessage(QString_message).md)

---

# [UgolkiGUI](UgolkiGUI.md) #
### Методы: ###
  * [void showNotifyingWindow(QString message)](UgolkiGUI#void_showNotifyingWindow(QString_message).md)
  * [void showMenu()](UgolkiGUI#void_showMenu().md)
  * [void menuButtonClicked(int buttonId)](UgolkiGUI#void_menuButtonClicked(int_buttonId).md)
  * [void deskButtonClicked(int buttonId)](UgolkiGUI#void_deskButtonClicked(int_buttonId).md)
  * [void infoPrint(QString string)](UgolkiGUI#void_infoPrint(QString_string).md)
  * [void drawFrame(UgolkiFrame \*someFrame)](UgolkiGUI#void_drawFrame(__*_someFrame).md)
### Сигналы: ###

---


# [UgolkiModel](UgolkiModel.md) #
## Методы: ##
  * [void calculatePossibleMoves(UgolkiFrame \*someFrame)](UgolkiModel#void_calculatePossibleMoves(__*_someFrame).md)
  * [void gameOverHandler()](UgolkiModel#void_gameOverHandler().md)
  * [void turnHandler(int oldPosRow, int oldPosColumn, int newPosRow, int newPosColumn)](UgolkiModel#void_turnHandler(int_oldPosRow,_int_oldPosColumn,_int_newPosRow,.md)
### Сигналы: ###
  * [gameOver(String reason)](UgolkiModel#gameOver(String_reason).md)

---


# [UgolkiAI](UgolkiAI.md) #
### Методы: ###
### Сигналы: ###
  * [botTurnReady(int oldPosRow, int oldPosColumn, int newPosRow, int newPosColumn)](UgolkiAI#botTurnReady(int_oldPosRow,_int_oldPosColumn,_int_newPosRow,_int.md)

# Заголовки #
## [variables.h](https://code.google.com/p/ugolki/source/browse/variables.h) ##
Заголовочный файл со списком препроцессорных переменных, которые определяют параметры приложения.
  * **UGOLKI\_BUILD\_VERSION** - версия билда, по умолчанию у планируемого релиза 100000. При изменении  после релиза какого либо исходного кода, протокола или препроцессорных переменных - версию рекомендуется поменять, это будет гарантировать совместимость версий при сетевой игре ----
### Правила игры ###
  * **UGOLKI\_MAXIMUM\_TURNS\_IN\_HOUSE** - максимально количество ходов, при в течение которых какой-либо камень может оставаться в своём доем. Значение - **40**.
  * **UGOLKI\_HOUSE\_WIDTH** - Ширина дома в камнях. Значение - **3**.
  * **UGOLKI\_HOUSE\_HEIGHT** - Высота дома в камнях. Значение - **3**.

### Режимы игры ###
  * **UGOLKI\_MODES** - количество режимов игры. Значение - **3**.
  * **UGOLKI\_MODE\_AI** - идентификатор режима игры против компьютера. Значение - **0**.
  * **UGOLKI\_MODE\_MULTIPLAYER** - идентификатор режима игры двух человек на одном компьютера. Значение - **1**.
  * **UGOLKI\_MODE\_NETWORK** - идентификатор режима игры по сети. Значение - **2**.
### Идентификаторы камней ###
  * **UGOLKI\_PLAYER\_1** - идентификатор камня первого игрока. Значение - **0**.
  * **UGOLKI\_PLAYER\_2** - идентификатор камня второго игрока. Значение - **1**.
  * **UGOLKI\_PLAYER\_EMPTY** - идентификатор пустой клетки. Значение - **-1**
### Максимальное количество игроков ###
  * **UGOLKI\_MAXPLAYERS** - максимальное количество игроков, участвующих в одной партии. Значение - **2**.

### Размеры шрифтов ###
  * **NOTIFICATION\_FONT\_SIZE\_PIXEL** - размер шрифта текста окна уведомлений (в пикселях). Значение - **30**.
  * **MENU\_BUTTONS\_FONT\_SIZE\_PIXEL** - размер шрифта текста кнопок меню (в пикселях). Значение - **30**.
  * **MENU\_BUTTONS\_HEIGHT\_FOR\_FONT\_MULTIPLICATOR** - множитель для значения размера шрифта текста кнопок меню. Значение - **2**.

### Размеры поля ###
  * **DESK\_SIZE** - сторона поля в клетках. Значение - **8**.
  * **DESK\_SIZE\_PIXEL** - сторона поля в пикселях. Значение - **400**.
### Шрифт клеток поля ###
  * **DESK\_CELL\_FONT\_PIXEL\_SIZE** - размер шрифта текста клетки поля в пикселях. Значение - **60**.

### Размеры виджета ###
  * **DESK\_WIDGET\_HEIGHT** - высота виджета, отображающего игровое поле. Значение - **100**.
  * **DESK\_WIDGET\_WIDTH** - ширина виджета, отображающего игровое поле. Значение - **300**.
  * **DESK\_INFORMATION\_TABLE\_PIXEL\_HEIGHT** - максимальная высота поля ввода сообщений в пикселях. Значение - **70**.

### Размеры дома ###
  * **UGOLKI\_HOUSE\_WIDTH** - ширина дома в камнях. Значение - **4**.
  * **UGOLKI\_HOUSE\_HEIGHT** - высота дома в камнях. Значение - **3**.

### Названия кнопок меню ###
  * **STRING\_MODE\_NETWORK** - название кнопки режима игры по сети. Значение - **Network Game**.
  * **STRING\_MODE\_AI** - название кнопки режима против компьютера. Значение - **Artificial Intelligence**.
  * **STRING\_MODE\_MULTIPLAYER** - название кнопки режима игры двух игроков на одном компьютере. Значение - **Two Players**.

### Различные названия ###
  * **STRING\_MAIN\_MENU** - надпись меню программы. Значение - **Main Menu**.
  * **STRING\_BACK\_TO\_MENU** - название кнопки возврата в меню. Значение - **Back to menu**.
  * **STRING\_APPLICATION\_NAME** - название приложения. Значение - **Ugolki**.
  * **STRING\_NOTIFICATION** - надпись в заголовке уведомления. Значение -  **Notification**.
  * **STRING\_BUTTON\_SEND** - надпись кнопки отправить. Значение - **Send**.

### Надписи о результаты партии ###
  * **STRING\_DRAW** - надпись о ничейном исходе партии. Значение **Nobody won!**.
  * **STRING\_PLAYER** и **STRING\_WON** - составные части надписи, сообщающей о том, кто выиграл. Значения - **Player** и **is the winner!** соответственно.

### Сообщения об ошибках и заглушки ###
  * **STRING\_ERROR\_DATA\_PROTOCOL** - сообщение об ошибке в протоколе передачи данных. Значение - **Data/Protocol Error**.
  * **STRING\_NOT\_IMPLEMENTED** - надпись для заглушки "Ещё не реализовано". Значение - **Not implemented yet**.
## Бот ##
  * **AI\_GAME\_TREE\_DEPTH** - Глубина просмотра дерева возможных ходов. Значение - **3**.
  * **AI\_MEAN** - подлость бота, отвечает за то, во сколько раз больше бот пытается ухудшить позицию противника по отношению к желанию улучшить свою. С каждым ходом влияние этой переменной уменьшается. Значение - **15**.
  * **AI\_CRITERIA\_DISTANCE\_TO\_HOUSE** - Важность критерия среднего расстояния каждого камня до дома. Значение - **100.0**.
  * **AI\_CRITERIA\_PIECES\_IN\_HOUSE** - Важность критерия количества камней в доме. Значение - **15000.0**.
  * **AI\_CRITERIA\_HOUSE\_PUNISHMENT** - Важность критерия количества камней в своем доме (отрицательный критерий). Значение - **0.000000003**.
  * **AI\_WON\_REWARD** - Награда к оценочной функции за нахождение терминального хода (выигрыша). Значение - **2000000**.

## [styles.h](https://code.google.com/p/ugolki/source/browse/styles.h) ##
Заголовочный файл со списком препроцессорных переменных, которые определяют внешний вид приложения.

### Цвета клеток поля ###
  * **COLOR\_WHITE** - цвет чёрной клетки поля. Значение - **#FFFFFF**.
  * **COLOR\_BLACK**  цвет чёрной клетки поля. Значение - **#EEEEEE**.

### Цвет выделенной клетки ###
  * **COLOR\_CELL\_SELECTED** Значение- **#AA3377**.

### Цвета камней ###
  * **COLOR\_PLAYER\_1** - цвет камней первого игрока. Значение - **#CC6633**.
  * **COLOR\_PLAYER\_2**  - цвет камней второго игрока. Значение - **#000000**.

  * **COLOR\_PRESSED\_PLAYER\_1** - цвет камня первого игрока, когда его выбрали, чтобы сделать ход. Значение - **#BB5522**.
  * **COLOR\_DISABLED\_PLAYER\_1**  - цвет камня первого игрока, когда камень не выбран. Значение - **#AA4411**

  * **COLOR\_PRESSED\_PLAYER\_2** - цвет камня второго игрока, когда его выбрали, чтобы сделать ход. Значение - **#DDDDAA**.
  * **COLOR\_DISABLED\_PLAYER\_2**  - цвет камня второго игрока, когда камень не выбран. Значение - **#CCCC99**