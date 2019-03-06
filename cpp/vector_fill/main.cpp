#include <random>
#include <iostream>
#include <chrono>

int main()
{
    std::mt19937 gen; // standard mersenne_twister_engine
    gen.seed(std::chrono::high_resolution_clock::now()
        .time_since_epoch().count());
        
    std::vector<int> my_vector(10,0);

    std::uniform_int_distribution<int> dis(0, my_vector.size()-1);
    
    for (int n = 0; n < 10000; ++n) {
        my_vector[dis(gen)]++;
    }
    
    for( int e : my_vector){
        std::cout << e << std::endl;
    }
}
