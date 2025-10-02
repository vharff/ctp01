CC = gcc 

# Compilation avec plein de verifications
#  CFLAG = -g -O0 -Wall -Wextra -Wno-compare-reals -fcheck=all -fimplicit-none -std=f2008 -pedantic -ffpe-trap=invalid,zero,overflow -fbacktrace -fall-intrinsics -Wno-unused-function -finit-real=snan -finit-logical=false -finit-integer=999999

# Compilation intermediaire
CFLAG = -g -O0 -Wall -fcommon

# Compilation aggressive
# CFLAG = -fast

# Math library for some setups
# CFLAG += -lm

all: integration

integration: integration.o fonction.o methodes.o constantes.h fonction.h methodes.h
	$(CC) $(CFLAG) fonction.o methodes.o integration.o  -o integration -lm
	
fonction.o: fonction.c constantes.h
	$(CC) $(CFLAG) -c fonction.c

methodes.o: methodes.c constantes.h
	$(CC) $(CFLAG) -c methodes.c

integration.o: integration.c constantes.h
	$(CC) $(CFLAG) -c integration.c

clean:
	\rm -f -r integration integration.txt *.o *.dSYM
