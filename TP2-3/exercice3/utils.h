
extern double *xdata, *ydata, *dydata;
extern int ndata;
extern int ndim;

void read_data();
double dist(double z, double params[ndim]);
void gradmodel(double z, double params[ndim], double g[ndim]);
void storemodel(double params[ndim]);
double chi2(double X[ndim]);
void gradchi2(double params[ndim], double g[ndim]);
