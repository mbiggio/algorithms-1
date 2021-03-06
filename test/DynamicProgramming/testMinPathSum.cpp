/*
  Copyright (C) 2019  Biagio Festa

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
#include <gtest/gtest.h>
#include <algorithms/DynamicProgramming/MinPathSum.hpp>
#include <vector>

namespace algorithms::test {

TEST(DynamicProgramming, MinPathSum) {
  const std::vector<int> kMatrix = {1, 3, 1, 1, 5, 1, 4, 2, 1};
  const int kExpectedSol = 7;

  ASSERT_EQ(MinPathSum(kMatrix.data(), 3, 3), kExpectedSol);
}

}  // namespace algorithms::test
