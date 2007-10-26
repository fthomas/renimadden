/*
   ReniMadden - Mensch ärgere dich nicht for KDE
   Copyright © 2007 Frank S. Thomas <frank@thomas-alfeld.de>

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

#include "playerid.h"

namespace ReniMadden {

  class Board {
    protected:
      unsigned dice;
      unsigned figuresOffBoard[4];
      unsigned figuresOnBoard[4][46];
      unsigned figuresOnBar[4][4];

    public:
      Board();
      Board& reset();
      Board& rollDice();
      unsigned getDice() const;
      Board& setDice(unsigned value);
      bool isWinner(playerId player) const;
      bool hasWinner() const;
  };

} // namespace ReniMadden

#endif // BOARD_H

// vim: set ts=2 sw=2:
