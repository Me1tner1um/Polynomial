#ifndef POLYNOMIAL_TEMPLATE_H
#define POLYNOMIAL_TEMPLATE_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

template<typename T>
class PolynomialTemplate {
private:
    int order;
    std::vector<T> coefficients;

public:
    // Конструкторы
    PolynomialTemplate();
    PolynomialTemplate(int ord, const std::vector<T>& coeffs);
    
    // Методы
    T evaluate(T x) const;
    std::string toString() const;
    
    // Геттеры и сеттеры
    int getOrder() const;
    std::vector<T> getCoefficients() const;
    void setCoefficients(const std::vector<T>& coeffs);
    
    // Операторы
    PolynomialTemplate<T> operator+(const PolynomialTemplate<T>& other) const;
    PolynomialTemplate<T> operator-(const PolynomialTemplate<T>& other) const;
    T operator()(T x) const;
};

#endif