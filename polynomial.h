#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <vector>
#include <string>

class Polynomial {
protected:
    int order;;
    std::vector<double> coefficients;
    static int objectCount;

public:
    // Конструкторы
    Polynomial(); // по умолчанию
    Polynomial(int ord, const std::vector<double>& coeffs);
    Polynomial(const Polynomial& other);
    virtual ~Polynomial();

    // Методы доступа
    int getOrder() const;
    std::vector<double> getCoefficients() const;
    void setCoefficients(const std::vector<double>& coeffs);

    double evaluate(double x) const;
    virtual std::string toString() const;
    void increaseDegree();
    void decreaseDegree();

    static int getObjectCount();

    Polynomial& operator=(const Polynomial& other);
};

#endif