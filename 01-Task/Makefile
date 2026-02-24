all: main

main: main.o DPN.o
	g++ -std=c++17 main.o DPN.o -o main

DPN.o: DPN.cpp DPN.h
	g++ -std=c++17 -c DPN.cpp -o DPN.o

main.o: main.cpp DPN.h
	g++ -std=c++17 -c main.cpp -o main.o

clean:
	@rm -f main.o DPN.o main
