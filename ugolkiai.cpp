#include "ugolkiai.h"
#include "qmath.h"
#include <QApplication>

UgolkiAI::UgolkiAI(QObject *parent) :
    QObject(parent)
{
    frameCache = new QHash<QByteArray, UgolkiFrame*>;
}
// поиск лучшего хода
void UgolkiAI::calculateBestMove(UgolkiFrame *frame)
{

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

                double followingFrameRecord = alphaBetaPruning(&followingFrame, AI_GAME_TREE_DEPTH, -INFINITY, +INFINITY, UGOLKI_BOT, UGOLKI_PLAYER_1);
                if (followingFrameRecord > criteriaRecord){
                    criteriaRecord = followingFrameRecord;
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

// поиск начального решения для лучшего хода
double UgolkiAI::heuristicValue(UgolkiFrame *frame, int playerId, int opponentId)
{

    double value = 0;
    double distanceToOpponentsHouse = 0; //negative criterion
    int piecesInOpponentsHouse = 0; //positive criterion
    int piecesInOwnHouse = 0; //positive criterion
    double housePunishment = 0; //negative criterion

    for (int i = 0; i < DESK_SIZE; i++) {
        for (int j = 0; j < DESK_SIZE; j++) {
            if (frame->matrix[i][j] == playerId) {
                distanceToOpponentsHouse -= frame->distanceToHouse(i, j, opponentId);
                if (frame->isInHouse(i, j, opponentId))
                    piecesInOpponentsHouse++;
                else
                    if (frame->isInHouse(i, j, playerId))
                        piecesInOwnHouse++;
            }
        }
    }

    double grade = AI_CRITERIA_DISTANCE_TO_HOUSE_GRADE;
    distanceToOpponentsHouse = pow(distanceToOpponentsHouse, grade);

    if (piecesInOpponentsHouse == UGOLKI_HOUSE_HEIGHT * UGOLKI_HOUSE_WIDTH)
        piecesInOpponentsHouse += AI_WON_REWARD;

    value += distanceToOpponentsHouse * AI_CRITERIA_DISTANCE_TO_HOUSE;
    grade = AI_HOUSE_PUNISHMENT_PIECES_IN_HOUSE_TURN_GRADE;
    housePunishment -= piecesInOwnHouse * pow(frame->turnCount, grade) + value * frame->turnCount * frame->turnCount;

    value += piecesInOpponentsHouse * AI_CRITERIA_PIECES_IN_HOUSE;
    value += housePunishment * AI_CRITERIA_HOUSE_PUNISHMENT;

    return value;
}

// обход дерева возможных ходов в поисках хорошего
double UgolkiAI::alphaBetaPruning(UgolkiFrame *frame, int depth,
                                  double alpha, double beta, int playerId, int opponentId)
{
    // глубина обхода
    if (depth % 3 == 0)
        QApplication::processEvents();

    if (depth == 0 ||
         isPlayerInHouse(frame, playerId, opponentId) ||
         isPlayerInHouse(frame, opponentId, playerId)) {
         // узел дерева не имеет детей
         return heuristicValue(frame, UGOLKI_BOT, UGOLKI_PLAYER_1) -
                AI_MEAN * heuristicValue(frame, UGOLKI_PLAYER_1, UGOLKI_BOT) / (frame->turnCount + 1);
    }

    if  (playerId == UGOLKI_PLAYER_1) {
        emit calculatePossibleMovesTask(frame);

        // обходим всех детей узла
        for (int oldPosRow = 0; oldPosRow < DESK_SIZE; oldPosRow++)
            for (int oldPosColumn = 0; oldPosColumn < DESK_SIZE; oldPosColumn++)
                for (int possibleMove = 0;
                     possibleMove < frame->possibleMoves[oldPosRow][oldPosColumn].size();
                     possibleMove++){

                    UgolkiFrame childFrame(frame);
                    childFrame.movePiece(oldPosRow, oldPosColumn,
                                          frame->possibleMoves[oldPosRow][oldPosColumn].at(possibleMove).first,
                                          frame->possibleMoves[oldPosRow][oldPosColumn].at(possibleMove).second
                                          );

                    double gamma = alphaBetaPruning(&childFrame, depth - 1,
                                                    alpha, beta,
                                                    opponentId, playerId);
                    if (gamma > alpha)
                        alpha = gamma;

                    if (beta <= alpha)
                        break;
                }
        // α := max(α, alphabeta(child, depth-1, α, β, not(Player) ))
        return alpha;
    }
    else
    {
        emit calculatePossibleMovesTask(frame);
        // обходим всех детей узла
        for (int oldPosRow = 0; oldPosRow < DESK_SIZE; oldPosRow++)
            for (int oldPosColumn = 0; oldPosColumn < DESK_SIZE; oldPosColumn++)
                for (int possibleMove = 0;
                    possibleMove < frame->possibleMoves[oldPosRow][oldPosColumn].size();
                    possibleMove++) {

                    UgolkiFrame childFrame(frame);
                    childFrame.movePiece(oldPosRow, oldPosColumn,
                                          frame->possibleMoves[oldPosRow][oldPosColumn].at(possibleMove).first,
                                          frame->possibleMoves[oldPosRow][oldPosColumn].at(possibleMove).second
                                          );
                    double gamma = alphaBetaPruning(&childFrame, depth - 1,
                                                    alpha, beta,
                                                    opponentId, playerId);
                    if (gamma < beta)
                        beta = gamma;
                    if (beta <= alpha)
                        break;
                }

        return beta;
    }
}

// все ли камни противника находятся в чужом доме?
bool UgolkiAI::isPlayerInHouse(UgolkiFrame *frame, int playerId, int opponentId){

    int criteria = 0;

    for (int i = 0; i < DESK_SIZE; i++) {
        for (int j = 0; j < DESK_SIZE; j++) {
            if (frame->matrix[i][j] == playerId &&
                    frame->isInHouse(i, j, opponentId)) {
                criteria += 1;
            }
        }
    }
    return criteria == UGOLKI_HOUSE_HEIGHT * UGOLKI_HOUSE_WIDTH;
}
