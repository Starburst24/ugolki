# `UgolkiModel` #
Класс описывает все правила игры.
### Поля: ###
#### UgolkiFrame currentFrame ####
Объект класса UgolkiFrame использующийся для хранения текущей игровой ситуации.

---

#### UgolkiNetwork  `*`network ####
Ссылка для взаимодействия с модулем UgolkiNetwork.
#### [UgolkiAI](UgolkiAI.md)  `*`ai ####
Ссылка для взаимодействия с модулем [UgolkiAI](UgolkiAI.md).
#### int gameMode ####
Текущий режим игры приложения

---

## Методы: ##
#### void calculatePossibleMoves(UgolkiFrame `*`someFrame) ####
Метод пересчитывает все возможные ходы для фишек игрока currentPlayersTurnId и записывает их во фрейм.

---

#### void gameOverHandler() ####
Метод проверки на завершение игры. Вызывается после каждого хода второго игрока.
Проверяет, находятся ли все элементы какого либо из игроков в доме. Если они в доме у обоих - ничья, если у одного из них - то победа присуждается ему. После 40 хода метод проверяет, не находится ли у одного или обоих игроков в своем доме свой камень. Если у обоих есть в своем доме камни - ничья. Если у одного из них - то этот игрок проиграл.

---

#### void turnHandler(int oldPosRow, int oldPosColumn, int newPosRow, int newPosColumn) ####
Метод является обработчиком сигналов opponentTurnReady и botTurnReady, а также вызывается [UgolkiGUI](UgolkiGUI.md) который передает ходы игрока/игроков. Он проверяет возможность такого хода, в случае его невозможности игра завершается, так как либо неисправен бот, либо, в сетевом режиме по причине вмешательства, или сетевой ошибки, произошла рассинхронизация позиций игроков, игру продолжать невозможно.

---

#### bool checkBoundsOfSquare(int row, int column) ####
Метод проверяет, существует ли клетка с координатами row, column на доске и возвращает истину, если это так.

---

#### void watchNeighboringSquares(int row, int column, UgolkiFrame  `*`currentFrame) ####
Метод проверяет возможность сделать ход на соседние клетки, относительно камня, находящегося на клетке с координатами row, column. При наличии таковых, список ходов для рассматриваемого камня соответсвенно пополняется.

---

#### void searchForJumps(int row, int column, UgolkiFrame `*`currentFrame, bool visitedSquares  `[ ` DESK\_SIZE  `] ` `[ ` DESK\_SIZE  `] `, int `*`firstSquare) ####
Метод проверяет возможность сделать какие-либо прыжки, относительно камня, находящегося на клетке с координатами row, column. При наличии таковых, список ходов для рассматриваемого камня соответсвенно пополняется.

---

### Сигналы: ###
#### void modelMessage(QString message) ####
Сигнал испускается при отправке сообщения, предназначенного для вывода в информационное поле. Используется в [UgolkiGUI](UgolkiGUI.md)

---

#### gameOver(QString reason) ####
Сигнал оповещающий об окончании партии. reason — строка с причиной окончания игры (вы победили/проиграли/ничья/). Используется в [UgolkiGUI](UgolkiGUI.md)  для отображения в специальном окне.