
double f1(double x) ;
double df1(double x) ;
double d2f1(double x) ;

double f2(double x) ;
double df2(double x) ;
double d2f2(double x) ;

double fL1(double x) ;
double dfL1(double x) ;

double NR(double (*fin)(double),double (*df)(double),double , int, double eps, int *, long double[]) ;
double halley(double (*fin)(double),double (*df)(double),double (*d2f)(double),double , int, double eps, int *, long double[]) ;

