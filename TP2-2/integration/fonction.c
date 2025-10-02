#include <math.h>
#include<stdio.h>
#include "constantes.h"


real a , b  , exact;
real (*f)(real);

real test1(real x){
    return x*x+x+1; 
}

real test2(real x){
    return 0.; // A MODIFIER
}

real sinus(real x){return sin(x);}

real carre(real x){return x*x;}

real lineaire(real x){return x;}

real mystere(double x){return x*(1-x)*sin(200*x*(1-x))*sin(200*x*(1-x));}


void choix(int cas){
    // Choix de la fonction a integrer et des bornes
    switch(cas){
        case 1:
            // Cas de test 1: ????
            a=0; b=1; f=test1;
            exact = 11./6.; // A modifier
            break;
        case 2:
            // Cas de test 2: ???
            a=0; b=0; f=test2;
            exact = 0; // A modifier
            break;
        case 3:
            // Cas de tordu 3: x*x sur [0,1]
            a=0; b=1; f=carre;
            exact = 1./3.;
            break;
        case 4:
            // Cas de tordu 4: x sur [0,1]
            a=0; b=1; f=lineaire;
            exact = 1./2.;
            break;
        case 5:
            // Cas de test 5: sin sur [0,pi]
            a=0; b=M_PI; f=sinus;
            exact = 2;
            break;
        case 6:
            // Cas tordu 6: mystere sur [0,1]
            a=0; b=1; f=mystere;
            exact = 8.04977183346942e-2;
            break;
    }
    printf("\nIntegration de f entre %6.3f et %6.3f :  I =  %6.6f \n",a,b,exact);
}
