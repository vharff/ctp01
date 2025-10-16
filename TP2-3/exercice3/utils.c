#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "utils.h"

double *xdata, *ydata, *dydata;
int ndata;
int ndim=2;

// -------------------------------------------------------
void read_data(){
// This routine reads the Supernovae data file and builds
// the corresponding arrays
// Distances are converted to c/H0 units
// -------------------------------------------------------

    const double clight = 299792.4585; // speed of light in km/s
    const double H0100 = 100.;         // 100 km/s/Mpc (used to normalize Hubble)
    FILE *fich = fopen("sndata.txt","r");
    int i;

    // get number of data points
    fscanf(fich,"%d", &ndata);
    
    xdata  = (double *) malloc(ndata*sizeof(double));
    ydata  = (double *) malloc(ndata*sizeof(double));
    dydata = (double *) malloc(ndata*sizeof(double));

    // read data points
    for(i=0;i<ndata;i++){
        fscanf(fich, "%lf  %lf  %lf", &xdata[i], &ydata[i], &dydata[i] );
    }

    // convert distances to c/H0 units
    for(i=0;i<ndata;i++){
        ydata[i]  = ydata[i] / (clight/H0100);
        dydata[i] = dydata[i] / (clight/H0100);
    }
    fclose(fich);

  
}
// -------------------------------------------------------



// -----------------------------------------------------
double model(double z, double params[ndim]){
    // Luminosity distance as a function of redshift z and
    // parameters params = (h, Omega_m).

    double d;
    
    // ============================
    //        CHANGE HERE
    d=0;
    // ============================

    return d;
}
// -----------------------------------------------------

// -----------------------------------------------------
void gradmodel(double z, double params[ndim], double g[ndim]){
    // Computes the gradient of the uminosity distance as a
    // function of redshift z and parameters params = (h, Omega_m).
    // the gradient is returned as an argument array "g"

    // ============================
    //        CHANGE HERE
    g[0]=0; g[1]=0;
    // ============================

}
// -----------------------------------------------------


// -----------------------------------------------------
void storemodel(double params[ndim]){
    // Write to file an array of redshift-distance for a
    // given set of parameters params = (h,Omega_m)
    
    const int n=100;
    int i;
    double xmin, xmax, dx, x;
    xmin = 0;
    xmax = 0.6;
    dx = (xmax-xmin)/(n-1.);

    FILE *fich=fopen("model.txt", "w");
    for(i=0;i<ndim;i++){fprintf(fich,"%lf  ",params[i]);}; fprintf(fich, "\n");
    for(i=0;i<n;i++){
        x = xmin+i*dx;
        fprintf(fich,"%lf  %lf  \n",x, model(x,params));
    }
    fclose(fich);
}
// -----------------------------------------------------


// -----------------------------------------------------
double chi2(double X[ndim]){
    // Compute the chi2 of model 'dist' and data (xdata,
    // ydata, dydata)
    double c2=0.;
    int i;
    for(i=0;i<ndata;i++){
        c2 += pow((model(xdata[i],X)-ydata[i])/dydata[i],2);
    }
    return c2;
}
// -----------------------------------------------------


// -----------------------------------------------------
void gradchi2(double params[ndim], double g[ndim]){
// -----------------------------------------------------
    // Computes the gradient of the chi2 with respect to
    // the parameters params=(h,Omega_m) for a given value
    // of theese parameters.
    // the gradient is returned as an argument array 'g'
    
    
    // ============================
    //        CHANGE HERE
    g[0]=0; g[1]=0;
    // ============================

}
// -----------------------------------------------------
