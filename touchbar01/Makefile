BIN=touchbar
SRC=touchbar.mm main.cpp
SRC_H=touchbar.h
CXX=clang++ -std=c++11
FLTK-CONFIG ?= fltk-config
CFLAGS=$(shell $(FLTK-CONFIG) --cflags)
LDFLAGS=$(shell $(FLTK-CONFIG) --ldflags)
LIBS=$(shell $(FLTK-CONFIG) --libs)

all : $(BIN)

run : $(BIN)
	./$(BIN)

$(BIN) : $(SRC) $(SRC_H)
	$(CXX) -o $(BIN) $(SRC) $(CFLAGS) $(LDFLAGS) $(LIBS)

clean :
	rm -f $(BIN)
