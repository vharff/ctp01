#include <stdio.h>
#include <math.h>
const double EulerConstant = exp(1.0);
typedef double real;
void func(real x0, real mu); 
void f2();
void f4();
double ex4_f(double x);
double ex4_dfdx1(double x, double dx);
void main(){
    real x0 = 0.11;
    real mu = 3.9;

    f4();
    // func(x0,mu);
}

void f2(){
    real xn;
    real yn;
    real gamma;
    real p;
    FILE *fich;
    fich = fopen("fich21.txt","w");
    p = 0.11;
    while(p<1e9){
        gamma = sqrt(p*p+1);
        xn = gamma - p;
        yn = 1/(gamma+p);
        fprintf(fich,"%le %le %le %le \n",p,xn,yn,xn-yn);
        p = 2*p;
    }
    fclose(fich);
}

void f4(){
    double xn;
    double yn,zn,un,vn;
    double gamma;
    double dx;
    double x =1;

    FILE *fich;
    fich = fopen("fich41.txt","w");
    dx = 1.0;
    for(dx = 1.0; dx > 1e-12; dx = dx/1.1){
        xn = ex4_dfdx1(x,dx);
        yn = (ex4_f(x)-ex4_f(x-dx))/dx;
        zn = (ex4_f(x+dx)-ex4_f(x-dx))/2/dx;
        un = (-ex4_f(x+2*dx)+8*ex4_f(x+dx)-8*ex4_f(x-dx)+ex4_f(x-2*dx))/12/dx;
        vn = (ex4_f(x+2*dx)+5*ex4_f(x+dx)-5*ex4_f(x-dx)-ex4_f(x-2*dx))/14/dx;
        fprintf(fich,"%le %le %le %le %le %le \n",dx,xn-ex4_f(x),yn-ex4_f(x),zn-ex4_f(x),un-ex4_f(x),vn-ex4_f(x));
    }
    fclose(fich);
}

double ex4_f(double x){
    return(pow(EulerConstant,x));
}

double ex4_dfdx1(double x, double dx){
    double res =  ex4_f(x+dx)-ex4_f(x);
    return(res/dx);
}


void func(real x0,real mu){
    real xn = x0;
    real yn = 0.11;
    int n;
    FILE *fich;
    fich = fopen("fich3.txt","w");
    for(n=0;n<150;n=n+1){
        xn = mu*xn*(1-xn);
        yn = mu*yn - mu*(yn*yn) ;
        fprintf(fich,"%i %le %le %le \n",n,xn,yn,xn-yn);
    }
    fclose(fich);
    

}