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


    //memcpy(this, frameToClone, sizeof(*frameToClone));

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

void UgolkiFrame::swapPlayers(){
    for (int i = 0; i < DESK_SIZE; i++)
        for (int j = 0; j < DESK_SIZE; j++){
            switch ( matrix[i][j] ){
            case UGOLKI_PLAYER_1:
                matrix[i][j] = UGOLKI_PLAYER_2;
                break;
            case UGOLKI_PLAYER_2:
                matrix[i][j] = UGOLKI_PLAYER_1;
                break;
            }
        }
}
