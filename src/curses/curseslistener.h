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

#ifndef CURSES_LISTENER_H
#define CURSES_LISTENER_H

#include "board.h"
#include "listener.h"

namespace ReniMadden
{

class CursesListener : public Listener
{
public:
    CursesListener(Board* board);

    void diceRolled(const int dice);
    void playerChanged(const playerId player);
    void figureMoved(const BoardInfo& info, const Move& move);
    void gameEndedWithWinner(const playerId player);

private:
    Board* mBoard;
    int cy;
    int cx;
    uint mWait;
    std::vector<std::vector<int> > mField;

    void drawBoard();
    void refreshBoard();
    void refreshOffBoard();
    void drawOffBoard(const int y, const int x, const playerId player);
    void refreshBar();
    void refreshAll();

};

} // namespace ReniMadden

#endif // CURSES_LISTENER_H

// vim: set ts=4 sw=4:
