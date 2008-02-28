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

#ifndef BOARDTEST_H
#define BOARDTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "board.cpp"
#include "move.cpp"
#include "playerid.h"

using namespace std;
using namespace ReniMadden;

class BoardTest : public CppUnit::TestFixture {

  CPPUNIT_TEST_SUITE(BoardTest);
  CPPUNIT_TEST(testDice);
  CPPUNIT_TEST(testMovesBoard);
  CPPUNIT_TEST(testMovesBar);
  CPPUNIT_TEST(testGetOpponentField); 
  CPPUNIT_TEST_SUITE_END();

  private:
    Board* board;

  public:
    void setUp() {
      board = new Board();
    }

    void tearDown() {
      delete board;
    }

    void testDice() {
      board->setDice(3);
      CPPUNIT_ASSERT( board->getDice() == 3 );

      board->reset();
      CPPUNIT_ASSERT( board->getDice() == 0 );

      for (int i = 0; i < 4096; i++) {
        board->rollDice();
        CPPUNIT_ASSERT( board->getDice() >= 1 && board->getDice() <= 6 );
      }
    }

    void testMovesBoard() {
      board->reset();
      board->setFiguresOnField(PLAYER1, 20, 1);
      board->setFiguresOnField(PLAYER1, 10, 1);
      board->setDice(4);
      CPPUNIT_ASSERT( board->isMoveAllowed(PLAYER1, Move(20, 24)) == true );
      CPPUNIT_ASSERT( board->isMoveAllowed(PLAYER1, Move(20, 25)) == false );
    }

    void testMovesBar() {
      board->reset();
      board->setFiguresOnField(PLAYER1, 48, 1);
      board->setDice(2);
      list<Move> pm = board->getPossibleMoves(PLAYER1);
      CPPUNIT_ASSERT( pm.front() == Move(48, 50) );

      board->reset();
      board->setFiguresOnField(PLAYER1, 46, 1);
      board->setFiguresOnField(PLAYER1, 48, 1);
      board->setDice(3);
      pm = board->getPossibleMoves(PLAYER1);
      CPPUNIT_ASSERT( pm.size() == 1 );
      CPPUNIT_ASSERT( board->canMove(PLAYER1) == true );
      CPPUNIT_ASSERT( pm.front() == Move(48, 51) );

      board->reset();
      board->setFiguresOnField(PLAYER1, 46, 1);
      board->setFiguresOnField(PLAYER1, 49, 1);
      board->setDice(2);
      pm = board->getPossibleMoves(PLAYER1);
      CPPUNIT_ASSERT( pm.size() == 2 );
      CPPUNIT_ASSERT( board->canMove(PLAYER1) == true );
      CPPUNIT_ASSERT( pm.front() == Move(46, 48) );
      pm.pop_front();
      CPPUNIT_ASSERT( pm.front() == Move(49, 51) );
    }

    void testGetOpponentField() {
      CPPUNIT_ASSERT( Board::getOpponentField(PLAYER1, PLAYER2, 1) == 37 );
      CPPUNIT_ASSERT( Board::getOpponentField(PLAYER1, PLAYER3, 1) == 25 );
      CPPUNIT_ASSERT( Board::getOpponentField(PLAYER1, PLAYER4, 1) == 13 );
      
      CPPUNIT_ASSERT( Board::getOpponentField(PLAYER2, PLAYER1, 1) == 13 );
      CPPUNIT_ASSERT( Board::getOpponentField(PLAYER3, PLAYER2, 1) == 13 );
      CPPUNIT_ASSERT( Board::getOpponentField(PLAYER4, PLAYER3, 1) == 13 );
      
      CPPUNIT_ASSERT( Board::getOpponentField(PLAYER4, PLAYER1, 7) == 43 );
      CPPUNIT_ASSERT( Board::getOpponentField(PLAYER4, PLAYER2, 8) == 32 );
      CPPUNIT_ASSERT( Board::getOpponentField(PLAYER4, PLAYER3, 9) == 21 );
    }
};

#endif // BOARDTEST_H

// vim: set ts=2 sw=2: