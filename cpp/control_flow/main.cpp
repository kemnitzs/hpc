#include <iostream>
void print_hello_world(){
  std::cout << "Hello World" << std::endl;
}
int main(int argc, char** argv) {
  std::cout << "hello world or meow? h|m" << std::endl;
  char answer;
  std::cin >> answer;

  if ( answer == 'h' ) {
    print_hello_world();
  }else if ( answer == 'm' ) {
    std::cout << "meow" << std::endl;
  }else{
      return -1;
  }
  return 0;
}
