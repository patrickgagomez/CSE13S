#include "Dictionary.h"
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

int main() {

  string S[] = {"one", "two", "foo", "bar", "happy", "is", "three", "par"};
  Dictionary A;

  for (int i = 0; i < 8; i++) {
    A.setValue(S[i], i + 1);
  }

  cout << "A.size() = " << A.size() << endl << A << endl;

  A.setValue("one", 3);

  cout << "A.size() = " << A.size() << endl << A << endl;

  string sA = A.to_string();
  cout << "STRING: " << endl << sA << endl;

  A.begin();
  for (int i = 0; i < 10; i++) {
    A.next();
  }

  cout << endl << "going backwards!" << endl;

  A.end();
  A.prev();
  A.prev();
  A.prev();

  cout << endl;

  Dictionary copy = Dictionary(A);
  cout << "copy: " << endl << copy << endl;

  bool checkEQ = A.equals(copy);
  if (checkEQ) {
    cout << "they are equal!" << endl;
  } else if (!checkEQ) {
    cout << "not equal bruddah..." << endl;
  }

  Dictionary noEQ;

  for (int i = 0; i < 6; i++) {
    noEQ.setValue(S[i], i + 2);
  }

  bool defNEQ = A.equals(noEQ);
  if (defNEQ) {
    cout << "they are equal!" << endl;
  } else if (!defNEQ) {
    cout << "not equal bruddah..." << endl;
  }

  A.clear();
  cout << "A.size() = " << A.size() << endl << A << endl;
}
