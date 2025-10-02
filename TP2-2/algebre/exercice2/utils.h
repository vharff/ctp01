void show_matrix(int, int, double *);
void product(int, double *, double *, double *);

void make_system(int, double *, double *, double *);

double diff(int n, double *, double *);

void solve(int n, double *, double *, double *);

double cond(int, double *);

extern void dgemv_(const char*, const int *, const int *, const double *,
  const double[], const int *, const double[], const int *, const double *,
  double[], const int*);

