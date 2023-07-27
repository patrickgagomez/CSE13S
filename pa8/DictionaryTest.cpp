/*******************************************************************************
 * Patrick Gomez
 * pggomez 2022 Spring CSE101 PA#8 DictionaryTestcpp
 * The '.cpp' file for the Dictionary Testing File.
 *********************************************************************************/
#include "Dictionary.h"
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

int main() {

  Dictionary A;

  A.setValue("c", 3);
  A.setValue("a", 1);
  A.setValue("b", 2);

  A.remove("a");
  if (A.size() != 2) {
    cout << 1 << endl;
    return 1;
  }
  A.setValue("e", 5);
  A.remove("c");
  if (A.size() != 2) {
    cout << 2 << endl;
    return 2;
  }
  cout << "passed first testing!" << endl;
  A.clear();

  A.setValue("d", 1);
  A.setValue("b", 5);
  A.setValue("a", 10);
  A.setValue("c", 15);
  A.setValue("f", 20);
  A.setValue("e", 25);
  A.setValue("g", 30);
  A.begin();

  cout << "Curr key: " << A.currentKey() << endl;
  cout << "A: " << endl << A << endl;
  A.remove("a");
  cout << "A: " << endl << A << endl;

  if (A.hasCurrent()) {
    cout << "fail 1" << endl;
    return 1;
  }
  A.end();
  A.remove("d");
  cout << "A: " << endl << A << endl;
  if (A.currentKey() != "g" || A.currentVal() != 30) {
    cout << "fail 2" << endl;
    return 2;
  }
  A.remove("g");
  if (A.hasCurrent()) {
    cout << "fail 3" << endl;
    return 3;
  }
  cout << "passed second test!" << endl;
  A.clear();

  string S[] = {"one", "two", "foo", "bar", "happy", "is", "three", "par"};

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

  return 0;
}
