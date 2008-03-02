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

#include <iostream>
#include <unistd.h>

#include "game.h"
#include "playerid.h"

using namespace std;

namespace ReniMadden
{

Game::Game(Board& _board)
{
    board = _board;
    activeId = PLAYER1;
}

void Game::play_unattended()
{

    while (! board.hasWinner()) {
        cout << endl;

        // Let the player try to "escape" from off-board three times.
        if (board.needsToEscape(activeId)) {
            for (int i = 0; i < 3; i++) {
                board.rollDice();
                cout << "Player " << activeId << " tries to escape: "
                << board.getDice() << endl;

                if (board.getDice() == 6) {
                    board.addFiguresOffBoard(activeId, -1);
                    board.addFiguresOnField(activeId, 0, 1);
                    break;
                }
            }
            // The player is unlucky; next!
            if (board.getDice() != 6) {
                nextPlayer();
                continue;
            }
        }

        // Let the player dice (again).
        board.rollDice();
        if (board.getDice() == 6 && board.canEscape(activeId)) {
            board.addFiguresOffBoard(activeId, -1);
            board.addFiguresOnField(activeId, 0, 1);
        }
        cout << "Player " << activeId << " dices: " << board.getDice() << endl;
        usleep(5000);
        list<Move> pm = board.getPossibleMoves(activeId);
        if (pm.empty()) {
            activeId = (playerId)(((int)activeId + 1) % 4) ;
            continue;
        }
        Move m = board.getPossibleMoves(activeId).front();
        board.move(activeId, m);
        cout << "Player " << activeId << " makes this move: "
        << m <<  endl;
        if (!board.isSane()) {
            cout << "ERRRROR";
            return;
        }

        if (board.isWinner(activeId))
            cout << "Player " << activeId << " has won!" << endl;

        activeId = (playerId)(((int)activeId + 1) % 4) ;
    } // while (! board.hasWinner())
}

playerId Game::nextPlayer()
{
    activeId = (playerId)((activeId + 1) % 4);
    return activeId;
}

} // namespace ReniMadden

// vim: set ts=4 sw=4:
