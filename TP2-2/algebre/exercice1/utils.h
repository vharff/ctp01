void show_matrix(int, int, double *);

double* makeA(int, int);
double* makeB(int, int);

void check(int, int, int, double *);

void product(int, int, int, double *, double *, double *);

extern void dgemm_(const char*, const char*, const int*, const int*, const int*,
const double*, double *, const int*, double *, const int *,
const double*, double*, const int*);