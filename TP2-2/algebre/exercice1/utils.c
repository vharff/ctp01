#include<stdio.h>
#include<stdlib.h>
#include<math.h>




const double a1=1.3, a2=3.2;
const double b1=4.7, b2=9.1;



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
double* makeA(int m, int p){

    // Build matrix A (m x p)

    int i, k;

    double *A = (double*) malloc(m*p*sizeof(double));
    for(k=0; k<p; k++) {      // columns
        for(i=0; i<m; i++) {  // rows
           A[i+m*k] = a1*(i+1.0) + a2*(k+1.0); // column-major
      }
    }

    return A;
    
}
// -----------------------------------------------------------------


// -----------------------------------------------------------------
double* makeB(int p, int n){

    // Build matrix B (p x n)

    int k,j;

    double *B = (double*) malloc(p*n*sizeof(double));
    for(j=0; j<n; j++) {      // columns
        for(k=0; k<p; k++) {  // rows
          B[k+p*j] = b1*(k+1.0) + b2*(j+1.0); // column-major
      }
    }

    return B;
    
}
// -----------------------------------------------------------------



// -----------------------------------------------------------------
void check(int m, int p, int n, double*C){
    
    // Check that matrix C has been successfully computed as the
    // product of A and B (as defined above)
    
    int i,j;
    double Cij, d, delta=0.0;

    for(j=0; j<n;j++) {        // columns

        for(i=0; i<m; i++) {   // row

            // Analytical values of the coefficients
            Cij = a1*b2*(i+1.0)*(j+1.0)*p + (a1*b1*(i+1.0)+a2*b2*(j+1.0))*p*(p+1.0)/2.0 + a2*b1*p*(p+1.0)*(2*p+1.0)/6.0 ;
            
            // local difference
            d = fabs(C[i+m*j] - Cij); // column-major

            // max difference
            if (d>delta){delta=d;}

        }
    }

    
    if(delta<1.e-2){
        printf(" Check: SUCCESSFUL\n");
    } else {
        printf(" Check: FAILED (max diff = %.0le) \n", delta);
    }
    
}
// -----------------------------------------------------------------



void product(int m, int p, int n, double *A, double *B, double *C){
    double aux = 0.;
    int i,j,k;
    for (j = 0; j < n; j++){
        for (k = 0; k < p; k++) {
            aux = 0.;
            for (i = 0; i < m; i ++){
                C[i+m*j] += A[i+m*k]*B[k+p*j];
            }
            //C[i+m*j] = aux;
        }
    }

}
// Boucles dans l'ordre i,j,k (--> + imbriqué) : 403ms
// j i k : 480 ms
// j k i : 360 ms


