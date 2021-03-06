#ifndef PERMUTATION_H
#define	PERMUTATION_H
#include <iostream>
#include <stdint.h>

typedef int element_t;

class Permutation {

public:
    virtual int getNumElmts() = 0;
    virtual ~Permutation();

    /**
     * Returns the i-th element of the permutation.
     * The index i starts in 1. If i == 0, returns
     * 0.
     */
    virtual element_t getElement(int i) = 0;

    virtual void applyTransposition(int i, int j, int k) = 0;

    virtual void applyReversal(int i, int j) = 0;

    virtual bool sorted() const = 0;

    virtual Permutation *getInverse() = 0;

    virtual void print(std::ostream &os);

protected:
    static element_t *inverse(element_t *p, int n);
};


#endif	/* PERMUTATION_H */

