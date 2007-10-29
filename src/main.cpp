#include "board.h"
#include "playerid.h"
#include "move.h"

#include <ctime>
#include <iostream>
#include <list>

using namespace std;
using namespace ReniMadden;

int main(int argc, char* argv[]) {

  Board board = Board;

  board.setFiguresOffBoard(PLAYER1, 3);
  board.setFiguresOnField(PLAYER1, 0, 1);
  board.setDice(6);

  board.getPossibleMoves(PLAYER1);

  cout << "dsf" << endl;

  return 0;
}

// vim: set ts=2 sw=2:
