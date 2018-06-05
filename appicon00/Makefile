BIN=changeappicon
SRC=change_app_icon.mm junk.cpp main.cpp
SRC_H=change_app_icon.h junk.h
CXX=clang++ -std=c++11
FLTK-CONFIG ?= fltk-config
CFLAGS=$(shell $(FLTK-CONFIG) --use-images --cflags)
LDFLAGS=$(shell $(FLTK-CONFIG) --use-images --ldflags)
LIBS=$(shell $(FLTK-CONFIG) --use-images --libs)

all : $(BIN)

run : $(BIN)
	./$(BIN)

$(BIN) : $(SRC) $(SRC_H)
	$(CXX) -o $(BIN) $(SRC) $(CFLAGS) $(LDFLAGS) $(LIBS)

clean :
	rm -f $(BIN)
