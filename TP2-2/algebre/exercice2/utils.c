#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "utils.h"


// -----------------------------------------------------------------
void show_matrix(int m, int n, double *M){
    
    // Display (m x n) matrix M as rows and columns
    // For debug purposes only...
    // Uses column-major convention

    int i,j;
    printf("Matrice = \n");
    
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            printf("%6.2lf ",M[i+m*j]);
        }
        printf("\n");
    }

}
// -----------------------------------------------------------------



// -----------------------------------------------------------------
void product(int n, double *A, double *x, double *b){

    // Simple wrapper to the dgemv blas routine to compute the dot
    // product of matrix A with vector x and store it to vector b.
    
    double alpha=1., beta=0;
    int incr=1;
    
    dgemv_("N",&n,&n,&alpha,A,&n,x,&incr,&beta,b,&incr);
    
}
// -----------------------------------------------------------------



// -----------------------------------------------------------------
void make_system(int n, double *A, double *b, double *x){
    
    // Build matrix A (n x n), right hand side b, and analytical solution.
    // Vandermonde matrix with evenly spaced coefficients 0 <= a_i <= 1
    // Sor seek of simlpicity, the solution first set, and the rhs is then
    // computed as b=Ax
    
    int i, j;
    double ai;
    
    // Vandemonde matrix
    for(j=0; j<n; j++) { for(i=0; i<n; i++) {
        ai = i / (n-1.);
        A[i+n*j] = pow(ai,j);
    } }
    
    // analytical solution with constant coefficients
    for(i=0; i<n; i++) { x[i] = 1. ; }

    // right hand side computed as b = Ax
    product(n,A,x,b);
    
}
// -----------------------------------------------------------------



// -----------------------------------------------------------------
double diff(int n, double *X1, double *X2){
    
    // Compute the L2-norm of the difference between two vectors and
    // noramlize it to the L2-norm of the first vector.
    
    int i;
    double x=0,y=0;
    for(i=0;i<n;i++){
        x += (X2[i]-X1[i]) * (X2[i]-X1[i]) ;
        y += X1[i]*X1[i] ;
    }
    return sqrt(x/y);
}
// -----------------------------------------------------------------



// -----------------------------------------------------------------
void solve(int n, double *A, double *b, double *x){

    // Simple wrappter to the dgesv() lapack routine that solves linear
    // systems Ax=b using LU decomposition.
    // Warning: dgesv() modifies A and b when called.
    
    double *Acopy = (double*) malloc(n*n*sizeof(double));

    A,IPIV,B,INFO = dgesv_(&n,1,A,&n,B,&LDB);
    // ***********************************************
    // IMPLEMENTER ICI l'appel à la routine DGESV()
    // ***********************************************

    
    free(Acopy);
    
}
// -----------------------------------------------------------------



// -----------------------------------------------------------------
double cond(int n, double *A){
    
    // Compute and return the condition number of an (n x n) matrix A
    // using the singular value decomposition
    
    double c;
    double * Acopy = (double *) malloc(n*n*sizeof(double));
    int i;

    // save local copy of A (otherwise dgesdd modifies A)
    for(i=0; i<n*n; i++) Acopy[i] = A[i];

    // ***********************************************
    // IMPLEMENTER ICI LE CALCUL DES VALEURS SINGULIERES
    // ET DU NOMBRE DE CONDITIONNEMENT
    c = 0;
    // ***********************************************

    // free memory
    free(Acopy);

    return c;
    
}

// -----------------------------------------------------------------
