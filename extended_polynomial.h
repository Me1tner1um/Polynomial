#ifndef EXTENDED_POLYNOMIAL_H
#define EXTENDED_POLYNOMIAL_H

#include "polynomial.h"

// Класс с массивами степеней
class PowerArrayPolynomial : public Polynomial {
private:
    int* powerIndices;
    int powerCount;

public:
    PowerArrayPolynomial();
    PowerArrayPolynomial(int ord, const double* coeffs, const int* powers, int powerCnt);
    PowerArrayPolynomial(const PowerArrayPolynomial& other);
    ~PowerArrayPolynomial();
    
    int* getPowerIndices() const;
    int getPowerCount() const;
    void setPowerIndices(const int* powers, int count);
    
    std::string toString() const override;
};

// Класс с строковым представлением
class StringFormPolynomial : public Polynomial {
private:
    std::string formattedString;

public:
    StringFormPolynomial();
    StringFormPolynomial(int ord, const double* coeffs);
    StringFormPolynomial(const StringFormPolynomial& other);
    
    void updateFormattedString();
    std::string toString() const override;
};

#endif