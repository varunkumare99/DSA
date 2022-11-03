#include "RedBlackTree.h"
#include <vector>

template <typename T>
void createRBTree(RedblackTree<T> &rbTree, const vector<int> &nodes) {
  for (int i = 0; i < nodes.size(); ++i) {
    rbTree.rb_insert(new Node<int>{nodes[i]});
  }
}

int main() {
  int numOfNodes, num;
  vector<int> nodes;

  cout << "Enter number of nodes: ";
  cin >> numOfNodes;

  cout << "enter " << numOfNodes << " nodes : ";
  for (int i = 0; i < numOfNodes; ++i) {
    cin >> num;
    nodes.push_back(num);
  }

  RedblackTree<int> rbTree;
  createRBTree(rbTree, nodes);
  rbTree.preOrder();
}
