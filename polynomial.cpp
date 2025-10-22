#include "polynomial.h"
#include <sstream>
#include <iomanip>

// Инициализация статического члена
int Polynomial::objectCount = 0;

// Конструктор по умолчанию
Polynomial::Polynomial() : order(0) {
    coefficients.push_back(0.0);
    objectCount++;
}

// Конструктор с параметрами
Polynomial::Polynomial(int ord, const std::vector<double>& coeffs) : order(ord), coefficients(coeffs) {
    objectCount++;
}

// Конструктор копирования
Polynomial::Polynomial(const Polynomial& other) : order(other.order), coefficients(other.coefficients) {
    objectCount++;
}

// Деструктор
Polynomial::~Polynomial() {
    objectCount--;
}

// Методы доступа
int Polynomial::getOrder() const {
    return order;
}

std::vector<double> Polynomial::getCoefficients() const {
    return coefficients;
}

void Polynomial::setCoefficients(const std::vector<double>& coeffs) {
    coefficients = coeffs;
    order = coeffs.size() - 1;
}

// Вычисление значения многочлена
double Polynomial::evaluate(double x) const {
    double result = 0.0;
    double power = 1.0;
    
    for (int i = 0; i <= order; i++) {
        result += coefficients[i] * power;
        power *= x;
    }
    
    return result;
}

// Строковое представление
std::string Polynomial::toString() const {
    std::ostringstream oss;
    bool firstTerm = true;
    
    for (int i = order; i >= 0; i--) {
        if (coefficients[i] != 0.0) {
            if (!firstTerm && coefficients[i] > 0) {
                oss << " + ";
            } else if (coefficients[i] < 0) {
                oss << " - ";
            }
            
            double absCoeff = std::abs(coefficients[i]);
            
            if (i == 0) {
                oss << absCoeff;
            } else if (i == 1) {
                if (absCoeff != 1.0) {
                    oss << absCoeff << "*x";
                } else {
                    oss << "x";
                }
            } else {
                if (absCoeff != 1.0) {
                    oss << absCoeff << "*x^" << i;
                } else {
                    oss << "x^" << i;
                }
            }
            
            firstTerm = false;
        }
    }
    
    if (firstTerm) {
        oss << "0";
    }
    
    return oss.str();
}

// Увеличение степени
void Polynomial::increaseDegree() {
    coefficients.push_back(0.0);
    order++;
}

// Уменьшение степени
void Polynomial::decreaseDegree() {
    if (order > 0) {
        coefficients.pop_back();
        order--;
    }
}

// Статический метод
int Polynomial::getObjectCount() {
    return objectCount;
}

// Оператор присваивания
Polynomial& Polynomial::operator=(const Polynomial& other) {
    if (this != &other) {
        order = other.order;
        coefficients = other.coefficients;
    }
    return *this;
}