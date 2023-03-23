
CC = gcc-12
CFLAGS = -O2

all:	exem_01

exem_01: dataSet_01.o, bidefun.o
	$(CC) $(CFLAGS) -o exem_01 bidefun.o dataSet_01.o

dataSet_01.o: dataSet_01.c
	$(CC) $(CFLAGS) -o dataSet_01.o -c dataSet_01.c

bidefun.o: bidefun.c, bidefun.h
	$(CC) $(CFLAGS) -o bidefun.o -c bidefun.c

clean: 
	rm *.o
	rm exem*
