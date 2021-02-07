EXECUTABLE = FNEXEC FPEXEC TestInputPair

CXX = g++

LD = ld

LDFLAGS = -r

CFLAGS = -O3 -msse4.2 -I .
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
endif
ifeq ($(UNAME_S),Darwin)
	CFLAGS += -I/opt/local/include
endif

#CFLAGS = -O3 -march=native -P -E

all: $(EXECUTABLE)

print.o: print.c print.h
	$(CXX) $(CFLAGS) -c $< -o $@

popcount.o: popcount.c popcount.h
	$(CXX) $(CFLAGS) -c $< -o $@

bit_convert.o: bit_convert.c bit_convert.h
	$(CXX) $(CFLAGS) -c $< -o $@
	
vector_filter.o: vector_filter.c vector_filter.h
	$(CXX) $(CFLAGS) -c $< -o $@

mask.o: mask.c mask.h
	$(CXX) $(CFLAGS) -c $< -o $@
	
FNEXEC: mask.o print.o bit_convert.o popcount.o vector_filter.o FNEXEC.cc
	$(CXX) $(CFLAGS) $^ -o $@
	
FPEXEC: mask.o print.o bit_convert.o popcount.o vector_filter.o FPEXEC.cc
	$(CXX) $(CFLAGS) $^ -o $@

TestInputPair: mask.o print.o bit_convert.o popcount.o vector_filter.o TestInputPair.cc
	$(CXX) $(CFLAGS) $^ -o $@

	
.PHONY : clean

clean:
	rm *.o $(EXECUTABLE)
