#include<stdio.h>
#include "constantes.h"
#include "math.h"


// -----------------------------------------------------------
/*
NEWTON-COTES...
 les diffentes methodes ont 4 arguments :
 - f : la fonction a integrer
 - a, b : les bornes d'integration
 - n : le nombre d'intervalles a utiliser
*/
// -----------------------------------------------------------


// -----------------------------------------------------------
real rectangles(real (* f)(real), real a, real b, int n)
{ // Methode des rectangles
    
    int j;
    real integrale, h, xi;
   
    h=(b-a)/n;
    
    integrale=0.;
    for (j = 0; j < n; j += 1){
        xi = a + h*j;
        integrale += f(xi);
    }
   integrale *= h;
   return integrale;
}
// -----------------------------------------------------------



// -----------------------------------------------------------
real trapezes(real (* f)(real), real a, real b, int n)
{ // Methode des trapèzes
    
    int j;
    real integrale, h, xi;
   
    h=(b-a)/n;
    
    integrale=0.; 
    for (j = 0; j < n; j += 1){
        xi = a + h*j;
        integrale += (f(xi)+f(xi+h))/2;
    }
   integrale *= h;

   return integrale;
}
// -----------------------------------------------------------



// -----------------------------------------------------------
real simpson(real (* f)(real), real a, real b, int n)
{ // Methode de Simpson
    
    int j;
    real integrale, h, xi;
   
    h=(b-a)/n;
    
    integrale=0.; // A MODIFIER
    for (j = 0; j < n; j += 2){
        xi = a + h*j;
        integrale += f(xi+h)+f(xi-h)+4*f(xi);
    }
   integrale *= h/3;
   return integrale;
}
// -----------------------------------------------------------



/*
GAUSS-LEGENDRE...
 
 ng: nombre de points de quadrature
 xg: position des points sur [-1,1]]
 wg: poids affecte a chaque point

 Les positions et poids doivent etre calcules une unique fois (pour un nombre ng de points fixe)
 avec la routine init_gauss(). Ces variables sont définies comme globales et ne sont pas passes
 comme argument de fonction. 
 
 Les integrales sont ensuites calculées autant de fois que necessaire avec la routine gauss()
 
*/

int ng;
real *xg, *wg;

// -----------------------------------------------------------
real gauss(real (* f)(real), real a, real b){
    int i;
    real integrale;
    
    integrale=0.; // A MODIFIER

    return integrale;
}
// -----------------------------------------------------------


// -----------------------------------------------------------
void init_gauss(){
    // Cette routine calcule les positions sur [-1,1] et les poids associes pour
    // la methode de Gauss-Legendre avec ng points.
    
    int i, j, m;
    const real eps = 3.e-15;
    real p1, p2, p3, pp, z, z1;
    
    /* Roots are symmetric in the interval so only need to find half of them  */
    m = floor((ng+1)/2.);
    
    // Loop over the desired roots */
    for(i=0;i<m;i++){
        
        /* Starting with the above approximation to the ith root */
        z  = cos( M_PI * (i+0.75)/(ng+0.5) );
        z1 = z + 1.0;
        
        /* Main loop of refinement by NEWTON'S method   */
        while(fabs(z-z1) > eps){
            /*  Recurrence relation to get the Legendre polynomial evaluated at z */
            p1 = 1.;
            p2 = 0.;
            for(j=1;j<=ng;j++){
                p3 = p2;
                p2 = p1;
                p1 = ((2*j-1) * z * p2 - (j-1)*p3) / j ;
            }
            
            /* p1 is now the desired Legendre polynomial. We next compute pp,
             its derivative, by a standard relation involving also p2, the
             polynomial of one lower order.      */
            pp = ng*(z*p1-p2)/(z*z-1.) ;
            z1 = z;
            
            /* Newton's Method  */
            z = z1 - p1/pp;
            
        }
        
        /* Roots will be bewteen -1.0 & 1.0 and symmetric about the origin   */
        xg[i]     = -z;
        xg[ng-i-1] =  z;

        /* Compute the weight and its symmetric counterpart */
        wg[i] = 1.0/((1-z*z)*pp*pp);
        wg[ng-i-1] = wg[i];

    }
    
}
// -----------------------------------------------------------
