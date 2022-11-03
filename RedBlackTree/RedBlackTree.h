#include <algorithm>
#include <array>
#include <climits>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>

#define COLOR_RED 1
#define COLOR_BLACK 2
#define ANSI_COLOR_RED "\033[31;1m"
#define ANSI_COLOR_BLACK "\033[35;1m"
#define ANSI_COLOR_NORMAL "\033[0m"

using namespace std;

template <typename T> struct Node {
  T m_key;
  Node *m_parent;
  Node *m_lchild;
  Node *m_rchild;
  int m_color{COLOR_RED};
};

template <typename T> class RedblackTree {
private:
  Node<T> *m_root;
  void preOrderP(Node<T> *root);
  static Node<T> *NIL_NODE_PTR;

public:
  RedblackTree();
  void rb_left_rotate(Node<T> *x);
  void rb_right_rotate(Node<T> *x);
  void rb_insert(Node<T> *x);
  void rb_insert_fixup(Node<T> *x);
  void preOrder();
  void createRBTree(const vector<int> &nodes);
};

template <typename T> RedblackTree<T>::RedblackTree() {
  NIL_NODE_PTR = new Node<T>{m_color : COLOR_BLACK};
  m_root = NIL_NODE_PTR;
}

template <typename T> Node<T> *RedblackTree<T>::NIL_NODE_PTR;

template <typename T> void RedblackTree<T>::preOrderP(Node<T> *root) {
  if (root == NIL_NODE_PTR)
    return;

  preOrderP(root->m_lchild);
  if (root->m_color == COLOR_RED) {
    cout << ANSI_COLOR_RED << root->m_key << ANSI_COLOR_NORMAL << " ";
  } else {
    cout << ANSI_COLOR_BLACK << root->m_key << ANSI_COLOR_NORMAL << " ";
    ;
  }
  preOrderP(root->m_rchild);
}

template <typename T> void RedblackTree<T>::rb_left_rotate(Node<T> *x) {
  Node<T> *y = x->m_rchild;  // make y right child of x
  x->m_rchild = y->m_lchild; // make y's left subtree as x's right subtree

  if (y->m_lchild != NIL_NODE_PTR)
    y->m_lchild->m_parent = x;
  y->m_parent = x->m_parent;

  if (x->m_parent == NIL_NODE_PTR)
    m_root = y;
  else if (x == x->m_parent->m_lchild)
    x->m_parent->m_lchild = y;
  else
    x->m_parent->m_rchild = y;

  y->m_lchild = x; // put x of y's left
  x->m_parent = y; // make x child of y
}

template <typename T> void RedblackTree<T>::rb_right_rotate(Node<T> *x) {
  Node<T> *y = x->m_lchild;  // make y left child of x
  x->m_lchild = y->m_rchild; // make y's right subtree as x's left subtree

  if (y->m_rchild != NIL_NODE_PTR)
    y->m_rchild->m_parent = x;
  y->m_parent = x->m_parent;

  if (x->m_parent == NIL_NODE_PTR)
    m_root = y;
  else if (x == x->m_parent->m_lchild)
    x->m_parent->m_lchild = y;
  else
    x->m_parent->m_rchild = y;

  y->m_rchild = x; // put x of y's right
  x->m_parent = y; // make x child of y
}

template <typename T> void RedblackTree<T>::rb_insert(Node<T> *x) {
  Node<T> *parentNode = NIL_NODE_PTR;
  Node<T> *rootNode = m_root;
  while (rootNode != NIL_NODE_PTR) {
    parentNode = rootNode;
    if (rootNode->m_key < x->m_key)
      rootNode = rootNode->m_rchild;
    else
      rootNode = rootNode->m_lchild;
  }
  x->m_parent = parentNode;

  if (parentNode == NIL_NODE_PTR)
    m_root = x;
  else if (parentNode->m_key > x->m_key)
    parentNode->m_lchild = x;
  else
    parentNode->m_rchild = x;

  x->m_lchild = NIL_NODE_PTR;
  x->m_rchild = NIL_NODE_PTR;

  x->m_color = COLOR_RED;
  rb_insert_fixup(x);
}

template <typename T> void RedblackTree<T>::rb_insert_fixup(Node<T> *x) {
  // check if parent is red
  while (x->m_parent->m_color == COLOR_RED) {

    // x's parent is left child of x's grand parent
    if (x->m_parent == x->m_parent->m_parent->m_lchild) {

      // y is the uncle of x (right)
      Node<T> *y = x->m_parent->m_parent->m_rchild;

      if (y->m_color == COLOR_RED) {

        /*color parent and uncle as black
         * color grand parent as red
         * set x as grandparent , move up by two levels
         */

        x->m_parent->m_color = COLOR_BLACK;
        y->m_color = COLOR_BLACK;
        x->m_parent->m_parent->m_color = COLOR_RED;
        x = x->m_parent->m_parent;
      }
      // y(uncle) is black
      else {
        // x is the right child
        if (x == x->m_parent->m_rchild) {
          x = x->m_parent;
          rb_left_rotate(x);
        }

        // color parent as black and grand parent as red
        x->m_parent->m_color = COLOR_BLACK;
        x->m_parent->m_parent->m_color = COLOR_RED;
        rb_right_rotate(x->m_parent->m_parent);
      }
    }

    // x's parent is right child of x's grand parent
    else {

      // y is the uncle of x (left)
      Node<T> *y = x->m_parent->m_parent->m_lchild;

      if (y->m_color == COLOR_RED) {

        /*color parent and uncle as black
         * color grand parent as red
         * set x as grandparent , move up by two levels
         */

        x->m_parent->m_color = COLOR_BLACK;
        y->m_color = COLOR_BLACK;
        x->m_parent->m_parent->m_color = COLOR_RED;
        x = x->m_parent->m_parent;
      }
      // y(uncle) is black
      else {
        // x is the left child
        if (x == x->m_parent->m_lchild) {
          x = x->m_parent;
          rb_right_rotate(x);
        }

        // color parent as black and grand parent as red
        x->m_parent->m_color = COLOR_BLACK;
        x->m_parent->m_parent->m_color = COLOR_RED;
        rb_left_rotate(x->m_parent->m_parent);
      }
    }
  }
  m_root->m_color = COLOR_BLACK;
}

template <typename T> void RedblackTree<T>::preOrder() {
  cout << "\nPriting Reb-Black Tree nodes in pre-order...\n";
  preOrderP(m_root);
  cout << endl;
}
