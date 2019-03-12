//summary.cpp
#include "summary.h"
#include <cmath>

void Summary::west(double* stat){

    double xbar = pX[0];
    double RSS = 0;
    for(int i=0; i< n; i++){
      RSS += ((double)(i)/(double)(i+1))*(pX[i] - xbar)*(pX[i] - xbar);
      xbar += (1./(double)(i+1))*(pX[i] - xbar);
    }
    stat[0] = xbar;
    stat[1] = RSS/(double)(n - 1);
}


