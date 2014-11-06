CXX=clang++
CXXFLAGS=-std=c++11 -mtune=native -march=native -O2 -g -Weverything -ferror-limit=1
LDFLAGS=-lm
SRC=painter.cpp
INC=$(SRC,.cpp=.h)

all: $(SRC) $(INC)
	$(CXX) $(CXXFLAGS) $(SRC) main.cpp -o prog $(LDFLAGS)

run: all
	./prog

clean:
	rm -f prog
