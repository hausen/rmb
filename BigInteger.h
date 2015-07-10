#ifndef BIGINTEGER_H
#define BIGINTEGER_H
#include <iostream>
#include <stddef.h>

typedef unsigned int digit_t;

class BigInteger {
public:
  BigInteger(size_t ndigits, size_t radix);
  BigInteger(const BigInteger &other);
  ~BigInteger();
  digit_t operator[](size_t idx) const;
  bool next();
  bool isMaxInt();

private:
  digit_t *digits;
  size_t ndigits;
  size_t radix;

  friend std::ostream& operator<<(std::ostream&, const BigInteger&);
};

std::ostream& operator<<(std::ostream&, const BigInteger&);

#endif
