//summary.cpp
#include "summary.h"
#include <cmath>

void Summary::west(std::array<double,2>& stat){

    double xbar = pX[0];
    double RSS = 0;
    for(int i=0; i< pX.size(); i++){
      auto e = pX[i];
      RSS += ((double)(i)/(double)(i+1))*(e - xbar)*(e - xbar);
      xbar += (1./(double)(i+1))*(e - xbar);
    }
    stat[0] = xbar;
    stat[1] = RSS/(double)(pX.size() - 1);
}


