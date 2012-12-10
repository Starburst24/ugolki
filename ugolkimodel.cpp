#include "ugolkimodel.h"
#include <stdio.h>

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
/*
void UgolkiModel::calculatePossibleMoves(UgolkiFrame *someFrame){
    for (int i = 0; i < DESK_SIZE; i++)
        for (int j = 0; j < DESK_SIZE; j++)
            someFrame->possibleMoves[i][j].clear();

    for (int i = 0; i < DESK_SIZE; i++)
        for (int j = 0; j < DESK_SIZE; j++)
            if (someFrame->currentPlayersTurnId == someFrame->matrix[i][j])
            {

                for (int k = 0; k < DESK_SIZE; k++)
                    for (int l = 0; l < DESK_SIZE; l++)
                        someFrame->possibleMoves[i][j] << QPair<int, int>(k,l);
            }
}*/

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

bool UgolkiModel::checkBoundsOfSquare(int currentRow, int currentColumn)
{
    if(currentRow < 0 || currentRow > DESK_SIZE - 1)
        return false;
    if(currentColumn < 0 || currentColumn > DESK_SIZE - 1)
        return false;
    return true;
}


void UgolkiModel::watchNeighboringSquares(int i, int j, UgolkiFrame *currentFrame)
{
    QPair<int,int> turn;

    if(checkBoundsOfSquare(i - 1, j))
        if(currentFrame->matrix[i - 1][j] == UGOLKI_PLAYER_EMPTY)
        {
            turn = qMakePair(i - 1, j);
            currentFrame->possibleMoves[i][j].append(turn);
        }

    if(checkBoundsOfSquare(i, j + 1))
        if(currentFrame->matrix[i][j + 1] == UGOLKI_PLAYER_EMPTY)
        {
            turn = qMakePair(i, j + 1);
            currentFrame->possibleMoves[i][j].append(turn);
        }

    if(checkBoundsOfSquare(i + 1, j))
        if(currentFrame->matrix[i + 1][j] == UGOLKI_PLAYER_EMPTY)
        {
            turn = qMakePair(i + 1, j);
            currentFrame->possibleMoves[i][j].append(turn);
        }

    if(checkBoundsOfSquare(i, j - 1))
        if(currentFrame->matrix[i][j - 1] == UGOLKI_PLAYER_EMPTY)
        {
            turn = qMakePair(i, j - 1);
            currentFrame->possibleMoves[i][j].append(turn);
        }
}

void UgolkiModel::searchForJumps(int i, int j,
                    UgolkiFrame *currentFrame,
                    bool visitedSquares[DESK_SIZE][DESK_SIZE],
                    int *firstSquare)
{
    QPair<int,int> turn;
    visitedSquares[i][j] = true;

    // jumping up
    if(checkBoundsOfSquare(i - 2, j))
        if(currentFrame->matrix[i - 1][j] != UGOLKI_PLAYER_EMPTY && visitedSquares[i - 2][j] != true)
            if(currentFrame->matrix[i - 2][j] == UGOLKI_PLAYER_EMPTY)
            {
                visitedSquares[i - 2][j] = true;
                searchForJumps(i - 2, j, currentFrame, visitedSquares, firstSquare);
            }

    // jumping down
    if(checkBoundsOfSquare(i + 2, j))
        if(currentFrame->matrix[i + 1][j] != UGOLKI_PLAYER_EMPTY && visitedSquares[i + 2][j] != true)
            if(currentFrame->matrix[i + 2][j] == UGOLKI_PLAYER_EMPTY)
            {
                visitedSquares[i + 2][j] = true;
                searchForJumps(i + 2, j, currentFrame, visitedSquares, firstSquare);
            }


    // jumping right
    if(checkBoundsOfSquare(i, j + 2))
        if(currentFrame->matrix[i][j + 1] != UGOLKI_PLAYER_EMPTY && visitedSquares[i][j + 2] != true)
            if(currentFrame->matrix[i][j + 2] == UGOLKI_PLAYER_EMPTY)
            {
                visitedSquares[i][j + 2] = true;
                searchForJumps(i, j + 2, currentFrame, visitedSquares, firstSquare);
            }

    // jumping left
    if(checkBoundsOfSquare(i, j - 2))
        if(currentFrame->matrix[i][j - 1] != UGOLKI_PLAYER_EMPTY && visitedSquares[i][j -2 ] != true)
            if(currentFrame->matrix[i][j - 2] == UGOLKI_PLAYER_EMPTY)
            {
                visitedSquares[i][j - 2] = true;
                searchForJumps(i, j - 2, currentFrame, visitedSquares, firstSquare);
            }

    // add a new turn on each new square
    if(i * DESK_SIZE + j != *firstSquare)
    {
        turn = qMakePair(i, j);
        currentFrame->possibleMoves[*firstSquare / DESK_SIZE][*firstSquare % DESK_SIZE].append(turn);
    }
}

void UgolkiModel::calculatePossibleMoves(UgolkiFrame *currentFrame)
{
    bool visitedSquares[DESK_SIZE][DESK_SIZE] = {{false},
                                                 {false},
                                                 {false},
                                                 {false},
                                                 {false},
                                                 {false},
                                                 {false},
                                                 {false}};

    for (int i = 0; i < DESK_SIZE; i++)
        for (int j = 0; j < DESK_SIZE; j++)
            currentFrame->possibleMoves[i][j].clear();

    for(int i = 0; i < DESK_SIZE; i++)
        for(int j = 0; j < DESK_SIZE; j++)
        {
            // finding necessary pieces to calculate turns
            if(currentFrame->matrix[i][j] == currentFrame->currentPlayersTurnId)
            {
                int firstSquare = i * DESK_SIZE + j;

                watchNeighboringSquares(i, j, currentFrame);
                clearVisited(visitedSquares);
                searchForJumps(i, j, currentFrame, visitedSquares, &firstSquare);
            }
        }
}

void UgolkiModel::clearVisited(bool visitedSquares[DESK_SIZE][DESK_SIZE])
{
    for(int i = 0; i < DESK_SIZE; i++)
        for(int j = 0; j < DESK_SIZE; j++)
            visitedSquares[i][j] = false;
}



