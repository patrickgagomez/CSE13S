/*********************************************************************************
 * Patrick Gomez, pggomez
 * 2022 Spring CSE101 PA#6
 * BigIntegerTest.cpp
 *  The '.cpp' test file for all of the BigInteger functions.
 *********************************************************************************/


#include "BigInteger.h"
#include "List.h"
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

int main() {

  string s1 = "1232741712";
  string s2 = "4567698391823";

  BigInteger A = BigInteger(s1);
  BigInteger B = BigInteger(s2);

  cout << endl;

  cout << "A = " << A << endl;
  cout << "B = " << B << endl;

  cout << "========================" << endl;

  BigInteger C = A + B;
  cout << "A + B = " << C << endl;
  cout << "========================" << endl;
  BigInteger D = B + A;
  cout << "B + A = " << D << endl;
  cout << "========================" << endl;
  BigInteger E = A - A;
  cout << "A - A = " << E << endl;
  cout << "========================" << endl;
  BigInteger F = B - A;
  cout << "B - A = " << F << endl;
  cout << "========================" << endl;
  BigInteger G = A * B;
  cout << "A * B = " << G << endl;
  cout << "========================" << endl;
  BigInteger H = B * A;
  cout << "B * A = " << H << endl;
  cout << "========================" << endl;
  // BigInteger I = C*E;
  // cout << "C * E = " << I << endl;

  BigInteger BI = BigInteger("123456789");
  cout << BI << endl;

  string str2 = "000123456007892";
  BigInteger BI2 = BigInteger(str2);
  cout << BI2 << endl;

  string str3 = "000123456789";
  BigInteger BI3 = BigInteger(str3);

  if (BI == BI3) {
    cout << "bi and bi3! they are equal!" << endl;
  }

  if (BI.compare(BI2) == 0) {
    cout << "they are equal!" << endl;
  }

  string test_tostr = BI2.to_string();
  cout << "testing tostr: " << test_tostr << endl;

  BI2.makeZero();
  cout << BI2 << endl;

  BigInteger BI4 = BigInteger("123");
  BigInteger BI5 = BigInteger("456");

  BigInteger MULT = BI4.mult(BI5);
  cout << "mult test 1:" << endl
       << "expected: +05 60 88" << endl
       << "got: " << MULT << endl;

  BigInteger BI6 = BigInteger("4521");
  BigInteger BI7 = BigInteger("3462");

  BigInteger MULT2 = BI6.mult(BI7);
  cout << "mult test 2:" << endl
       << "expected: +15 65 17 02" << endl
       << "got: " << MULT2 << endl;

  BigInteger BI8 = BigInteger("1234");
  BigInteger BI9 = BigInteger("5678");

  BigInteger DIFF = BI8.sub(BI9);
  cout << "sub test:" << endl
       << "expected: -44 44" << endl
       << "got:      " << DIFF << endl;

return 0;
}
