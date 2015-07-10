#include "../PermutationArray.h"
#include <stdlib.h>

int main(int argc, char *argv[])
{
  int n = argc-3;
  if (n < 1) {
    std::cerr << "Wrong parameters!" << std::endl;
    return 1;
  }
  int i = atoi(argv[1]);
  int j = atoi(argv[2]);
  int *elmts = new int[n];

  for (int i=3; i<argc; ++i) {
    elmts[i-3] = atoi(argv[i]);
  }

  PermutationArray p(elmts, n);

  p.print(std::cout);
  std::cout << std::endl;

  p.applyReversal(i,j);
  std::cout << "r(" << i << "," << j << ")" << std::endl;

  p.print(std::cout);
  std::cout << std::endl;

}
