/*

*/

#ifndef BOARD_H
#define BOARD_H

namespace ReniMadden {

  class Board {
    protected:
      int dice[2];
      int figuresOnBoard[4][46];

    void reset() {
        for (int i = 0; i < 46; i++) {
            figuresOnBoard[1][i] = 0;
        }
    }
}

} // namespace ReniMadden

#endif // BOARD_H
