/*
  Copyright (C) 2018  Biagio Festa

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
#include <algorithms/Graph/BinaryTree.hpp>
#include <string>

namespace algorithms::test {

TEST(BinaryTree, SingleValue) {
  constexpr int kValue = 1;
  BinaryTree<int> binaryTree{kValue};

  ASSERT_EQ(binaryTree.size(), 1ull);
  ASSERT_EQ(binaryTree.getRoot().getValue(), kValue);
  ASSERT_EQ(binaryTree.getRoot().getLeft(), nullptr);
  ASSERT_EQ(binaryTree.getMutableRoot()->getMutableLeft(), nullptr);
  ASSERT_EQ(binaryTree.getRoot().getRight(), nullptr);
  ASSERT_EQ(binaryTree.getMutableRoot()->getMutableRight(), nullptr);
  ASSERT_EQ(binaryTree.getRoot().getParent(), nullptr);
  ASSERT_EQ(binaryTree.getMutableRoot()->getMutableParent(), nullptr);
}

TEST(BinaryTree, ChangeValue) {
  std::string oldValue = "1";
  std::string newValue = "2";
  BinaryTree<std::string> binaryTree{oldValue};

  ASSERT_NE(oldValue, newValue);

  binaryTree.getMutableRoot()->setValue(newValue);
  ASSERT_EQ(binaryTree.getRoot().getValue(), newValue);

  binaryTree.getMutableRoot()->setValue(std::move(newValue));
  ASSERT_TRUE(newValue.empty());
}

TEST(BinaryTree, PushLeft) {
  constexpr int kFirstValue = 1;
  constexpr int kSecondValue = 2;

  BinaryTree<int> binaryTree{kFirstValue};

  binaryTree.getMutableRoot()->pushValueLeft(kSecondValue);
  ASSERT_EQ(binaryTree.size(), 2ull);

  ASSERT_NE(binaryTree.getRoot().getLeft(), nullptr);
  ASSERT_EQ(binaryTree.getRoot().getLeft()->getValue(), kSecondValue);
  ASSERT_EQ(binaryTree.getRoot().getLeft()->getParent(), &binaryTree.getRoot());
}

TEST(BinaryTree, PushRight) {
  constexpr int kFirstValue = 1;
  constexpr int kSecondValue = 2;

  BinaryTree<int> binaryTree{kFirstValue};

  binaryTree.getMutableRoot()->pushValueRight(kSecondValue);
  ASSERT_EQ(binaryTree.size(), 2ull);

  ASSERT_NE(binaryTree.getRoot().getRight(), nullptr);
  ASSERT_EQ(binaryTree.getRoot().getRight()->getValue(), kSecondValue);
  ASSERT_EQ(binaryTree.getRoot().getRight()->getParent(),
            &binaryTree.getRoot());
}

TEST(BinaryTree, PruneLeft) {
  BinaryTree<int> binaryTree{1};

  binaryTree.getMutableRoot()->pushValueLeft(2)->pushValueLeft(3);
  ASSERT_EQ(binaryTree.size(), 3ull);

  binaryTree.getMutableRoot()->pruneRight();
  ASSERT_EQ(binaryTree.size(), 3ull);

  binaryTree.getMutableRoot()->pruneLeft();
  ASSERT_EQ(binaryTree.size(), 1ull);

  ASSERT_EQ(binaryTree.getRoot().getLeft(), nullptr);
}

TEST(BinaryTree, PruneRight) {
  BinaryTree<int> binaryTree{1};

  binaryTree.getMutableRoot()->pushValueRight(2)->pushValueRight(3);
  ASSERT_EQ(binaryTree.size(), 3ull);

  binaryTree.getMutableRoot()->pruneLeft();
  ASSERT_EQ(binaryTree.size(), 3ull);

  binaryTree.getMutableRoot()->pruneRight();
  ASSERT_EQ(binaryTree.size(), 1ull);

  ASSERT_EQ(binaryTree.getRoot().getRight(), nullptr);
}

}  // namespace algorithms::test
