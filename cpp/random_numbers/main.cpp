#include <random>
#include <iostream>
#include <chrono>
 
int main()
{
    std::mt19937 gen; // standard mersenne_twister_engine
    gen.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());

    std::uniform_real_distribution<double> dis(0.0, 20.0);
    for (int n = 0; n < 10; ++n) {
        std::cout << dis(gen) << ' ';
    }
    std::cout << std::endl;
}
