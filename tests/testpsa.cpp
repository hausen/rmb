#include "../PermutationStatus.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "Usage: testpsa maxrank" << std::endl;
    return 1;
  }
  std::cout << "PermutationStatus has " << sizeof(PermutationStatus)
            << " bytes" << std::endl;
  int maxrank = atoi(argv[1]);
  PermutationStatusArray psa(maxrank);
  for (int i=0; i<=maxrank; ++i) {
    PermutationStatus status;
    switch(i%4) {
      case 0: status = Unvisited; break;
      case 1: status = PreviousLevel; break;
      case 2: status = CurrentLevel; break;
      case 3: status = NextLevel; break;
    }
    psa.set(i, status);
  }

  for (int i=0; i<=maxrank; ++i) {
    PermutationStatus ps = psa.get(i);
    switch(ps) {
    case Unvisited:
      std::cout << i << ": unvisited" << std::endl;
      break;
    case PreviousLevel:
      std::cout << i << ": previous level" << std::endl;
      break;
    case CurrentLevel:
      std::cout << i << ": current level" << std::endl;
      break;
    case NextLevel:
      std::cout << i << ": next level" << std::endl;
      break;
    default:
      int n = 0;
      memcpy(&n, &ps, sizeof(PermutationStatus));
      std::cout << i << ": ERROR " << n << std::endl;
    }
  }
}
