#include "PermutationStatus.h"
#include <assert.h>

PermutationStatusArray::PermutationStatusArray(size_t maxrank) {
  this->maxrank = maxrank;
  arraySize = (maxrank+1)/(sizeof(unsigned long)*4) + 1;
  statuses = new unsigned long[arraySize]();
}

PermutationStatusArray::~PermutationStatusArray() {
  delete[] statuses;
}

PermutationStatus PermutationStatusArray::get(size_t rank) {
  size_t arrIdx = rank / (sizeof(unsigned long)*4);
  size_t bitIdx = 2*(rank % (sizeof(unsigned long)*4));
  assert(arrIdx < arraySize);
  assert(bitIdx < sizeof(unsigned long)*8);
  switch ((statuses[arrIdx] >> bitIdx) & 3ul) {
    case 0ul:
      return Unvisited;
    case 1ul:
      return PreviousLevel;
    case 2ul:
      return CurrentLevel;
    case 3ul:
      return NextLevel;
  }
  assert(false);
  return Unvisited;
}

void PermutationStatusArray::set(size_t rank, PermutationStatus status) {
  size_t arrIdx = rank / (sizeof(unsigned long)*4);
  size_t bitIdx = 2*(rank % (sizeof(unsigned long)*4));
  assert(arrIdx < arraySize);
  assert(bitIdx < sizeof(unsigned long)*8);
  unsigned long bitmask = 3ul << bitIdx;
  unsigned long st;
  switch (status) {
    case Unvisited:
      st = 0ul; break;
    case PreviousLevel:
      st = 1ul; break;
    case CurrentLevel:
      st = 2ul; break;
    case NextLevel:
      st = 3ul; break;
  }
  statuses[arrIdx] = (statuses[arrIdx] & ~bitmask) | (st << bitIdx);
}

PermutationStatusArrayIterator::PermutationStatusArrayIterator
(PermutationStatusArray &array)
: arrIdx(0), bitIdx(0), currRank(0), statuses(array) {
}

void PermutationStatusArrayIterator::reset() {
  arrIdx = 0;
  bitIdx = 0;
  currRank = 0;
}

bool PermutationStatusArrayIterator::next() {
  if (currRank < statuses.maxrank) {
    ++currRank;
    bitIdx = (bitIdx + 2) % (sizeof(unsigned long)*8);
    if (bitIdx == 0) {
      ++arrIdx;
    }
    return true;
  } else {
    return false;
  }
}

PermutationStatus PermutationStatusArrayIterator::getStatus() {
  unsigned long st = (statuses.statuses[arrIdx] >> bitIdx) & 3ul;
  switch (st) {
    case 0ul:
      return Unvisited;
    case 1ul:
      return PreviousLevel;
    case 2ul:
      return CurrentLevel;
    case 3ul:
      return NextLevel;
  }
  assert(false);
  return Unvisited;
}

void PermutationStatusArrayIterator::setStatus(PermutationStatus status) {
  unsigned long bitmask = 3ul << bitIdx;
  // set the bits
  unsigned long st;
  switch (status) {
    case Unvisited:
      st = 0ul; break;
    case PreviousLevel:
      st = 1ul; break;
    case CurrentLevel:
      st = 2ul; break;
    case NextLevel:
      st = 3ul; break;
    default:
      assert(false); break;
  }
  statuses.statuses[arrIdx] =
    (statuses.statuses[arrIdx] & ~bitmask) | (st << bitIdx);
}

size_t PermutationStatusArrayIterator::getRank() {
  return currRank;
}
