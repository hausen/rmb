#include <iostream>
#include <deque>
#include "PermutationArray.h"
#include "KRMB.h"
#include <limits.h>
#include <stdlib.h>
#include <set>

#define INFINITY INT_MAX

using namespace std;

void colorReset(ostream &os)
{
  os << "\x1b[0m";
}

void colorBlock(ostream &os)
{
  os << "\x1b[1;30;47m";
}

void colorInvert(ostream &os)
{
  os << "\x1b[0;37;40m";
}


void prettyPrint(KRMB &rmb, Permutation &p, ostream &os) {
  int k = rmb.getK(), a = rmb.getA(), b = rmb.getB();
  set<int> cs, ds;
  for(int i=1; i<=k; ++i) {
    cs.insert(rmb.getC(i));
    ds.insert(rmb.getD(i));
  }

  int n = p.getNumElmts();
  os << "[";
  for (int i=1; i<=n; ++i) {
    if (i == a)
      colorBlock(os);
    if (cs.find(i) != cs.end())
      colorInvert(os);
    os << p.getElement(i);
    if (ds.find(i) != ds.end())
      colorBlock(os);
    if (i == b)
      colorReset(os);
    if (i < n)
      os << " ";
  }
  os << "]";
}

//int n;
deque<KRMB> allKRMBs;

deque<KRMB> *sort(PermutationArray *p, PermutationArray *parent, int dmax)
{
  if (p->sorted())
    return new deque<KRMB>();
  if (dmax <= 0)
    return NULL;

  deque<KRMB> *seq = NULL;
  for (deque<KRMB>::iterator itRMB = allKRMBs.begin();
       itRMB != allKRMBs.end(); ++itRMB) {
    PermutationArray newp(*p);
    (*itRMB).applyTo(newp);
    if (newp == *parent)
      continue;
    deque<KRMB> *newseq = sort(&newp, p, dmax-1);
    if (newseq != NULL) {
      if ( seq == NULL || (newseq->size()+1 < seq->size()) ) {
#ifdef DEBUG
        if (parent == NULL)
          cerr << "found sequence with d = " << newseq->size()+1 << endl;
#endif
        if (seq != NULL) delete seq;
        dmax = newseq->size();
        newseq->push_front(*itRMB);
        if (dmax == 1) return newseq;
        seq = newseq;
      } else {
        delete newseq;
      }
    }
  }
  return seq;
}

int main(int argc, char *argv[]) {
  int n = argc - 4;
  if (n < 1) {
    cerr << "Usage: krmbsorter minK maxK maxD p1 p2 .. pn" << endl;
    return 1;
  }
  int mink = atoi(argv[1]);
  int maxk = atoi(argv[2]);
  int dmax = atoi(argv[3]);
  if (n < maxk) {
    cerr << "Error: n < maxK" << endl;
    return 1;
  }
  if (maxk < mink) {
    cerr << "Error: maxK < minK" << endl;
    return 1;
  }

  int *elmts = new int[n];
  for (int i=4; i<argc; ++i) {
    elmts[i-4] = atoi(argv[i]);
  }
  PermutationArray p(elmts, n);

  cerr << "sorting ";
  p.print(cerr);
  cerr << endl;
  
  delete[] elmts;

  for (int k=mink; k<=maxk; ++k) {
    KRMB rmb(k,n);
    do {
      allKRMBs.push_back(rmb);
    } while (rmb.next());
  }

  deque<KRMB> *seq = sort(&p, &p, dmax);

  if (seq != NULL) {
    cout << "d: " << seq->size() << endl;
    deque<KRMB>::iterator it = seq->begin();
    while (it != seq->end()) {
      prettyPrint(*it, p, cout);
      cout << endl;
      std::cout << " ↓ " << *it << endl;
      (*it).applyTo(p);
      ++it;
    }
    cout << "[";
    p.print(cout);
    cout << "]" << endl;
  } else {
    cerr << "could not sort with " << dmax << " moves!" << endl;
    return 2;
  }
}
