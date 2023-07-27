/*********************************************************************************
 * Patrick Gomez, pggomez
 * 2022 Spring CSE101 PA#5
 * ListTest.cpp
 *  The tester '.cpp' file for all of the List functions.
 *********************************************************************************/

#include "List.h"
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

List runTest(List *pA);

int main() {
  List L;
  for (int i = 0; i < 9; i++) {
    L.insertBefore(i);
  }
  cout << L << endl;

  List A, B, sD;

  L.moveFront();
  for (int i = 0; i < (L.length() / 2); i++) {
    A.insertBefore(L.peekNext());
    L.moveNext();
  }
  for (int j = 0; j < ((L.length() / 2) + 1); j++) {
    B.insertBefore(L.peekNext());
    L.moveNext();
  }

  cout << A << endl << B << endl;

  A.moveFront();
  B.moveFront();
  for (int k = 0; k < A.length(); k++) {
    sD.insertBefore(B.peekNext());
    sD.insertBefore(A.peekNext());
    A.moveNext();
    B.moveNext();
  }
  cout << endl << sD << endl;

  List C, D;

  for (int i = 1; i <= 10; i++) {
    C.insertAfter(i);
  }

  for (int i = 1; i <= 5; i++) {
    D.insertAfter(i);
  }

  cout << "C = " << C << endl;
  cout << endl;
  cout << "length" << C.length() << endl;
  cout << "front" << C.front() << endl;
  cout << "back" << C.back() << endl;
  cout << "D = " << D << endl;

  C.moveFront();
  for (int j = 0; j < 10; j++) {
    cout << "peeknext: " << C.peekNext() << endl;
    cout << "C.position() = " << C.position() << endl;
    C.moveNext();
  }
  cout << endl;

  C.moveFront();
  for (int j = 0; j < 4; j++) {
    C.moveNext();
  }

  C.setBefore(11);
  C.setAfter(13);
  cout << "C = " << C << endl;
  cout << "D = " << D << endl;

  List E, F, G, H;
  E.insertBefore(1);
  E.insertAfter(3);
  E.insertAfter(2);
  F.insertBefore(3);
  F.insertBefore(2);
  F.insertBefore(1);
  G.insertAfter(1);
  G.insertAfter(2);
  G.insertAfter(3);
  G.insertAfter(3);
  G.insertAfter(2);
  G.insertAfter(1);
  H = E.concat(F);
  cout << "E = " << E << endl;
  cout << "F = " << F << endl;
  cout << "E + F = " << H << endl;
  cout << "G = " << G << endl;

  if (!G.equals(E.concat(F))) {
    printf("nah\n");
  }
  printf("yea!\n");

  List J;
  J.insertAfter(1);
  J.insertAfter(1);
  J.insertAfter(2);
  J.insertAfter(1);
  J.insertAfter(3);
  J.insertAfter(4);
  J.insertAfter(2);
  J.insertAfter(2);
  J.insertAfter(8);
  J.moveNext();
  J.moveNext();

  cout << "J (noclean) = " << J << endl;
  cout << "pos = " << J.position() << endl;
  cout << "peeknext: " << J.peekNext() << endl;
  cout << "peekprev: " << J.peekPrev() << endl;
  J.cleanup();
  cout << "J (cleaned) = " << J << endl;
  cout << "pos = " << J.position() << endl;
  cout << "peeknext: " << J.peekNext() << endl;
  cout << "peekprev: " << J.peekPrev() << endl;

  return (EXIT_SUCCESS);
}

/*

List J;
  J.insertAfter(1);
  J.insertAfter(1);
  J.insertAfter(2);
  J.insertAfter(1);
  J.insertAfter(3);
  J.insertAfter(4);
  J.insertAfter(2);
  J.insertAfter(2);
  J.insertAfter(8);
  J.moveNext();
  J.moveNext();

  cout << "J (noclean) = " << J << endl;
  cout << "pos = " << J.position() << endl;
  cout << "peeknext: " << J.peekNext() << endl;
  cout << "peekprev: " << J.peekPrev() << endl;
  J.cleanup();
  cout << "J (cleaned) = " << J << endl;
  cout << "pos = " << J.position() << endl;
  cout << "peeknext: " << J.peekNext() << endl;
  cout << "peekprev: " << J.peekPrev() << endl;



int i, n = 10;
List A;

for (i = 1; i <= n; i++) {
A.insertAfter(i);
}

cout << "A = " << A << endl;
List B = runTest(&A);
cout << "B = " << B << endl;
List C = List(A);
cout << "C = " << C << endl;
A.clear();
cout << "A = " << A << endl;

List D;

D.insertBefore(1);
D.insertBefore(2);
D.insertBefore(3);
D.insertBefore(5);
D.insertBefore(12);
cout << "D = " << D << endl;

D.movePrev();
cout << "prev: " << D.peekPrev() << endl;
cout << "next: " << D.peekNext() << endl;
D.eraseAfter();
if (D.length() != 4) {
cout << "nah" << endl;
}
cout << "D = " << D << endl;

List E, F, G, H;
E.insertBefore(1);
E.insertAfter(3);
E.insertAfter(2);
F.insertBefore(3);
F.insertBefore(2);
F.insertBefore(1);
G.insertAfter(1);
G.insertAfter(2);
G.insertAfter(3);
G.insertAfter(3);
G.insertAfter(2);
G.insertAfter(1);
H = E.concat(F);
cout << "E = " << E << endl;
cout << "F = " << F << endl;
cout << "E + F = " << H << endl;
cout << "G = " << G << endl;

if (!G.equals(E.concat(F))) {
printf("nah\n");
}
printf("yea!\n");

List J;
J.insertAfter(1);
J.insertAfter(1);
J.insertAfter(2);
J.insertAfter(1);
J.insertAfter(3);
J.insertAfter(4);
J.insertAfter(2);
J.insertAfter(2);
J.insertAfter(8);

cout << "J (noclean) = " << J << endl;
J.cleanup();
cout << "J (cleaned) = " << J << endl;
*/
/*
int i, n = 10;
List A, B;

for (i = 1; i <= n; i++) {
A.insertAfter(i);
}

for (i = 1; i <= 5; i++) {
B.insertAfter(i);
}

cout << "A = " << A << endl;
cout << endl;
cout << A.length() << endl;
cout << A.front() << endl;
cout << A.back() << endl;
cout << "A = " << A << endl;

A.moveFront();
for(int j = 0; j < n; j++){
        cout << "peeknext: " << A.peekNext() << endl;
cout << "A.position() = " << A.position() << endl;
        A.moveNext();
}
cout << endl;

A.moveFront();
for(int j = 0; j < 4; j++){
        A.moveNext();
}

A.setBefore(11);
A.setAfter(13);
cout << "A = " << A << endl;
cout << "B = " << B << endl;


List C = A.concat(B);
cout << "C = " << C << endl;
}
*/

List runTest(List *pA) {
  List A = *pA;
  return A;
}
