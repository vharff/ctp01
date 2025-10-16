CC = gcc

# Compilation intermediaire
CFLAG = -g -O0 -Wall -fbounds-check -Wextra -fcommon

# Compilation aggressive
# CFLAG = -fast

LIBS = -lm -llapack

all: exo2

exo2: constants.h utils.h utils.o exercice2.o
	$(CC) $(CFLAG) utils.o exercice2.o -o  exo2 $(LIBS)

utils.o: utils.c constants.h utils.h
	$(CC) $(CFLAG) -c utils.c

exercice2.o: exercice2.c constants.h utils.h
	$(CC) $(CFLAG) -c exercice2.c

clean:
	\rm -f -r exo2 star.txt mr.txt *.o *.mod *.dSYM

