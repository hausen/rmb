#include <algorithm>
#include <iostream>
#include <stdlib.h>

using namespace std;

int binSearchLargest(int* X, int* M, int L, int i) {
  int lo=1;
  int hi=L;
  while (lo <= hi) {
    int mid = (lo+hi) % 2 == 0 ? (lo+hi) / 2 : (lo+hi+1) / 2;
    if (X[M[mid]] < X[i]) {
      lo = mid+1;
    } else {
      hi = mid-1;
    }
  }
  return lo;
}

int* lis(int N, int* X, int& L) {
  int* P = new int[N]();
  int* M = new int[N+1]();
  L = 0;
  for (int i=0; i<N; ++i) {
    int newL = binSearchLargest(X, M, L, i);

    P[i] = M[newL-1];
    M[newL] = i;

    if (newL > L) {
     L = newL;
    }
  }

  int* S = new int[L];
  int k = M[L];
  for (int i=L-1; i>=0; --i) {
    S[i] = X[k];
    k = P[k];
  }

  delete P;
  delete M;

  return S;
}

int binSearchSmallest(int* X, int* M, int L, int i) {
  int lo=1;
  int hi=L;
  while (lo <= hi) {
    int mid = (lo+hi) % 2 == 0 ? (lo+hi) / 2 : (lo+hi+1) / 2;
    if (X[M[mid]] > X[i]) {
      lo = mid+1;
    } else {
      hi = mid-1;
    }
  }
  return lo;
}

int *lds(int N, int *X, int &L) {
  int* P = new int[N]();
  int* M = new int[N+1]();
  L = 0;
  for (int i=0; i<N; ++i) {
    int newL = binSearchSmallest(X, M, L, i);

    P[i] = M[newL-1];
    M[newL] = i;

    if (newL > L) {
     L = newL;
    }
  }

  int* S = new int[L];
  int k = M[L];
  for (int i=L-1; i>=0; --i) {
    S[i] = X[k];
    k = P[k];
  }

  delete P;
  delete M;

  return S;
}

ostream& printPermutation(int* p, int n, ostream& os) {
  for (int i=0; i<n; ++i) {
    if (i > 0) os << " ";
    os << p[i];
  }
  return os;
}

int main(int argc, char *argv[]) {
  if (argc < 1) {
    cerr << "Usage: " << argv[0] << " N" << endl;
    return 1;
  }
  int N = atoi(argv[1]);

  int* X = new int[N];
  for (int i=0; i<N; ++i) {
    X[i] = i+1;
  }

  int lisLen, ldsLen;
  int* lisArray, * ldsArray;

  do {

    lisArray = lis(N, X, lisLen);
    if (lisLen >= N/2.0) {
      delete lisArray;
      continue;
    }
    ldsArray = lds(N, X, ldsLen);
    if (ldsLen > N/2.0) {
      delete lisArray;
      delete ldsArray;
      continue;
    }

    printPermutation(X, N, cout) << endl;

    cout << "LIS = ";
    printPermutation(lisArray, lisLen, cout) << endl;
    delete lisArray;

    cout << "LDS = ";
    printPermutation(ldsArray, ldsLen, cout) << endl;
    delete ldsArray;

    cout << endl;
  } while ( next_permutation(X, X+N) );

  delete X;
}
