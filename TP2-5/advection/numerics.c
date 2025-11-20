//===================================================================================================
// This file contains the constants that describes the numerical setup of the program.
// It also contains routines to build the space and time grids and to free them.
//===================================================================================================

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "physics.h"

// SPACE PROPERTIES ------------------------
int nx;          // number of spatial grid points
double dx;       // spatial step
double *x=NULL;  // spatial grid

// TIME PROPERTIES -------------------------
double cfl;      // CFL parameter
double dt;       // time step
double tmax;     // Max integration time
int nt;          // number of time steps
double *t=NULL;  // time grid



//---------------------------------------------------------------------------------------------------
double get_param(char *name, double val){
//---------------------------------------------------------------------------------------------------
// This routine reads the parameter file, finds and retuns the value of a given parameter
// Arguments:
//  - name (str): string of the paremeter name as referenced in the parameter file
//  - val (real): default parameter value in case no value found in file
// Output:
//  - parameter value
//---------------------------------------------------------------------------------------------------

    int i,j;
    double x;
    FILE *fich=fopen("param.txt","r");
    char tmp[100];
    char str[8]; for(i=0;i<9;i++){str[i]=' ';}

    // Find line starting with parameter nam
    fgets(tmp, 100,fich);
    while(!feof(fich) && strncmp(tmp,name,sizeof(*name))){fgets(tmp, 1000,fich);}
    if (feof(fich)){
        printf("Parameter not found in parameter file: %s \n",name);
        printf("               => Using default value: %lf\n",val);
        return val;
    }

    // Find "=" character
    i=0;
    while(tmp[i++]!='=' && tmp[i]!='\n'){}
    if(tmp[i]=='\n'){
        printf("Equal sign not found in parameter file for parameter: %s \n",name);
        printf("                              => Using default value: %lf\n",val);
        return val;
    }

    // Get value
    j=0;
    while(tmp[i]==' '){i++;}
    while(tmp[i]!=' ' && tmp[i]!='\n'){str[j]=tmp[i];j++;i++;}
    
    // convert string to numerical float
    x = atof(str);
    
    fclose(fich);
    
    return x;
    
//---------------------------------------------------------------------------------------------------
}
//---------------------------------------------------------------------------------------------------



//---------------------------------------------------------------------------------------------------
void setup_grids()
//---------------------------------------------------------------------------------------------------
// This routine reads the parameter file with (nx,cfl,tmax) and builds the x and t arrays
// Arguments: None
//---------------------------------------------------------------------------------------------------
{
    
    int i;

    // Get parameter values from file -----------------------------------
    nx   = (int) get_param("nx",64);
    cfl  = get_param("cfl",0.95);
    tmax = get_param("tmax",1.0);

    // setup grids ------------------------------------------------------
    dx=(xmax-xmin)/nx;
    x = malloc(nx*sizeof(double));
    for(i=0;i<nx;i++){x[i] = xmin+i*dx;}

    dt = cfl * dx/C;
    nt = (int)ceil(tmax/dt);
    t = malloc((nt+1)*sizeof(double));
    for(i=0;i<nt+1;i++){t[i]=i*dt;}


    // Display some information on the run -----------------------------
    printf("-------------------------------------------------\n");
    printf("Solving the diffusion equation for:\n");
    printf("nx   = %10i\n",nx);
    printf("dx   = %10.3e\n",dx);
    printf("CFL  = %10.3e\n",cfl);
    printf("nt   = %10i\n",nt);
    printf("dt   = %10.3e\n",dt);
    printf("tmax = %10.3e\n",t[nt]);

//---------------------------------------------------------------------------------------------------
}
//---------------------------------------------------------------------------------------------------



//---------------------------------------------------------------------------------------------------
void finish_grids(){
//---------------------------------------------------------------------------------------------------
// This routine deallocates the grids
// Arguments: None
//---------------------------------------------------------------------------------------------------

free(t);
free(x);

//---------------------------------------------------------------------------------------------------
}
//---------------------------------------------------------------------------------------------------
