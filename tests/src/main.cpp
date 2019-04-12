#include <iostream>
#include <string>

#include <config.hpp>
#include <tests.hpp>

int
main() {
   testSuite1();
   testSuite2();

#ifdef WIN32
   std::cout << std::endl << "Press Return to exit..." << std::endl;
   std::string input;
   std::getline(std::cin, input);
#endif

   return 0;
}
