FindPath : FindPath.o List.o Graph.o
	gcc -std=c17 -Wall -o FindPath FindPath.o List.o Graph.o

FindPath.o: FindPath.c List.h Graph.h
	gcc -std=c17 -Wall -c FindPath.c

GraphTest : GraphTest.o Graph.o List.o
	gcc -std=c17 -Wall -o GraphTest GraphTest.o Graph.o List.o

GraphTest.o : GraphTest.c List.h Graph.h
	gcc -std=c17 -Wall -c GraphTest.c

List.o : List.c List.h
	gcc -std=c17 -Wall -c List.c

Graph.o : Graph.c Graph.h List.h
	gcc -std=c17 -Wall -c Graph.c

clean :
	rm -f Graph GraphTest FindPath out.txt *.o

format:
	clang-format -i -style=file *.c *.h
