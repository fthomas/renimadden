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

      for (int j = 0; j < 52; j++)
        figuresOnBoard[i][j] = 0;
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

  Board& Board::setDice(const int value) {
    if (value < 1 || value > 6)
      throw std::out_of_range("Board::setDice(): dice value is out of range");
    else
      dice = value;
    return *this;
  }

  int Board::getFiguresOffBoard(const playerId player) const {
    return figuresOffBoard[player];
  }

  Board& Board::addFiguresOffBoard(const playerId player, const int figures) {
    if ((figuresOffBoard[player] + figures) < 0)
      throw std::logic_error("Board::addFiguresOffBoard(): number of figures "
        "off-board will be negative");
    else
      figuresOffBoard[player] += figures;
    return *this;
  }

  Board& Board::setFiguresOffBoard(const playerId player, const int figures) {
    if (figures < 0)
      throw std::out_of_range("Board::setFiguresOffBoard(): number of figures "
        "off-board is negative");
    else
      figuresOffBoard[player] = figures;
    return *this;
  }

  int Board::getFiguresOnField(const playerId player, const int field) const {
    return figuresOnBoard[player][field];
  }

  Board& Board::addFiguresOnField(const playerId player, const int field,
    const int figures) {
    if ((figuresOnBoard[player][field] + figures) < 0)
      throw std::logic_error("Board::addFiguresOnField(): number of figures "
        "on field will be negative");
    else
      figuresOnBoard[player][field] += figures;
    return *this;
  }

  Board& Board::setFiguresOnField(const playerId player, const int field,
    const int figures) {
    if (figures < 0)
      throw std::out_of_range("Board::setFiguresOnField(): number of figures "
        "on field is negative");
    else
      figuresOnBoard[player][field] = figures;
    return *this;
  }

  int Board::getOpponentField(const playerId player, const playerId opponent,
    const int field) {
    int dist_opp = field + (player-opponent)*12;
    return (dist_opp < 0 ? dist_opp + 48 : dist_opp) % 48;
  }

  bool Board::isWinner(const playerId player) const {
    // Has the player off-board figures?
    if (figuresOffBoard[player] > 0)
      return false;

    // Has the player figures on-board?
    for (int i = 0; i < 48; i++) {
      if (figuresOnBoard[player][i] > 0)
        return false;
    }

    // If there are no remaining off-board and on-board figures they all must
    // be in the bar. So throw an exception if the bar is not fully stuffed.
    for (int j = 48; j < 52; j++) {
      if (figuresOnBoard[player][j] == 0)
        throw std::logic_error("Board::isWinner(): bar has empty fields "
          "although there are no remaining figures off- and on-board");
    }

    return true;
  }

  bool Board::hasWinner() const {
    for (int i = 0; i < 4; i++) {
      if (isWinner((playerId)i))
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

    // This list will hold all possible Moves for player and a pointer to it
    // will be the return value of this method.
    std::list<Move>* possibleMoves = new std::list<Move>;

    // Figures that got from off-board to on-board must move away from the
    // first field on the board as long as there are other figures off-board.
    // If the field where this figure could move is occupied by another own
    // figure it is allowed that it moves one field further. If this field is
    // also occupied it may move another field further.
    if (getFiguresOnField(player, 0) > 0) {
      if (getFiguresOffBoard(player) > 0) {
        if (getFiguresOnField(player, dice) == 0)
          possibleMoves->push_back(Move(0, dice));
        else if (getFiguresOnField(player, dice + 1) == 0)
          possibleMoves->push_back(Move(0, dice + 1));
        else if (getFiguresOnField(player, dice + 2) == 0)
          possibleMoves->push_back(Move(0, dice + 2));

        return *possibleMoves;
      }
      else if (getFiguresOnField(player, dice) == 0)
        possibleMoves->push_back(Move(0, dice));
    }

    for (int i = 1; i < 43; i++) {
      if (getFiguresOnField(player, i) > 0) {
        if (getFiguresOnField(player, i + dice) == 0)
          possibleMoves->push_back(Move(i, i + dice));
      }
    }

    // Check possible moves right in front of the bar.
    for (int j = 43; j < 51; j++) {
      if (j + dice > 51)
        break;

      if (getFiguresOnField(player, j) > 0) {
        bool can_move = true;
        
        // Moves in or into the bar are only allowed if no other figure is on
        // a field in front of the move's destination. Or to put it another
        // way, you can't jump over figures that are in the bar.
        int lower_limit = (j > 47) ? j: 47;
        for (int k = j + dice; k > lower_limit; k--) {
          if (getFiguresOnField(player, k) != 0)
            can_move = false;
        }

        if (getFiguresOnField(player, j + dice) == 0 && can_move)
          possibleMoves->push_back(Move(j, j + dice));
      }
    }

    return *possibleMoves;
  }

  bool Board::canMove(const playerId player) const {
    return ! getPossibleMoves(player).empty();
  }

  bool Board::isMoveAllowed(const playerId player, const Move& move) const {
    std::list<Move> pm = getPossibleMoves(player);
    std::list<Move>::const_iterator it;

    for (it = pm.begin(); it != pm.end(); ++it) {
      if (*it == move)
        return true;
    }
    return false;
  }

  void Board::move(const playerId player, const Move& move) {
    if (! isMoveAllowed(player, move))
      return;

    int start = move.getStartField();
    int end = move.getEndField();

    // Move the own figure from the start field to the end field.
    if (getFiguresOnField(player, start) > 0) {
      addFiguresOnField(player, start, -1);
      addFiguresOnField(player, end, 1);
    }

    // Capture possible opponent figures and move them off-board.
    for (int i = 0; i < 4; i++) {
      playerId opponent = (playerId) i;
      if (opponent == player)
        continue;

      int opp_field = getOpponentField(player, opponent, end);
      if (getFiguresOnField(opponent, opp_field) > 0) {
        addFiguresOnField(opponent, opp_field, -1);
        addFiguresOffBoard(opponent, 1);
        break;
      }
    }
  }

} // namespace ReniMadden

// vim: set ts=2 sw=2:
