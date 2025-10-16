#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "utils.h"


int main() {

    int nmax=100;
    const double eps=1.e-15;
    double x0;
    int i, iter;
    long double x,xth,xs[nmax];
    
    
    // initial guess
    x0 = 0.5;

    // get solution for f1 or f2 with Newton-Raphson method
    x = NR(f2,df2,x0,nmax,eps,&iter,xs);

    // save iterations and errors compared to an exact value xth
    xth = 1.;
    FILE *fich=fopen("NR.txt","w");
    for(i=0;i<iter;i++){
        fprintf(fich,"%3i %14.6le %14.6le \n", i, xs[i], fabs(xs[i]-xth));
    }
    fclose(fich);

    
    return EXIT_SUCCESS;
}

