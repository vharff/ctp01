/*
 Remarques :
 - Il n'est pas forcement pertinent de definir un type personnalise de
   reels car les routines lapack sont différentes selon le type de reels
   utilse simple/double, de toutes facons
 - Il n'est pas possible d'utiliser de l'allocation statique avec des
   matrices aussi grandes
 - Il n'est pas non plus forcement pertinent de definir les matrices
   comme des pointeurs de pointeurs (permettant d'utiliser la notation
   M[i][J] car les routines lapack utilisent la notation column-major
   issue du Fortran. Il est donc preferable de gerer a la main
   l'organisation des elements dans les tableaux.
 */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "utils.h"

int main(){

    clock_t tic, toc;

    const int M = 1000;
    const int P = 1000;
    const int N = 1000;
    double *C = (double*) calloc(M*N, sizeof(double));

    // Create matrices A and B --------------------------------------
    double *A = makeA(M, P); // show_matrix(M,P,A);
    double *B = makeB(P, N); // show_matrix(P,N,B);


    // Evaluate product using homemade routine -----------------------
    printf("\nPersonal method:\n");
    tic = clock();
    
    product(M, P, N, A, B, C);

    toc = clock();
    // show_matrix(M,N,C);
    check(M, P, N, C);
    printf(" Elapsed time (ms): %lf \n", (toc-tic)*1e3/CLOCKS_PER_SEC);

    
    // Evaluate product using lapack routine ------------------------
    printf("\nLapack method:\n");
    tic = clock();
    double alpha = 1.;
    double beta = 0.;
    dgemm_("N", "N", &M, &N, &P, &alpha, A, &M, B, &P, &beta, C, &M);


    toc = clock();
    // show_matrix(M,N,C);
    check(M, P, N, C);
    printf(" Elapsed time (ms): %lf \n", (toc-tic)*1e3/CLOCKS_PER_SEC);

    // Free all matrices -------------------------------------------
    free(A); free(B); free(C);
    printf("\n");

    return EXIT_SUCCESS;
}
