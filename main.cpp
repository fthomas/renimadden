//#include "board.h"
//#include "playerid.h"
#include "move.h"

#include <ctime>
#include <iostream>

using namespace std;
using namespace ReniMadden;

int main(int argc, char* argv[]) {

/*  Board board1 = Board;
  board1.reset();
  board1.rollDice();
  board1.getPossibleMoves(PLAYER1);*/

  Move m1  = Move(1, 4);
  cout << m1;

  return 0;
}

// vim: set ts=2 sw=2:
