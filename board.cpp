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
#include <list>
#include <stdexcept>

#include "board.h"

namespace ReniMadden {

  Board::Board() {
    reset();
  }

  Board& Board::reset() {
    // Reset dice.
    dice = 0;

    // Reset the count of figures that are off-board and empty all fields on
    // the board and on the bars.
    for (int i = 0; i < 4; i++) {
      figuresOffBoard[i] = 4;

      for (int j = 0; j < 50; j++)
        figuresOnBoard[i][j] = 0;
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

  Board& Board::setDice(const unsigned value) {
    if (value < 1 || value > 6)
      throw std::out_of_range("Board::setDice(): dice value is out of range");
    else
      dice = value;

    return *this;
  }

  unsigned Board::getFiguresOnField(const playerId player,
    const unsigned field) const {
    return figuresOnBoard[player][field];
  }

  Board& Board::setFiguresOnField(const playerId player, const unsigned field,
    const int figures) {
    return *this;
  }

  bool Board::isWinner(const playerId player) const {
    // Has the player off-board figures?
    if (figuresOffBoard[player] > 0)
      return false;

    // Has the player figures on-board?
    for (int i = 0; i < 46; i++) {
      if (figuresOnBoard[player][i] > 0)
        return false;
    }

    // If there are no remaining off-board and on-board figures they all must
    // be in the bar. So throw an exception if the bar is not fully stuffed.
    for (int j = 46; j < 50; j++) {
      if (figuresOnBoard[player][j] == 0)
        throw std::logic_error("Board::isWinner(): bar has empty fields "
          "although there are no remaining figures off- and on-board");
    }

    return true;
  }

  bool Board::hasWinner() const {
    for (int i = 0; i < 4; i++) {
      if (this->isWinner((playerId)i))
        return true;
    }
    return false;
  }

  std::list<Move>& Board::getPossibleMoves(const playerId player) const {
    // Check if the dice was rolled before and throw a logic error if it
    // wasn't since there are no possible moves then (if you don't count moves
    // where start == end).
    if (dice == 0)
      throw std::logic_error("Board::getPossibleMoves(): dice is still set "
        "to zero, roll it first");

    std::list<Move>* possibleMoves = new std::list<Move>;

/*
    if (getFiguresOnField(player, 0) > 0 && figuresOffBoard[player] > 0) {
      if (getFiguresOnField(player, dice) > 0) {
        if (getFiguresOnField(player, dice+1) > 0)
          possibleMoves->push_back(Move(0, dice+2));
        else
          possibleMoves->push_back(Move(0, dice+1));
      }
      else
        possibleMoves->push_back(Move(0, dice));
    }

    return *possibleMoves;
    */
  }

} // namespace ReniMadden

// vim: set ts=2 sw=2:
