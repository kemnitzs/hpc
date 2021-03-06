// anovaMPI.cpp
#include <array>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include "mpi.h"
#include <cmath>
#include <sstream>
#include "summary.h"

using std::cout;
using std::endl;
using std::ifstream;

int main(int argc, char** argv) {
  std::array<std::vector<double>, 4> pData;

  MPI_Init(&argc, &argv);

  int my_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  int number_of_processors;
  MPI_Comm_size(MPI_COMM_WORLD, &number_of_processors);
  int values_per_line = atoi(argv[1]);

  std::array<double, 2> stat;

  if (my_rank == 0) {

    // processor 0 reads all the data in
    ifstream fIn(argv[2]);
    for (int j = 0; j < number_of_processors; j++) {
      pData[j].resize(values_per_line);
      std::string line;
      getline( fIn, line );
      std::stringstream sstr(line);
      for (int i = 0; i < values_per_line; i++) {
	sstr >> pData[j][i];
      }
    }

    fIn.close();

    // send data to all other processors
    for (int i = 1; i < number_of_processors; i++) {
      for( auto& e : pData[i] ){
	std::cout << e << " ";
      }
      std::cout << std::endl;
      MPI_Send(pData[i].data(), pData[i].size(), MPI_DOUBLE, i, 0,
	       MPI_COMM_WORLD);
    }
    Summary mySummary(pData[0]);
    double sum = 0 ;
    for( auto& e : pData[0] ){
      sum += e;
    }
    sum /= pData[0].size();
    double vsum = 0;
    for( auto& e : pData[0] ){
      vsum += pow(e - sum,2);
    }
    double rsq = (1.0 / (pData[0].size())) * vsum; 
    vsum = (1.0 / (pData[0].size()-1)) * vsum;
    
    std::cout << "sum " << sum  << std::endl;
    std::cout << "vsum " << vsum << std::endl;
    std::cout << "rsq " << rsq << std::endl;
    
    mySummary.west(stat);
    cout << "For processor " << my_rank << " the mean and variance are "
	 << stat[0] << " and " << stat[1] << endl;

    double num = 0;
    double xBar = stat[0];
    double den = ((double)(values_per_line - 1)) * stat[1];

    for (int i = 1; i < number_of_processors; i++) {
      MPI_Status status;
      MPI_Recv(stat.data(), stat.size(), MPI_DOUBLE, i, 1, MPI_COMM_WORLD,
	       &status);
      num += ((double)(i) / (double)(i + 1)) * (stat[0] - xBar) * (stat[0] - xBar);
      xBar = ((double)(i) / (double)(i + 1)) * xBar + stat[0] / ((double)(i + 1));
      den += ((double)(values_per_line - 1)) * stat[1];
    }
    num *= (double)values_per_line / ((double)(number_of_processors - 1));
    den /= (double)(number_of_processors * values_per_line - number_of_processors);
    cout << "The grand average is " << xBar << endl;
    cout << "The numerator mean square is " << num << " on "
	 << (number_of_processors - 1) << " degrees-of-freedom" << endl;
    cout << "The denominator mean square is " << den << " on "
	 << (values_per_line * number_of_processors - number_of_processors)
	 << " degrees-of-freedom" << endl;
    if (den != 0) {
      cout << "The F-ratio is " << (num / den) << endl;
    }
  } else { // all other ranks but 0
    std::vector<double> mypData(values_per_line);
    MPI_Status status;
    MPI_Recv(mypData.data(), mypData.size(), MPI_DOUBLE, 0, 0, MPI_COMM_WORLD,&status);
    for( auto& e : mypData ){
      std::cout << e << " ";
    }
    std::cout << std::endl;

    Summary mySummary(mypData);
    mySummary.west(stat);
    double sum = 0 ;
    for( auto& e : mypData ){
      sum += e;
    }
    sum /= mypData.size();
    double vsum = 0;
    for( auto& e : mypData ){
      vsum += pow(e - sum,2);
    }
    vsum = (1.0 / (mypData.size()-1)) * vsum;
    
    std::cout << "sum " << sum  << std::endl;
    std::cout << "vsum " << vsum << std::endl;
    
    cout << "For processor " << my_rank << " the mean and variance are "
	 << stat[0] << " and " << stat[1] << endl;
    MPI_Send(stat.data(), stat.size(), MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);
  }

  MPI_Finalize();

  return 0;
}
