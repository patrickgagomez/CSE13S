#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 7
#
#  make                     makes Order
#  make DictionaryTest      makes DictionaryTest
#  make clean               removes all binaries
#  make format 							formats all working files
#------------------------------------------------------------------------------

Order : Order.o Dictionary.o
	g++ -std=c++17 -Wall -o Order Order.o Dictionary.o

Order.o : Order.cpp Dictionary.o
	g++ -std=c++17 -Wall -c Order.cpp

DictionaryTest : DictionaryTest.o Dictionary.o
	g++ -std=c++17 -Wall -o DictionaryTest DictionaryTest.o Dictionary.o

DictionaryTest.o : Dictionary.h DictionaryTest.cpp
	g++ -std=c++17 -Wall -c DictionaryTest.cpp

Dictionary.o : Dictionary.h Dictionary.cpp
	g++ -std=c++17 -Wall -c Dictionary.cpp

clean :
	rm -f DictionaryTest Order *.o

format:
	clang-format -i -style=file *.cpp *.h


