/*
 * File:   PermutationArray.cpp
 * Author: jamile
 *
 * Created on 4 de Setembro de 2014, 15:00
 */

#include "PermutationArray.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <iostream>

PermutationArray::PermutationArray()
{
    elmts = NULL;
    n = 0;
}

PermutationArray::PermutationArray(int n)
{
    this->n = n;
    elmts = new element_t[n];
    for (int i=0; i<n; ++i) {
        elmts[i] = i+1;
    }
}

PermutationArray::PermutationArray(PermutationArray &other)
{
    this->n = other.n;
    this->elmts = new element_t[n];
    memcpy(this->elmts, other.elmts, n*sizeof(element_t));
}

PermutationArray::PermutationArray(int elmts[], int n)
{
    this->elmts = new element_t[n];
    this->n = n;
    for(int i = 0; i<n; ++i)
        this->elmts[i] = (element_t)elmts[i];
}

PermutationArray::~PermutationArray()
{
    delete[] elmts;
}

bool PermutationArray::operator==(const PermutationArray &other) const
{
  return memcmp(this->elmts, other.elmts, n*sizeof(element_t)) == 0;
}

Permutation *PermutationArray::getInverse()
{
    PermutationArray *ret = new PermutationArray();
    ret->n = n;
    ret->elmts = inverse(elmts, n);
    return ret;
}

int PermutationArray::getNumElmts()
{
    return n;
}


element_t PermutationArray::getElement(int i)
{
    if (i==0)
        return 0;
    else if (i >= n+1)
        return n+1;
    else
        return elmts[i-1];
}

void PermutationArray::applyTransposition(int i, int j, int k) {
    size_t leftBlockSize = j-i;
    size_t rightBlockSize = k-j;
    size_t tmpSize = leftBlockSize + rightBlockSize;
    element_t *tmp = new element_t[tmpSize];
    memcpy(tmp, &elmts[j-1], rightBlockSize*sizeof(element_t));
    memcpy(tmp+rightBlockSize, &elmts[i-1], leftBlockSize*sizeof(element_t));
    memcpy(&elmts[i-1], tmp, tmpSize*sizeof(element_t));
    delete[] tmp;
}

void PermutationArray::applyReversal(int i, int j) {
    assert(i >= 1);
    assert(i < j);
    assert(j <= n);
    --i, --j;
    while (i < j) {
      std::swap(elmts[i], elmts[j]);
      ++i, --j;
    }
}

bool PermutationArray::sorted() const {
    element_t lastElmt = 0;
    for (int i = 0; i < n; ++i) {
      if (elmts[i] < lastElmt) {
        return false;
      }
      lastElmt = elmts[i];
    }
    return true;
}

// From:
// Myrvold, Wendy; Ruskey, Frank.
// Ranking and unranking permutations in linear time
// Information Processing Letters 79 (2001) 281-284
size_t PermutationArray::rank() const {
  element_t *pcopy = new element_t[n];
  element_t *inv = new element_t[n];

  for (int i=0; i<n; ++i) {
    pcopy[i] = elmts[i]-1;
    inv[elmts[i]-1] = i;
  }
  size_t r = rank(n, pcopy, inv);

  delete[] pcopy;
  delete[] inv;

  return r;
}

PermutationArray *PermutationArray::unrank(size_t rank, int n) {
  element_t *p = new element_t[n];
  for (int i=0; i<n; ++i) {
    p[i] = (element_t)(i+1);
  }
  unrank(n, rank, p);
  PermutationArray *ret = new PermutationArray();
  ret->elmts = p;
  ret->n = n;
  return ret;
}

size_t PermutationArray::rank(int n, element_t *p, element_t *inv) {
  if (n < 2)
    return 0;
  int s = p[n-1];
  std::swap(p[n-1], p[inv[n-1]]);
  std::swap(inv[s], inv[n-1]);
  return s + n*rank(n-1, p, inv);
}

void PermutationArray::unrank(int n, size_t rank, element_t *p) {
  if (n > 0) {
    std::swap(p[n-1], p[rank % n]);
    unrank(n-1, rank/n, p);
  }
}
