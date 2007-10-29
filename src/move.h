/*
   ReniMadden - Mensch ärgere dich nicht for KDE
   Copyright © 2007 Frank S. Thomas <frank@thomas-alfeld.de>

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

#ifndef MOVE_H
#define MOVE_H

#include <ostream>
#include <stdexcept>

namespace ReniMadden {

  class Move {
    private:
      int start;
      int end;

    public:
      inline Move() {
        start = 0;
        end = 0;
      }

      inline Move(const int _start, const int _end) {
        if (_start >= _end)
          throw std::logic_error("Move::Move(): start is greater than end");

        if (_start < 0 || _end > 49)
          throw std::out_of_range("Move::Move(): start or end are out of the "
            "valid range");

        start = _start;
        end = _end;
      }

      inline int getStartField() const {
        return start;
      }

      inline int getEndField() const {
        return end;
      }
  };

  std::ostream& operator<<(std::ostream& os, const Move& move);

} // namespace ReniMadden

#endif // MOVE_H

// vim: set ts=2 sw=2: