#include "polynomial_template.h"
#include <sstream>
#include <iomanip>

// Конструктор по умолчанию
template<typename T>
PolynomialTemplate<T>::PolynomialTemplate() : order(0) {
    coefficients.push_back(T());
}

// Конструктор с параметрами
template<typename T>
PolynomialTemplate<T>::PolynomialTemplate(int ord, const std::vector<T>& coeffs) 
    : order(ord), coefficients(coeffs) {}

// Вычисление значения многочлена
template<typename T>
T PolynomialTemplate<T>::evaluate(T x) const {
    T result = T();
    T power = T(1);
    
    for (int i = 0; i <= order; i++) {
        result += coefficients[i] * power;
        power *= x;
    }
    
    return result;
}

// Строковое представление
template<typename T>
std::string PolynomialTemplate<T>::toString() const {
    std::ostringstream oss;
    bool firstTerm = true;
    
    for (int i = order; i >= 0; i--) {
        if (coefficients[i] != T()) {
            if (!firstTerm) {
                if (coefficients[i] > T()) {
                    oss << " + ";
                } else {
                    oss << " - ";
                }
            }
            
            T absCoeff = (coefficients[i] < T()) ? -coefficients[i] : coefficients[i];
            
            if (i == 0) {
                oss << absCoeff;
            } else if (i == 1) {
                if (absCoeff != T(1)) {
                    oss << absCoeff << "*x";
                } else {
                    oss << "x";
                }
            } else {
                if (absCoeff != T(1)) {
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

// Геттеры
template<typename T>
int PolynomialTemplate<T>::getOrder() const { 
    return order; 
}

template<typename T>
std::vector<T> PolynomialTemplate<T>::getCoefficients() const { 
    return coefficients; 
}

// Сеттер
template<typename T>
void PolynomialTemplate<T>::setCoefficients(const std::vector<T>& coeffs) {
    coefficients = coeffs;
    order = coeffs.size() - 1;
}

// Оператор сложения
template<typename T>
PolynomialTemplate<T> PolynomialTemplate<T>::operator+(const PolynomialTemplate<T>& other) const {
    int maxOrder = std::max(order, other.order);
    std::vector<T> resultCoeffs(maxOrder + 1, T());
    
    for (int i = 0; i <= maxOrder; i++) {
        T coeff1 = (i <= order) ? coefficients[i] : T();
        T coeff2 = (i <= other.order) ? other.coefficients[i] : T();
        resultCoeffs[i] = coeff1 + coeff2;
    }
    
    return PolynomialTemplate<T>(maxOrder, resultCoeffs);
}

// Оператор вычитания
template<typename T>
PolynomialTemplate<T> PolynomialTemplate<T>::operator-(const PolynomialTemplate<T>& other) const {
    int maxOrder = std::max(order, other.order);
    std::vector<T> resultCoeffs(maxOrder + 1, T());
    
    for (int i = 0; i <= maxOrder; i++) {
        T coeff1 = (i <= order) ? coefficients[i] : T();
        T coeff2 = (i <= other.order) ? other.coefficients[i] : T();
        resultCoeffs[i] = coeff1 - coeff2;
    }
    
    return PolynomialTemplate<T>(maxOrder, resultCoeffs);
}

// Оператор вызова функции
template<typename T>
T PolynomialTemplate<T>::operator()(T x) const {
    return evaluate(x);
}

// Явная инстанциация для часто используемых типов
template class PolynomialTemplate<int>;
template class PolynomialTemplate<double>;
template class PolynomialTemplate<float>;