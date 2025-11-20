//==================================================================================================
// This file contains the routines to solve one single time-step of the advection equation using the
// explicit various schemes (exlicit and implicit)
//==================================================================================================
#include<stdlib.h>
#include "physics.h"
//--------------------------------------------------------------------------------------------------
void Upwind(int nx, double y[nx], double cfl)

//--------------------------------------------------------------------------------------------------
// This routine performs one single time-step of the advection equation using the Upwind scheme.
// ARGUMENTS:
//   nx (int):       number of physical grid points
//   y (real*(n)):   array before and after update
//   cfl:            the Courant parameter
//--------------------------------------------------------------------------------------------------
{
    //    int i;
    //    double *ycopy=NULL;
    //    ycopy = malloc(nx*sizeof(double));
    //    ycopy[0]=(1-cfl)*y[0]+cfl*y[nx-1]; //Q3
    //    for(i=1;i<nx;i++){
    //        ycopy[i] = (1-cfl)*y[i]+cfl*y[i-1]; //Q2
    //    }
    //    y = ycopy;
    //    printf("Solver %d %d- \n",y[0],y[10]);


    int i;
    double *ycopy=NULL;
    ycopy = malloc(nx*sizeof(double));
    for(i=0;i<nx;i++){ycopy[i]=y[i];}
    y[0]=(1-cfl)*ycopy[0]+cfl*ycopy[nx-1]; //Q3
    for(i=1;i<nx;i++){
        y[i] = (1-cfl)*ycopy[i]+cfl*ycopy[i-1]; //Q2
    }

}

//--------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------
void FTCS(int nx, double y[nx], double cfl)
//--------------------------------------------------------------------------------------------------
// This routine performs one single time-step of the advection equation using the FTCS scheme.
// ARGUMENTS:
//   nx (int):       number of physical grid points
//   y (real*(n)):   array before and after update
//   cfl:            the Courant parameter
//--------------------------------------------------------------------------------------------------
{
    int i;
    double *ycopy=NULL;
    ycopy = malloc(nx*sizeof(double));
    for(i=0;i<nx;i++){ycopy[i]=y[i];}
    y[0] -= cfl/2.0*(ycopy[1]-ycopy[nx-1]); 
    y[nx-1] -= cfl/2.0*(ycopy[0]-ycopy[nx-2]);
    for(i=1;i<nx-1;i++){
        y[i] -= cfl*(ycopy[i+1]-ycopy[i-1])/2.0; //Q9
    }


//--------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------
void LaxFriedrichs(int nx, double y[nx], double cfl)
//--------------------------------------------------------------------------------------------------
// This routine performs one single time-step of the advection equation using the Lax-Friedrichs scheme.
// ARGUMENTS:
//   nx (int):       number of physical grid points
//   y (real*(n)):   array before and after update
//   cfl:            the Courant parameter
//--------------------------------------------------------------------------------------------------
{
    int i;
    double *ycopy=NULL;
    ycopy = malloc(nx*sizeof(double));
    for(i=0;i<nx;i++){ycopy[i]=y[i];}
    y[0] = (1-cfl)/2.0*ycopy[1]+(1+cfl)/2.0*ycopy[nx-1]; 
    y[nx-1] = (1-cfl)/2.0*ycopy[0]+(1+cfl)/2.0*ycopy[nx-2]; 
    for(i=1;i<nx-1;i++){
        y[i] = (1-cfl)/2.0*ycopy[i+1]+(1+cfl)/2.0*ycopy[i-1]; //13
    }


//--------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------




//--------------------------------------------------------------------------------------------------
void BurgersLF(int nx, double y[nx], double cfl)
//--------------------------------------------------------------------------------------------------
// This routine performs one single time-step of the Burgers equation using the Lax-Friedrichs scheme.
// ARGUMENTS:
//   nx (int):       number of physical grid points
//   y (real*(n)):   array before and after update
//   cfl:            the Courant parameter
//--------------------------------------------------------------------------------------------------
{
    int i;
    double newcfl;
    double *ycopy=NULL;
    ycopy = malloc(nx*sizeof(double));
    for(i=0;i<nx;i++){ycopy[i]=y[i];}
    
    newcfl = cfl*(ycopy[1]+ycopy[nx-1])/(2.0*C);
    y[0] = (1-newcfl)/2.0*ycopy[1]+(1+newcfl)/2.0*ycopy[nx-1]; 

    newcfl = cfl*(ycopy[0]+ycopy[nx-2])/(2.0*C);
    y[nx-1] = (1-newcfl)/2.0*ycopy[0]+(1+newcfl)/2.0*ycopy[nx-2]; 

    for(i=1;i<nx-1;i++){
        newcfl = cfl*(ycopy[i+1]+ycopy[i-1])/(2.0*C);
        y[i] = (1-newcfl)/2.0*ycopy[i+1]+(1+newcfl)/2.0*ycopy[i-1]; //13
    }


    // y = ?????

//--------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------



double *a=NULL,*b=NULL, *c=NULL;
double alpha,beta;

//--------------------------------------------------------------------------------------------------
void setup_CN(int nx, double cfl)
//--------------------------------------------------------------------------------------------------
// This routine allocates the arrays used in the Crank-Nicolson scheme and sets their values according
// to the CN method and the boundary conditions. This must be done only once for all time steps.
// ARGUMENTS:
//   None
//--------------------------------------------------------------------------------------------------
{
    int i;

    a = malloc((nx-1)*sizeof(double));
    b = malloc((nx  )*sizeof(double));
    c = malloc((nx-1)*sizeof(double));

    for(i=0;i<nx-1;i++){
        a[i]=-cfl*0.25;
        b[i]=1;
        c[i]=cfl*0.25;
    }
    b[nx-1] = 1;
    beta = -cfl*0.25;
    alpha = cfl*0.25;

    // a,b,c,alpha,beta = ???
    
//--------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------
void tridag(int n, double a[n-1], double b[n], double c[n-1],double r[n],double u[n]){
//--------------------------------------------------------------------------------------------------
// This function solves the linear system M*U=R where
// - R is the source term
// - U is the system solution
// - M is a square tri-diagonal matrix
// ARGUMENTS:
//   n (int):        size of the square system
//   a (real*(n-1)): lower diagonal
//   b (real*n):     main diagonal
//   c (real*(n-1)): upper diagonal
//   r (real*n):     source term
// OUPUTS:
//   u: system solution (size n)
//--------------------------------------------------------------------------------------------------
    double gam[n-1];
    double bet;
    int j;

    // Gauss pivot for tridiagonal matrices
    bet  = b[0];
    u[0] = r[0]/bet;
    for(j=1;j<n;j++){
        gam[j-1] = c[j-1]/bet;
        bet = b[j]-a[j-1]*gam[j-1];
        u[j] = (r[j]-a[j-1]*u[j-1])/bet;
    }

    // Backward substitution
    for(j=n-2;j>=0;j--){
        u[j] = u[j] - gam[j]*u[j+1];
    }

//--------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------



//--------------------------------------------------------------------------------------------------
void cyclic(int n, double a[n-1], double b[n], double c[n-1], double alpha, double beta, double r[n],double x[n]){
//--------------------------------------------------------------------------------------------------
// This function solves the linear system M*X=R where
// - R is the source term
// - X is the system solution
// - M is a square tri-diagonal matrix with corners (cyclic matrix)
// ARGUMENTS:
//   n (int):        size of the square system
//   a (real*(n-1)): lower diagonal
//   b (real*n):     main diagonal
//   c (real*(n-1)): upper diagonal
//   alpha:          lower-left corner
//   beta:           upper right corner
//   r (real*n):     source term
// OUPUTS:
//   x: system solution (size n)
//--------------------------------------------------------------------------------------------------
    double gama,fact;
    double bb[n],u[n],z[n];
    int i;

    gama = -b[0];

    bb[0]     = b[0]-gama;
    for(i=1;i<n-1;i++){bb[i]=b[i];}
    bb[n-1]     = b[n-1] - alpha*beta/gama;
    tridag(n,a,bb,c,r,x);

    u[0] = gama;
    for(i=1;i<n-1;i++){u[i]=0.0;}
    u[n-1] = alpha;
    tridag(n,a,bb,c,u,z);

    fact = (x[0]+beta*x[n-1]/gama) / (1.0+z[0]+beta*z[n-1]/gama);
    for(i=0;i<n;i++){x[i]=x[i]-fact*z[i];}

//--------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------
void CN(int nx, double y[nx], double cfl)
//--------------------------------------------------------------------------------------------------
// This routine performs one time-step of the advection equation using the Crank-Nicolson scheme.
// ARGUMENTS:
//   nx (int):       number of physical grid points
//   y (real*(n)): array before and after update
//--------------------------------------------------------------------------------------------------
{
    int i;
    double s[nx];

    // Set source term
    // s = ???
    for(i=1;i<nx-1;i++){
        s[i]=y[i]+cfl*0.25*(y[i-1]-y[i+1]);
    }
    s[0]=y[0]+cfl*0.25*(y[nx-1]-y[1]);
    s[nx-1]=y[nx-1]+cfl*0.25*(y[nx-2]-y[0]);

    // solve linear system
    cyclic(nx,a,b,c,alpha,beta,s,y);


//--------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------
void finish_CN()
//--------------------------------------------------------------------------------------------------
// This routine deallocates the arrays used in the Crank-Nicolson scheme
// ARGUMENTS:
//   None
//--------------------------------------------------------------------------------------------------
{

    free(a);
    free(b);
    free(c);

//--------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------


