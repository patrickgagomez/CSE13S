/*********************************************************************************
 * Patrick Gomez, pggomez
 * 2022 Spring CSE101 PA#6
 * Arithmetic.cpp
 *	The '.cpp' file for the main program
 *********************************************************************************/

#include "BigInteger.h"
#include "List.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
  // check if we got infile and outfile...
  if (argc != 3) {
    fprintf(stderr, "Program Error: No infile/outfile specified.\n");
    exit(EXIT_FAILURE);
  }
  // open infile

  fstream infile;
  infile.open(argv[1], ios::in);

  ofstream cout(argv[2]);

  /*
  fstream outfile;
  outfile.open(argv[2], ios::out);
  */

  string strA;
  string strB;
  string clear;

  std::getline(infile, strA);
  std::getline(infile, clear);
  std::getline(infile, strB);

  // cout << strA << endl;
  // cout << strB << endl;

  BigInteger A = BigInteger(strA);
  BigInteger B = BigInteger(strB);

  cout << A << endl;
  cout << B << endl;

  BigInteger C = A + B;
  cout << C << endl;

  BigInteger D = A - B;
  cout << D << endl;

  BigInteger E = A - A;
  cout << E << endl;

  BigInteger F = A + A;
  BigInteger G = F + A;
  BigInteger H = B + B;
  BigInteger I = G - H;
  cout << I << endl;

  BigInteger J = A * B;
  cout << J << endl;

  BigInteger K = A * A;
  cout << K << endl;

  BigInteger L = B * B;
  cout << L << endl;

  BigInteger M;
  for (int i = 0; i < 9; i++) {
    M += A;
  }
  for (int i = 0; i < 4; i++) {
    M *= M;
  }
  BigInteger N;
  for (int i = 0; i < 16; i++) {
    N += B;
  }
  for (int i = 0; i < 5; i++) {
    N *= N;
  }
  BigInteger O = M + N;
  cout << O << endl;

  return 0;
}
