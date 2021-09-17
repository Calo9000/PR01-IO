TARGET=object
 
# compiler
CC=gcc
# debug
DEBUG=-g
# optimisation
OPT=-O0
# warnings
WARN=-Wall
 
PTHREAD=-pthread
 
CCFLAGS=$(DEBUG) $(OPT) $(WARN) $(PTHREAD) -pipe

 
# linker
LD=gcc
LDFLAGS=$(PTHREAD) $(GTKLIB) -export-dynamic -lm
 
OBJS=    knapsack.o
 
all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS)
    
knapsack.o: knapsack.c
	$(CC) -c $(CCFLAGS) knapsack.c $(GTKLIB) -o knapsack.o -lm
    
clean:
	rm -f *.o $(TARGET)
