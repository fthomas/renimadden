/*
   ReniMadden - Mensch ärgere dich nicht for KDE
   Copyright © 2008 Frank S. Thomas <frank@thomas-alfeld.de>

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

#include <stdexcept>

#include "game.h"

using namespace std;

namespace ReniMadden
{

Game::Game(Board& board)
{
    mBoard = board;
    mActiveId = PLAYER1;
    mListeners = std::list<Listener>();
}

Game& Game::playUnattended()
{
    // Play as long as the board has no winner.
    while (! mBoard.hasWinner()) {
        if (mBoard.needsToEscape(mActiveId)) {
            for (int i = 0; i < 3; i++) {
                mBoard.rollDice();
                diceRolledInform(mBoard.getDice());
                if (mBoard.getDice() == 6) {
                    mBoard.escape(mActiveId);
                    break;
                }
            }
            if (mBoard.getDice() != 6) {
                nextPlayer();
                continue;
            }
        }

        std::list<Move> pm = std::list<Move>();

        while (mBoard.rollDice().getDice() == 6) {
            if (mBoard.canEscape(mActiveId)) {
                mBoard.escape(mActiveId);
            }
            pm = mBoard.getPossibleMoves(mActiveId);
            if (! pm.empty()) {
                mBoard.move(mActiveId, pm.front());
            }
        }

        pm = mBoard.getPossibleMoves(mActiveId);
        if (! pm.empty()) {
            mBoard.move(mActiveId, pm.front());
        } else {
            nextPlayer();
            continue;
        }

        if (! mBoard.isSane()) {
            throw std::logic_error("Game::playUnattended(): board is insane");
        }

        if (mBoard.isWinner(mActiveId)) {
            gameEndedWithWinnerInform(mActiveId);
            return *this;
        }
        nextPlayer();
    }
    return *this;
}

Game& Game::diceRolledInform(const int dice)
{
    std::list<Listener>::iterator it;
    for (it = mListeners.begin(); it != mListeners.end(); ++it) {
        (*it).diceRolled(dice);
    }
    return *this;
}

Game& Game::playerChangedInform(const playerId player)
{
    std::list<Listener>::iterator it;
    for (it = mListeners.begin(); it != mListeners.end(); ++it) {
        (*it).playerChanged(player);
    }
    return *this;
}

Game& Game::gameEndedWithWinnerInform(const playerId player)
{
    std::list<Listener>::iterator it;
    for (it = mListeners.begin(); it != mListeners.end(); ++it) {
        (*it).gameEndedWithWinner(player);
    }
    return *this;
}

playerId Game::nextPlayer()
{
    int playersCnt = mBoard.getPlayersCnt();
    mActiveId = (playerId)((mActiveId + 1) % playersCnt);
    playerChangedInform(mActiveId);
    return mActiveId;
}

} // namespace ReniMadden

// vim: set ts=4 sw=4:
