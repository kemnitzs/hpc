#include <vector>

int main(int argc, char** argv){
  int a = 0 ;

  std::vector<double> v(100,0);

  v[-1] = 10;

  return 0;
}
