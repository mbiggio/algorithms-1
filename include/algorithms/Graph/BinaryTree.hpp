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
#ifndef ALGORITHMS__GRAPH__BINARY_TREE__HPP
#define ALGORITHMS__GRAPH__BINARY_TREE__HPP
#include <cassert>
#include <list>
#include <stack>
#include <type_traits>
#include <utility>
#include <vector>

namespace algorithms {

template <typename T>
class BinaryTree {
 public:
  using value_type = T;
  using const_reference = const value_type&;
  using size_type = std::size_t;
  class Node;

  template <typename U>
  BinaryTree(U&& rootValue) {
    const auto newIterator = _treeNodes.emplace(_treeNodes.end(),
                                                std::forward<U>(rootValue),
                                                nullptr,
                                                nullptr,
                                                nullptr,
                                                this);
    newIterator->_iterator = newIterator;
  }

  size_type size() const noexcept { return _treeNodes.size(); }

  const Node& getRoot() const noexcept { return _treeNodes.front(); }

  Node* getMutableRoot() noexcept { return &(_treeNodes.front()); }

 private:
  std::list<Node> _treeNodes;

  BinaryTree(const BinaryTree&) = delete;
  BinaryTree operator=(const BinaryTree&) = delete;

 public:
  class Node {
   public:
    template <typename U>
    Node(U&& value, Node* parent, Node* left, Node* right, BinaryTree* master)
        : _data(std::forward<U>(value)),
          _parent(parent),
          _leftChild(left),
          _rightChild(right),
          _master(master) {
      static_assert(std::is_constructible_v<value_type, U>);
    }

    const_reference getValue() const noexcept { return _data; }

    template <typename U>
    void setValue(U&& value) {
      static_assert(std::is_assignable_v<value_type&, U>);
      _data = std::forward<U>(value);
    }

    const Node* getLeft() const noexcept { return _leftChild; }

    Node* getMutableLeft() noexcept { return _leftChild; }

    const Node* getRight() const noexcept { return _rightChild; }

    Node* getMutableRight() noexcept { return _rightChild; }

    const Node* getParent() const noexcept { return _parent; }

    Node* getMutableParent() noexcept { return _parent; }

    template <typename U>
    Node* pushValueLeft(U&& value) {
      assert(_leftChild == nullptr);  // !

      auto& listNodes = _master->_treeNodes;
      auto newIterator = listNodes.emplace(listNodes.end(),
                                           std::forward<U>(value),
                                           this,
                                           nullptr,
                                           nullptr,
                                           _master);
      newIterator->_iterator = newIterator;
      _leftChild = &(listNodes.back());

      return _leftChild;
    }

    template <typename U>
    Node* pushValueRight(U&& value) {
      assert(_leftChild == nullptr);  // !

      auto& listNodes = _master->_treeNodes;
      auto newIterator = listNodes.emplace(listNodes.end(),
                                           std::forward<U>(value),
                                           this,
                                           nullptr,
                                           nullptr,
                                           _master);
      newIterator->_iterator = newIterator;
      _rightChild = &(listNodes.back());

      return _rightChild;
    }

    void pruneLeft() {
      pruneSubTree(_leftChild);
      _leftChild = nullptr;
    }

    void pruneRight() {
      pruneSubTree(_rightChild);
      _rightChild = nullptr;
    }

   private:
    using list_iterator = typename std::list<Node>::iterator;

    value_type _data;
    Node* _parent;
    Node* _leftChild;
    Node* _rightChild;
    BinaryTree* _master;
    list_iterator _iterator;

    Node(const Node&) = delete;
    Node(Node&&) = delete;
    Node& operator=(const Node&) = delete;
    Node& operator=(Node&&) = delete;

    void pruneSubTree(Node* node) {
      std::stack<Node*> dfs;
      dfs.push(node);

      while (!dfs.empty()) {
        Node* const current = dfs.top();
        dfs.pop();

        if (current != nullptr) {
          dfs.push(current->_leftChild);
          dfs.push(current->_rightChild);

          _master->_treeNodes.erase(current->_iterator);
        }
      }
    }

    friend class BinaryTree;
  };
};

}  // namespace algorithms

#endif  // ALGORITHMS__GRAPH__SIMPLE_BINARY_TREE__HPP
