// Book: "General Relativity" (Walid, 2024)
// Eq. 6.2.6  for g = sqrt(h)
// Eq. 6.2.19 for P

#include<stdio.h>
#include<stdlib.h>
#include "constants.h"
#include "utils.h"

int n = 256;

int main(){
    
    double y[2*n+1];
    x = (double *) malloc((n+1)*sizeof(double));
    xx = (double *) malloc(n*sizeof(double));
    int i;
    
    
    // set stellar mass
    double M = 0.3;
    
    // init vector y
    printf("test1\n");
    init(M, n, y);

    // compute solution for the given mass
    printf("test8\n");
    solve(M, n, y);
    
    // store solution profiles to file
    store(M, n, y);
    
    // Compute the solution for many masses and save the M-R relation
    MR(n);
    
    // free grid arrays
    free(x); free(xx);
    
    return EXIT_SUCCESS;
    
}
