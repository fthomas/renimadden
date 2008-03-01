/*
   ReniMadden - Mensch ärgere dich nicht for KDE
   Copyright © 2007-2008 Frank S. Thomas <frank@thomas-alfeld.de>

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

#include <ostream>

#include "move.h"

namespace ReniMadden {

  Move::Move() {
    start = 0;
    end = 0;
  }

  Move::Move(const int _start, const int _end) {
    if (_start >= _end)
      throw std::logic_error("Move::Move(): start is greater than end");

    if (_start < 0)
      throw std::out_of_range("Move::Move(): start is negative");

    start = _start;
    end = _end;
  }

  int Move::getStartField() const {
    return start;
  }

  int Move::getEndField() const {
    return end;
  }

  bool operator==(const Move& a, const Move& b) {
    return (a.getStartField() == b.getStartField())
      && (a.getEndField() == b.getEndField());
  }

  std::ostream& operator<<(std::ostream& os, const Move& move) {
    return os << "Move(" << move.getStartField() << ", "
                         << move.getEndField() << ")";
  }

} // namespace ReniMadden

// vim: set ts=2 sw=2:
