#pragma once


class Move {

private:
    int playerId;
    int figureId;
    int rolled;

public:

    Move();

    /**
     * Should be in a format %1d%1d%2d -> player id, figure id, rolled amount
     * @param fromWeb
     */
    explicit Move(int fromWeb);

    Move(int playerId, int figureId, int rolled);

    int toWeb() const;

    int getPlayerId() const;

    void setPlayerId(int playerId);

    int getFigureId() const;

    void setFigureId(int figureId);

    int getRolled() const;

    void setRolled(int rolled);

};
