/*
   ReniMadden - Mensch ärgere dich nicht for KDE
   Copyright © 2007-2008 Frank S. Thomas <frank@thomas-alfeld.de>

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef BOARD_H
#define BOARD_H

#include <list>
#include <vector>

#include "move.h"
#include "playerid.h"

namespace ReniMadden
{

class Board
{
    friend class BoardTest;

public:
    Board(const int players = 4, const int size = 48, const int figurespp = 4);
    Board& reset();
    bool isSane() const;

    Board& rollDice();
    int getDice() const;

    int getPlayersCnt() const;
    int getBoardSize() const;
    int getFiguresOffBoard(const playerId player) const;
    int getFiguresOnField(const playerId player, const int field) const;
    int getOpponentField(const playerId player, const playerId opponent,
                         const int field) const;

    bool isWinner(const playerId player) const;
    bool hasWinner() const;

    std::list<Move>& getPossibleMoves(const playerId player) const;
    bool canMove(const playerId player) const;
    bool canEscape(const playerId player) const;
    bool needsToEscape(const playerId player) const;
    bool isFieldOccupied(const playerId player, const int field) const;
    bool isSliceOccupied(const playerId player, const int start,
                         const int end) const;
    bool isMoveAllowed(const playerId player, const Move& move) const;
    Board& move(const playerId player, const Move& move);
    Board& escape(const playerId player);

private:
    /** Stores the value of the dice. */
    int mDice;

    /** Stores the number of players on the board. */
    int mPlayersCnt;

    /**
     * Stores the size of the board, so the count of fields that are shared
     * among all players.
     */
    int mBoardSize;

    /** Stores the number of figures per player. */
    int mTotalFigures;

    /** Stores the number of all fields on the board including the bar. */
    int mFieldsCnt;

    /**
     * Stores the gap between adjacent players, so the count of fields
     * between the starting points of two adjacent players.
     */
    int mGap;

    std::vector<int> mFiguresOffBoard;
    std::vector<std::vector<int> > mFiguresOnField;

    Board& setDice(const int value);

    Board& setFiguresOffBoard(const playerId player, const int figures);
    Board& addFiguresOffBoard(const playerId player, const int figures);

    Board& setFiguresOnField(const playerId player, const int field,
                             const int figures);
    Board& addFiguresOnField(const playerId player, const int field,
                             const int figures);

    std::list<Move>& getCapturingMoves(const playerId player,
                                       const std::list<Move>& moves) const;
    Board& capture(const playerId player, const int field);
};

} // namespace ReniMadden

#endif // BOARD_H

// vim: set ts=4 sw=4:
