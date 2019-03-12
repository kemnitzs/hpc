#include <vector>
#include <iostream>
#include <omp.h>

struct Simulation {
    void run(){
      // TODO add long running code here
      int my_tid = omp_get_thread_num();
#pragma omp critical
      std::cout << "my tid " << my_tid << std::endl;
    }   
};

int main(int argc, char** argv){
  std::vector<Simulation> simulations;
  simulations.push_back(Simulation()); 
  simulations.push_back(Simulation()); 
  simulations.push_back(Simulation()); 
  simulations.push_back(Simulation()); 
  simulations.push_back(Simulation()); 
  simulations.push_back(Simulation()); 

  #pragma omp parallel for
  for (int i = 0; i < simulations.size(); ++i){
    simulations[i].run();
  }

  return 0;
}
