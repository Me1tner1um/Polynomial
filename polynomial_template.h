#ifndef POLYNOMIAL_TEMPLATE_H
#define POLYNOMIAL_TEMPLATE_H

#include <iostream>
#include <string>
#include <sstream>

template<typename T>
class PolynomialTemplate {
private:
    int order;
    T* coefficients;

public:
    // Конструкторы
    PolynomialTemplate();
    PolynomialTemplate(int ord, const T* coeffs);
    PolynomialTemplate(const PolynomialTemplate<T>& other);
    ~PolynomialTemplate();
    
    // Методы
    T evaluate(T x) const;
    std::string toString() const;
    
    // Геттеры и сеттеры
    int getOrder() const;
    T* getCoefficients() const;
    void setCoefficients(int ord, const T* coeffs);
    
    // Операторы
    PolynomialTemplate<T> operator+(const PolynomialTemplate<T>& other) const;
    PolynomialTemplate<T> operator-(const PolynomialTemplate<T>& other) const;
    T operator()(T x) const;
    
    // Присваивание
    PolynomialTemplate<T>& operator=(const PolynomialTemplate<T>& other);
};

#endif