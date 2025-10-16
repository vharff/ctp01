#include "constants.h"
void init(double M, int n, double y[2*n+1]);
void solve(double M, int n, double y[2*n+1]);
void store(double M, int n, double y[2*n+1]);
void MR(int n);
void getFJ(double M, int n, double y[2*n+1], double F[2*n+1], double J[(2*n+1)*(2*n+1)]);
extern void dgesv_(int*, int*,double*, int*, int *, double*, int*, int*);
