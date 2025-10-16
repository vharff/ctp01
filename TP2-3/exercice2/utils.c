#include<stdio.h>
#include<math.h>
#include "constants.h"
#include "utils.h"

double gamm1 = 5./3. ;
double dx, *x, *xx;

// --------------------------------------------------------------
void init(double M, int n, double y[2*n+1]){
// This routine sets initial guesses for all coordinates of the
// main vector y
// --------------------------------------------------------------
    
    int i;

    dx = 1.0 / n;
    
    printf("test init0\n");

    // position array
    for(i=0;i<n+1;i++){x[i] = i*dx;}
    for(i=0;i<n  ;i++){xx[i] = 0.5 * (x[i]+x[i+1]) ;}
        
    printf("test init1\n");

    // Vector of guesses
    // ======================
    //      CHANGE HERE
    // ======================
    double R = (1+2*M)/pow(M,0.5);
    for(i=0;i<n  ;i++){y[i] = 1 ;}  // metrics
    for(i=n;i<2*n;i++){y[i] = (M/pow(R,3))*pow(cos(M_PI*x[i-n]/2),2);}   // density
    y[2*n] = R;                     // radius
    // ======================

    printf("test init2\n");
}
// --------------------------------------------------------------


// --------------------------------------------------------------
void solve(double M, int n, double y[2*n+1]){
// this routine starts from a guess (y as input) and applies
// Newton-Raphson iterations to get the solution (y as output).
// --------------------------------------------------------------

    int i,k, nvar=2*n+1;
    double F[nvar], dy[nvar];
    double J[nvar*nvar];
    int info;
    int ipiv[nvar];
    int satisfying = 0;
    int nrhs = 1;
    double sumsq=0;
    k = 0;
    printf("test\n");
    while (satisfying == 0 && k<100){
        getFJ(M,n,y,F,J);
        dgesv_(&nvar,&nrhs,J,&nvar,ipiv,F,&nvar,&info);
        for(i=0;i<nvar;i++)
           {y[i] -= F[i];
            sumsq += F[i]*F[i];}
        k +=1;
        if (sumsq < pow(10,-10)){satisfying = 1;}
        
        printf("M = %7.4f   R = %5.2f   iter = %3d\n", M, y[nvar-1], k);
        sumsq = 0;
    }

            
}
// --------------------------------------------------------------



// --------------------------------------------------------------
void store(double M, int n, double y[2*n+1]){
// This routine saves the density and metrics profiles to a file
// --------------------------------------------------------------

    int i;
    double R=y[2*n];

    FILE *fich = fopen("star.txt","write");
    
    fprintf(fich,"%lf   %lf \n",gamm1, M);
    
    // save to file (x, g, rho) ------------------------------
    fprintf(fich,"%14.7le   %14.7le   %14.7le \n", 0., 1. , y[n]);
    for(i=1;i<n;i++){fprintf(fich,"%14.7le   %14.7le   %14.7le \n", R*x[i], y[i-1], y[n+i]);}
    fprintf(fich,"%14.7le   %14.7le   %14.7le \n", R, y[n-1], 0.0);
        
    fclose(fich);
        
}
// --------------------------------------------------------------



// --------------------------------------------------------------
void MR(int n){
// This routine computes the solutions for many different masses
// and store the M(R) relation to a file
// --------------------------------------------------------------
    double y[2*n+1];
    const int nm = 200;
    const double Mmin=0.01, Mmax=0.32;
    double M;
    int i;

    FILE *fich = fopen("mr.txt", "w");
    fprintf(fich,"%lf \n", gamm1);

    // init profiles for the very first mass only
    M = Mmin;
    init(M,n,y);

    // Then, the radius and profiles obtained for one mass are
    //used as guesses for the next mass
    for(i=0;i<nm;i++){
        M = Mmin + (Mmax-Mmin) * (double) i/ (nm-1.0);
        solve(M,n,y);
        fprintf(fich,"%lf  %lf  \n",M, y[2*n]);
    }

    fclose(fich);

}
// --------------------------------------------------------------



// --------------------------------------------------------------
void getFJ(double M, int n, double y[2*n+1], double F[2*n+1], double J[(2*n+1)*(2*n+1)]){
    // This routine computes for a given mass M:
    // F: the vector with the value of the 2*n+1 non-linear fonctions
    //    to solve
    // J: the Jacobian matrix with the 2*n+1 derivatives of these
    //    fonctions with respect to the 2n+1 variables
    // Variables and fonctions have the following indices:
    //    0 <= i <=  n-1 : n values of g
    //    n <= i <= 2n-1 : n vaues of rho
    //      i = 2n       : value of R
    // --------------------------------------------------------------
    double g[n+1], rho[n+1], P[n+1], Pr[n+1];
    double rr[n], gg[n], pp[n], dg[n], dP[n],z1[n], z2[n];
    double R;
    int i,nvar=2*n+1;
    
    g[0] = 1.;  for(i=1;i<n+1;i++){g[i] = y[i-1];}
    for(i=0;i<n;i++){rho[i]=y[i+n];}; rho[n] = 0.;
    R   = y[2*n];
    
    for(i=0;i<n;  i++){gg[i] = 0.5*(g[i+1]+g[i]);}
    for(i=0;i<n;  i++){dg[i] = g[i+1]-g[i];}
    for(i=0;i<n;  i++){rr[i] = 0.5*(rho[i+1]+rho[i]);}
    for(i=0;i<n+1;i++){P[i]  = pow(fabs(rho[i]),gamm1);}
    for(i=0;i<n;  i++){pp[i] = 0.5*(P[i+1]+P[i]);}
    for(i=0;i<n;  i++){dP[i] = P[i+1] - P[i];}
    for(i=0;i<n+1;i++){Pr[i] = gamm1*P[i]/rho[i];}
    for(i=0;i<n;  i++){z1[i] = 8*M_PI * R*R*xx[i]*xx[i];}
    for(i=0;i<n;  i++){z2[i] = xx[i] / dx / (gg[i]*gg[i]*gg[i]);}
    
    for(i=0;i<(2*n+1)*(2*n+1);i++){J[i] = 0.;}
    
    // equations for g -----------------------------------------------
    for(i=0;i<n;i++){F[i] = z1[i] * rr[i] - 2*z2[i]*dg[i]  - 1 + 1./(gg[i]*gg[i]);}
    
    // derivatives with respect to y_i = g_(i+1) with 0<=i<=n-1
    for(i=0;i<n;i++){J[i+nvar*i] = z2[i] * ( -2 + 3.*dg[i]/gg[i]) - 1/(gg[i]*gg[i]*gg[i]);}
    
    // derivatives with respect to y_(i-1) = g_i with 1<=i<=n-1 (fixed g0)
    for(i=1;i<n;i++){ J[i+nvar*(i-1)] = z2[i] * (  2 + 3.*dg[i]/gg[i]) - 1/(gg[i]*gg[i]*gg[i]);}
    
    // derivatives with respect to y_(i+n) = rho_i with 0<=i<=n-1
    for(i=0;i<n;i++){J[i+nvar*(i+n)] = z1[i] / 2.0;}
    
    // derivativs with respect to y(i+n+1) = rho_(i+1) to 1<=i<=n-1 (fixed rho_(n))
    for(i=0;i<n-1;i++){J[i+nvar*(i+n+1)] = J[i+nvar*(i+n)];}
    
    // derivatives with respect to R
    for(i=0;i<n;i++){J[i+2*n*nvar] = 2*z1[i]/R*rr[i];}
    
    
    // equations for rho --------------------------------------------
    for(i=0;i<n;i++){F[n+i] = z1[i]*pp[i] + 2*z2[i]*gg[i]/(pp[i]+rr[i])*dP[i] + 1 - 1.0/(gg[i]*gg[i]);}
    
    // derivatives with respect to y_i = g_(i+1) with 0<=i<=n-1
    for(i=n;i<2*n;i++){ J[i+nvar*(i-n)]   = -2*z2[i-n]/(pp[i-n]+rr[i-n])*dP[i-n] + 1/(gg[i-n]*gg[i-n]*gg[i-n]);}
    
    // derivatives with respect to y_(i-1) = g_i with 1<=i<=n-1 (fixed g0)
    for(i=n+1;i<2*n;i++){J[i+nvar*(i-n-1)] = -2*z2[i-n]/(pp[i-n]+rr[i-n])*dP[i-n] + 1/(gg[i-n]*gg[i-n]*gg[i-n]);}
    
    // derivatives with respect to y_(i+n) = rho_i with 0<=i<=n-1
    for(i=n;i<2*n;i++) {J[i+nvar*i] = z1[i-n] * 0.5*Pr[i-n]
        - z2[i-n]*gg[i-n]/(pp[i-n]+rr[i-n]) * (  (Pr[i-n]  +1)*dP[i-n]/(pp[i-n]+rr[i-n]) + 2*Pr[i-n] );}
    
    // derivatives with respect to y(i+n+1) = rho_(i+1) with 1<=i<=n-1 (fixed rho_(n))
    for(i=n;i<2*n-1;i++) {J[i+nvar*(i+1)] = z1[i-n] * 0.5*Pr[i-n+1]
        - z2[i-n]*gg[i-n]/(pp[i-n]+rr[i-n]) * (  (Pr[i-n+1]+1)*dP[i-n]/(pp[i-n]+rr[i-n]) - 2*Pr[i-n+1] );}
    
    // derivatives with respect to R
    for(i=0;i<n;i++) {J[i+n+2*n*nvar] = 2*z1[i]/R*pp[i];}
    
    
    // equation for R ------------------------------------------------
    F[2*n]         = 1/(g[n]*g[n]) + 2*M/R - 1.0;
    J[2*n+nvar*(n-1)] = -2./(g[n]*g[n]*g[n]);
    J[2*n+2*n*nvar]   = -2*M/(R*R);
    
}
// --------------------------------------------------------------
