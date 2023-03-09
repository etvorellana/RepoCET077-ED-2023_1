
CC = gcc-12
CFLAGS = -O2

all:	exem_01, exem_02


exem_01: dataSet_01.c
	$(CC) $(CFLAGS) -o exem_01 dataSet_01.c	

exem_02: dataSet_02.o, bidefun.o
	$(CC) $(CFLAGS) -o exem_02 bidefun.o dataSet_02.o

dataSet_02.o: dataSet_02.c
	$(CC) $(CFLAGS) -c -o dataSet_02.o dataSet_02.c

bidefun.o: bidefun.c, bidefun.h
	$(CC) $(CFLAGS) -o bidefun.o -c bidefun.c

clean: 
	rm *.o
	rm exem*
