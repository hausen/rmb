#include <iostream>
#include "../KRMBParam.h"

int main() {
  size_t k = 2, n = 9;
  KRMBParam rmb(k,n);

  do {
    std::cout << "rmb(" << rmb.a << "," << rmb.b;
    for (size_t i=1; i<=k; ++i) {
      std::cout << " ; " << rmb.c[i] << "<>" << rmb.d[i];
    }
    std::cout << ")" << std::endl;
  } while (rmb.next());
}
