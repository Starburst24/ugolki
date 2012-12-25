#include "ugolkimodel.h"
#include <stdio.h>

UgolkiModel::UgolkiModel(UgolkiNetwork *networkRef, UgolkiAI *aiRef, QObject *parent) :
    QObject(parent)
{
    network = networkRef;
    ai = aiRef;

    connect(&currentFrame, SIGNAL(frameChanged(UgolkiFrame*)),
            SLOT(calculatePossibleMoves(UgolkiFrame*)));

    connect(ai, SIGNAL(calculatePossibleMovesTask(UgolkiFrame*)),
            SLOT(calculatePossibleMoves(UgolkiFrame*)));

    connect(ai, SIGNAL(botTurnReady(int,int,int,int)),
            SLOT(turnHandler(int,int,int,int)));
}


void UgolkiModel::gameOverHandler()
{
    // камень в своём доме
    bool selfHousePunishment[UGOLKI_MAXPLAYERS];
    // количество камней в чужом доме
    int piecesInHouse[UGOLKI_MAXPLAYERS];
    // сначало камни все в своём доме, штрафа нет
    for (int i = 0; i < UGOLKI_MAXPLAYERS; i++) {
        piecesInHouse[i] = 0;
        selfHousePunishment[i] = false;
    }
    // обходим доску
    for (int i = 0; i < DESK_SIZE; i++)
        for (int j = 0; j < DESK_SIZE; j++) {
            int playerId = currentFrame.matrix[i][j];         
            if (playerId != UGOLKI_PLAYER_EMPTY) {
                 // для камня проверяем, находится ли он в доме противника
                if (currentFrame.isInHouse(i, j, currentFrame.playerOpponent(playerId)))
                    piecesInHouse[playerId]++;
                // если он в своём доме и ходов прошло больше допустимого
                if (currentFrame.isInHouse(i, j, playerId)
                        && currentFrame.turnCount >= UGOLKI_MAXIMUM_TURNS_IN_HOUSE)
                    selfHousePunishment[playerId] = true;
           }
        }

    // всего камней в доме противника
    int piecesInHouseTotal = 0;
    // какой-либо камень в своём доме
    bool selfHousePunishmentAll = false;
    for (int i = 0; i < UGOLKI_MAXPLAYERS; i++) {
        piecesInHouseTotal += piecesInHouse[i];
        selfHousePunishmentAll &= selfHousePunishment[i];
    }

    // ничья: все камни в домах противника
    if (piecesInHouseTotal == UGOLKI_HOUSE_HEIGHT * UGOLKI_HOUSE_WIDTH * UGOLKI_MAXPLAYERS
            || selfHousePunishmentAll) {
        emit gameOver(STRING_DRAW);
        return;
    }

    for (int i = 0; i < UGOLKI_MAXPLAYERS; i++) {
        // возможность ничьи исключена, у кого все камни в доме - победитель, посылаем соотв. сигнал
        if (piecesInHouse[i] == UGOLKI_HOUSE_HEIGHT * UGOLKI_HOUSE_WIDTH) {
            if (gameMode == UGOLKI_MODE_MULTIPLAYER)
                emit gameOver(QString(STRING_PLAYER " " + tr("%1").arg(i + 1) + " " STRING_WON));

            if (gameMode == UGOLKI_MODE_AI){
                if (i == UGOLKI_PLAYER_1)
                    emit gameOver(STRING_YOU_WON);
                if (i == UGOLKI_BOT)
                    emit gameOver(STRING_YOU_LOST);
            }
            // победитель найден - выход из цикла
            break;
        }

        // камень до сих пор в своём доме, оппонент такого игрока выигрывает
        if (selfHousePunishment[i] == true){
            if (gameMode == UGOLKI_MODE_AI)
                if (i != UGOLKI_BOT)
                    emit gameOver(STRING_YOU_LOST);
                else
                    emit gameOver(STRING_YOU_WON);

            if (gameMode == UGOLKI_MODE_MULTIPLAYER){
                emit gameOver(QString(STRING_PLAYER " " + tr("%1").arg(currentFrame.playerOpponent(i) + 1) + " " STRING_WON));
            }

            break;
        }
    }
}

void UgolkiModel::turnHandler(int oldPosRow, int oldPosColumn,
                              int newPosRow, int newPosColumn)
{
    // некорректный ход - закрываем приложение
    if (!currentFrame.validateMove(oldPosRow, oldPosColumn, newPosRow, newPosColumn)) {
        emit gameOver(STRING_ERROR_DATA_PROTOCOL);
    }
    // двигаем камень
    currentFrame.movePiece(oldPosRow, oldPosColumn, newPosRow, newPosColumn);
    // только что сделал ход второй игрок, проверяем, не завершилась ли партия
    if (currentFrame.currentPlayersTurnId == UGOLKI_PLAYER_1)
        gameOverHandler();
    // игра против ии: ходит бот, считаем лучший ход для него
    if (gameMode == UGOLKI_MODE_AI && currentFrame.currentPlayersTurnId == UGOLKI_PLAYER_2){
        ai->calculateBestMove(&this->currentFrame);
    }
}

bool UgolkiModel::checkBoundsOfSquare(int currentRow, int currentColumn)
{
    // проверяем, может ли клетка иметь такие координаты
    if (currentRow < 0 || currentRow > DESK_SIZE - 1)
        return false;
    if (currentColumn < 0 || currentColumn > DESK_SIZE - 1)
        return false;
    return true;
}

// просмотр соседних клеток в поисках хода на них
void UgolkiModel::watchNeighboringSquares(int i, int j, UgolkiFrame *frame)
{
    QPair<int,int> turn;

    // смотрим вверх, если клетка сверху существует
    if (checkBoundsOfSquare(i - 1, j))
        // она пуста
        if (frame->matrix[i - 1][j] == UGOLKI_PLAYER_EMPTY)
        {
            // сделать ход можно, добавляем в список
            turn = qMakePair(i - 1, j);
            frame->possibleMoves[i][j].append(turn);
        }
    // смотрим вправо
    if (checkBoundsOfSquare(i, j + 1))
        if (frame->matrix[i][j + 1] == UGOLKI_PLAYER_EMPTY)
        {
            turn = qMakePair(i, j + 1);
            frame->possibleMoves[i][j].append(turn);
        }
    // смотрим вниз
    if (checkBoundsOfSquare(i + 1, j))
        if (frame->matrix[i + 1][j] == UGOLKI_PLAYER_EMPTY)
        {
            turn = qMakePair(i + 1, j);
            frame->possibleMoves[i][j].append(turn);
        }
    // смотрим влево
    if (checkBoundsOfSquare(i, j - 1))
        if (frame->matrix[i][j - 1] == UGOLKI_PLAYER_EMPTY)
        {
            turn = qMakePair(i, j - 1);
            frame->possibleMoves[i][j].append(turn);
        }
}

// просмотр возможных прыжков через камни
void UgolkiModel::searchForJumps(int i, int j,
                                 UgolkiFrame *frame,
                                 bool visitedSquares[DESK_SIZE][DESK_SIZE],
                                 int *firstSquare)
{
    QPair<int,int> turn;
    // текущая клетка уже просмотрена
    visitedSquares[i][j] = true;

    // прыжки вверх, если клетка через одну вверху существует
    if (checkBoundsOfSquare(i - 2, j))
        // соседняя клетка вверху занята и следующая за ней не просмотрена
        if (frame->matrix[i - 1][j] != UGOLKI_PLAYER_EMPTY && visitedSquares[i - 2][j] != true)
            // клетка через одну вверху пуста, продолжаем поиск, начиная с неё
            if (frame->matrix[i - 2][j] == UGOLKI_PLAYER_EMPTY) {
                searchForJumps(i - 2, j, frame, visitedSquares, firstSquare);
            }
    // прыжки вниз
    if (checkBoundsOfSquare(i + 2, j))
        if (frame->matrix[i + 1][j] != UGOLKI_PLAYER_EMPTY && visitedSquares[i + 2][j] != true)
            if (frame->matrix[i + 2][j] == UGOLKI_PLAYER_EMPTY) {
                searchForJumps(i + 2, j, frame, visitedSquares, firstSquare);
            }
    // прыжки вправо
    if (checkBoundsOfSquare(i, j + 2))
        if (frame->matrix[i][j + 1] != UGOLKI_PLAYER_EMPTY && visitedSquares[i][j + 2] != true)
            if (frame->matrix[i][j + 2] == UGOLKI_PLAYER_EMPTY) {
                searchForJumps(i, j + 2, frame, visitedSquares, firstSquare);
            }
    // прыжки влево
    if (checkBoundsOfSquare(i, j - 2))
        if (frame->matrix[i][j - 1] != UGOLKI_PLAYER_EMPTY && visitedSquares[i][j -2 ] != true)
            if (frame->matrix[i][j - 2] == UGOLKI_PLAYER_EMPTY) {
                searchForJumps(i, j - 2, frame, visitedSquares, firstSquare);
            }

    // добавляем ход с начальной клетки поиска до каждой новой достигнутой
    if (i * DESK_SIZE + j != *firstSquare) {
        turn = qMakePair(i, j);
        frame->possibleMoves[*firstSquare / DESK_SIZE][*firstSquare % DESK_SIZE].append(turn);
    }
}

void UgolkiModel::calculatePossibleMoves(UgolkiFrame *frame)
{
    // просмотренные клетки для поиска
    bool visitedSquares[DESK_SIZE][DESK_SIZE];

    // очистка старого списка
    for (int i = 0; i < DESK_SIZE; i++)
        for (int j = 0; j < DESK_SIZE; j++) {
            frame->possibleMoves[i][j].clear();
        }

    for (int i = 0; i < DESK_SIZE; i++)
        for (int j = 0; j < DESK_SIZE; j++) {
            // выбераем камни игрока, который сейчас должен сходить
            if (frame->matrix[i][j] == frame->currentPlayersTurnId) {
                // указываем начальную клетку для поиска прыжков
                int firstSquare = i * DESK_SIZE + j;     
                for(int k = 0; k < DESK_SIZE; k++)
                     for(int l = 0; l < DESK_SIZE; l++)
                         visitedSquares[k][l] = false;

                watchNeighboringSquares(i, j, frame);
                searchForJumps(i, j, frame, visitedSquares, &firstSquare);
            }
        }
}
