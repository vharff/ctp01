CC = gcc

# Compilation avec plein de verifications
#  CFLAG = -g -O0 -Wall -Wextra -Wno-compare-reals -fcheck=all -fimplicit-none -std=f2008 -pedantic -ffpe-trap=invalid,zero,overflow -fbacktrace -fall-intrinsics -Wno-unused-function -finit-real=snan -finit-logical=false -finit-integer=999999

# Compilation intermediaire
CFLAG = -g -O2 -Wall

# Compilation aggressive
# CFLAG = -fast

# Math library for some setups
#CFLAG += -lm

# lapack library
LIBS = -lblas -llapack

exo2: exercice2.o utils.o
	$(CC) $(CFLAG) $(LIBS) utils.o exercice2.o -o exo2
	
utils.o: utils.c utils.h
	$(CC) $(CFLAG) -c utils.c

exercice2.o: exercice2.c
	$(CC) $(CFLAG) -c exercice2.c

clean:
	\rm -f -r exo2 *.o *.dSYM
