#include <iostream>
#include <ctime>
#include "board.h"

using namespace std;
using namespace ReniMadden;

int main(void) {
  Board board1, board3;
  Board* board2 = new Board;

  cout << board1.rollDice().getDice() << endl;
  board1.reset();
  for (int i=0; i < 40000; i++) board1.reset();

  cout << board2->rollDice().getDice() << endl;
  for (int i=0; i < 40000; i++) board1.reset();
  cout << board3.rollDice().getDice() << endl;
  board3.setDice(3);
  cout << "hat jemand gewonnen: " << board3.hasWinner() << endl;
  return 0;
}

// vim: set ts=2 sw=2:
