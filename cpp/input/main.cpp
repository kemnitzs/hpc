#include <iostream>
#include <fstream>

void analysis(){
  std::cout << "implement the super complicated analyis code here" << std::endl;
}

int main(int argc, char** argv){
  
  std::ifstream in("run_analysis.txt");

  bool run_analysis = false;
  in >> run_analysis;

  if ( run_analysis == true ) {
    analysis( );
  }

  return 0;
}
