#include <stdio.h>
#include <array>
#include <iostream>
#include <gsl/gsl_statistics.h>

int
main(void)
{
  std::array<double,5> values = {17.2, 18.1, 16.5, 18.3, 12.6};

  double mean     = gsl_stats_mean(values.data(), 1, 5);
  double variance = gsl_stats_variance(values.data(), 1, 5);
  double largest  = gsl_stats_max(values.data(), 1, 5);
  double smallest = gsl_stats_min(values.data(), 1, 5);

  std::cout << "the dataset is ";
  for( double& value : values ){
    std::cout << value << " ";
  }
  std::cout << std::endl;
  
  std::cout << "The sample mean is " <<  mean << std::endl;
  std::cout << "The estimated variance is " << variance << std::endl;
  std::cout << "The largest value is " << largest << std::endl;
  std::cout << "The smallest value is " << smallest << std::endl;
  return 0;
}
