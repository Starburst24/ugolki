#include "ugolkimodel.h"

UgolkiModel::UgolkiModel(UgolkiNetwork *networkRef, UgolkiAI *aiRef, QObject *parent) :
    QObject(parent)
{
    network = networkRef;
    ai = aiRef;

    connect(&currentFrame,
            SIGNAL(frameChanged(UgolkiFrame*)),
            SLOT(calculatePossibleMoves(UgolkiFrame*))
            );

}

void UgolkiModel::calculatePossibleMoves(UgolkiFrame *someFrame){
    for (int i = 0; i < DESK_SIZE; i++)
        for (int j = 0; j < DESK_SIZE; j++)
            someFrame->possibleMoves[i][j].clear();

    for (int i = 0; i < DESK_SIZE; i++)
        for (int j = 0; j < DESK_SIZE; j++)
            if (someFrame->currentPlayersTurnId == someFrame->matrix[i][j]){

                for (int k = 0; k < DESK_SIZE; k++)
                    for (int l = 0; l < DESK_SIZE; l++)
                        someFrame->possibleMoves[i][j] << QPair<int, int>(k,l);
            }



}

void UgolkiModel::gameOverHandler(){

    int piecesInHouse[UGOLKI_MAXPLAYERS];
    for (int i = 0; i < UGOLKI_MAXPLAYERS; i++)
        piecesInHouse[i]=0;

    for (int i = 0; i < UGOLKI_HOUSE_HEIGHT; i++)
        for (int j = 0; j < UGOLKI_HOUSE_WIDTH; j++){
            if (currentFrame.matrix[i][j] == UGOLKI_PLAYER_2)
                piecesInHouse[UGOLKI_PLAYER_2]++;
            if (currentFrame.matrix[DESK_SIZE - i - 1][DESK_SIZE - j -1] == UGOLKI_PLAYER_1)
                piecesInHouse[UGOLKI_PLAYER_1]++;

        }

    int piecesInHouseTotal = 0;
    for (int i = 0; i < UGOLKI_MAXPLAYERS; i++)
        piecesInHouseTotal += piecesInHouse[i];

    if (piecesInHouseTotal == UGOLKI_HOUSE_HEIGHT * UGOLKI_HOUSE_WIDTH * UGOLKI_MAXPLAYERS)
        emit gameOver(STRING_DRAW);
    else
    for (int i = 0; i < UGOLKI_MAXPLAYERS; i++)
        if (piecesInHouse[i] == UGOLKI_HOUSE_HEIGHT * UGOLKI_HOUSE_WIDTH){
            emit gameOver(QString(STRING_PLAYER
                                  " " +
                                  tr("%1").arg(i + 1)
                                  +
                                  " "
                                  STRING_WON));
            break;
        }




}

void UgolkiModel::turnHandler(int oldPosRow, int oldPosColumn,
                 int newPosRow, int newPosColumn){

    /* validation of the move */
    if (!currentFrame.validateMove(oldPosRow, oldPosColumn, newPosRow, newPosColumn)){
        emit gameOver(STRING_ERROR_DATA_PROTOCOL);
    }

    /* moving the piece */
    currentFrame.movePiece(oldPosRow, oldPosColumn, newPosRow, newPosColumn);

    if (currentFrame.currentPlayersTurnId == UGOLKI_PLAYER_1)
        gameOverHandler();
}


