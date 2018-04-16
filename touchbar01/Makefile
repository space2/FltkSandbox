BIN=touchbar
SRC=touchbar.mm main.cpp
SRC_H=touchbar.h
CXX=clang++ -std=c++11
CFLAGS=$(shell fltk-config --cflags)
LDFLAGS=$(shell fltk-config --ldflags)
LIBS=$(shell fltk-config --libs)

all : $(BIN)

run : $(BIN)
	./$(BIN)

$(BIN) : $(SRC) $(SRC_H)
	$(CXX) -o $(BIN) $(SRC) $(CFLAGS) $(LDFLAGS) $(LIBS)

clean :
	rm -f $(BIN)
