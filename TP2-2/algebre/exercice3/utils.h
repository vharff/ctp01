#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void show_matrix(int m, int n, double *M);
double dot(const int n, double [n], double[n]);
void store(const char *, const int n, const int nv, double wr[n], double vr[n][nv]);

void makeA(const int n, double *);
void get_all_evv(const int n, double[], const int nv, double[n], double[nv][n]);

void makeLDU(const int n, double[n-1], double[n], double[n-1]);
void get_target_evv(const int n, double[n-1], double[n], double[n-1], const int nv, double[nv], double[nv], double[nv][n]);


