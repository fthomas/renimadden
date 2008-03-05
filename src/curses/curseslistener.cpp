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

#include <vector>
#include <unistd.h>
#include <ncurses.h>

#include "curseslistener.h"

#define playerChar(player) ((char) ((int) player + 65))
#define figureChar(player) ((char) ((int) player + 97)) | A_BOLD | A_UNDERLINE

namespace ReniMadden
{

CursesListener::CursesListener(Board* board)
{
    mBoard = board;
    cy = 10;
    cx = 24;
    mWait = 500000;
    std::vector<std::vector<int> > tmp(board->getBoardSize(),
                                       std::vector<int>(2, 0));
    mField = tmp;

    drawBoard();
    refreshAll();
}

void CursesListener::refreshAll()
{
    refreshOffBoard();
    refreshBoard();
    refreshBar();

    int ch = getch();
    int step = 50000;
    if (ch == KEY_RIGHT && mWait - step >= step) {
        mWait -= step;
    } else if (ch == KEY_LEFT && mWait + step <= 5000000) {
        mWait += step;
    }

    move(0, 0);
    refresh();
    usleep(mWait);
}

void CursesListener::diceRolled(const int dice)
{
    mvprintw(cy - 5, cx + 25, "Dice value: %i", dice);
    refreshAll();
}

void CursesListener::playerChanged(const playerId player)
{
    mvprintw(cy - 6, cx + 25, "Active player: %c", playerChar(player));
    mvaddch(cy - 5, cx + 25 + 12, ' ');
    refreshAll();
}

void CursesListener::figureMoved(const BoardInfo& info, const Move& move)
{
    refreshAll();
}

void CursesListener::gameEndedWithWinner(const playerId player)
{
    mvprintw(cy - 3, cx + 25, "Player %c wins the game!", playerChar(player));
    refreshAll();
}

void CursesListener::drawBoard()
{
    mvprintw(cy - 9, cx - 21, "ReniMadden curses interface");
    mvprintw(cy - 8, cx - 21, "===========================");

    mvaddch(cy, cx - 3, 'A');
    mvaddch(cy - 1, cx, 'B');
    mvaddch(cy, cx + 3, 'C');
    mvaddch(cy + 1, cx, 'D');

    int y = cy - 1;
    int x = cx - 18;

    for (int i = 0; i < mField.size(); i++) {
        mField[i][0] = y;
        mField[i][1] = x;
        mvaddch(y, x, '0');

        if (i < 5) {
            x += 3;
        } else if (i < 10) {
            y--;
        } else if (i < 12) {
            x += 3;
        } else if (i < 17) {
            y++;
        } else if (i < 22) {
            x += 3;
        } else if (i < 24) {
            y++;
        } else if (i < 29) {
            x -= 3;
        } else if (i < 34) {
            y++;
        } else if (i < 36) {
            x -= 3;
        } else if (i < 41) {
            y--;
        } else if (i < 46) {
            x -= 3;
        } else if (i < 48) {
            y--;
        }
    }
}

void CursesListener::refreshBoard()
{
    for (int i = 0; i < mField.size(); i++) {
        bool occupied = false;
        playerId occupiedBy;

        for (int p = 0; p < mBoard->getPlayersCnt(); p++) {
            playerId player = (playerId) p;
            int pos = mBoard->getOpponentField(PLAYER1, player, i);

            if (mBoard->getFiguresOnField(player, pos) > 0) {
                occupied = true;
                occupiedBy = player;
                break;
            }
        }

        if (occupied) {
            mvaddch(mField[i][0], mField[i][1], figureChar(occupiedBy));
        } else {
            mvaddch(mField[i][0], mField[i][1], '0');
        }
    }
}

void CursesListener::refreshOffBoard()
{
    for (int i = 0; i < mBoard->getPlayersCnt(); i++) {
        if (i == 0) {
            drawOffBoard(cy - 5, cx - 18, (playerId) i);
        } else if (i == 1) {
            drawOffBoard(cy - 5, cx +  9, (playerId) i);
        } else if (i == 2) {
            drawOffBoard(cy + 4, cx +  9, (playerId) i);
        } else if (i == 3) {
            drawOffBoard(cy + 4, cx - 18, (playerId) i);
        }
    }
}

void CursesListener::drawOffBoard(const int y, const int x,
                                  const playerId player)
{
    mvprintw(y, x, "%c:", playerChar(player));
    int fy = y;
    int fx = x + 3;
    int f = mBoard->getFiguresOffBoard(player);

    for (int i = 0; i < 4; i++) {
        if (f >= i + 1) {
            mvaddch(fy, fx, figureChar(player));
        } else {
            mvaddch(fy, fx, ' ');
        }

        if (i == 1) {
            fy++;
            fx = x + 3;
        } else {
            fx += 3;
        }
    }
}

void CursesListener::refreshBar()
{
    int s = mBoard->getBoardSize();
    for (int p = 0; p < mBoard->getPlayersCnt(); p++) {
        for (int b = 0; b < 4; b++) {
            if (p == 0) {
                if (mBoard->getFiguresOnField((playerId) p, s + b) > 0) {
                    mvaddch(cy, cx - 15 + 3 * b, figureChar(p));
                } else {
                    mvaddch(cy, cx - 15 + 3 * b, (char)(b + 48 + 1));
                }
            } else if (p == 1) {
                if (mBoard->getFiguresOnField((playerId) p, s + b) > 0) {
                    mvaddch(cy - 5 + b, cx, figureChar(p));
                } else {
                    mvaddch(cy - 5 + b, cx, (char)(b + 48 + 1));
                }
            } else if (p == 2) {
                if (mBoard->getFiguresOnField((playerId) p, s + b) > 0) {
                    mvaddch(cy, cx + 15 - 3 * b, figureChar(p));
                } else {
                    mvaddch(cy, cx + 15 - 3 * b, (char)(b + 48 + 1));
                }
            } else if (p == 3) {
                if (mBoard->getFiguresOnField((playerId) p, s + b) > 0) {
                    mvaddch(cy + 5 - b, cx, figureChar(p));
                } else {
                    mvaddch(cy + 5 - b, cx, (char)(b + 48 + 1));
                }
            }
        }
    }
}

} // namespace ReniMadden

// vim: set ts=4 sw=4:
