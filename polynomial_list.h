#ifndef POLYNOMIAL_LIST_H
#define POLYNOMIAL_LIST_H

#include "extended_polynomial.h"
#include <vector>

struct PolynomialNode {
    Polynomial* data;
    PolynomialNode* next;
    PolynomialNode* prev;
    
    PolynomialNode(Polynomial* poly) : data(poly), next(nullptr), prev(nullptr) {}
    ~PolynomialNode() { delete data; }
};

class PolynomialList {
private:
    PolynomialNode* head;
    PolynomialNode* tail;
    int size;

public:
    PolynomialList();
    ~PolynomialList();
    
    void add(Polynomial* poly);
    void remove(int index);
    void insert(int index, Polynomial* poly);
    Polynomial* get(int index) const;
    int find(const Polynomial& poly) const;
    void displayAll() const;
    int getSize() const;
    
    void demonstratePolymorphism() const;
};

#endif