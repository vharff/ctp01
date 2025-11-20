
# C COMPILER
CC   = gcc

# COMPiLATION OPTIONS
#OPTS = -Ofast #-fcommon
OPTS = -g -Wall -Wextra # -fcommon

LIBS = -lm

# GLOBAL TARGET
all: advection

# COMPILE PHYSICS MODULE
physics.o: physics.c
	$(CC) $(OPTS) -c physics.c

# COMPILE NUMERICS MODULE
numerics.o: numerics.c 
	$(CC) $(OPTS) -c numerics.c

# COMPILE SOLVER MODULE
solvers.o: solvers.c physics.o numerics.o
	$(CC) $(OPTS) -c solvers.c

# COMPILE MAIN PROGRAM, LINK AND PRODUCE EXECUTABLE
advection: advection.c physics.o numerics.o solvers.o
	$(CC) $(OPTS) advection.c physics.o numerics.o solvers.o -o advection ${LIBS}


# CLEAN UP THINGS
clean:
	\rm -rf *.o *.mod advection.txt *.dSYM advection
