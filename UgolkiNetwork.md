# `UgolkiNetwork` #
Класс отвечает за сетевой режим игры
### Поля: ###
#### QHostAddress clientAddress, serverAddress ####
Переменные адресов клиента и сервера

---

#### short clientPort, serverPort ####
Порты клиента и сервера

---

#### QTcpSocket socket ####
Сокет соединения.

---

### Методы: ###
~~====QByteArrayPacket makePingPacket()====
Метод формирует пакет типа PING

---

#### QByteArrayPacket makeNextTurnPacket(int currentPlayersTurnId, int oldPosRow, int oldPosColumn, int newPosRow, int newPosColumn) ####
Метод формирует пакет типа NEXT\_TURN

---

#### QByteArrayPacket makePlayerMessagePacket(QString message) ####
Метод формирует пакет типа PLAYER\_MESSAGE~~
#### void sendPacket(QByteArrayPacket datagram, int descr) ####
Метод позволяет отправлять датаграммы по дескриптору.

---

#### void packetHandler(QByteArray datagram) ####
Обработчик входящих пакетов. Посылает сигналы графическому интерфейсу и модели по приходу соответствующих пакетов.

---

#### void serverStart() ####
Метод выполняет перечень инструкций по созданию сервера. Создается сокет, ожидается входящее соединение. Функция каждые несколько секунд отдает управление системе для обновления интерфейса,  но завершается только при закрытии приложения, ошибки сокета или установлении соединения.

---

#### void connectToServer(QString address, short port) ####
Метод выполняет перечень инструкций для установления соединения с сервером.
Открывается сокет, пытается соединиться по адресу переданным в параметрах.  Функция каждые несколько секунд отдает управление системе для обновления интерфейса,  но завершается только при закрытии приложения, установлении соединения, ошибки сокета или из-за таймаута.

---

### Сигналы: ###
#### playerConnected() ####
Сигнал оповещает о том что оппонент подсоединился

---

#### connectionTerminated(QString reason) ####
Сигнал оповещает о завершении или неудаче в соединении, reason — строка с причиной.

---

#### opponentTurnReady(int oldPosRow, int oldPosColumn, int newPosRow, int newPosColumn) ####
Сигнал оповещающий о готовности хода противника.

---

#### networkMessage(QString message) ####
Сигнал о сообщении от оппонента, message — само сообщение. [UgolkiGUI](UgolkiGUI.md) перехватывает это сообщение и выводит его в информационное поле.

---
