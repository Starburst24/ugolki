#include "ugolkiai.h"
#include "qmath.h"
#include "QtGUI/QApplication"

UgolkiAI::UgolkiAI(QObject *parent) :
    QObject(parent)
{
}

void UgolkiAI::calculateBestMove(UgolkiFrame *frame){

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



                followingFrame.currentPlayersTurnId = followingFrame.playerOpponent(followingFrame.currentPlayersTurnId);
                emit calculatePossibleMovesTask(&followingFrame);
                //  followingFrame.currentPlayersTurnId = UGOLKI_PLAYER_1;

                double followingCriteria = 0;
                followingCriteria += criteriaHousePunishment(&followingFrame) - AI_MEAN * criteriaHousePunishment(&followingFrame, true);
                followingCriteria += criteriaDistanceToOpponentsHouse(&followingFrame) - AI_MEAN * criteriaDistanceToOpponentsHouse(&followingFrame, true);
                followingCriteria += criteriaPiecesInHouse(&followingFrame) - AI_MEAN * criteriaPiecesInHouse(&followingFrame, true);

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

}


double UgolkiAI::criteriaDistanceToOpponentsHouse(UgolkiFrame *frame, bool invert){

    double criteria = 0;
    int playerId = frame->currentPlayersTurnId;

    if (invert)
        playerId = frame->playerOpponent(playerId);



    for (int i = 0; i < DESK_SIZE; i++) {
        for (int j = 0; j < DESK_SIZE; j++) {
            if (frame->matrix[i][j] == playerId){
                criteria -= frame->distanceToHouse(i, j, frame->playerOpponent(playerId));
            }

        }

    }

    return criteria * AI_CRITERIA_DISTANCE_TO_HOUSE;
}

double UgolkiAI::criteriaPiecesInHouse(UgolkiFrame *frame, bool invert){

    double criteria = 0;
    int playerId = frame->currentPlayersTurnId;

    if (invert)
        playerId = frame->playerOpponent(playerId);

    for (int i = 0; i < DESK_SIZE; i++) {
        for (int j = 0; j < DESK_SIZE; j++) {
            if (frame->matrix[i][j] == playerId &&
                    frame->isInHouse(i, j, frame->playerOpponent(playerId))){
                criteria += 1.0;
            }
        }
    }

    return criteria * AI_CRITERIA_PIECES_IN_HOUSE;
}

double UgolkiAI::criteriaHousePunishment(UgolkiFrame *frame, bool invert){

    double criteria = 0;
    int playerId = frame->currentPlayersTurnId;

    if (invert)
        playerId = frame->playerOpponent(playerId);

    for (int i = 0; i < DESK_SIZE; i++) {
        for (int j = 0; j < DESK_SIZE; j++) {

            if (frame->matrix[i][j] == playerId){
                if (i < UGOLKI_HOUSE_HEIGHT && j < UGOLKI_HOUSE_WIDTH)
                    criteria -= 1.0 * pow(frame->turnCount, 3) *
                            pow(frame->distanceToHouse(i, j,
                                                       frame->playerOpponent(playerId)), 10);
            }
        }
    }

    return criteria * AI_CRITERIA_HOUSE_PUNISHMENT;
}


