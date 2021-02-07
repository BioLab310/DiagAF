EXECUTABLE=GenPair1sub GenPair1delins GenPairunequal PairEdConfirm
CXX = g++

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
endif
ifeq ($(UNAME_S),Darwin)
	CFLAGS += -I/opt/local/include
endif

all: $(EXECUTABLE)
basic.o:basic.cpp	
	$(CXX) -c $^ -o $@

GenPair1sub: basic.o GenPair1sub.cpp
	$(CXX) $^ -o $@	

GenPair1delins: basic.o GenPair1delins.cpp
	$(CXX) $^ -o $@	
	
GenPairunequal: basic.o GenPairunequal.cpp
	$(CXX) $^ -o $@

PairEdConfirm: basic.o PairEdConfirm.cpp
	$(CXX) $^ -o $@
	
.PHONY : clean

clean:
	rm *.o $(EXECUTABLE)
