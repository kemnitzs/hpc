#include <boost/mpi.hpp>
#include <iostream>
#include <string>
#include <boost/serialization/vector.hpp>
namespace mpi = boost::mpi;

int main()
{
  mpi::environment env;
  mpi::communicator world;

  // create a vector that holds 4GB of data 
  std::vector<double> large;

  if (world.rank() == 0) {
    large.resize(4l*1024l*1024l*1024l/sizeof(double));
    world.send(1, 0, large);
    large.resize(0);
    large.shrink_to_fit();
  } else {
    world.recv(0, 0, large);
    std::cout << "large hold " << large.size()*sizeof(double)/1024/1024/1024 << " GB" << std::endl;
  }

  return 0;
}
