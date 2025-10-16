#include<stdio.h>
#include<math.h>

// -----------------------------------------------------
int descent_const(int ndim, void (*gradf)(double X[ndim], double g[ndim]), double X[ndim] , double alpha, double eps, int nmax){
    // This function minimizes a given fonction using the gradient
    // descent with constant coefficient
    //  - grad(X) (input):
    //      a function that returns the gradient of the
    //      minimized function for a given set X of parameters
    // - X (input and output):
    //      array with the initial parameter guess in input,
    //      solution with optimal parameters in output
    // - alpha (input):
    //      Descent coefficient
    // - eps (input):
    //      tolerance for convergence
    // - nmax (input):
    //       maximal number of iterations
    // - iter (returned):
    //       number of iterations performed
    // -----------------------------------------------------
    
    
    int iter=0;

    // ============================
    //        CHANGE HERE
    // ============================
    
    return iter;
    
}
// -----------------------------------------------------





// -----------------------------------------------------
int descent_BB(int ndim, void (*gradf)(double X[ndim], double g[ndim]), double X[ndim] , double alpha0, double eps, int nmax){
    // This function minimizes a given fonction using the
    // Barzilai-Borwein method
    //  - grad(X) (input):
    //      a function that returns the gradient of the
    //      minimized function for a given set X of parameters
    // - X (input and output):
    //      array with the initial parameter guess in input,
    //      solution with optimal parameters in output
    // - alpha (input):
    //      Descent coefficient
    // - eps (input):
    //      tolerance for convergence
    // - nmax (input):
    //       maximal number of iterations
    // - iter (returned):
    //       number of iterations performed
    // -----------------------------------------------------
        
    int iter=0;
    
    // ============================
    //        CHANGE HERE
    // ============================

    
    return iter;
    
    
}
// -----------------------------------------------------
