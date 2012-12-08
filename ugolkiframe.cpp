#include "ugolkiframe.h"

UgolkiFrame::UgolkiFrame(QObject *parent) :
    QObject(parent)
{
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

    for (int i = 0; i < DESK_SIZE; i++)
        for (int j = 0; j < DESK_SIZE; j++)
            matrix[i][j] = UGOLKI_PLAYER_EMPTY;


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
