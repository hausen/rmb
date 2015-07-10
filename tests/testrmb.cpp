#include "../KRMB.h"

int main() {
  KRMB rmb(2,8);

  do {
    std::cout << rmb << std::endl;
  } while (rmb.next());
}
