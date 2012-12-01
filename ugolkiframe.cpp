#include "ugolkiframe.h"

UgolkiFrame::UgolkiFrame(QObject *parent) :
    QObject(parent)
{
}

void UgolkiFrame::movePiece(int oldPosRow, int oldPosColumn,
                            int newPosRow, int newPosColumn){


}

void UgolkiFrame::resetFrame(){

    for (int i = 0; i < DESK_SIZE; i++)
        for (int j = 0; j < DESK_SIZE; j++)
            matrix[i][j] = -1;


    for (int i = 0; i < DESK_HOUSE_HEIGHT; i++)
        for (int j = 0; j < DESK_HOUSE_WIDTH; j++){
            matrix[DESK_SIZE - i - 1][DESK_SIZE - j - 1] = 0;
            matrix[i][j] = 1;
        }


}



bool UgolkiFrame::validateMove(int oldPosRow, int oldPosColumn,
                               int newPosRow, int newPosColumn){

}
