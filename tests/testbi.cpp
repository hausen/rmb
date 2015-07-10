#include "../BigInteger.cpp"

using namespace std;

int main() {
  BigInteger bi(3, 10);
  cout << bi[2] << endl;
  
  do {
    std::cout << bi << std::endl;
  } while (bi.next());

  cout << bi[2] << endl;
}
