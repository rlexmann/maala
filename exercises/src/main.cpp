#include <iostream>
#include <string>

#include <common.hpp>
#include <config.hpp>

#include <elimination.hpp>
#include <matrix.hpp>
#include <solver.hpp>
#include <twoPointBoundary.hpp>

using namespace maala;

int
main() {
   TRACE("Demo");

   auto Y = twoPointBoundarySecondDegreeSolver(ConstCoeff(1),
                                               ConstCoeff(0),
                                               ConstCoeff(0),
                                               LinearCoeff(125),
                                               0,
                                               0,
                                               1,
                                               0,
                                               4);
   Y.print();

#ifdef WIN32
   std::cout << std::endl << "Press Return to exit..." << std::endl;
   std::string input;
   std::getline(std::cin, input);
#endif

   return 0;
}
