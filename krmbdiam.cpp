#define MAX_N 13
#include <assert.h>
#include <iostream>
#include <deque>
#include <stdlib.h>
#include "KRMB.h"
#include "PermutationArray.h"
#include "PermutationStatus.h"

using namespace std;

size_t factorial(size_t n) {
  size_t ret = 1;
  for (size_t i=2; i<=n; ++i) {
    ret *= i;
  }
  return ret;
}

int n;
deque<KRMB> allKRMBs;
PermutationStatusArray *statuses;

void visit(int level, size_t maxrank) {
  size_t permutationsInCurrentLevel = 0;
  size_t permutationsInNextLevel = 0;
  std::cerr << "Visiting level " << level << "..." << std::endl;
  PermutationStatusArrayIterator statusesIterator(*statuses);

  do {
    if (statusesIterator.getStatus() != CurrentLevel) {
      continue;
    }
    ++permutationsInCurrentLevel;
    size_t currRank = statusesIterator.getRank();
    PermutationArray *p = PermutationArray::unrank(currRank, n);
    for (deque<KRMB>::iterator itRMB = allKRMBs.begin();
         itRMB != allKRMBs.end(); ++itRMB) {
      PermutationArray newp(*p);
      (*itRMB).applyTo(newp);
      size_t rank = newp.rank();
      PermutationStatus status = statuses->get(rank);
      if (status == Unvisited) {
        ++permutationsInNextLevel;
        statuses->set(rank, NextLevel);
      }
    }
    delete p;
  } while (statusesIterator.next());

  std::cout << "level: " << level <<
               ", permutations: " <<
               permutationsInCurrentLevel << std::endl;

  if (permutationsInNextLevel == 0) {
    PermutationStatusArrayIterator statusesIterator(*statuses);
    std::cout << "diameter: " << level << std::endl;
    do {
      if (statusesIterator.getStatus() == CurrentLevel) {
        size_t rank = statusesIterator.getRank();
        PermutationArray *p = PermutationArray::unrank(rank, n);
        p->print(std::cout);
        std::cout << std::endl;
        delete p;
      }
    } while(statusesIterator.next());
    return;
  }

  statusesIterator.reset();
  do {
    switch(statusesIterator.getStatus()) {
    case CurrentLevel:
      statusesIterator.setStatus(PreviousLevel);
      break;
    case NextLevel:
      statusesIterator.setStatus(CurrentLevel);
      break;
    default:
      break;
    }
  } while (statusesIterator.next());

  visit(level+1, maxrank);
}

int main(int argc, char *argv[]) {
  if (argc < 4)
  {
    std::cerr << "Usage: krmbdiam.exe mink maxk n" << std::endl;
    return 1;
  }
  int mink = atoi(argv[1]);
  int maxk = atoi(argv[2]);
  n = atoi(argv[3]);
  if (n > MAX_N) {
    std::cerr << "n cannot be greater than " << MAX_N << "!" << std::endl;
    exit(1);
  }
  if (mink < 1) {
    cerr << "Error: minK < 1" << endl;
    return 1;
  }
  if (maxk < mink) {
    cerr << "Error: maxK < minK" << endl;
    return 1;
  }
  cerr << "Precomputing krmbs... ";
  for (int k=mink; k<=maxk; ++k) {
    cerr << k;
    unsigned long numops = 0;
    KRMB rmb(k,n);
    do {
      allKRMBs.push_back(rmb);
      ++numops;
    } while (rmb.next());
    cerr << "(" << numops << ") ";
  }
  cerr << " done." << endl;
  size_t maxrank = factorial(n)-1;
  statuses = new PermutationStatusArray(maxrank);

  PermutationArray identity(n);
  statuses->set(identity.rank(), CurrentLevel);
  visit(0, maxrank);
}
