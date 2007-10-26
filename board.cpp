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
#include <stdexcept>

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

  unsigned Board::getDice() const {
    return dice;
  }

  Board& Board::setDice(unsigned value) {
    if (value < 1 || value > 6)
      throw std::out_of_range("value for Board::setDice() is out of range");
    else
      dice = value;

    return *this;
  }

  bool Board::isWinner(playerId player) const {
    // Does the player has off-board figures?
    if (figuresOffBoard[player] > 0)
      return false;

    // Does the player has figures on-board?
    for (int i = 0; i < 46; i++) {
      if (figuresOnBoard[player][i] > 0)
        return false;
    }

    // If there are no remaining off-board and on-board figures they all must
    // be in the bar. So throw an exception if the bar is not fully stuffed.
    for (int j = 0; j < 4; j++) {
      if (figuresOnBar[player][j] == 0)
        throw std::logic_error("bar has empty fields although there are no " 
          "remaining figures off- and on-board");
    }

    return true;
  }

  bool Board::hasWinner() const {
    if (this->isWinner(PLAYER1))
      return true;
    if (this->isWinner(PLAYER2))
      return true;
    if (this->isWinner(PLAYER3))
      return true;
    if (this->isWinner(PLAYER4))
      return true;

    return false;
  }

} // namespace ReniMadden

// vim: set ts=2 sw=2:
