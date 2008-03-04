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

#include <ncurses.h>

#include "game.h"

using namespace ReniMadden;

int main(int argc, char* argv[])
{
    initscr();
    printw("TEST");
    refresh();
    getch();
    endwin();
    return 0;
}

// vim: set ts=4 sw=4:
