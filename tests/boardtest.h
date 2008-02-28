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

#include <board.cpp>

using namespace std;
using namespace ReniMadden;

class BoardTest : public CppUnit::TestFixture {

  CPPUNIT_TEST_SUITE(BoardTest);
  CPPUNIT_TEST(testDice);
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
};

#endif // BOARDTEST_H

// vim: set ts=2 sw=2:
