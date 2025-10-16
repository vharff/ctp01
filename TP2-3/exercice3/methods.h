
int descent_const(int ndim, void (*gradf)(double X[ndim], double g[ndim]), double X[ndim] , double alpha, double eps, int nmax);

int descent_BB(int ndim, void (*gradf)(double X[ndim], double g[ndim]), double X[ndim] , double alpha, double eps, int nmax);
