CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11

main: main.o terminal.o
	$(CXX) $(CXXFLAGS) main.o terminal.o -o main
main.o: terminal.h
terminal.o: terminal.h
clean:
	rm *.o main
