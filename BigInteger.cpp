#include "BigInteger.h"
#include <assert.h>
#include <string.h>

BigInteger::BigInteger(size_t ndigits, size_t radix)
{
  this->ndigits = ndigits;
  this->digits = new digit_t[ndigits]();
  this->radix = radix;
}

BigInteger::BigInteger(const BigInteger &other)
 : ndigits(other.ndigits), radix(other.radix)
{
  this->digits = new digit_t[ndigits];
  memcpy(this->digits, other.digits, ndigits*sizeof(digit_t));
}

BigInteger::~BigInteger() {
  delete[] digits;
}

digit_t BigInteger::operator[](size_t idx) const {
  assert(idx < ndigits);
  return digits[idx];
}

bool BigInteger::isMaxInt() {
  for (size_t i = 0; i < ndigits; ++i) {
    if (digits[i] != radix-1) {
      return false;
    }
  }
  return true;
}

bool BigInteger::next() {
  if (isMaxInt()) {
    return false;
  }

  for (size_t i = 0; i < ndigits; ++i) {
    digits[i] += 1;
    if (digits[i] < radix) {
      break;
    } else {
      digits[i] = 0;
    }
  }

  return true;
}

std::ostream& operator<<(std::ostream& os, const BigInteger& bi) {
  for (int i=bi.ndigits-1; i>=0; --i) {
    os << bi.digits[i];
  }
  return os;
}

