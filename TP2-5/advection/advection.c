//==================================================================================================
// This program solves the advection equation.
// Some parameters are set at run time in file "param.txt"
// Results are stored in 'advection.txt'
// A dedicated python script is provided to read and plot the results
//==================================================================================================

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "physics.h"
#include "numerics.h"
#include "solvers.h"
void store(double y[nx], FILE *out_file);
void storex(double x[nx], FILE *out_file);
void error(double y[nx],double t);


//==================================================================================================
int main(){
//==================================================================================================

    int i,it;
    double *y=NULL,*yy=NULL;
    

    // Open output file, read parameter file and build grids ---------------
    FILE *out_file=fopen("advection.txt","w");
    setup_grids();
    y = malloc(nx*sizeof(double));
    yy = malloc(nx*sizeof(double));
    
    setup_CN(nx,cfl);

   
    for(i=0;i<nx;i++){
        y[i]=yexact(x[i],0);} // Q1
    

    // store initial conditions to file
    storex(x,out_file);
    store(y,out_file);


    // Solves EDP -----------------------------------------------------
    for(it=0;it<nt;it++){
        //Upwind(nx,y,cfl);

        //FTCS(nx,y,cfl);
        
        //LaxFriedrichs(nx,y,cfl);

        //BurgersLF(nx,y,cfl);

        CN(nx,y,cfl);
    }

    // Store final, and analytical solutions, display relative error --
    store(y,out_file);
    for(i=0;i<nx;i++){yy[i]=yexact(x[i],t[nt]);};  store(yy,out_file);
    error(y,t[nt]);


    // Deallocate arrays and close ouput file -------------------------
    free(y); free(yy);
    finish_grids();
    finish_CN();
    fclose(out_file);
    printf("-------------------------------------------------\n");

    return EXIT_SUCCESS;

//==================================================================================================
}
//==================================================================================================




//--------------------------------------------------------------------------------------------------
void store(double y[nx], FILE *out_file){
//--------------------------------------------------------------------------------------------------
// This routine writes data to file only after a given number of time steps have been performed.
// It adds a very last point for display purposes
// ARGUMENTS:
//   it (int):              index of the current time step
//   y (real*(nx+2)):       solution to store
//   out_file (fie lptr):  file where to write results
//---------------------------------------------------------------------------------------------------
    int i;
    for(i=0;i<nx;i++){fprintf(out_file,"%10.4e  ",y[i]);}
    fprintf(out_file,"%10.4e  ",y[0]);
    fprintf(out_file,"\n");

//--------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------



//--------------------------------------------------------------------------------------------------
void storex(double x[nx], FILE *out_file){
//--------------------------------------------------------------------------------------------------
// This routine writes data to file only after a given number of time steps have been performed.
// It adds a very last point for display purposes
// ARGUMENTS:
//   it (int):              index of the current time step
//   y (real*(nx+2)):       solution to store
//   out_file (fie lptr):  file where to write results
//--------------------------------------------------------------------------------------------------
    int i;
    for(i=0;i<nx;i++){fprintf(out_file,"%10.4e  ",x[i]);}
    fprintf(out_file,"%10.4e  ",xmax);
    fprintf(out_file,"\n");

//--------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------
void error(double y[nx],double t)
//--------------------------------------------------------------------------------------------------
// This routine computes the error between the numerical and analytical solutions at a given time,
// and at a quarter of the box.
// ARGUMENTS:
//   y (real*(nx+2)): array of numerical solution
//   t (real):        current time
//--------------------------------------------------------------------------------------------------
{
    int i;

    // index at the first quarter
    i = (int) (nx/4.0)-1;

    // display relative error
    printf("-------------------------------------------------\n");
    printf("Relative error: %12.4e\n",(1-y[i]/yexact(x[i],t)));

//--------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------



