#include <array>
#include <vector>

struct Particle {
  std::array<double,3> velocity;
  std::array<double,3> position;
  int charge = -2;
};

int main(int argc, char** argv){
  std::vector<Particle> particles(1000);
  double d = 0.001; // step width

  // initialization
  for( Particle& particle : particles ){
    particle.position = {0,0,0};
    particle.velocity = {0,1,0};
  }

  while( true ) {
    // pusher
    for( Particle& particle : particles ){
      particle.position = { particle.velocity[0] * d, particle.velocity[1] * d, particle.velocity[2] *d };
    }
  }
    
  return 0;
}
