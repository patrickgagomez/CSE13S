#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 6
#
#  make                     makes Arithmetic
#  make BigIntegerClient    makes BigIntegerClient
#  make ListClient          makes ListClient
#  make clean               removes all binaries
#  make format 							formats all working files
#------------------------------------------------------------------------------

Arithmetic : Arithmetic.o List.o BigInteger.o
	g++ -std=c++17 -Wall -o Arithmetic Arithmetic.o List.o BigInteger.o

Arithmetic.o : Arithmetic.cpp List.o BigInteger.o
	g++ -std=c++17 -Wall -c Arithmetic.cpp

BigIntegerClient : BigIntegerClient.o List.o BigInteger.o
	g++ -std=c++17 -Wall -o BigIntegerClient BigIntegerTest.o List.o BigInteger.o

BigIntegerClient.o : List.h BigInteger.h BigIntegerTest.cpp
	g++ -std=c++17 -Wall -c BigIntegerTest.cpp

ListClient : ListClient.o List.o
	g++ -std=c++17 -Wall -o ListClient ListTest.o List.o

ListClient.o : List.h ListTest.cpp
	g++ -std=c++17 -Wall -c ListTest.cpp

List.o : List.h List.cpp
	g++ -std=c++17 -Wall -c List.cpp

BigInteger.o : BigInteger.h BigInteger.cpp
	  g++ -std=c++17 -Wall -c BigInteger.cpp

clean :
	rm -f BigIntegerClient ListClient Arithmetic out *.o

format:
	clang-format -i -style=file *.cpp *.h


