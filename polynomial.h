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
    // CON/DEstructors
    Polynomial(); // по умолчанию
    Polynomial(int ord, const std::vector<double>& coeffs);
    Polynomial(const Polynomial& other);
    virtual ~Polynomial();

    // Basic methods
    int getOrder() const;
    std::vector<double> getCoefficients() const;
    void setCoefficients(const std::vector<double>& coeffs);

    double evaluate(double x) const;
    virtual std::string toString() const;
    void increaseDegree();
    void decreaseDegree();

    static int getObjectCount();

    // Operations
    Polynomial operator+(const Polynomial& other) const;
    Polynomial operator-(const Polynomial& other) const;
    Polynomial& operator++();
    Polynomial operator++(int); 
    Polynomial& operator--(); 
    Polynomial operator--(int); 
    double operator()(double x) const; 
    double operator[](int index) const; 
    Polynomial& operator=(const Polynomial& other);

    // IN/OUTput
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& poly);
    friend std::istream& operator>>(std::istream& is, Polynomial& poly);

    void saveToTextFile(const std::string& filename) const;
    void loadFromTextFile(const std::string& filename);
    void saveToBinaryFile(const std::string& filename) const;
    void loadFromBinaryFile(const std::string& filename);

};

#endif