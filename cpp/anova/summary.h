///////////////////////////////////////////////////////////////////////
#include <vector>
#include <array>

//summary.h
#ifndef SUMMARY_H
#define SUMMARY_H
class Summary{
  std::vector<double>& pX; 
  
public:
  Summary(std::vector<double>& pData): 
    pX(pData)
  {
  }	
  void west(std::array<double,2>& stat);

};
#endif


