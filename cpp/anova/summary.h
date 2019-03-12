///////////////////////////////////////////////////////////////////////
//summary.h
#ifndef SUMMARY_H
#define SUMMARY_H
class Summary{
  int n;//sample size and number of variables
  double* pX;//pointer to data array
  
public:
  Summary(){pX = 0;}
  Summary(int N, double* pData){
    n = N;
    pX = pData;
  }	
  ~Summary(){delete[] pX;};//destructor
  void west(double* stat);
};
#endif


