#include "KRMB.h"
#include <assert.h>

KRMB::KRMB(size_t k, size_t nelmts)
 : param(k, nelmts), k(k), nelmts(nelmts)
{
  assert(k > 0);
  assert(nelmts >= k);
}

KRMB::KRMB(const KRMB &other)
 : param(other.param), k(other.k), nelmts(other.nelmts)
{
}

KRMB::~KRMB()
{
}

int KRMB::getK() const
{
  return (int)k;
}

int KRMB::getN() const
{
  return (int)nelmts;
}

int KRMB::getA() const
{
  return param.a;
}

int KRMB::getB() const
{
  return param.b;
}

int KRMB::getC(int i) const
{
  return param.c[i];
}

int KRMB::getD(int i) const
{
  return param.d[i];
}

bool KRMB::next()
{
  return param.next();
}

void KRMB::applyTo(Permutation &p)
{
  for (size_t i = 1; i <= k; ++i)
  {
    if (param.c[i] < param.d[i]) {
      p.applyReversal(param.c[i], param.d[i]);
    }
  }
  if (param.a < param.b) {
    p.applyReversal(param.a, param.b);
  }
}

std::ostream& operator<<(std::ostream &os, const KRMB &rmb)
{
  os << "rmb(" << rmb.param.a << "," << rmb.param.b;
  for (size_t i = 1; i <= rmb.k; ++i) {
    os << " ; " << rmb.param.c[i] << "<>" << rmb.param.d[i];
  }
  os << ")";

  return os;
}
