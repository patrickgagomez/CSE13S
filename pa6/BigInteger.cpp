/*********************************************************************************
 * Patrick Gomez, pggomez
 * 2022 Spring CSE101 PA#6
 * BigInteger.cpp
 *	The '.cpp' file for BigInteger.
 *********************************************************************************/

#include "BigInteger.h"
#include "List.h"
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

void negateList(List &L);
void sumList(List &S, List A, List B, int sgn);
int normalizeList(List &L);
void shiftList(List &L, int p);
void scalarMultList(List &L, ListElement m);

// make sure to change these for final submission!
long base = 1000000000;
int power = 9;

// Class Constructors & Destructors ----------------------------------------

// Constructor that creates a new BigInteger in the zero state:
// signum=0, digits=().
BigInteger::BigInteger() { signum = 0; }

// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s) {
  signum = 0;

  digits.clear();

  if (s.length() == 0) {
    std::cerr << "Big Integer: Constructor: non-numeric string" << endl;
    return;
  }

  int start = 0;
  if (s[0] == '-') {
    signum = -1;
    start = 1;
  } else if (s[0] == '+') {
    signum = 1;
    start = 1;
  } else {
    signum = 1;
  }

  // CITATION:
  // https://stackoverflow.com/questions/25726531/how-to-remove-leading-zeros-from-string-using-c#:~:text=this%20in%2C%20use%3A-,str.,size()-1))%3B
  s.erase(start, min(s.find_first_not_of('0'), s.size() - 1));

  int len = (s.length() - start);
  int remaining = len % power;
  if (remaining == 0) {
    remaining = power;
  }

  std::string::size_type sz;

  string buff = "";

  for (int i = start; i < len;) {
    for (int j = 0; j < remaining; j++) {
      buff += s[i];
      i++;
    }
    remaining = power;
    long insert = stol(buff, &sz);
    digits.insertBefore(insert);
    buff = "";
  }
}

// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger &N) {
  signum = N.signum;
  digits = List(N.digits);
}

// Access functions --------------------------------------------------------

// Returns -1, 1 or 0 according to whether this BigInteger is positive,
// negative or 0, respectively.
int BigInteger::sign() const { return signum; }

// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger &N) const {
  if (this->digits.equals(N.digits) == true) {
    return 0;
  }

  if (this->signum == -1) {
    return -1;
  } else if (N.signum == -1) {
    return 1;
  }

  if (this->digits.length() < N.digits.length()) {
    return -1;
  }

  long A = digits.front();
  long B = N.digits.front();

  if (A < B) {
    return -1;
  } else if (A > B) {
    return 1;
  } else if (A == B) {
    return 0;
  }

  List lA = digits;
  List lB = N.digits;

  lA.moveFront();
  lB.moveFront();

  while (lA.peekNext() != -5) {
    long A = lA.peekNext();
    long B = lB.peekNext();
    if (A != B) {
      return 1;
    }
  }

  return 1;
}

// Manipulation procedures -------------------------------------------------

// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero() {
  signum = 0;
  digits.clear();
}

// If this BigInteger is zero, does nothing, otherwise reverses the sign of
// this BigInteger positive <--> negative.
void BigInteger::negate() {
  if (signum == -1) {
    signum = 1;
  } else if (signum == 1) {
    signum = -1;
  }

  return;
}
// BigInteger Arithmetic operations ----------------------------------------
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger &N) const {
  List sum;

  List A = this->digits;
  List B = N.digits;

  if (this->signum == -1) {
    negateList(A);
  }

  /*
if (N.signum == -1){
negateList(B);
}
  */

  sumList(sum, A, B, N.signum);
  int sign = normalizeList(sum);

  BigInteger BI;
  BI.digits = sum;
  BI.signum = sign;
  return BI;
}

// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger &N) const {
  List diff;

  List A = this->digits;
  List B = N.digits;

  if (this->signum == -1) {
    negateList(A);
  }

  if (N.signum == -1) {
    negateList(B);
  }

  // sumList(diff, this->digits, N.digits, -1);
  sumList(diff, A, B, -1);

  // cout << "sum(diffed): " << diff << endl;
  int sign = normalizeList(diff);
  // cout << "normalized!: " << diff << endl;
  // cout << "sign w/norm: " << sign << endl;

  BigInteger BI;
  BI.digits = diff;
  BI.signum = sign;
  return BI;
}
// Returns a BigInteger representing the product of this and N.
BigInteger BigInteger::mult(const BigInteger &N) const {
  List original = this->digits;
  List nList = N.digits;
  List fin;
  for (int i = 0; i < nList.length(); i++) {
    fin.insertAfter(0);
  }

  int shift = 0;
  int sign = 0;
  nList.moveBack();

  for (int i = 0; i < nList.length(); i++) {
    long multVal = nList.peekPrev();
    List copyOG = original;
    scalarMultList(copyOG, multVal);
    shiftList(copyOG, shift);
    sign = normalizeList(copyOG);

    fin.moveFront();
    fin.insertAfter(0);

    sumList(fin, copyOG, fin, sign);

    copyOG.clear();
    shift++;
    nList.movePrev();
  }

  normalizeList(fin);
  fin.moveFront();
  while (fin.peekNext() == 0) {
    fin.eraseAfter();
  }

  if (this->signum == -1 && N.signum == 1) {
    sign = -1;
  }
  if (N.signum == -1 && this->signum == 1) {
    sign = -1;
  }

  BigInteger multFin;
  multFin.digits = fin;
  multFin.signum = sign;
  return multFin;
}

// Other Functions ---------------------------------------------------------

// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.

std::string BigInteger::to_string() {
  string result;

  if (digits.length() == 0) {
    return "0";
  } else {
    if (signum == -1) {
      result += "-";
    }
    int counter = 0;
    long temp;
    digits.moveFront();
    while (digits.peekNext() != -5) {
      if (counter == 0) {
        temp = digits.peekNext();
        result += std::to_string(temp);
        digits.moveNext();
        counter++;
      } else {
        temp = digits.peekNext() + base;
        result += std::to_string(temp).substr(1);
        digits.moveNext();
        counter++;
      }
    }
    return result;
  }
}

// Helper Functions -------------------------------------------------------

// negateList()
// Changes the sign of each integer in List L. Used by sub().
void negateList(List &L) {

  L.moveFront();
  while (L.peekNext() != -5) {
    long changeData = L.peekNext();
    changeData *= -1;
    L.setAfter(changeData);
    L.moveNext();
  }
  return;
}

// sumList()
// Overwrites the state of S with A + sgn*B (considered as vectors).
// Used by both sum() and sub().
void sumList(List &S, List A, List B, int sgn) {
  if (A.length() > B.length()) {
    List temp = A;
    A = B;
    B = temp;
  }

  B.moveFront();
  while (B.peekNext() != -5) {
    long temp = B.peekNext();
    temp *= sgn;
    B.setAfter(temp);
    B.moveNext();
  }

  S.clear();
  S.moveFront();
  A.moveBack();
  B.moveBack();
  while (A.peekPrev() != -5) {
    long tempSum = (A.peekPrev() + B.peekPrev());
    // cout << A.peekPrev() << " + " << B.peekPrev() << " = " << tempSum <<
    // endl;
    S.insertAfter(tempSum);
    // cout << "inserting " << tempSum << "!" << endl;
    A.movePrev();
    B.movePrev();
  }
  while (B.peekPrev() != -5) {
    S.insertAfter(B.peekPrev());
    // cout << "inserting " << B.peekPrev() << "!" << endl;
    B.movePrev();
  }

  return;
}

// normalizeList()
// Performs carries from right to left (least to most significant
// digits, then returns the sign of the resulting integer. Used
// by add(), sub() and mult().
int normalizeList(List &L) {
  L.moveBack();
  int counter = 0;
  int sign = 1;

  while (L.peekPrev() != -5) {
    long val = L.peekPrev();

    if (val < 0) {
      // if val is NEGATIVE
      if (L.front() < 0) {
        // cant have a negative on the far left
        negateList(L);
        sign = -1;
      }
      val = L.peekPrev();
      // we have to check again i think
      while (val < 0) {
        val += base;
        counter++;
      }
      L.setBefore(val);
      L.movePrev();
      val = L.peekPrev();
      val -= counter;
      L.setBefore(val);
      counter = 0;
      continue;

    } else if (val >= base) {
      // if val is BIGGER than base
      while (val >= base) {
        val -= base;
        counter++;
      }
      L.setBefore(val);
      L.movePrev();
      val = L.peekPrev();
      if (val == -5) {
        L.insertBefore(counter);
      } else if (val != -5) {
        val += counter;
        L.setBefore(val);
      }
      counter = 0;
      continue;
    } else {
      L.movePrev();
      counter = 0;
    }
  }

  L.moveFront();
  int numNZ = 0;
  while (L.peekNext() != -5) {
    if (L.peekNext() != 0) {
      numNZ++;
    }
    L.moveNext();
  }
  if (numNZ == 0) {
    sign = 0;
  }

  return sign;
}

// shiftList()
// Prepends p zero digits to L, multiplying L by base^p. Used by mult().
void shiftList(List &L, int p) {

  L.moveBack();
  int amountofZ = p;
  while (amountofZ != 0) {
    L.insertBefore(00);
    amountofZ--;
  }

  return;
}

// scalarMultList()
// Multiplies L (considered as a vector) by m. Used by mult().
void scalarMultList(List &L, ListElement m) {

  L.moveFront();
  while (L.peekNext() != -5) {
    long val = L.peekNext();
    val *= m;
    L.setAfter(val);
    L.moveNext();
  }
  return;
}

// Overriden Operators -----------------------------------------------------

// Inserts string representation of N into stream.
std::ostream &operator<<(std::ostream &stream, BigInteger N) {
  if (N.signum == -1) {
    stream << "-";
  } else if (N.signum == 1) {
    // stream << "+";
  } else if (N.signum == 0) {
    stream << "0";
    return stream;
  }

  int numOut = 0;
  N.digits.moveFront();
  while (N.digits.peekNext() != -5) {
    if (N.digits.peekNext() == 0) {
      int baseHold = base;
      int counter = 0;
      while (baseHold != 1) {
        baseHold /= 10;
        counter++;
      }
      stream << setw(counter) << setfill('0') << "";
      N.digits.moveNext();
      continue;
    }
    if (N.digits.peekNext() < (base / 10) && numOut == 0) {
      stream << N.digits.peekNext();
      numOut++;
      N.digits.moveNext();
      continue;
    }

    if (N.digits.peekNext() < (base / 10)) {
      int counter = 1;
      int baseHold = base;
      while (N.digits.peekNext() < (baseHold / 10)) {
        baseHold /= 10;
        counter++;
      }
      stream << setw(counter) << setfill('0') << N.digits.peekNext() << "";
    } else {
      stream << N.digits.peekNext() << "";
    }
    N.digits.moveNext();
  }
  // stream << endl;

  return stream;
}

// Returns true if and only if A equals B.
bool operator==(const BigInteger &A, const BigInteger &B) {
  if (A.sign() == -1 && B.sign() != -1) {
    return false;
  }
  if (B.sign() == -1 && A.sign() != -1) {
    return false;
  }
  if (A.compare(B) == 0) {
    return true;
  }
  return false;
}

// Returns true if and only if A is less than B.
bool operator<(const BigInteger &A, const BigInteger &B) {
  if (A.compare(B) == -1) {
    return true;
  }
  return false;
}

// Returns true if and only if A is less than or equal to B.
bool operator<=(const BigInteger &A, const BigInteger &B) {
  if (A.compare(B) == -1 || A.compare(B) == 0) {
    return true;
  }
  return false;
}

// Returns true if and only if A is greater than B.
bool operator>(const BigInteger &A, const BigInteger &B) {
  if (A.compare(B) == 1) {
    return true;
  }
  return false;
}

// Returns true if and only if A is greater than or equal to B.
bool operator>=(const BigInteger &A, const BigInteger &B) {
  if (A.compare(B) == 1 || A.compare(B) == 0) {
    return true;
  }
  return false;
}

// Returns the sum A+B.
BigInteger operator+(const BigInteger &A, const BigInteger &B) {
  BigInteger opSum = A.add(B);
  return opSum;
}

// Overwrites A with the sum A+B.
BigInteger operator+=(BigInteger &A, const BigInteger &B) {
  A = A.add(B);
  return A;
}

// Returns the difference A-B.
BigInteger operator-(const BigInteger &A, const BigInteger &B) {
  BigInteger opDiff = A.sub(B);
  return opDiff;
}

// Overwrites A with the difference A-B.
BigInteger operator-=(BigInteger &A, const BigInteger &B) {
  A = A.sub(B);
  return A;
}

// Returns the product A*B.
BigInteger operator*(const BigInteger &A, const BigInteger &B) {
  BigInteger opMult = A.mult(B);
  return opMult;
}

// Overwrites A with the product A*B.
BigInteger operator*=(BigInteger &A, const BigInteger &B) {
  A = A.mult(B);
  return A;
}
