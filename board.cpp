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

#include <cstdlib>
#include <ctime>
#include "board.h"

namespace ReniMadden {

  Board::Board() {
    this->reset();
  }

  Board& Board::reset() {
    // Reset dice.
    dice = 0;

    // Reset the count of figures that are off-board and empty all fields on
    // the board and on the bars.
    for (int i = 0; i < 4; i++) {
      figuresOffBoard[i] = 4;

      for (int j = 0; j < 46; j++)
        figuresOnBoard[i][j] = 0;

      for (int k = 0; k < 4; k++)
        figuresOnBar[i][k] = 0;
    }

    return *this;
  }

  Board& Board::rollDice() {
    std::srand((unsigned)std::time(NULL)+(unsigned)std::clock());
    dice = (double(std::rand())/RAND_MAX)*6+1;
    return *this;
  }

  int Board::getDice() const {
    return dice;
  }

} // namespace ReniMadden

// vim: set ts=2 sw=2:
