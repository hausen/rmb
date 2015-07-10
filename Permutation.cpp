#include <assert.h>
#include <stdlib.h>
#include "Permutation.h"

Permutation::~Permutation()
{
}

element_t* Permutation::inverse(element_t *p, int n)
{
    element_t *inv = new element_t[n];
    for(int i=0; i < n; ++i) {
        inv[p[i]-1] = i+1;
    }

    return inv;
}

void Permutation::print(std::ostream &os)
{
    int n = getNumElmts();
    
    for(int i = 1; i <= n; ++i) {
        os << (int)getElement(i);
        if (i < n)
            os << " ";
    }
}
 
