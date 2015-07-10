#include "KRMBParam.h"
#include <string.h>

KRMBParam::KRMBParam(size_t k, size_t n)
{
  this->k = k;
  this->n = n;
  this->c = new param_t[k+1]();
  this->d = new param_t[k+1]();
  reset();
}

KRMBParam::KRMBParam(const KRMBParam &other)
{
  this->k = other.k;
  this->n = other.n;
  this->a = other.a;
  this->b = other.b;
  this->c = new param_t[k+1]();
  this->d = new param_t[k+1]();
  memcpy(c, other.c, (k+1)*sizeof(param_t));
  memcpy(d, other.d, (k+1)*sizeof(param_t));
}

KRMBParam::~KRMBParam()
{
  delete this->c;
  delete this->d;
}

void KRMBParam::reset()
{
  this->a = 1;
  if (k >= 1)
  {
    c[1] = a;
    d[1] = a;
  }
  for (size_t i = 2; i<=k; ++i)
  {
    c[i] = d[i-1]+1;
    d[i] = c[i];
  }
  this->b = d[k];
}

bool KRMBParam::next()
{
  return incrementB();  
}

bool KRMBParam::incrementB()
{
  if (b < n)
  {
    ++b;
  }
  else if (incrementD(k))
  {
    b = d[k];
  }
  else
  {
    return false;
  }
  return true;
}

bool KRMBParam::incrementD(size_t i)
{
  if (d[i] < n-k+i)
  {
    ++d[i];
  }
  else if (incrementC(i))
  {
    d[i] = c[i];
  }
  else
  {
    return false;
  }
  return true;
}

bool KRMBParam::incrementC(size_t i)
{
  if (c[i] < n-k+i)
  {
    ++c[i];
  }
  else if (i == 1)
  {
    if (incrementA())
    {
      c[1] = a;
    }
    else
    {
      return false;
    }
  }
  else if (incrementD(i-1))
  {
    c[i] = d[i-1]+1;
  }
  else
  {
    return false;
  }
  return true;
}

bool KRMBParam::incrementA()
{
  if (a < n-k+1)
  {
    ++a;
    return true;
  }
  return false;
}
