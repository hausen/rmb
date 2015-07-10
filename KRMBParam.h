#ifndef KRMBPARAM_H
#define KRMBPARAM_H
#include <stddef.h>

typedef unsigned int param_t;

class KRMBParam
{
public:
  KRMBParam(size_t k, size_t n);
  KRMBParam(const KRMBParam &other);
  ~KRMBParam();
  void reset();
  bool next();
  size_t k;
  size_t n;
  param_t a;
  param_t b;
  param_t* c;
  param_t* d;
private:
  bool incrementA();
  bool incrementB();
  bool incrementC(size_t i);
  bool incrementD(size_t i);
};
#endif
