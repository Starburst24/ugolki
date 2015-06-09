# 1. Проект архитектуры #
![http://ugolki.googlecode.com/files/architecture.png](http://ugolki.googlecode.com/files/architecture.png)

# 2. Проект интерфейса пользователя #
После запуска игры открывается меню или окно выбора режима игры. В окне вертикально расположены три кнопки: "Игра с ботом", "Сетевая игра" и "Игра вдвоём". Один клик по кнопке запускает соответствующий режим игры.

Главное окно игры содержит игровое поле, информационное поле вывода сообщений. В режиме сетевой игры доступно поле ввода для отправки сообщений противнику.

В конце игры открывается окно, уведомляющее о результате партии. В окне содержится два элемента: надпись, которая сообщает о победителе и кнопка возврата к меню выбора режима игры.

## 2.1 Игра человека с ботом ##
![http://ugolki.googlecode.com/files/vsbotgame.png](http://ugolki.googlecode.com/files/vsbotgame.png)

## 2.2 Игра по сети ##
Порядок и количество открытия окон в этом режиме серьёзно отличается от двух других режимов. Так после меню выбора игры открывается меню выбора режима сетевой игры, в котором расположены две кнопки: "Создать игру" и "Подключиться".

При нажатии на кнопку "Создать игру" на период времени, когда противник не подключился появляется окно с надписью "Открыто слушающее соединение" и информацией об IP адресе созданного сервера и номером порта, через который осуществляется соединение. При его установке открывается главное окно приложения.

Если игрок подключается к уже созданной игре, то открывается окно с полями для ввода IP адреса и номера порта созданного сервера.

После нажатии кнопки "OK", при невозможности соединения (такими как таймаут или какой либо ошибке сокета) автоматически появляется окно с надписью "Невозможно подключиться" и кнопкой "В меню", нажав на которую снова открывается меню. При установленном соединении открывается главное окно приложения.

Если в процессе игры соединение было разорвано, то появляется окно с оповещением об этом и кнопкой "В меню".

![http://ugolki.googlecode.com/files/networkgame.png](http://ugolki.googlecode.com/files/networkgame.png)

## 2.3 Игра за одним компьютером ##
![http://ugolki.googlecode.com/files/2players.png](http://ugolki.googlecode.com/files/2players.png)

# 3. Структура данных и подсистем #
  * [UgolkiModel](DataStructures#UgolkiModel.md) - абстрактная модель игры
  * [UgolkiFrame](DataStructures#UgolkiFrame.md) - класс фрейма игры
  * [UgolkiGUI](DataStructures#UgolkiGUI.md) - визуальный модуль
  * [UgolkiNetwork](DataStructures#UgolkiNetwork.md) - сетевой модуль
  * [UgolkiAI](DataStructures#UgolkiAI.md) - модуль искусственного интеллекта
# 4. Основные алгоритмы #
## 4.1. Алгоритм поиска всех возможных ходов для данного камня ##
### Просмотр соседних клеток ###
Для имеющегося камня на первой стадии проверяются все смежные клетки: верхняя, нижняя, правая, левая (Предварительно убеждаемся, не является ли текущая клетка - граничной, тогда определённые соседние клетки у неё отсутствуют). Если какие-либо из них пусты, то на них можно сходить и соответствующие данные записываются в список возможных ходов.
### Поиск возможных прыжков ###
Если же какие-либо из смежных клеток заняты, то, проверяются следующие за ними (если они существуют) на пустоту. При пустой клетке, расположенной за занятой переходим туда и повторяем алгоритм поиска прыжка для неё. Чтобы избежать зацикливания, отслеживаем, в каких клетках мы уже произвели поиск. В список ходов записываются от данной клетки до каждой новой, которую мы смогли достичь с помощью прыжков.
# [5. Проект подсистем](DataStructures#%D0%A1%D1%82%D1%80%D1%83%D0%BA%D1%82%D1%83%D1%80%D1%8B_%D0%B4%D0%B0%D0%BD%D0%BD%D1%8B%D1%85_%D0%B8_%D0%BF%D0%BE%D0%B4%D1%81%D0%B8%D1%81%D1%82%D0%B5%D0%BC.md) #

# 6. Структура кода #
```
 /ugolki
     /ugolki.pro
     /main.cpp
     /ugolkiframe.h
     /ugolkiframe.cpp
     /ugolkigui.h
     /ugolkigui.cpp
     /ugolkinetwork.h
     /ugolkinetwork.cpp
     /ugolkiai.h
     /ugolkiai.cpp
     /ugolkimodel.h
     /ugolkimodel.cpp
     /variables.h
     /styles.h
     /docs/
```
  * `ugolki.pro` - файл проекта
  * `main.cpp` - исходный код точки входа в программу
  * `ugolkiframe.h` - заголовок класса фрейма
  * `ugolkiframe.cpp` - класс фрейма
  * `ugolkigui.h` - заголовок класса интерфейса
  * `ugolkigui.cpp` - класс интерфейса
  * `ugolkimodel.h` - заголовок класса модели
  * `ugolkimodel.cpp` - класс модели
  * `ugolkinetwork.h` - заголовок класса сетевого модуля
  * `ugolkinetwork.cpp` - класс сетевого модуля
  * `ugolkiAI.h` - заголовок класса искусственного интеллекта
  * `ugolkiAI.cpp` - класс искусственного интеллекта
  * `variables.h` - заголовочный файл с различными препроцессорными переменными
  * `styles.h` - заголовочный файл, описывающий внешний вид приложения
  * `/docs/` - содержит документацию о системе: документацию пользователя,


# 7. Проект сборки #
## 7.1. Сборка системы ##
Для сборки системы необходимо:
  * Создать директорию /ugolki или перейти в неё, если она существует
  * Создать файл проекта командой
> `qmake -project`
  * Создать Makefile
> `qmake`
  * Произвести сборку
> `make`

# 8. Трассируемость требований в проектных решениях #
| **Модуль**| **UgolkiGUI** | **UgolkiModel** | **UgolkiNetwork** | **UgolkiAI** |
|:----------------|:--------------|:----------------|:------------------|:-------------|
| **1.1.1.1**     |               |                 |                   | <p align='center'><b>+</b></p> |
| **1.1.1.2**     |               |                 | <p align='center'><b>+</b></p> |              |
| **1.1.1.3**     |               |<p align='center'><b>+</b></p> |                   |              |
| **1.1.2**       |               |<p align='center'><b>+</b></p>|                   |              |
| **1.1.3**       |<p align='center'><b>+</b></p>|                 |                   |              |
| **1.1.4**       |               |<p align='center'><b>+</b></p>|                   |              |
| **1.1.5**|               |                 |                   |<p align='center'><b>+</b></p>|