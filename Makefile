COMPILER=gcc
CCFLAGS=-Wall -ansi -pedantic
all:comb

comb:comb.o
		$(COMPILER) $(CCFLAGS) -o comb comb.o
comb.o:comb.c 
		$(COMPILER) $(CCFLAGS) -c comb.c
clean:
		rm -f comb comb.o
