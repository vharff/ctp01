/*
 Remarques :
 - Il n'est pas forcement pertinent de definir un type personnalise de
   reels car les routines lapack sont différences selon le type de reels
   utilse simple/double, de toutes facons
 - Il n'est pas non plus forcement pertinent de definir les matrices
   comme des pointeurs de pointeurs (permettant d'utiliser la notation
   M[i][J] car les routines lapack utilisent la notation column-major
   issue du Fortran. Il est donc preferable de gerer a la main
   l'organisation des elements dans les tableaux.
 */

#include<stdio.h>
#include<stdlib.h>
#include "utils.h"

int main(){
    printf('entering main');

    const int N = 10;
    double *A   = (double*) malloc(N*N*sizeof(double));
    double *b   = (double*) malloc(N*sizeof(double));
    double *sol = (double*) malloc(N*sizeof(double));
    double *x   = (double*) malloc(N*sizeof(double));
    printf('variables declared');

    // Create system ------------------------------------
    make_system(N, A, b, sol);
    
    // Solve system -------------------------------------
    solve(N, A, b, x);

    // Compare the numerical to the expected solutions --
    printf("      exact     numerical\n");
    for(int i=0;i<N;i++){
        printf("%2d  %7.4lf  %10.4lf \n",i,sol[i],x[i]);
    }

    // Estimate error -----------------------------------
    printf("Error estimate:   %.2le \n",diff(N,sol,x));

    // Compute condition number -------------------------
    printf("Condition number: %.2le \n", cond(N,A));

    // Free all matrices --------------------------------
    free(A); free(b); free(x); free(sol);
    
    
    return EXIT_SUCCESS;
    
}
