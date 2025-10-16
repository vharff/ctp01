#include<math.h>
#include<stdio.h>
#include "utils.h"


// ---------------------------------------------------------------
// Functions to solve equation1
double f1 (double x){return pow(x,4)-3*pow(x,3)+pow(x,2)+3*x-2;}
double df1(double x){return 4*pow(x,3)-9*pow(x,2)+2*x+3;}
double d2f1(double x){return 0;}
// ---------------------------------------------------------------



// ---------------------------------------------------------------
// Functions to solve equation2
double f2 (double x){return (pow(x+1,0.5)-1)*exp(-x);}
double df2(double x){return exp(-x)*(-(pow(x+1,0.5)-1)+1/(2*(pow(x+1,0.5))));}
double d2f2(double x){return 0;}
// ---------------------------------------------------------------



// ---------------------------------------------------------------
// Functions to solve Lagrange equation
const double mu=1./332830.;
double fL1(double x){return 0;}
double dfL1(double x){return 0;}
// ---------------------------------------------------------------




// ---------------------------------------------------------------
double NR(double (*f)(double),double (*df)(double), double x0,int nmax, double eps, int *iter, long double xs[nmax]) {
    // Find a root of function f(x) by the Newton-Raphson method,
    // using its first and second derivatives df(x) and d2f(x).
    // x0:   initial guess (input)
    // nmax: maximal number of iteration (input)
    // eps:  tolerance for convergence (input)
    // iter: number of iterations before convergence (output)
    // xs:   array of solutions found, iteration by iteration (output)

    int i;
    long double x,dx;
    long double newx;
    int satisfying = 0;
    i = 0;
    x = x0;
    while(satisfying == 0 && i<nmax){
      newx = x - f(x)/df(x);
      if (fabs(newx-x)< eps){satisfying = 1;}
      xs[i] = x;
      i +=1;
      x = newx;

    }
    printf("Guess : %3.3f gave solution: x = %8.10f after %3i iterations\n",x0, x, i);


    *iter = i;
    
  return x;
}
// ---------------------------------------------------------------


// ---------------------------------------------------------------
double halley(double (*f)(double),double (*df)(double),double (*d2f)(double), double x0,int nmax, double eps, int *iter, long double xs[nmax]) {
    // Find a root of function f(x) by the Halley method,
    // using its derivative df(x).
    // x0:   initial guess (input)
    // nmax: maximal number of iteration (input)
    // eps:  tolerance for convergence (input)
    // iter: number of iterations before convergence (output)
    // xs:   array of solutions found, iteration by iteration (ouput)

    int i;
    double x,dx;
    
    i = 0;
    // =======================================
    //             CHANGE HERE
    // =======================================

    printf("Solution: x = %8.5f after %3i iterations\n", x, i);

    *iter = i;
    
  return x;
}
// ---------------------------------------------------------------
