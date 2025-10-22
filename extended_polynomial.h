#ifndef EXTENDED_POLYNOMIAL_H
#define EXTENDED_POLYNOMIAL_H

#include "polynomial.h"
#include <vector>
#include <string>

// Класс с массивами степеней
class PowerArrayPolynomial : public Polynomial {
private:
    std::vector<int> powerIndices;

public:
    PowerArrayPolynomial();
    PowerArrayPolynomial(int ord, const std::vector<double>& coeffs, const std::vector<int>& powers);
    PowerArrayPolynomial(const PowerArrayPolynomial& other);
    
    std::vector<int> getPowerIndices() const;
    void setPowerIndices(const std::vector<int>& powers);
    
    std::string toString() const override;
};

// Класс с строковым представлением
class StringFormPolynomial : public Polynomial {
private:
    std::string formattedString;

public:
    StringFormPolynomial();
    StringFormPolynomial(int ord, const std::vector<double>& coeffs);
    StringFormPolynomial(const StringFormPolynomial& other);
    
    void updateFormattedString();
    std::string toString() const override;
};

#endif