/*********************************************************************************
 * Patrick Gomez, pggomez
 * 2022 Spring CSE101 PA#5
 * Shuffle.cpp
 *  The '.cpp' file for all of the client shuffle program.
 *********************************************************************************/

#include "List.h"
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

void shuffle(List &D);

int main(int argc, char *argv[]) {
  // check that we got the right values!
  if (argc != 2) {
    fprintf(stderr, "Program Error: No card value given in program request.\n");
    exit(EXIT_FAILURE);
  }

  // cast the argument gathered to an int with checking!
  // citation: stackoverflow question of how to cast argv arguement to an int!
  std::istringstream ss(argv[1]);
  int userNum;
  if (!(ss >> userNum)) {
    std::cerr << "Invalid number: " << argv[1] << '\n';
  }

  // create a new list
  List L;

  // print out the first message of the program
  cout << "deck size       shuffle count" << endl
       << "------------------------------" << endl;

  // nested for loop to...
  for (int i = 1; i <= userNum; i++) {
    // fill the loop...
    for (int j = 0; j < i; j++) {
      L.insertBefore(j);
    }
    // then shuffle it, print it, and clear it!
    shuffle(L);
    L.clear();
    // and then do it all again +1
  }
  return 0;
}

void shuffle(List &D) {
  // keep track of the shuffle count and the size of
  // the list of the length passed in.
  int shuffleCount = 0;
  int shuffleSize = D.length();

  // boolean for if the list passed in is even
  bool even = false;

  // vvv   by default it is false, unless stated otherwise here
  if (shuffleSize % 2 == 0) {
    even = true;
  }

  // some small base cases to get out of the way when shuffling
  if (shuffleSize == 1) {
    cout << " 1               1" << endl;
    return;
  } else if (shuffleSize == 2) {
    cout << " 2               2" << endl;
    return;
  } else {

    // if it isnt a base case...

    // we make the lists that will be used to shuffle
    List A, B, sD;
    // this one hold the original list for comparison
    List og = D;

    do {
      // move to the front of the list passed in...
      D.moveFront();
      // insert half of it into list A
      for (int i = 0; i < (D.length() / 2); i++) {
        A.insertBefore(D.peekNext());
        D.moveNext();
      }

      // here:
      // if the list isnt even, we put 1/2 of the list PLUS ONE
      // into List B
      // otherwise if it IS even, we only put 1/2 into B
      if (!even) {
        for (int j = 0; j < ((D.length() / 2) + 1); j++) {
          B.insertBefore(D.peekNext());
          D.moveNext();
        }
      } else if (even) {
        for (int j = 0; j < (D.length() / 2); j++) {
          B.insertBefore(D.peekNext());
          D.moveNext();
        }
      }

      // move to the front of A and B...
      A.moveFront();
      B.moveFront();

      // and insert them in alternating order into sD (Shuffled Deck)!
      for (int k = 0; k < A.length(); k++) {
        sD.insertBefore(B.peekNext());
        sD.insertBefore(A.peekNext());
        A.moveNext();
        B.moveNext();
      }

      // if the List wasn't even, B will have one more element than A, so we
      // need to spit that out into sD here!
      if (!even) {
        sD.insertBefore(B.peekNext());
      }

      // increment the shuffle counter!
      shuffleCount++;

      // fix the lists and clear the ones that are going to be reused.
      D = sD;
      sD.clear();
      A.clear();
      B.clear();

      // and we do this while the shuffled
      // list does not equal the Original!
    } while (D.equals(og) == false);

    // once we are done, we print out the stats of the shuffle!

    // NOTE: std::setw and std::left were found when Googling "how to format
    // cout numbers" !! It might be a wacky way of doing it, but this is how I
    // did it!
    cout << " " << std::left << std::setw(5) << shuffleSize;
    cout << std::left << "           " << shuffleCount << endl;
  }
  return;
}
