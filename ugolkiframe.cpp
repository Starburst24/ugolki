#include "ugolkiframe.h"
#include <cmath>

UgolkiFrame::UgolkiFrame(QObject *parent) :
    QObject(parent)
{
    // юго-восточный угол поля
    playerHouse[UGOLKI_PLAYER_1] = qMakePair(DESK_SIZE - 1, DESK_SIZE - 1);
    // северо-западный угол поля
    playerHouse[UGOLKI_PLAYER_2] = qMakePair(0, 0);
}

// копирование фрейма
UgolkiFrame::UgolkiFrame(const UgolkiFrame *frameToClone)
{
    // юго-восточный угол поля
    playerHouse[UGOLKI_PLAYER_1] = qMakePair(DESK_SIZE - 1, DESK_SIZE - 1);
    // северо-западный угол поля
    playerHouse[UGOLKI_PLAYER_2] = qMakePair(0, 0);

    this->turnCount = frameToClone->turnCount;
    this->currentPlayersTurnId = frameToClone->currentPlayersTurnId;
    for (int i = 0; i < DESK_SIZE; i++)
        for (int j = 0; j < DESK_SIZE; j++) {
            possibleMoves[i][j] = frameToClone->possibleMoves[i][j];
            matrix[i][j] = frameToClone->matrix[i][j];
        }
}

void UgolkiFrame::movePiece(int oldPosRow, int oldPosColumn,
                            int newPosRow, int newPosColumn)
{
    // выходим, если ход недопустим
    if (validateMove(oldPosRow, oldPosColumn,
                     newPosRow, newPosColumn) == false)
        return;

    // перемещение камня на новую клетку
    matrix[newPosRow][newPosColumn] = matrix[oldPosRow][oldPosColumn];
    // удаление со старой
    matrix[oldPosRow][oldPosColumn] = UGOLKI_PLAYER_EMPTY;

    // оба передвинули по камню - сделан ход
    if (currentPlayersTurnId == UGOLKI_PLAYER_2) {
        currentPlayersTurnId = UGOLKI_PLAYER_1;
        turnCount++;
    }
    else
        // ход не завершён, ходит следующий игрок
        currentPlayersTurnId++;

    // обновляем фрейм
    emit frameChanged(this);
}

void UgolkiFrame::resetFrame()
{
    // первым ходит первый игрок, ходов не сделано
    currentPlayersTurnId = UGOLKI_PLAYER_1;
    turnCount = 0;

    // очистка всей доски и списка ходов
    for (int i = 0; i < DESK_SIZE; i++)
        for (int j = 0; j < DESK_SIZE; j++) {
            possibleMoves[i][j].clear();
            matrix[i][j] = UGOLKI_PLAYER_EMPTY;
        }

    // расстановка камней по домам
    for (int i = 0; i < UGOLKI_HOUSE_HEIGHT; i++)
        for (int j = 0; j < UGOLKI_HOUSE_WIDTH; j++) {
            matrix[DESK_SIZE - i - 1][DESK_SIZE - j - 1] = UGOLKI_PLAYER_1;
            matrix[i][j] = UGOLKI_PLAYER_2;
        }

    // сигнализируем об изменении фрейма
    frameChanged(this);
}

bool UgolkiFrame::validateMove(int oldPosRow, int oldPosColumn,
                               int newPosRow, int newPosColumn)
{
    // ищем в списке возмножных ходов
    return possibleMoves[oldPosRow][oldPosColumn].contains(qMakePair(newPosRow, newPosColumn));
}

bool UgolkiFrame::isInHouse(int row, int column, int playersHouseId)
{
    // проверка на соответсвие координат клетки областям, задающим дома игроков
    if (fabs(this->playerHouse[playersHouseId].first - row) < UGOLKI_HOUSE_HEIGHT &&
            fabs(this->playerHouse[playersHouseId].second - column) < UGOLKI_HOUSE_WIDTH)
        return true;

    return false;
}

int UgolkiFrame::playerOpponent(int player)
{
    if (player == UGOLKI_PLAYER_1)
        return UGOLKI_PLAYER_2;
    if (player == UGOLKI_PLAYER_2)
        return UGOLKI_PLAYER_1;
    return UGOLKI_PLAYER_1;
}

double UgolkiFrame::distance(int i, int j, int k, int l)
{
    // геометрическое расстояние между двумя точками с известными координатами
    return sqrt(pow(k - i, 2) + pow(l - j, 2));
}

double UgolkiFrame::distanceToHouse(int row, int column, int playersHouseId)
{
    // геометрическое расстояние до угловых клеток дома игрока
    return distance(row, column,
                    this->playerHouse[playersHouseId].first,
                    this->playerHouse[playersHouseId].second);
}
