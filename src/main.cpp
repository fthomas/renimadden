#include "board.h"
#include "playerid.h"
#include "move.h"

#include <ctime>
#include <iostream>
#include <list>

using namespace std;
using namespace ReniMadden;

int main(int argc, char* argv[]) {

  Board board = Board();

  board.setFiguresOffBoard(PLAYER1, 0);
  board.setFiguresOnField(PLAYER1, 46, 1);
  board.setFiguresOnField(PLAYER1, 47, 1);
  board.setFiguresOnField(PLAYER1, 23, 1);
  board.setFiguresOnField(PLAYER1, 49, 1);
  board.setDice(2);

  list<Move> pm = board.getPossibleMoves(PLAYER1);
  list<Move>::const_iterator it;
  for (it = pm.begin(); it != pm.end(); ++it)
    cout << *it << endl;

  return 0;
}

// vim: set ts=2 sw=2:
