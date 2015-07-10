#ifndef KRMB_H
#define KRMB_H
#include "Permutation.h"
#include "KRMBParam.h"
#include <iostream>

class KRMB
{
public:
  KRMB(size_t k, size_t nelmts);
  KRMB(const KRMB &other);
  ~KRMB();
  int getK() const;
  int getN() const;
  int getA() const;
  int getB() const;
  int getC(int i) const;
  int getD(int i) const;

  void applyTo(Permutation &p);
  bool next();

private:
  KRMBParam param;
  size_t k;
  size_t nelmts;

friend std::ostream& operator<<(std::ostream &, const KRMB &);
};

std::ostream& operator<<(std::ostream &, const KRMB &);

#endif
