#include "ugolkiai.h"

UgolkiAI::UgolkiAI(QObject *parent) :
    QObject(parent)
{
}

void UgolkiAI::calculateBestMove(UgolkiFrame *frame){



    emit botTurnReady(0,0,0,0);

}
