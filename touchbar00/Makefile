BIN=touchbar
SRC=simple_touchbar_api.mm simple_touchbar_api_test.cpp
SRC_H=simple_touchbar_api.h
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
