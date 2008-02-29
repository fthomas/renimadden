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

#include "move.h"
#include "playerid.h"

namespace ReniMadden {

  class Board {
    protected:
      int dice;
      int figuresOffBoard[4];

      // The first 48 fields are shared among all players and the last four
      // fields correspond to the bar of each player and are 'private'.
      int figuresOnBoard[4][52];

    public:
      Board();
      Board& reset();

      Board& rollDice();
      int getDice() const;
      Board& setDice(const int value);

      int getFiguresOffBoard(const playerId player) const;
      Board& addFiguresOffBoard(const playerId player, const int figures);
      Board& setFiguresOffBoard(const playerId player, const int figures);

      int getFiguresOnField(const playerId player, const int field) const;
      Board& addFiguresOnField(const playerId player, const int field,
        const int figures);
      Board& setFiguresOnField(const playerId player, const int field,
        const int figures);

      static int getOpponentField(const playerId player,
        const playerId opponent, const int field);

      bool isSane() const;
      bool isWinner(const playerId player) const;
      bool hasWinner() const;

      std::list<Move>& getPossibleMoves(const playerId player) const;
      bool canMove(const playerId player) const;
      bool needsToEscape(const playerId player) const;
      bool isMoveAllowed(const playerId player, const Move& move) const;
      void move(const playerId player, const Move& move);
  };

} // namespace ReniMadden

#endif // BOARD_H

// vim: set ts=2 sw=2:
