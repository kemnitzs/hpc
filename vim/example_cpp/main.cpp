#include <iostream>
#include <vector>

struct MyStructure {
    int a;
    int b;
};

int main(int argc, char** argv){
    MyStructure ms;

    ms.a;

    std::vector<double> v;

    for( auto& e : v ){
       e = 10; 
    }
    
    return 0;
}
