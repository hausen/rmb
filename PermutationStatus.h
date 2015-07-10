#ifndef PERMUTATIONSTATUS_H
#define PERMUTATIONSTATUS_H
#include <stddef.h>

enum PermutationStatus {
  Unvisited = 0,
  PreviousLevel = 1,
  CurrentLevel = 2, 
  NextLevel = 3
};

class PermutationStatusArrayIterator;

class PermutationStatusArray {
public:
  PermutationStatusArray(size_t maxrank);
  ~PermutationStatusArray();
  void set(size_t rank, PermutationStatus status);
  PermutationStatus get(size_t rank);
private:
  size_t maxrank;
  size_t arraySize;
  unsigned long *statuses;
  friend class PermutationStatusArrayIterator;
};

class PermutationStatusArrayIterator {
public:
  PermutationStatusArrayIterator(PermutationStatusArray &array);
  bool next();
  void reset();
  PermutationStatus getStatus();
  void setStatus(PermutationStatus status);
  size_t getRank();
private:
  size_t arrIdx;
  size_t bitIdx;
  size_t currRank;
  PermutationStatusArray &statuses;
};

#endif
