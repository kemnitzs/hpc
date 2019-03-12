// anovaMPI.cpp
#include <cstdlib>
#include <fstream>
#include <iostream>
#include "mpi.h"
#include "summary.h"

using std::cout;
using std::endl;
using std::ifstream;

int main(int argc, char** argv) {
  double** pData;

  MPI_Init(&argc, &argv);

  int myRank;
  MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
  int nP;
  MPI_Comm_size(MPI_COMM_WORLD, &nP);
  int n = atoi(argv[1]);

  if (myRank == 0) {
    pData = new double*[nP];

    ifstream fIn(argv[2]);
    for (int j = 0; j < nP; j++) {
      pData[j] = new double[n];
      for (int i = 0; i < n; i++) {
	fIn >> pData[j][i];
      }
    }

    fIn.close();

    for (int i = 1; i < nP; i++) {
      MPI_Send(pData[i], n, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
    }
    Summary mySummary(n, pData[0]);
    double* stat = new double[2];
    mySummary.west(stat);
    cout << "For processor " << myRank << " the mean and variance are "
	 << stat[0] << " and " << stat[1] << endl;

    double num = 0;
    double xBar = stat[0];
    double den = ((double)(n - 1)) * stat[1];

    for (int i = 1; i < nP; i++) {
      MPI_Status status;
      MPI_Recv(stat, 2, MPI_DOUBLE, i, 1, MPI_COMM_WORLD, &status);
      num +=
	  ((double)(i) / (double)(i + 1)) * (stat[0] - xBar) * (stat[0] - xBar);
      xBar =
	  ((double)(i) / (double)(i + 1)) * xBar + stat[0] / ((double)(i + 1));
      den += ((double)(n - 1)) * stat[1];
    }
    num *= (double)n / ((double)(nP - 1));
    den /= (double)(nP * n - nP);
    cout << "The grand average is " << xBar << endl;
    cout << "The numerator mean square is " << num << " on " << (nP - 1)
	 << " degrees-of-freedom" << endl;
    cout << "The denominator mean square is " << den << " on " << (n * nP - nP)
	 << " degrees-of-freedom" << endl;
    if (den != 0) cout << "The F-ratio is " << (num / den) << endl;
  }

  else {
    double* mypData = new double[n];
    MPI_Status status;
    MPI_Recv(mypData, n, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);
    Summary mySummary(n, mypData);
    double* stat = new double[2];
    mySummary.west(stat);
    cout << "For processor " << myRank << " the mean and variance are "
	 << stat[0] << " and " << stat[1] << endl;
    MPI_Send(stat, 2, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);
  }

  MPI_Finalize();

  return 0;
}
