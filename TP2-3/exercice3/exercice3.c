#include<stdio.h>
#include<stdlib.h>
#include "utils.h"
#include "methods.h"


int main(){

    const int nmax = 100000;
    double eps = 1.e-9;
    double alpha;
    double X[ndim];
    int iter;

    // Read data file -----------------------------------
    read_data();

    // Set initial guess for fit ------------------------
    
    // ==============================
    //        CHANGE HERE
    alpha = 0; X[0] = 0; X[1] = 0;
    // ==============================

    printf("Guess:\n");
    printf("  h        = %6.4f\n", X[0]);
    printf("  Omegam   = %6.4f\n", X[1]);

    // Perform fit --------------------------------------
    // iter = descent_const(ndim, gradchi2, X, alpha, eps, nmax);
    // iter = descent_BB(ndim, gradchi2, X, alpha, eps, nmax);

    printf("Best fit after %6i iterations:\n",iter);
    printf("  h        = %6.4f\n", X[0]);
    printf("  Omegam   = %6.4f\n", X[1]);
    printf("  Chi2/dof = %6.4f\n", chi2(X)/(ndata-ndim));
    storemodel(X);

    // Deallocate arrays --------------------------------
    free(xdata); free(ydata); free(dydata);

    return EXIT_SUCCESS;
    
}


