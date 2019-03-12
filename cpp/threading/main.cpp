#include <thread>
#include <vector>

struct Simulation {
    void run(){
    }
};

int main(int argc, char** argv){
  std::vector<Simulation> simulations;
  simulations.push_back(Simulation()); 

  std::vector<std::thread> threads;

  for (int i = 0; i < simulations.size(); ++i){
    threads.emplace_back( [&](){ return simulations[i].run(); } );
  }

  for( std::thread& t : threads ){
    t.join();
  }

  return 0;
}
