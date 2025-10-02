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


// ------------------------------------------------------------
double dot(const int n, double A[n], double B[n]) {
    
    // Compute the dot product of two vectors
    
    int i;
    double d=0;
    for(i=0;i<n;i++){d += A[i]*B[i];}
    return d;
}
// ------------------------------------------------------------



// ------------------------------------------------------------
void sort(int n, double w[n], double *v){

    // Sort the eigenvalues w and eigenvectors v by increasing
    // eignevalue
    
    int i,j,k,jmin;
    double lmin,tmp;

    for(i=0;i<n;i++){
        
        lmin = 1.e50;
        
        for(j=i+1;j<n;j++){
        
            // get max of unsorted eigen value
            if(w[j]<lmin){
                jmin = j;
                lmin = w[j] ;
            }
            
            // swap with current
            if (lmin<w[i]){
                w[jmin]=w[i]; w[i]=lmin;
                for(k=0;k<n;k++){
                    tmp = v[k+n*jmin];
                    v[k+n*jmin] = v[k+n*i];
                    v[k+n*i] = tmp;
                }
            }
            
        }
    }

}
// ------------------------------------------------------------



// ------------------------------------------------------------
void store(const char *name, const int n, const int nv, double w[nv], double v[n][nv]){
    
    // Save to file 'name':
    //   - the nv eigenvalues w
    //   - the nv eigenvectors of size n
    //
    //            w1   w2  w3 ... w_nv
    //            |    |   |       |
    // Format :   v1   v2  v3 ... v_nv
    //            |    |   |       |
    
    
    FILE *fich = fopen(name,"w");
    int iv, i;

    // First row: list of all eigenvalues
    for(iv=0; iv<nv; iv++){fprintf(fich," %11.3e",w[iv]);}
    fprintf(fich,"\n");
    
    // Other rows, coordinates of all eigenvectors
    // One column for each vector
    for(iv=0; iv<nv; iv++){fprintf(fich," %11.3e",0.0);}
    fprintf(fich,"\n");
    for(i=0; i<n; i++){
        for(iv=0; iv<nv; iv++){fprintf(fich," %11.3e",v[i][iv]);}
        fprintf(fich,"\n");
    }
    for(iv=0; iv<nv; iv++){fprintf(fich," %11.3e",0.0);}
    fprintf(fich,"\n");
    fclose(fich);
}
// ------------------------------------------------------------


// ------------------------------------------------------------
void makeA(const int n, double *A) {

    // Create band matrix A

    int i;
    double dx = 1.0/(double)(n+1);

    // ***********************************************
    // IMPLEMENTER ICI LA DEFINITION DE LA MATRICE A
    // ***********************************************

}
// ------------------------------------------------------------



// ------------------------------------------------------------
void get_all_evv(const int n, double A[], const int nv, double w[nv], double v[n][nv]) {
    
    // Simple wrapper to the dgeev() lapack routine that find
    // all eigenvalues and eigen vectors using the QR factorisaton
    
    int i, iv;
    double norm;
    double *Acopy = (double *) malloc(n*n*sizeof(double));
    double *wr   = (double *) malloc(n*sizeof(double));
    double *vr   = (double *) malloc(n*n*sizeof(double));

    // save local copy of A to prevent modification by dgeev()
    for(i=0;i<n*n;i++){Acopy[i]=A[i];}
    
    // ***********************************************
    // IMPLEMENTER ICI LE CALCUL DES VALEURS PROPRES ET VECTEURS PROPRES
    // Dans la suite, wr contient les parties reeles des valeurs propres
    // et vr contient la liste des vecteurs propres
    // ***********************************************

    // sort all with increasing eigenvalue
    sort(n, wr, vr);

    // select only the nv first eigenvalues
    for(iv=0;iv<nv;iv++){w[iv] = wr[iv];}
    for(i=0;i<n;i++){for(iv=0;iv<nv;iv++){v[i][iv] = vr[i+n*iv];}}

    // normalize vectors
    for(iv=0;iv<nv;iv++){
        norm = 0.;
        for(i=0;i<n;i++){norm+=v[i][iv]*v[i][iv];}
        if (norm>0){for(i=0;i<n;i++){v[i][iv] *= sqrt(n/2.0/norm);}}
    }
    
    free(wr); free(vr); free(Acopy);
    
}
// ------------------------------------------------------------




// ------------------------------------------------------------
void makeLDU(const int n, double L[n-1], double D[n], double U[n-1]) {

    // Create seperate diagonal D, sub-diagonal L,
    // and super-diagonal U arrays

    int i;
    double dx = 1.0/(double)(n+1);

    // ***********************************************
    // IMPLEMENTER ICI LA DEFINITION DE L, D et U
    // ***********************************************

}
// ------------------------------------------------------------




// ------------------------------------------------------------
void get_target_evv(const int n, double L[n-1], double D[n], double U[n-1], const int nv, double sigma[nv], double w[nv], double v[n][nv]) {

    int iv,i;
    double Lcopy[n-1], Dcopy[n], Ucopy[n-1];

    // ***********************************************
    // IMPLMENTER ICI LA METHODE SHIFT INVERT QUI CALCULE
    // LES NV VECTEURS PROPRES V ET LES VALEURS PROPRES ASSOCIEES W
    // LES PLUS PROCHES DES NV CIBLES SIGMA
    // ***********************************************

    // normalise vectors to sqrt(n/2) (max amplitude = 1)
    for(iv=0;iv<nv;iv++){for(i=0;i<n;i++){v[i][iv] *= sqrt(n/2.0);}}

}
// ------------------------------------------------------------



