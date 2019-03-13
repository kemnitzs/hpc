#include <array>


int main(int argc, char** argv){
  std::array<double, 3> a;
  std::array<double, 2> b;

  a = b;
  return 0;
}
