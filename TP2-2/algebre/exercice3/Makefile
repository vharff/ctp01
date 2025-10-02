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

exo3: exercice3.o utils.o
	$(CC) $(CFLAG) $(LIBS) utils.o exercice3.o -o exo3
	
utils.o: utils.c utils.h
	$(CC) $(CFLAG) -c utils.c

exercice3.o: exercice3.c
	$(CC) $(CFLAG) -c exercice3.c

clean:
	\rm -f -r exo3 *.o *.dSYM
