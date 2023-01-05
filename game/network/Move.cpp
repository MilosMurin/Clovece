#include "Move.h"


Move::Move(int playerId, int figureId, int rolled) : playerId(playerId), figureId(figureId), rolled(rolled) {}

Move::Move(): Move(-1, -1, -1) {}

Move::Move(int fromWeb) : Move(fromWeb / 1000 % 10, (fromWeb / 100) % 10, fromWeb % 100) { }

int Move::toWeb() const {
    return playerId * 1000 + figureId * 100 + rolled;
}

int Move::getPlayerId() const {
    return playerId;
}

void Move::setPlayerId(int playerId) {
    Move::playerId = playerId;
}

int Move::getFigureId() const {
    return figureId;
}

void Move::setFigureId(int figureId) {
    Move::figureId = figureId;
}

int Move::getRolled() const {
    return rolled;
}

void Move::setRolled(int rolled) {
    Move::rolled = rolled;
}
