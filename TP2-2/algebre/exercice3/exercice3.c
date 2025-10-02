#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "utils.h"

int main(int argc, char** argv) {
    
    int n=100;        // system size
    int nv=10;        // number of eigenvalues to keep
    double w[nv];      // eigenvalues
    double v[n][nv];  // eigenvectors
    clock_t tic, tac;

    
    // --------------------------------------------------
    // METHOD 1: GET ALL EIGENVALUES AT ONCE ------------
    // --------------------------------------------------

    // allocate and create band matrix
    double *A = malloc(n*n*sizeof(double));
    makeA(n, A);
    
    // get eigenvalues and eigenvectors
    tic = clock();
    get_all_evv(n, A, nv, w, v);
    tac = clock();
    
    // Display some results to screen
    printf("\n          Exact         Method 1      Error\n");
    for(int iv=0;iv<nv;iv++){
        printf(" %2d  %12lf  %12lf  %14le\n", iv, (iv+1.)*(iv+1)*M_PI*M_PI, w[iv], fabs(1-w[iv]/((iv+1)*(iv+1)*M_PI*M_PI)));
    }
    printf(" Time (ms): %lf \n", (tac-tic)*1e3/CLOCKS_PER_SEC);

    // Store eigenvalues and eigenvectors to file
    store("vvp_QR.txt", n, nv, w, v);

    // free matrix
    free(A);

    
    
    // --------------------------------------------------
    // METHOD 2: GET INDIVDUAL EIGENVALUES --------------
    // --------------------------------------------------

    int i;
    double L[n-1], D[n], U[n-1];
    double targets[nv];
    
    // Create the 3 diagonal terms of the system
    makeLDU(n,L,D,U);
    
    // Define approximate targets for eigenvalues
    for(i=0;i<nv;i++){ targets[i] = (i+1.)*(i+1.)*3.14*3.14-0.01; }

    // get eigenvalues and eigenvectors
    tic = clock();
    get_target_evv(n, L, D, U, nv, targets, w, v);
    tac = clock();

    // Display some results to screen
    printf("\n          Exact         Method 2      Error\n");
    for(int iv=0;iv<nv;iv++){
        printf(" %2d  %12lf  %12lf  %14le\n", iv, (iv+1.)*(iv+1)*M_PI*M_PI, w[iv], fabs(1-w[iv]/((iv+1)*(iv+1)*M_PI*M_PI)));
    }
    printf(" Time (ms): %lf \n\n", (tac-tic)*1e3/CLOCKS_PER_SEC);

    // Store eigenvalues and eigenvectors to file
    store("vvp_SI.txt", n, nv, w, v);

        
    return EXIT_SUCCESS;
    
}
