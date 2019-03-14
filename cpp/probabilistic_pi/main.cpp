#include <iostream>
#include <random>
#include <iomanip>
#include <omp.h>

using namespace std; 
  
using large_int = unsigned long long int;
using large_double = long double;

int main() 
{ 
    large_int circle_points = 0;
    large_int square_points = 0; 
  
    // Initializing rand() 
  
    #pragma omp parallel reduction(+:circle_points) reduction(+:square_points)  
    for( int i = 0; i < 300 ; i++) {
	  std::mt19937 gen;
	  auto tid = omp_get_thread_num();
	  gen.seed(tid);
	  std::uniform_real_distribution<large_double> dis(0, 1);
	  #pragma omp for
	  for (large_int i = 0; i < 1000000000; i++) { 
	      // Randomly generated x and y values 
	      large_double rand_x = dis(gen); 
	      large_double rand_y = dis(gen); 
	
	      // Distance between (x, y) from the origin 
	      large_double origin_dist = sqrt(rand_x * rand_x + rand_y * rand_y); 
	
	      // Checking if (x, y) lies inside the define 
	      // circle with R=1 
	      if (origin_dist <= 1){ 
		circle_points++; 
	      }
	
	      // Total number of points generated 
	      square_points++;
	 }
         #pragma omp critical
	 {
	   double pi = (4.0 * (large_double)circle_points) / (large_double)square_points; 
	   cout << std::scientific << circle_points  << " " << square_points << " - " << pi << endl ; 
	 }
    }
    double pi = ((large_double)4.0 * (large_double)circle_points) / (large_double)square_points; 
    cout << std::scientific << circle_points  << " " << square_points << " - " << pi << endl ; 
    
  
  return 0; 
} 
