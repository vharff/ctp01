#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "constantes.h"
#include "fonction.h"
#include "methodes.h"

int n;

int main(void){
    
    // Cette routine fixe les variables globales:
    // - f: fonction a intégrer
    // - a, b: bornes d'integration
    choix(6);
    
    
    // Q4-Q8:
    printf("\nNewton-Cotes:\n");
    real rect,trap,simp;
    n = 10;
    rect = rectangles(f,a,b,n);
    trap = trapezes(f,a,b,n);
    simp = simpson(f,a,b,n);
    printf("n = %d\n    Rect (Err) : %lf (%lf)\n    Trapèzes (Err) : %lf (%lf)\n    Simpson (Err) : %lf (%lf)\n",n,rect,rect-exact,trap,trap-exact,simp,simp-exact);
    n = 100;
    rect = rectangles(f,a,b,n);
    trap = trapezes(f,a,b,n);
    simp = simpson(f,a,b,n);
    printf("n = %d\n    Rect (Err) : %lf (%lf)\n    Trapèzes (Err) : %lf (%lf)\n    Simpson (Err) : %lf (%lf)\n",n,rect,rect-exact,trap,trap-exact,simp,simp-exact);
        n = 1000;
    rect = rectangles(f,a,b,n);
    trap = trapezes(f,a,b,n);
    simp = simpson(f,a,b,n);
    printf("n = %d\n    Rect (Err) : %lf (%lf)\n    Trapèzes (Err) : %lf (%lf)\n    Simpson (Err) : %lf (%lf)\n",n,rect,rect-exact,trap,trap-exact,simp,simp-exact);
    
    FILE *fich;
    fich = fopen("integration.txt","w");
    for (int i = 2; i < 1e7 ; i*=2){
        rect = rectangles(f,a,b,i);
        trap = trapezes(f,a,b,i);
        simp = simpson(f,a,b,i);
        printf("%d\n",i);
        fprintf(fich,"%d %.20lf %.20lf %.20lf\n",i,rect,trap,simp);

    }


    

    // Q9 : Methode de Gauss-Legendre
/*    ng = 4;
    xg = (real*) malloc(ng*sizeof(real));
    wg = (real*) malloc(ng*sizeof(real));
    init_gauss();
    integ = gauss(f, a, b);
    free(xg);
    free(wg);
    printf("\nGauss-Legendre: \n");
    printf("%4d  %lf  %le \n \n",ng, integ, fabs(1. - integ/exact));
 */
 
    return EXIT_SUCCESS;
    
}
