/*
 * File:   PermutationArray.h
 * Author: jamile
 *
 * Created on 4 de Setembro de 2014, 15:00
 */

#ifndef PERMUTATIONARRAY_H
#define	PERMUTATIONARRAY_H
#include "Permutation.h"

class PermutationArray : public Permutation {
public:
    PermutationArray();
    PermutationArray(int n); // identity permutation
    PermutationArray(PermutationArray &other);
    PermutationArray(int elmts[], int n);
    ~PermutationArray();
    bool operator==(const PermutationArray &other) const;

    Permutation *getInverse();
    int getNumElmts();
    element_t getElement(int i);
    void applyTransposition(int i, int j, int k);
    void applyReversal(int i, int j);
    bool sorted() const;
    size_t rank() const;
    static PermutationArray *unrank(size_t rank, int n);

    /**
     * Gera uma permutação aleatória.
     * @params elmts os elementos da permutação aleatória
     * @params n quantidade de elementos
     */
    //static void randomPermutation(int *elmts, int n);
private:
    static size_t rank(int n, element_t *p, element_t *inv);
    static void unrank(int n, size_t rank, element_t *p);
    element_t *elmts;
    int n;

    friend class RMB;
};

#endif	/* PERMUTATIONARRAY_H */
