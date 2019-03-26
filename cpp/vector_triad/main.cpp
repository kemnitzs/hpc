#include <vector>
#include <iostream>

using namespace std ;

int main(){
  int N = 1'000'000;
  vector<double> a(N);
  vector<double> b(N);
  vector<double> c(N);
  vector<double> d(N);

  int NITER = 100'000;

  std::cout << "memory used " << 4.0* N * sizeof(double)/1024/1024 << " MB" << std::endl;

  for(int r=0; r<NITER; ++r) {
    #pragma omp parallel for
    for(int i=0; i<N; ++i)
      a[i] = b[i] + c[i] * d[i];
  }

}
