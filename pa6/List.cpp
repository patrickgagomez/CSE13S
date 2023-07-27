/*********************************************************************************
 * Patrick Gomez, pggomez
 * 2022 Spring CSE101 PA#5
 * List.cpp
 *	The '.cpp' file for all of the List functions.
 *********************************************************************************/

#include "List.h"
#include <stdio.h>
#include <stdlib.h>

// define DUMMY variable
#define DUMMY -5

using namespace std;

// Class Constructors & Destructors ----------------------------------------
List::Node::Node(ListElement x) {
  data = x;
  next = nullptr;
  prev = nullptr;
}

// Constructor
List::List() {
  // create front and back dummy
  frontDummy = new Node(DUMMY);
  backDummy = new Node(DUMMY);
  // set the cursors to the dummies
  beforeCursor = frontDummy;
  afterCursor = backDummy;

  // link the front/back
  frontDummy->next = backDummy;
  backDummy->prev = frontDummy;

  // set cursor and num elements to base 0
  pos_cursor = 0;
  num_elements = 0;
}

// Copy Constructor
List::List(const List &L) {
  // Do the same setup as regular constructor
  frontDummy = new Node(DUMMY);
  backDummy = new Node(DUMMY);
  beforeCursor = frontDummy;
  afterCursor = backDummy;

  frontDummy->next = backDummy;
  backDummy->prev = frontDummy;

  pos_cursor = 0;
  num_elements = 0;

  // Load the passed in List's elements into the new
  // list using a while loop until you hit the back!
  Node *N = (L.backDummy)->prev;

  while (N->data != DUMMY) {
    insertAfter(N->data);
    N = N->prev;
  }
}

List::~List() {
  // clear the list...
  clear();
  // delete the dummies
  delete (frontDummy);
  delete (backDummy);

  // ez!
}

// Access functions --------------------------------------------------------

// THESE FUNCTIONS ALL JUST RETURN CERTAIN
// PIECES OF REQUESTED DATA.
int List::length() const { return num_elements; }

ListElement List::front() const { return frontDummy->next->data; }

ListElement List::back() const { return backDummy->prev->data; }

int List::position() const { return pos_cursor; }

ListElement List::peekNext() const { return afterCursor->data; }

ListElement List::peekPrev() const { return beforeCursor->data; }

// Manipulation procedures -------------------------------------------------

void List::clear() {

  // move to the front of the list
  moveFront();

  // until you hit the end... keep erasing
  while (afterCursor->data != DUMMY) {
    eraseAfter();
  }

  // set the elements and cursor back to 0!
  num_elements = 0;
  pos_cursor = 0;
  return;
}

void List::moveFront() {
  // check the length first... then set the cursor in the right spot!
  // dont forget to set the pos_cursor to zero as well
  if (length() >= 1) {
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
    pos_cursor = 0;
  }
  return;
}

void List::moveBack() {
  // same principle as moveFront(), but with the back!
  if (length() >= 1) {
    beforeCursor = backDummy->prev;
    afterCursor = backDummy;
    pos_cursor = num_elements;
  }
  return;
}

ListElement List::moveNext() {
  // create a base case for returning the passed over variable (save)
  ListElement save = -1;

  // check the length/position for validity...
  if (length() >= 1 && (position() < length())) {
    // grab the next element, then hop over it and
    // fix your cursor pointers/positon!
    save = afterCursor->data;
    afterCursor = afterCursor->next;
    beforeCursor = beforeCursor->next;
    pos_cursor += 1;
  }
  // return the variable you hopped over
  return save;
}

ListElement List::movePrev() {
  // same logic as moveNext!!! (but backwards haha)
  ListElement save = -1;
  if (length() >= 1 && position() > 0) {
    save = beforeCursor->data;
    beforeCursor = beforeCursor->prev;
    afterCursor = afterCursor->prev;
    pos_cursor -= 1;
  }
  return save;
}

void List::insertAfter(ListElement x) {
  // create the node to be inserted
  Node *N = new Node(x);

  // fix all the links between N and the existing
  // cursor nodes
  N->prev = beforeCursor;
  N->next = afterCursor;
  afterCursor->prev = N;
  afterCursor = N;
  beforeCursor->next = N;

  // increment the size of the list
  num_elements += 1;
  return;
}

void List::insertBefore(ListElement x) {
  // same principle as insertAfter, however.... vvv
  Node *N = new Node(x);

  N->prev = beforeCursor;
  N->next = afterCursor;
  afterCursor->prev = N;
  beforeCursor->next = N;
  beforeCursor = N;

  num_elements += 1;
  //  vvv    we update the position of the cursor here instead!
  pos_cursor += 1;
}

void List::setAfter(ListElement x) {
  // simply check the position is valid, then set the
  // after cursor to the passed in data
  if (position() < length()) {
    afterCursor->data = x;
  }
  return;
}

void List::setBefore(ListElement x) {
  // simply check the position is valid, then set the
  // before cursor to the passed in data
  if (position() > 0) {
    beforeCursor->data = x;
  }
  return;
}

void List::eraseAfter() {
  // check that the position is valid...
  if (position() > length()) {
    fprintf(stderr, "Erase after error: position < length!\n");
    exit(EXIT_FAILURE);
  }

  // check some base cases that you dont want to erase in
  if (length() == 0 || afterCursor == backDummy) {
    return;
  }

  // if we pass all that...
  // we fix the links to prepare for deletion
  afterCursor->next->prev = beforeCursor;
  beforeCursor->next = afterCursor->next;

  // then delete the after cursor and replace it
  delete (afterCursor);
  afterCursor = beforeCursor->next;

  // and fix the size of the list
  num_elements -= 1;
  return;
}

void List::eraseBefore() {
  // same principle as eraseAfter, except backwards
  if (position() < 0) {
    fprintf(stderr, "Erase before error: Position < 0!\n");
    exit(EXIT_FAILURE);
  }

  if (length() == 0 || beforeCursor == frontDummy) {
    return;
  }

  beforeCursor->prev->next = afterCursor;
  afterCursor->prev = beforeCursor->prev;

  delete (beforeCursor);
  beforeCursor = afterCursor->prev;

  num_elements -= 1;
  // we also change the cursor here! (as opposed to eraseAfter)
  pos_cursor -= 1;
  return;
}

// Other Functions ---------------------------------------------------------

int List::findNext(ListElement x) {
  // grab the check value to see if we found it...
  int check = moveNext();

  // check if we found it in the first hop...
  if (check == x) {
    return position();
  }

  // otherweise keep hopping until we find it
  while (position() < length()) {
    if (check == x) {
      return position();
    }
    check = moveNext();
  }
  // if we don't find it, just return -1!
  return -1;
}

int List::findPrev(ListElement x) {
  // same principle as findNext() here, but backwards
  int check = movePrev();
  if (check == x) {
    return position();
  }

  while (position() > 0) {
    if (check == x) {
      return position();
    }
    check = movePrev();
  }
  return -1;
}

void List::cleanup() {
  // move to the front of the list
  int moveOg = position();
  moveFront();

  // grab the original and match nodes
  Node *original = afterCursor;
  Node *match;

  for (int i = 0; i < moveOg; i++) {
    moveNext();
  }

  // set up ints for counters (position work)
  int outer = 0;
  int inner;

  // while the data in og is not at the dummy...
  while (original->data != DUMMY) {
    // set the match and inner counter here
    match = original->next;
    inner = outer + 1;
    // while the match isnt at the end...
    while (match->data != DUMMY) {
      // check if it equals the original, AC, and BC.
      Node *next = match->next;

      if (match->data == original->data) {
        if (match == beforeCursor) {
          // clean this up later (loops)
          eraseBefore();
          match = next;
          inner++;
          continue;
        }
        if (match == afterCursor) {
          eraseAfter();
          match = next;
          inner++;
          continue;
        }

        // then adjust the cursor
        if (inner < position()) {
          inner--;
          pos_cursor--;
        }

        // here we prepare to delete
        match->prev->next = match->next;
        match->next->prev = match->prev;
        // then delete and fix the length!
        delete (match);
        num_elements--;
      }
      // set match to the next value we grabbed earlier and
      // increment the inner loop counter
      match = next;
      inner++;
    }
    // this line increments the outer loop and
    // moves us to the next number to clean up
    // from the list
    original = original->next;
    outer++;
  }
  return;
}

List List::concat(const List &L) const {
  // create a new list and make sure youre at the front!
  List newL;
  newL.moveFront();

  // grab the back dummy of both "passed" in lists...
  Node *A = this->backDummy->prev;
  Node *B = L.backDummy->prev;

  // and while they arent equal to the dummy var...
  // insert them into the new list!
  while (B->data != DUMMY) {
    newL.insertAfter(B->data);
    B = B->prev;
  }

  // while they arent equal to the dummy var...
  // insert them into the new list!
  while (A->data != DUMMY) {
    newL.insertAfter(A->data);
    A = A->prev;
  }

  // return the new list that was created from both passed lists
  return newL;
}

//!!!COPIED SYNTAX FROM QUEUE.CPP EXAMPLE!!!
std::string List::to_string() const {
  Node *N = nullptr;
  std::string s = "";

  for (N = frontDummy->next; N->data != DUMMY; N = N->next) {
    s += std::to_string(N->data) + " ";
  }

  return s;
}

//!!!COPIED SYNTAX FROM QUEUE.CPP EXAMPLE!!!
bool List::equals(const List &L) const {
  bool eq = false;
  Node *N = nullptr;
  Node *M = nullptr;

  List TEST = L;
  eq = (this->length() == L.length());
  N = this->frontDummy->next;
  M = L.frontDummy->next;
  while (eq && N->data != -5) {
    eq = (N->data == M->data);
    N = N->next;
    M = M->next;
  }
  return eq;
}

// Overriden Operators -----------------------------------------------------

std::ostream &operator<<(std::ostream &stream, const List &L) {
  List cL = L;
  cL.moveFront();
  while (cL.peekNext() != DUMMY) {
    stream << cL.peekNext() << " ";
    cL.moveNext();
  }
  stream << std::endl;

  return stream; // << L.List::to_string();
}

bool operator==(const List &A, const List &B) { return A.List::equals(B); }

List &List::operator=(const List &L) {
  if (this != &L) { // not self assignment
    // make a copy of L
    List temp = L;

    // then swap the copy's fields with fields of this
    // (prof talked about how to swap here in lecture!)
    std::swap(frontDummy, temp.frontDummy);
    std::swap(backDummy, temp.backDummy);
    std::swap(beforeCursor, temp.beforeCursor);
    std::swap(afterCursor, temp.afterCursor);
    std::swap(pos_cursor, temp.pos_cursor);
    std::swap(num_elements, temp.num_elements);
  }

  // return this with the new data installed
  return *this;

  // the copy, if there is one, is deleted upon return
}
