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
}
*/
void UgolkiModel::gameOverHandler(){

    int piecesInHouse[UGOLKI_MAXPLAYERS];
    for (int i = 0; i < UGOLKI_MAXPLAYERS; i++)
        piecesInHouse[i]=0;

    for (int i = 0; i < UGOLKI_HOUSE_HEIGHT; i++)
        for (int j = 0; j < UGOLKI_HOUSE_WIDTH; j++){
            if (currentFrame.matrix[i][j] == UGOLKI_PLAYER_1)
                piecesInHouse[UGOLKI_PLAYER_1]++;
            if (currentFrame.matrix[DESK_SIZE - i - 1][DESK_SIZE - j -1] == UGOLKI_PLAYER_2)
                piecesInHouse[UGOLKI_PLAYER_2]++;

        }

    int piecesInHouseTotal = 0;
    for (int i = 0; i < UGOLKI_MAXPLAYERS; i++)
        piecesInHouseTotal += piecesInHouse[i];

    if (piecesInHouseTotal == UGOLKI_HOUSE_HEIGHT * UGOLKI_HOUSE_WIDTH * UGOLKI_MAXPLAYERS)
        emit gameOver(STRING_DRAW);
    else
        for (int i = 0; i < UGOLKI_MAXPLAYERS; i++){
            if (piecesInHouse[i] == UGOLKI_HOUSE_HEIGHT * UGOLKI_HOUSE_WIDTH){

                if (gameMode == UGOLKI_MODE_MULTIPLAYER)
                emit gameOver(QString(STRING_PLAYER
                                      " " +
                                      tr("%1").arg(i + 1)
                                      +
                                      " "
                                      STRING_WON));

                if (gameMode == UGOLKI_MODE_AI){
                    if (i == UGOLKI_PLAYER_1)
                        emit gameOver(STRING_YOU_WON);
                    if (i == UGOLKI_BOT)
                        emit gameOver(STRING_YOU_LOST);
                }

                break;
            }
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

    if (gameMode == UGOLKI_MODE_AI && currentFrame.currentPlayersTurnId == UGOLKI_PLAYER_2){
        ai->calculateBestMove(&this->currentFrame);
    }
}

bool UgolkiModel::checkBoundsOfSquare(int currentRow, int currentColumn) {

    if(currentRow < 0 || currentRow > DESK_SIZE - 1)
        return false;
    if(currentColumn < 0 || currentColumn > DESK_SIZE - 1)
        return false;
    return true;

}



void UgolkiModel::watchNeighboringSquares(int i, int j, UgolkiFrame *frame) {
    QPair<int,int> turn;

    if(checkBoundsOfSquare(i - 1, j))
        if(frame->matrix[i - 1][j] == UGOLKI_PLAYER_EMPTY)
        {
            turn = qMakePair(i - 1, j);
            frame->possibleMoves[i][j].append(turn);
        }

    if(checkBoundsOfSquare(i, j + 1))
        if(frame->matrix[i][j + 1] == UGOLKI_PLAYER_EMPTY)
        {
            turn = qMakePair(i, j + 1);
            frame->possibleMoves[i][j].append(turn);
        }

    if(checkBoundsOfSquare(i + 1, j))
        if(frame->matrix[i + 1][j] == UGOLKI_PLAYER_EMPTY)
        {
            turn = qMakePair(i + 1, j);
            frame->possibleMoves[i][j].append(turn);
        }

    if(checkBoundsOfSquare(i, j - 1))
        if(frame->matrix[i][j - 1] == UGOLKI_PLAYER_EMPTY)
        {
            turn = qMakePair(i, j - 1);
            frame->possibleMoves[i][j].append(turn);
        }
}

void UgolkiModel::searchForJumps(int i, int j,
                                 UgolkiFrame *frame,
                                 bool visitedSquares[DESK_SIZE][DESK_SIZE],
                                 int *firstSquare)
{
    QPair<int,int> turn;
    visitedSquares[i][j] = true;

    // jumping up
    if(checkBoundsOfSquare(i - 2, j))
        if(frame->matrix[i - 1][j] != UGOLKI_PLAYER_EMPTY && visitedSquares[i - 2][j] != true)
            if(frame->matrix[i - 2][j] == UGOLKI_PLAYER_EMPTY)
            {
                visitedSquares[i - 2][j] = true;
                searchForJumps(i - 2, j, frame, visitedSquares, firstSquare);
            }

    // jumping down
    if(checkBoundsOfSquare(i + 2, j))
        if(frame->matrix[i + 1][j] != UGOLKI_PLAYER_EMPTY && visitedSquares[i + 2][j] != true)
            if(frame->matrix[i + 2][j] == UGOLKI_PLAYER_EMPTY)
            {
                visitedSquares[i + 2][j] = true;
                searchForJumps(i + 2, j, frame, visitedSquares, firstSquare);
            }


    // jumping right
    if(checkBoundsOfSquare(i, j + 2))
        if(frame->matrix[i][j + 1] != UGOLKI_PLAYER_EMPTY && visitedSquares[i][j + 2] != true)
            if(frame->matrix[i][j + 2] == UGOLKI_PLAYER_EMPTY)
            {
                visitedSquares[i][j + 2] = true;
                searchForJumps(i, j + 2, frame, visitedSquares, firstSquare);
            }

    // jumping left
    if(checkBoundsOfSquare(i, j - 2))
        if(frame->matrix[i][j - 1] != UGOLKI_PLAYER_EMPTY && visitedSquares[i][j -2 ] != true)
            if(frame->matrix[i][j - 2] == UGOLKI_PLAYER_EMPTY)
            {
                visitedSquares[i][j - 2] = true;
                searchForJumps(i, j - 2, frame, visitedSquares, firstSquare);
            }

    // add a new turn on each new square
    if(i * DESK_SIZE + j != *firstSquare)
    {
        turn = qMakePair(i, j);
        frame->possibleMoves[*firstSquare / DESK_SIZE][*firstSquare % DESK_SIZE].append(turn);
    }
}

void UgolkiModel::calculatePossibleMoves(UgolkiFrame *frame) {
    bool visitedSquares[DESK_SIZE][DESK_SIZE];

    for (int i = 0; i < DESK_SIZE; i++)
        for (int j = 0; j < DESK_SIZE; j++){
            frame->possibleMoves[i][j].clear();
            visitedSquares[i][j] = false;
    }

    for(int i = 0; i < DESK_SIZE; i++)
        for(int j = 0; j < DESK_SIZE; j++)
        {
            // finding necessary pieces to calculate turns
            if(frame->matrix[i][j] == frame->currentPlayersTurnId)
            {
                int firstSquare = i * DESK_SIZE + j;

                watchNeighboringSquares(i, j, frame);

                for(int k = 0; k < DESK_SIZE; k++)
                    for(int l = 0; l < DESK_SIZE; l++)
                        visitedSquares[k][l] = false;

                searchForJumps(i, j, frame, visitedSquares, &firstSquare);
            }
        }
}




