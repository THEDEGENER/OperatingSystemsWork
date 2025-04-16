#include <iostream>
#include <vector>
#include <string>


/*
  stack data structure
  the stack is a LIFO structure meaning its a first in last out creating a sort of vertical stack
  where items are pushed ontop of the stack and popped of the stack
*/


int main (int argc, char *argv[]) {
  std::vector<std::string> stack{};
  
  stack.push_back("Minecraft");
  stack.push_back("skyrim");

  std::cout << stack.size() << std::endl;
  return 0;
}
