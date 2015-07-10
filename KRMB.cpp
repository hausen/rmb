#include "KRMB.h"
#include <assert.h>

KRMB::KRMB(size_t k, size_t nelmts)
 : param(2*k+2, nelmts), k(k), nelmts(nelmts)
{
  assert(k > 0);
  assert(nelmts >= k);
  next();
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

int KRMB::getA() const
{
  return param[0]+1;
}

int KRMB::getB() const
{
  return param[2*k+1]+1;
}

int KRMB::getC(int i) const
{
  return param[2*i-1]+1;
}

int KRMB::getD(int i) const
{
  return param[2*i]+1;
}

bool KRMB::next()
{
  while (param.next())
  {
    if (parametersAreValid())
    {
      return true;
    }
  }
  return false;
}

void KRMB::applyTo(Permutation &p)
{
  for (size_t i = 1; i <= k; ++i)
  {
    int ci = param[2*i-1]+1;
    int di = param[2*i]+1;
    if (ci < di) {
      p.applyReversal(ci, di);
    }
  }
  int a = param[0]+1;
  int b = param[2*k+1]+1;
  if (a < b) {
    p.applyReversal(a, b);
  }
}

bool KRMB::parametersAreValid()
{
  int a = param[0];
  int b = param[2*k+1];
  if (b-a+1 < (int)k) {
    return false;
  }

  int lastDi = a-1;
  for (size_t nblock = 1; nblock <= k; ++nblock)
  {
    int ci = param[2*nblock-1];
    int di = param[2*nblock];
    bool valid = (lastDi < ci) && (ci <= di);
    if (!valid)
      return false;
    lastDi = di;
  }
  int dk = param[2*k];
  return (dk <= b);
}

std::ostream& operator<<(std::ostream &os, const KRMB &rmb)
{
  os << "rmb(" << rmb.param[0]+1 << "," << rmb.param[2*rmb.k+1]+1;
  for (size_t i = 1; i <= rmb.k; ++i) {
    os << " ; " << rmb.param[2*i-1]+1 << "<>" << rmb.param[2*i]+1;
  }
  os << ")";

  return os;
}
