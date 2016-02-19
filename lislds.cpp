#include <iostream>
#include <stdlib.h>

using namespace std;

int binSearchLargest(int N, int* X, int* M, int L, int i) {
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
    int newL = binSearchLargest(N, X, M, L, i);

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

int binSearchSmallest(int N, int* X, int* M, int L, int i) {
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
    int newL = binSearchSmallest(N, X, M, L, i);

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


int main(int argc, char *argv[]) {
  int N = argc - 1;
  if (N < 1) {
    cerr << "Usage: " << argv[0] << " p1 p2 .. pN" << endl;
    return 1;
  }
  int* X = new int[N];
  for (int i=1; i<argc; ++i) {
    X[i-1] = atoi(argv[i]);
  }

  int L;
  int* S = lis(N, X, L);

  cout << "LIS =";
  for (int i=0; i<L; ++i) {
    cout << " " << S[i];
  }
  cout << endl;
  delete S;

  S = lds(N, X, L);

  cout << "LDS =";
  for (int i=0; i<L; ++i) {
    cout << " " << S[i];
  }
  cout << endl;

}
