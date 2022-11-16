CXXFLAGS=-std=c++11 -Wall -O3
OBJ=solver.o game.o test.o

all: $(OBJ)
	$(CXX) main.cpp -o sudoku $(OBJ) $(CXXFLAGS) $(LDFLAGS)

debug: $(OBJ)
	$(CXX) debug.cpp -o debug $(OBJ) $(CXXFLAGS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

clean:
	rm $(OBJ) sudoku