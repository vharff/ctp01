CC = gcc

CFLAG = -g -O0 -fcheck=all -fbacktrace


LIBS = -lm

all: exo1

exo1:  utils.o exercice1.o utils.h
	$(CC) $(CFLAG) utils.o exercice1.o -o exo1 $(LIBS)

utils.o: utils.c utils.h
	$(CC) $(CFLAG) -c utils.c

exercice1.o: exercice1.c utils.h
	$(CC) $(CFLAG) -c exercice1.c


clean:
	\rm -f -r exo1 NR.txt *.o *.out *.dSYM
