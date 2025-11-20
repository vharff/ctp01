//==================================================================================================
// This file contains the constants that describes the physical setup of the program.
// It also contains a function to compute the analytical solution.
//==================================================================================================

#include<math.h>


double const C = 1.0;     // Advection velocity
double const xmin=0.0;    // left space limits
double const xmax=1.0;    // right space limits
double const k=1.0;       // Wave vector

//--------------------------------------------------------------------------------------------------
double yexact(double x, double t)
// This function returns the analytical solution corresponding to
// - various initial conditions
// - periodic boundarry condtions
// At t=0, this fonction provides the initial condition.
// ARGUMENTS:
//   x (real): the spatial coordinate
//   t (real): time
// OUTPUTS:
//   y: the initial function
//--------------------------------------------------------------------------------------------------
{
    double z,y;
    int k=1;
    double L = xmax-xmin;

    // Sinus
    z = x-xmin-C*t;
    z = z - L * (int) floor((z-xmin)/L);
    y = sin(2*M_PI*k*z/L) ;

    // Creneau
    //  if (z < 0.2){y = 1;}
    //  else {y=0;}

    // Gaussienne
    //  z = z-L/2.0;
    //  y = exp(-z*z/(2*0.02*0.02));
    
    
    return y;
}
//--------------------------------------------------------------------------------------------------

