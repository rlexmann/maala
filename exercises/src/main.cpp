#include <iostream>
#include <string>

#include <chapters.hpp>
#include <config.hpp>

int
main()
{
  exChapter1();

#ifdef WIN32
  std::cout << std::endl << "Press Return to exit..." << std::endl;
  std::string input;
  std::getline(std::cin, input);
#endif

  return 0;
}