#include <vector>

using namespace std ;

int main(){
  vector<double> a(1000);
  vector<double> b(1000);
  vector<double> c(1000);
  vector<double> d(1000);

  int NITER = 10000;
  int N = a.size();


  for(int r=0; r<NITER; ++r) {
    #pragma omp parallel for
    for(int i=0; i<N; ++i)
      a[i] = b[i] + c[i] * d[i];
  }

}
