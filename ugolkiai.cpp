#include "ugolkiai.h"
#include "qmath.h"
#include "QtGUI/QApplication"

UgolkiAI::UgolkiAI(QObject *parent) :
    QObject(parent)
{
    //connect(this, SIGNAL(turnTask(UgolkiFrame*)), SLOT(bestMove(UgolkiFrame*)));
}

void UgolkiAI::calculateBestMove(UgolkiFrame *frame){


    bestMove(frame, AI_GAME_TREE_DEPTH);


}

double UgolkiAI::bestMove(UgolkiFrame *frame, int depth){

    QApplication::processEvents();



    int recordOldPosRow, recordOldPosColumn,
            recordNewPosRow, recordNewPosColumn;

    double criteriaRecord = -INFINITY;

    for (int oldPosRow = 0; oldPosRow < DESK_SIZE; oldPosRow++)
        for (int oldPosColumn = 0; oldPosColumn < DESK_SIZE; oldPosColumn++)
            for (int possibleMove = 0;
                 possibleMove < frame->possibleMoves[oldPosRow][oldPosColumn].size();
                 possibleMove++){

                UgolkiFrame followingFrame(frame);
                followingFrame.movePiece(oldPosRow, oldPosColumn,
                                         frame->possibleMoves[oldPosRow][oldPosColumn].at(possibleMove).first,
                                         frame->possibleMoves[oldPosRow][oldPosColumn].at(possibleMove).second
                                         );




                emit calculatePossibleMovesTask(&followingFrame);
              //  followingFrame.currentPlayersTurnId = UGOLKI_PLAYER_1;

                double followingCriteria = 0;
                followingCriteria += criteriaHousePunishment(&followingFrame);
                followingCriteria += criteriaDistanceToHouse(&followingFrame);
                followingCriteria += criteriaPiecesInHouse(&followingFrame);

                if (followingCriteria > criteriaRecord){
                    criteriaRecord = followingCriteria;
                    recordOldPosRow = oldPosRow;
                    recordOldPosColumn = oldPosColumn;
                    recordNewPosRow = frame->possibleMoves[oldPosRow][oldPosColumn].at(possibleMove).first;
                    recordNewPosColumn = frame->possibleMoves[oldPosRow][oldPosColumn].at(possibleMove).second;

                }
            }

    botTurnReady(recordOldPosRow, recordOldPosColumn,
                 recordNewPosRow, recordNewPosColumn
                 );




    return criteriaRecord;
}


double UgolkiAI::criteriaDistanceToHouse(UgolkiFrame *frame){


    double criteria = 0;
    int otherPlayerId;


    for (int i = 0; i < DESK_SIZE; i++) {
        for (int j = 0; j < DESK_SIZE; j++) {
            if (frame->matrix[i][j] == UGOLKI_BOT){
                                    criteria -= distance(i, j,
                                     frame->playerHouse[UGOLKI_PLAYER_1].first,
                                     frame->playerHouse[UGOLKI_PLAYER_1].second);

            }

        }

    }

    return criteria * AI_CRITERIA_DISTANCE_TO_HOUSE;
}

double UgolkiAI::criteriaPiecesInHouse(UgolkiFrame *frame){

    //maximum UGOLKI_HOUSE_WIDTH * UGOLKI_HOUSE_HEIGHT
    //minimum 0
    double criteria = 0;


    for (int i = 0; i < DESK_SIZE; i++) {
        for (int j = 0; j < DESK_SIZE; j++) {
            if (frame->matrix[i][j] == UGOLKI_BOT){



                if (distance(i,
                             frame->playerHouse[UGOLKI_PLAYER_1].second,
                             frame->playerHouse[UGOLKI_PLAYER_1].first,
                             frame->playerHouse[UGOLKI_PLAYER_1].second
                             ) < UGOLKI_HOUSE_HEIGHT &&
                        distance(frame->playerHouse[UGOLKI_PLAYER_1].first,
                                 j,
                                 frame->playerHouse[UGOLKI_PLAYER_1].first,
                                 frame->playerHouse[UGOLKI_PLAYER_1].second) < UGOLKI_HOUSE_WIDTH
                        )
                    criteria += 1.0;
            }

        }

    }

    return criteria * AI_CRITERIA_PIECES_IN_HOUSE;
}

double UgolkiAI::criteriaHousePunishment(UgolkiFrame *frame){

    //maximum 0
    //minimum -INFINITY
    double criteria = 0;

    for (int i = 0; i < DESK_SIZE; i++) {
        for (int j = 0; j < DESK_SIZE; j++) {

            if (frame->matrix[i][j] == UGOLKI_BOT){
                if (i < UGOLKI_HOUSE_WIDTH && j < UGOLKI_HOUSE_HEIGHT)
                    criteria -= 1.0 * pow(frame->turnCount, 2) * pow(distance(i, j, 0, 0), frame->turnCount);
            }

        }

    }

    return 1 * criteria * AI_CRITERIA_HOUSE_PUNISHMENT;
}

double UgolkiAI::distance(int i, int j, int k, int l){
    return sqrt(pow(i - k, 2) + pow(j - l, 2));
}
