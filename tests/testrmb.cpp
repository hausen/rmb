#include "../KRMB.h"

int main() {
  KRMB rmb(2,9);

  do {
    std::cout << rmb << std::endl;
  } while (rmb.next());
}
