#include "ugolkiframe.h"

UgolkiFrame::UgolkiFrame(QObject *parent) :
    QObject(parent)
{
    //SOUTH EAST
    playerHouse[UGOLKI_PLAYER_1] = qMakePair(DESK_SIZE - 1, DESK_SIZE - 1);
    //NORTH WEST
    playerHouse[UGOLKI_PLAYER_2] = qMakePair(0, 0);
}

UgolkiFrame::UgolkiFrame(const UgolkiFrame *frameToClone){

    //SOUTH EAST
    playerHouse[UGOLKI_PLAYER_1] = qMakePair(DESK_SIZE - 1, DESK_SIZE - 1);
    //NORTH WEST
    playerHouse[UGOLKI_PLAYER_2] = qMakePair(0, 0);

    this->turnCount = frameToClone->turnCount;
    this->currentPlayersTurnId = frameToClone->currentPlayersTurnId;
    for (int i = 0; i < DESK_SIZE; i++)
        for (int j = 0; j < DESK_SIZE; j++){
            possibleMoves[i][j] = frameToClone->possibleMoves[i][j];
            matrix[i][j] = frameToClone->matrix[i][j];
        }

}

void UgolkiFrame::movePiece(int oldPosRow, int oldPosColumn,
                            int newPosRow, int newPosColumn){

    if (validateMove(oldPosRow, oldPosColumn,
                     newPosRow, newPosColumn) == false)
        return;


    matrix[newPosRow][newPosColumn] = matrix[oldPosRow][oldPosColumn];
    matrix[oldPosRow][oldPosColumn] = UGOLKI_PLAYER_EMPTY;

    if (currentPlayersTurnId == UGOLKI_PLAYER_2){
        currentPlayersTurnId = UGOLKI_PLAYER_1;
        turnCount++;
    }
    else
        currentPlayersTurnId++; //next player moves


    emit frameChanged(this);

}

void UgolkiFrame::resetFrame(){

    currentPlayersTurnId = UGOLKI_PLAYER_1;
    turnCount = 0;

    for (int i = 0; i < DESK_SIZE; i++)
        for (int j = 0; j < DESK_SIZE; j++){
            possibleMoves[i][j].clear();
            matrix[i][j] = UGOLKI_PLAYER_EMPTY;
        }


    for (int i = 0; i < UGOLKI_HOUSE_HEIGHT; i++)
        for (int j = 0; j < UGOLKI_HOUSE_WIDTH; j++){
            matrix[DESK_SIZE - i - 1][DESK_SIZE - j - 1] = UGOLKI_PLAYER_1;
            matrix[i][j] = UGOLKI_PLAYER_2;
        }

    frameChanged(this);
}



bool UgolkiFrame::validateMove(int oldPosRow, int oldPosColumn,
                               int newPosRow, int newPosColumn){
    QPair<int, int> pair(newPosRow, newPosColumn);
    return possibleMoves[oldPosRow][oldPosColumn].contains(pair);

}


bool UgolkiFrame::isInHouse(int row, int column, int playersHouseId){
    if (distance(row,
                 this->playerHouse[playersHouseId].second,
                 this->playerHouse[playersHouseId].first,
                 this->playerHouse[playersHouseId].second
                 ) < UGOLKI_HOUSE_HEIGHT &&
            distance(this->playerHouse[playersHouseId].first,
                     column,
                     this->playerHouse[playersHouseId].first,
                     this->playerHouse[playersHouseId].second) < UGOLKI_HOUSE_WIDTH
            )
        return true;
    return false;
}

int UgolkiFrame::playerOpponent(int player){
    if (player == UGOLKI_PLAYER_1)
        return UGOLKI_PLAYER_2;
    if (player == UGOLKI_PLAYER_2)
        return UGOLKI_PLAYER_1;
    return UGOLKI_PLAYER_1;
}



double UgolkiFrame::distance(int i, int j, int k, int l){
    return sqrt(pow(k - i, 2) + pow(l - j, 2));
}


double UgolkiFrame::distanceToHouse(int row, int column, int playersHouseId){
    return distance(row, column,
                    this->playerHouse[playersHouseId].first,
                    this->playerHouse[playersHouseId].second);
}
