#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <cmath>

class PolynomialException : public std::exception {
private:
    std::string message;
public:
    PolynomialException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

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
    bool operator==(const Polynomial& other) const;
    bool operator!=(const Polynomial& other) const;

    // IN/OUTput
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& poly);
    friend std::istream& operator>>(std::istream& is, Polynomial& poly);

    void saveToTextFile(const std::string& filename) const;
    void loadFromTextFile(const std::string& filename);
    void saveToBinaryFile(const std::string& filename) const;
    void loadFromBinaryFile(const std::string& filename);

    // Exceptions
    double safeEvaluate(double x) const;
    double safeGetCoefficient(int index) const;
    void safeSetCoefficient(int index, double value);

};

#endif