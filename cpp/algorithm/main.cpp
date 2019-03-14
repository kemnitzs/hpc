#include <algorithm>
#include <vector>
#include <random>
#include <iostream>

int main(int argc, char** argv){
  std::vector<double> v(10);

  std::mt19937 gen;
  std::uniform_real_distribution<> dis(0, 1);
  auto rand = [&](){
    return dis(gen);
  };

  // put a random number in each element of the container
  std::generate( std::begin(v), std::end(v), rand );

  std::cout << "random vector:" << std::endl;  
  for( double& e : v ){
    std::cout << e << std::endl;
  }

  // sort the vector  
  std::sort( std::begin(v), std::end(v) );

  std::cout << "sorted vector:" << std::endl;  
  for( double& e : v ){
    std::cout << e << std::endl;
  }

  return 0;
}
