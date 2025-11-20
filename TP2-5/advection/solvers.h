void Upwind(int nx, double y[nx+2], double cfl);
void FTCS(int nx, double y[nx+2], double cfl);
void LaxFriedrichs(int nx, double y[nx+2], double cfl);
void BurgersLF(int nx, double y[nx+2], double cfl);

extern double *a,*b,*c;
void setup_CN(int nx, double cfl);
void CN(int nx, double y[nx+2],double cfl);
void finish_CN();
void tridag(int n, double a[n-1], double b[n], double c[n-1],double r[n]);
