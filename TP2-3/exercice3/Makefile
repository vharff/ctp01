CC = gcc

# Compilation intermediaire
CFLAG = -g -O0 -Wall -fbounds-check -Wextra -fcommon

# Compilation aggressive
# CFLAG = -fast

LIBS = -lm

all: exo3

exo3: utils.h utils.o methods.h methods.o exercice3.o
	$(CC) $(CFLAG) utils.o methods.o exercice3.o -o exo3 $(LIBS)

utils.o: utils.c utils.h
	$(CC) $(CFLAG) -c utils.c

methods.o: methods.c methods.h
	$(CC) $(CFLAG) -c methods.c

exercice3.o: exercice3.c
	$(CC) $(CFLAG) -c exercice3.c

clean:
	\rm -f -r exo3 model.txt *.o *.mod *.dSYM

