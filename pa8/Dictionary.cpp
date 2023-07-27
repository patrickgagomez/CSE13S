/*******************************************************************************
 * Patrick Gomez
 * pggomez 2022 Spring CSE101 PA#8 Dictionary.cpp
 * The '.cpp' file for the Dictionary ADT.
 *********************************************************************************/
#include "Dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

// Class Constructors & Destructors ----------------------------------------
Dictionary::Node::Node(keyType k, valType v) {
  key = k;
  val = v;
  parent = nullptr;
  left = nullptr;
  right = nullptr;
  color = black;
}

Dictionary::Dictionary() {
  nil = new Node("", -1);
  root = nil;
  current = nullptr;
  num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary &D) {
  // set everything to nullptr except what was passed in
  nil = new Node("", -1);
  root = nil;
  current = nullptr;
  num_pairs = 0;

  // then copy over the other dictionary
  preOrderCopy(D.root, D.nil);
}

Dictionary::~Dictionary() {
  if (nil != nullptr) {
    clear();
    delete (nil);
    nil = nullptr;
  }
}

// Helper Functions (Optional) ---------------------------------------------

void Dictionary::inOrderString(std::string &s, Node *R) const {
  if (R != nil) {
    inOrderString(s, R->left);
    s += (R->key);
    s += " : ";
    s += std::to_string(R->val);
    s += "\n";
    inOrderString(s, R->right);
  }
  return;
}

void Dictionary::preOrderString(std::string &s, Node *R) const {
  if (R != nil) {
    s += (R->key);
    s += "\n";
    preOrderString(s, R->left);
    preOrderString(s, R->right);
  }
  return;
}

void Dictionary::preOrderCopy(Node *R, Node *N) {
  if (R != nil) {
    if (R->key != N->key && R->val != N->val) {
      setValue(R->key, R->val);
      preOrderCopy(R->left, N);
      preOrderCopy(R->right, N);
    }
  }
  return;
}

void Dictionary::inOrderCopy(Node *R, Node *N) {
  if (R != nullptr) {
    if (R->key != N->key && R->val != N->val) {
      inOrderCopy(R->left, N);
      setValue(R->key, R->val);
      inOrderCopy(R->right, N);
    }
  }
  return;
}

void Dictionary::postOrderDelete(Node *R) {
  if (R == nullptr || R == nil) {
    return;
  }
  postOrderDelete(R->left);
  postOrderDelete(R->right);
  num_pairs--;
  delete (R);
}

Dictionary::Node *Dictionary::search(Node *R, keyType k) const {
  while (R->key != k && R != nil) {
    if (R->key > k) {
      R = R->left;
    } else if (R->key < k) {
      R = R->right;
    }
  }

  if (R->key == k) {
    return R;
  }
  return nil;
}

Dictionary::Node *Dictionary::findMin(Node *R) {
  // dont do anything on empty dict.
  if (R == nullptr || R == nil) {
    return nullptr;
  }

  // otherwise slam left until nullptr
  while (R->left != nil) {
    R = R->left;
  }
  // and return left most node
  return R;
}

Dictionary::Node *Dictionary::findMax(Node *R) {
  // dont do anything on empty dict.
  if (R == nullptr || R == nil) {
    return nullptr;
  }

  // otherwise slam right until nullptr
  while (R->right != nil) {
    R = R->right;
  }
  // and return right most node
  return R;
}

Dictionary::Node *Dictionary::findNext(Node *N) {
  // call find min on the right if it's not null...
  if (N->right != nil) {
    return findMin(N->right);
  }

  // otherwise grab N's parent
  Node *y = N->parent;
  // and while it's not null and it's right isnt null
  while (y != nil && N == y->right) {
    // inchworm the tree
    N = y;
    y = y->parent;
  }
  // and return y node
  return y;
}

Dictionary::Node *Dictionary::findPrev(Node *N) {
  // same concept as above, but with LEFT instead of right.
  if (N->left != nil) {
    return findMax(N->left);
  }
  Node *y = N->parent;
  while (y != nil && N == y->left) {
    N = y;
    y = y->parent;
  }
  return y;
}

// RBT Helper Functions (Optional) -----------------------------------------

// FOR ALL RBT FUNCTIONS I FOLLOWED PSEUDO.
void Dictionary::LeftRotate(Node *N) {
  Node *y = N->right;

  N->right = y->left;
  if (y->left != nil) {
    y->left->parent = N;
  }

  y->parent = N->parent;
  if (N->parent == nil) {
    root = y;
  } else if (N == N->parent->left) {
    N->parent->left = y;
  } else {
    N->parent->right = y;
  }

  y->left = N;
  N->parent = y;
}

void Dictionary::RightRotate(Node *N) {
  Node *y = N->left;

  N->left = y->right;
  if (y->right != nil) {
    y->right->parent = N;
  }
  y->parent = N->parent;
  if (N->parent == nil) {
    root = y;
  } else if (N == N->parent->right) {
    N->parent->right = y;
  } else {
    N->parent->left = y;
  }

  y->right = N;
  N->parent = y;
}

void Dictionary::RB_InsertFixUp(Node *N) {
  while (N->parent->color == red) {
    if (N->parent == N->parent->parent->left) {
      Node *y = N->parent->parent->right;
      if (y->color == red) {
        N->parent->color = black;
        y->color = black;
        N->parent->parent->color = red;
        N = N->parent->parent;
      } else {
        if (N == N->parent->right) {
          N = N->parent;
          LeftRotate(N);
        }
        N->parent->color = black;
        N->parent->parent->color = red;
        RightRotate(N->parent->parent);
      }
    } else {
      Node *y = N->parent->parent->left;
      if (y->color == red) {
        N->parent->color = black;
        y->color = black;
        N->parent->parent->color = red;
        N = N->parent->parent;
      } else {
        if (N == N->parent->left) {
          N = N->parent;
          RightRotate(N);
        }
        N->parent->color = black;
        N->parent->parent->color = red;
        LeftRotate(N->parent->parent);
      }
    }
  }
  root->color = black;
}

void Dictionary::RB_Transplant(Node *u, Node *v) {
  if (u->parent == nil) {
    root = v;
  } else if (u == u->parent->left) {
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }
  v->parent = u->parent;
}

void Dictionary::RB_DeleteFixUp(Node *N) {
  while (N != root && N->color == black) {
    if (N == N->parent->left) {
      Node *w = N->parent->right;
      if (w->color == red) {
        w->color = black;
        N->parent->color = red;
        LeftRotate(N->parent);
        w = N->parent->right;
      }
      if (w->left->color == black && w->right->color == black) {
        w->color = red;
        N = N->parent;
      } else {
        if (w->right->color == black) {
          w->left->color = black;
          w->color = red;
          RightRotate(w);
          w = N->parent->right;
        }
        w->color = N->parent->color;
        N->parent->color = black;
        w->right->color = black;
        LeftRotate(N->parent);
        N = root;
      }
    } else {
      Node *w = N->parent->left;
      if (w->color == red) {
        w->color = black;
        N->parent->color = red;
        RightRotate(N->parent);
        w = N->parent->left;
      }
      if (w->right->color == black && w->left->color == black) {
        w->color = red;
        N = N->parent;
      } else {
        if (w->left->color == black) {
          w->right->color = black;
          w->color = red;
          LeftRotate(w);
          w = N->parent->left;
        }
        w->color = N->parent->color;
        N->parent->color = black;
        w->left->color = black;
        RightRotate(N->parent);
        N = root;
      }
    }
  }
  N->color = black;
}

void Dictionary::RB_Delete(Node *N) {
  Node *y = N;
  Node *x;

  int y_original_color = y->color;
  if (N->left == nil) {
    x = N->right;
    RB_Transplant(N, N->right);
  } else if (N->right == nil) {
    x = N->left;
    RB_Transplant(N, N->left);
  } else {
    y = findMin(N->right);
    y_original_color = y->color;
    x = y->right;
    if (y->parent == N) {
      x->parent = y;
    } else {
      RB_Transplant(y, y->right);
      y->right = N->right;
      y->right->parent = y;
    }
    RB_Transplant(N, y);
    y->left = N->left;
    y->left->parent = y;
    y->color = N->color;
  }
  if (y_original_color == black) {
    RB_DeleteFixUp(x);
  }
}

// Access functions --------------------------------------------------------

int Dictionary::size() const { return num_pairs; }

bool Dictionary::contains(keyType k) const {
  if (root == nil || num_pairs == 0) {
    return false;
  }

  Node *N = root;
  while (N->key != k && N != nil) {
    if (N->key > k) {
      if (N->left == nil) {
        return false;
      }
      N = N->left;
    } else if (N->key < k) {
      if (N->right == nil) {
        return false;
      }
      N = N->right;
    }
  }
  if (N->key == k) {
    return true;
  }
  return false;
}

valType &Dictionary::getValue(keyType k) const {
  // make sure it contains K first...
  if (contains(k)) {
    // then we grab the root...
    Node *N = root;
    // and go find K
    while (N->key != k && N != nil) {
      if (N->key > k) {
        N = N->left;
      } else if (N->key < k) {
        N = N->right;
      }
    }
    // once we find it, return its value
    return N->val;
  }
  // otherwise return nil val (nil)
  return nil->val;
}

bool Dictionary::hasCurrent() const {
  // if current is defined... you have a current!
  if (current != nullptr) {
    return true;
  }
  // other wise you dont.
  return false;
}

keyType Dictionary::currentKey() const {
  // if you dont have a current, throw a logic error
  if (!hasCurrent()) {
    throw std::logic_error("No current.");
  }
  // otherwise return the current key
  return current->key;
}

valType &Dictionary::currentVal() const {
  // if you dont have a current, throw a logic error
  if (!hasCurrent()) {
    throw std::logic_error("No current.");
  }
  // otherwise return current val
  return current->val;
}

// Manipulation procedures -------------------------------------------------

void Dictionary::clear() {
  // simple clear func.
  if (num_pairs == 0 || root == nil) {
    return;
  }

  postOrderDelete(root);
  root = nil;
  current = nullptr;
  return;
}

void Dictionary::setValue(keyType k, valType v) {
  Node *y = nil;
  Node *x = root;
  while (x != nil) {
    y = x;
    if (k < x->key) {
      x = x->left;
    } else if (k == x->key) {
      x->val = v;
      return;
    } else {
      x = x->right;
    }
  }
  Node *z = new Node(k, v);
  z->parent = y;
  if (y == nil) {
    root = z;
  } else if (z->key < y->key) {
    y->left = z;
  } else {
    y->right = z;
  }
  z->left = nil;
  z->right = nil;
  z->color = red;
  RB_InsertFixUp(z);
  num_pairs++;
}

void Dictionary::remove(keyType k) {
  Node *curr = root;

  while (curr != nil && curr->key != k) {
    if (k < curr->key) {
      curr = curr->left;
    } else {
      curr = curr->right;
    }
  }
  if (curr == nil) {
    return;
  }

  if (current == curr) {
    current = nullptr;
  }

  RB_Delete(curr);
  num_pairs--;
  return;
}

void Dictionary::begin() {
  if (root == nil) {
    current = nullptr;
  }
  current = findMin(root);
}

void Dictionary::end() {
  if (root == nil) {
    current = nullptr;
  }

  current = findMax(root);
}

void Dictionary::next() {
  if (current == findMax(root) || current == nullptr) {
    current = nullptr;
    return;
  }
  current = findNext(current);
}

void Dictionary::prev() {
  if (current == findMin(root) || current == nullptr) {
    current = nullptr;
    return;
  }

  current = findPrev(current);
}

// Other Functions ---------------------------------------------------------

std::string Dictionary::to_string() const {
  std::string s = "";

  inOrderString(s, root);

  return s;
}

std::string Dictionary::pre_string() const {
  std::string s = "";
  preOrderString(s, root);
  return s;
}

bool Dictionary::equals(const Dictionary &D) const {
  // if both are empty, they are equal...
  if (this->root == nil && D.root == nil) {
    return true;
  } else if (this->root == nil || D.root == nil) {
    return false;
  } else {

    std::string A = "";
    std::string B = "";

    this->preOrderString(A, this->root);
    D.preOrderString(B, D.root);

    // if they are the same, D and this are equal!
    if (A == B) {
      return true;
    }
    return false;
  }
}

// Overloaded Operators ----------------------------------------------------

std::ostream &operator<<(std::ostream &stream, Dictionary &D) {
  return stream << D.to_string();
}

bool operator==(const Dictionary &A, const Dictionary &B) {
  // simple == overwrite with helper functions
  bool eq = A.equals(B);
  if (eq) {
    return true;
  } else {
    return false;
  }
}

Dictionary &Dictionary::operator=(const Dictionary &D) {
  // same syntax as pa6 operator=!
  if (this != &D) {

    Dictionary temp = D;

    std::swap(nil, temp.nil);
    std::swap(root, temp.root);
    std::swap(current, temp.current);
    std::swap(num_pairs, temp.num_pairs);
  }

  return *this;
}
