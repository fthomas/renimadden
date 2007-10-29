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

  board.setFiguresOffBoard(PLAYER1, 3);
  board.setFiguresOnField(PLAYER1, 0, 1);
  board.setDice(6);

  std::list<Move> g =  board.getPossibleMoves(PLAYER1);

  cout << g.front() << endl;

  board.setFiguresOffBoard(PLAYER1, 2);
  board.setFiguresOnField(PLAYER1, 6, 1);

  cout << board.getPossibleMoves(PLAYER1).front() << endl;
  cout << (Move(1,2) == Move(1,2)) << endl;

  return 0;
}

// vim: set ts=2 sw=2:
