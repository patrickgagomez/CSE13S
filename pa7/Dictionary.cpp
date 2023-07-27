/*******************************************************************************
 *Patrick Gomez,
 *pggomez 2022 Spring CSE101 PA#7 Dictionary.cpp The '.cpp' file for the
 *Dictionary ADT
 *********************************************************************************/
#include "Dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

// Class Constructors & Destructors ----------------------------------------

Dictionary::Node::Node(keyType k, valType v) {
  // set everything to nullptr except what was passed in
  key = k;
  val = v;
  parent = nullptr;
  left = nullptr;
  right = nullptr;
}

Dictionary::Dictionary() {
  // set everything to nullptr except what was passed in
  nil = new Node("", 0);
  root = nullptr;
  current = nullptr;
  num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary &D) {
  // set everything to nullptr except what was passed in
  nil = new Node("", 0);
  root = D.root;
  current = root;
  num_pairs = 0;

  // then copy over the other dictionary
  inOrderCopy(D.root, nil);
  // preOrderCopy(D.root, nil);
}

Dictionary::~Dictionary() {
	if (nil != nullptr){
  	clear();
  	delete (nil);
		nil = nullptr;
	}
}

// Access functions --------------------------------------------------------

// simple function to return the size, or num of pairs
int Dictionary::size() const { return num_pairs; }

bool Dictionary::contains(keyType k) const {
  // if the root is null or there are no pairs...
  if (root == nullptr || num_pairs == 0) {
    // it cannot contain k
    return false;
  }

  // otherwise grab the root...
  Node *N = root;
  // while our grabbed key doesnt equal passed key and N is not nullptr...
  while (N->key != k && N != nullptr) {
    // check where we need to go (left or right)...
    if (N->key > k) {
      // if we reach a leaf it does not contain!
      if (N->left == nullptr) {
        return false;
      }
      N = N->left;
    } else if (N->key < k) {
      // if we reach a leaf it does not contain!
      if (N->right == nullptr) {
        return false;
      }
      N = N->right;
    }
  }
  // if what we found is equal to k... it contains k
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
    while (N->key != k && N != nullptr) {
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

// Helper Functions (Optional) ---------------------------------------------

void Dictionary::inOrderString(std::string &s, Node *R) const {
  // does an inorder traversal to grab the keys and values, the stores them in
  // s.
  if (R != nullptr) {
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
  // does an preorder traversal to grab the keys, the stores them in s.
  if (R != nullptr) {
    s += (R->key);
    s += "\n";
    //if (R->left != nullptr) {
    preOrderString(s, R->left);
    //}
    //if (R->right != nullptr) {
    preOrderString(s, R->right);
    //}
  }
  return;
}

void Dictionary::preOrderCopy(Node *R, Node *N) {
  // does an preorder traversal to copy a Dict. by calling set value.
  if (R != nullptr) {
    if (R->key != N->key && R->val != N->val) {
      setValue(R->key, R->val);
      preOrderCopy(R->left, N);
      preOrderCopy(R->right, N);
    }
  }
  return;
}

void Dictionary::inOrderCopy(Node *R, Node *N) {
  // does an inorder traversal to copy a Dict. by calling set value.
  if (R != nullptr) {
    if (R->key != N->key && R->val != N->val) {
      inOrderCopy(R->left, N);
      setValue(R->key, R->val);
      inOrderCopy(R->right, N);
    }
  }
}

void Dictionary::postOrderDelete(Node *R) {

  // does a postorder traversal, deleting along the way...
  if (R == nullptr || R == nil) {
    return;
  }
	//std::cout << "TEST: " << R->key << std::endl;
  postOrderDelete(R->left);
  postOrderDelete(R->right);
  num_pairs--;

  //std::cout << "TEST: " << R->key << std::endl;
  delete (R);
}

Dictionary::Node *Dictionary::search(Node *R, keyType k) const {
  // while passed in key and k are not the same and R is not null...
  while (R->key != k && R != nullptr) {
    // decide where to go in the tree (left / right)...
    if (R->key > k) {
      R = R->left;
    } else if (R->key < k) {
      R = R->right;
    }
  }
  // once we end up at the position, return the key if it matches.
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
  while (R->left != nullptr) {
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
  while (R->right != nullptr) {
    R = R->right;
  }
  // and return right most node
  return R;
}

Dictionary::Node *Dictionary::findNext(Node *N) {
  // call find min on the right if it's not null...
  if (N->right != nullptr) {
    return findMin(N->right);
  }

  // otherwise grab N's parent
  Node *y = N->parent;
  // and while it's not null and it's right isnt null
  while (y != nullptr && N == y->right) {
    // inchworm the tree
    N = y;
    y = y->parent;
  }
  // and return y node
  return y;
}

Dictionary::Node *Dictionary::findPrev(Node *N) {
  // same concept as above, but with LEFT instead of right.
  if (N->left != nullptr) {
    return findMax(N->left);
  }
  Node *y = N->parent;
  while (y != nullptr && N == y->left) {
    N = y;
    y = y->parent;
  }
  return y;
}

// Manipulation procedures -------------------------------------------------

void Dictionary::clear() {
  // simple clear func.
	if (num_pairs == 0){
		return;
	}
  postOrderDelete(root);
	root = nil;
	current = nullptr;
  return;
}

void Dictionary::setValue(keyType k, valType v) {
  // create a node to be inserted
  Node *inserting = new Node(k, v);

  // if the root is null (empty dict)...
  if (root == nullptr) {
    // just insert the node at the root and return
    inserting->parent = root;
    root = inserting;
    num_pairs++;
    return;
  } else {
    // otherwise start at the root...
    Node *find = root;
    // and while find isnt null...
    while (find != nullptr) {
      // decide where to go... (left or right)
      if (find->key >= k) {
        // if you find a matching key...
        if (find->key == k) {
          // reset the values there and return
          inserting->parent = find;
          find->val = inserting->val;
          return;
        }
        // if find's left is null, we have to insert
        if (find->left == nullptr) {
          inserting->parent = find;
          find->left = inserting;
          num_pairs++;
          return;
        } else {
          find = find->left;
        }
      } else {
        // if finds right is null, we have to insert
        if (find->right == nullptr) {
          inserting->parent = find;
          find->right = inserting;
          num_pairs++;
          return;
        } else {
          find = find->right;
        }
      }
    }
  }
}

void Dictionary::remove(keyType k) {
  // if the root is the key...
  if (root->key == k) {
    // also if current is at the root...
    if (current == root) {
      // current gets reset
      current = nullptr;
    }
    // free the root and return;
    free(root);
    num_pairs -= 1;
    return;
  }

  // create a current and previous node
  Node *curr = root;
  Node *prev = nullptr;

  // while the current is not null and the k isnt the one passed in...
  while (curr != nullptr && curr->key != k) {
    // inchworm the tree...
    prev = curr;
    // decide which way to go
    if (k < curr->key) {
      curr = curr->left;
    } else {
      curr = curr->right;
    }
  }
  // if we run into a nullptr, just return, nothing to remove
  if (curr == nullptr) {
    // num_pairs--;
    return;
  }

  // otherwise of currents left or right is null
  if (curr->left == nullptr || curr->right == nullptr) {
    // create a new current
    Node *newCurr = nullptr;

    // and use it to traverse the opposite way
    if (curr->left == nullptr) {
      newCurr = curr->right;
    } else {
      newCurr = curr->left;
    }

    // if prev becomes null, just return out
    if (prev == nullptr) {
      return;
    }

    // if current is equal to previous' left, make that the new curr, otherwise
    // the right is the new curr
    if (curr == prev->left) {
      prev->left = newCurr;
    } else {
      prev->right = newCurr;
    }

    // if the current is not null
    if (current != nullptr) {
      // and if it matches the iterator...
      if (curr->val == current->val && curr->key == current->key) {
        // reset the iterator before freeing
        current = nullptr;
      }
    }
    // free current and decrement size...
    free(curr);
    num_pairs -= 1;
    return;

  } else {
    // otherwise create nodes p and temp...
    Node *p = nullptr;
    Node *temp;

    // temp is equal to curr's right and while temp left is not null...
    temp = curr->right;
    while (temp->left != NULL) {
      // inchworm left
      p = temp;
      temp = temp->left;
    }

    // if p isnt null, then p's left becomes temps right
    if (p != nullptr) {
      p->left = temp->right;
    } else {
      // otherwise currents right becomes temps right
      curr->right = temp->right;
    }
    // current key is = temp key and val = temp val...
    curr->key = temp->key;
    curr->val = temp->val;

    // check if the iterator needs to be fixed
    if (current != nullptr) {
      if (temp->val == current->val && temp->key == current->key) {
        current = nullptr;
      }
    }
    // and free temp!
    num_pairs -= 1;
    free(temp);
    return;
  }
  return;
}

void Dictionary::begin() {
  // if not empty...
  if (root == nullptr) {
    current = nullptr;
  }

  // the min is the beginning
  current = findMin(root);
  // std::cout << "Begin: " << current->val << " / " << current->key <<
  // std::endl;
}

void Dictionary::end() {
  // if not empty
  if (root == nullptr) {
    current = nullptr;
  }

  // the max is the end
  current = findMax(root);
  // std::cout << "End: " << current->val << " / " << current->key << std::endl;
}

void Dictionary::next() {
  // if you are at the end, dont go further, remove iterator
  if (current == findMax(root) || current == nullptr) {
    current = nullptr;
    return;
  }
  // otherwise call find next on current iterator
  current = findNext(current);
  // std::cout << "Next: " << current->val << " / " << current->key <<
  // std::endl;
}

void Dictionary::prev() {
  // if you are at the beginning, dont go any further back, remove iterator
  if (current == findMin(root) || current == nullptr) {
    current = nullptr;
    return;
  }

  // otherwise find prev
  current = findPrev(current);
  // std::cout << "Prev: " << current->val << " / " << current->key <<
  // std::endl;
}

// Other Functions ---------------------------------------------------------

std::string Dictionary::to_string() const {
  std::string s = "";

  // create a string and if the dict is empty, return nothing
  if (root == nullptr) {
    return s;
  }

  // otherwise start at the root
  Dictionary::Node *curr = root;
  while (curr != nullptr) {
    // and add pieces of the dict to s
    if (curr->left == nullptr) {
      s += curr->key;
      s += " : ";
      s += std::to_string(curr->val);
      s += "\n";
      curr = curr->right;
    } else {

      // otherwise make a Node previous = to curr's left
      Dictionary::Node *pre = curr->left;
      // and while pre's right isnt null or equal to curr...
      while (pre->right != nullptr && pre->right != curr) {
        // keep moving it right
        pre = pre->right;
      }

      // then, if pre's right is nullptr
      if (pre->right == nullptr) {
        // set pre's right to curr and curr to curr's left
        pre->right = curr;
        curr = curr->left;
      }

      // otherwise add curr's piece to string s
      else {
        pre->right = nullptr;
        s += curr->key;
        s += " : ";
        s += std::to_string(curr->val);
        s += "\n";
        curr = curr->right;
      }
    }
  }
  // return the created string
  return s;
}

std::string Dictionary::pre_string() const {
  // use helper func. preOrderString!
  std::string s = "";
  preOrderString(s, root);
  return s;
}

bool Dictionary::equals(const Dictionary &D) const {
  // if both are empty, they are equal...
  if (this->root == nullptr && D.root == nullptr) {
    return true;
    // both empty
    // if only one is empty, they are not equal...
  } else if (this->root == nullptr || D.root == nullptr) {
    return false;
    // one is empty
  } else {


    // create inorder traversal strings for both and compare them...
    std::string A = "";
    std::string B = "";


		//PRE ORDER INSTEAD OF IN ORDER
    this->preOrderString(A, this->root);
    D.preOrderString(B, D.root);

		cout << "A: " << A << endl;
		cout << "B: " << B << endl;

    // if they are the same, D and this are equal!
    if (A == B) {
      return true;
    }
    return false;
  }
}

// Overloaded Operators ----------------------------------------------------

std::ostream &operator<<(std::ostream &stream, Dictionary &D) {
  // create a copy of passed in dictionary
  Dictionary cD = D;
  // if its empty... return nothin.
  if (cD.root == nullptr) {
    return stream;
  }

  // otherwise grab the root...
  Dictionary::Node *curr = cD.root;
  while (curr != nullptr) {
    if (curr->left == nullptr) {
      // once we reach a leaf, stream the key and val
      stream << curr->key << " : " << curr->val << std::endl;
      curr = curr->right;
    } else {
      // otherwise make a pre and set it to curr->left
      Dictionary::Node *pre = curr->left;
      // keep walking right...
      while (pre->right != nullptr && pre->right != curr) {
        pre = pre->right;
      }

      // if pres right is null...
      if (pre->right == nullptr) {
        // set it to curr and set curr to currs left (similar syntax)
        pre->right = curr;
        curr = curr->left;
      }

      // otherwise../
      else {
        // set pore right to null and stream out the current key and value
        pre->right = nullptr;
        stream << curr->key << " : " << curr->val << std::endl;
        // stream << curr->val << " : " << curr->key << std::endl;
        curr = curr->right;
      }
    }
  }
  // return the stream!
  return stream;
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
