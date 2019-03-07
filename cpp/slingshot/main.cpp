#include <array>
#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>

double length( std::array<double,3>& v ) {
  return sqrt( 
	v[0]*v[0] + 
	v[1]*v[1] +
	v[2]*v[2]
    );
}

struct Planet {
  std::array<double,3> position;
  std::array<double,3> velocity;
  double radius;
  double mass;

  void print(std::ofstream& out){
    out << position[0] << " " << position[1] << " " << radius << std::endl;
  }
};

struct Spacecraft {
  std::array<double,3> position;
  std::array<double,3> velocity;

  void print(){
    auto speed = length(velocity);
    std::cout << position[0] << " " << position[1] << " " << speed << std::endl;
  }
};

double calculate_distance(const Planet& p, const Spacecraft& s){
  std::array<double,3> v = { 
    p.position[0] - s.position[0],
    p.position[1] - s.position[1],
    p.position[2] - s.position[2]
  };
  return length(v);
}

std::array<double,3> calculate_normalized_direction(const Planet& p, const Spacecraft& s){
  std::array<double,3> direction = { 
    p.position[0] - s.position[0],
    p.position[1] - s.position[1],
    p.position[2] - s.position[2]
  };
  double l = length(direction);
  direction[0] /= l;
  direction[1] /= l;
  direction[2] /= l;
  return direction;
}

double calculate_acceleration(const Planet& p, const Spacecraft& s){
  double distance = calculate_distance( p , s );
  return (6.673E-11*p.mass)/(distance*distance);
}

struct Simulation {
  std::vector<Planet> planets;
  std::vector<Spacecraft> spacecrafts; 
  double time_step = 0.1;

  void run(){
    for (int i = 0; i < 10000; ++i){
      for( Spacecraft& spacecraft : spacecrafts ){
	for( Planet& planet : planets ){
	  auto nd = calculate_normalized_direction( planet , spacecraft );
	  double acceleration = calculate_acceleration( planet, spacecraft );
	  spacecraft.velocity = {
	    spacecraft.velocity[0] + nd[0] * acceleration * time_step,
	    spacecraft.velocity[1] + nd[1] * acceleration * time_step,
	    spacecraft.velocity[2] + nd[2] * acceleration * time_step
	  };
	}
      }
      
      push();  
      for( Spacecraft& spacecraft : spacecrafts ){
        spacecraft.print();
      }
    }
  }
  
  void push(){
    for( Spacecraft& spacecraft : spacecrafts ){
      spacecraft.position = { 
	spacecraft.position[0] + spacecraft.velocity[0] * time_step,
	spacecraft.position[1] + spacecraft.velocity[1] * time_step,
	spacecraft.position[2] + spacecraft.velocity[2] * time_step
      };
    }
    for( Planet& planet : planets ){
      planet.position = {
	planet.position[0] + planet.velocity[0] * time_step,
	planet.position[1] + planet.velocity[1] * time_step,
	planet.position[2] + planet.velocity[2] * time_step
      };
    }
  }

};


int main(int argc, char** argv){

  Planet earth;
  earth.position = { 0,0,0 };
  earth.mass = 5.98E24;
  earth.radius = 6380000;
  earth.velocity = { -10000 , 0, 0 };

  Spacecraft my_spacecraft;
  my_spacecraft.position = { 6'380'000-5000000, -10000000   , 0 }; // in meters 
  my_spacecraft.velocity = { 0        , 30000, 0 }; // in ...

  Simulation simulation;

  simulation.planets.push_back( earth );
  simulation.spacecrafts.push_back( my_spacecraft );

  simulation.run();

  std::ofstream out("planets.gp");
  for( Planet& planet : simulation.planets ){
    planet.print(out);
  }

  return 0;
}
