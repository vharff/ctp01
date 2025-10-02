#include "constantes.h"

real rectangles(real (* f)(real), real a, real b, int n);
real trapezes  (real (* f)(real), real a, real b, int n);
real simpson   (real (* f)(real), real a, real b, int n);

int ng;
real *xg, *wg;
void init_gauss();
real gauss(real (*f)(real), real a, real b);
