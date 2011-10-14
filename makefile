CPP  = g++.exe
CC   = gcc.exe
WINDRES = windres.exe
RES  = 
OBJ  = rational.o etrees.o ExpressionTemplate.o get2011.o
LIBS = -lpthreadGC2
INCS = 
CXXINCS = 
BIN  = get2011.exe 
CXXFLAGS = $(CXXINCS)  
#CFLAGS = -pg                 # For profiler
#CFLAGS = -g -Wall -std=c++0x # With debugger
CFLAGS = -s -fno-exceptions -std=c++0x -O3       # productive version          
RM = del

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after

clean: clean-custom
	${RM} $(OBJ) $(BIN) 

$(BIN) : $(OBJ) 
	g++ $(CFLAGS) $(OBJ) -o $@ ${LIBS}
	upx $@
	
get2011.o : get2011.cc get2011.h
	g++ $(CFLAGS) -c get2011.cc -o get2011.o ${LIBS}
  
etrees.o : etrees.c etrees.h  
	g++ -c $(CFLAGS) $< -o $@

rational.o : rational.c rational.h  
	g++ -c $(CFLAGS) $< -o $@

%.o : %.cc %.h  # Not exact, but a good approximation
	g++ -c $(CFLAGS) $< -o $@