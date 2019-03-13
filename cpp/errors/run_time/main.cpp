
#include <vector>

int main(int argc, char** argv){
  
  std::vector<double> v(100);
  v[100] = 10;

  int* a = nullptr;
  int b = *a;

  return 0;
}
