#include "polynomial_template.h"
#include <sstream>
#include <iomanip>

// Конструктор по умолчанию
template<typename T>
PolynomialTemplate<T>::PolynomialTemplate() : order(0) {
    coefficients = new T[1];
    coefficients[0] = T();
}

// Конструктор с параметрами
template<typename T>
PolynomialTemplate<T>::PolynomialTemplate(int ord, const T* coeffs) : order(ord) {
    coefficients = new T[order + 1];
    for (int i = 0; i <= order; i++) {
        coefficients[i] = coeffs[i];
    }
}

// Конструктор копирования
template<typename T>
PolynomialTemplate<T>::PolynomialTemplate(const PolynomialTemplate<T>& other) : order(other.order) {
    coefficients = new T[order + 1];
    for (int i = 0; i <= order; i++) {
        coefficients[i] = other.coefficients[i];
    }
}

// Деструктор
template<typename T>
PolynomialTemplate<T>::~PolynomialTemplate() {
    delete[] coefficients;
}

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
T* PolynomialTemplate<T>::getCoefficients() const { 
    T* copy = new T[order + 1];
    for (int i = 0; i <= order; i++) {
        copy[i] = coefficients[i];
    }
    return copy;
}

// Сеттер
template<typename T>
void PolynomialTemplate<T>::setCoefficients(int ord, const T* coeffs) {
    delete[] coefficients;
    order = ord;
    coefficients = new T[order + 1];
    for (int i = 0; i <= order; i++) {
        coefficients[i] = coeffs[i];
    }
}

// Оператор сложения
template<typename T>
PolynomialTemplate<T> PolynomialTemplate<T>::operator+(const PolynomialTemplate<T>& other) const {
    int maxOrder = std::max(order, other.order);
    T* resultCoeffs = new T[maxOrder + 1];
    
    for (int i = 0; i <= maxOrder; i++) {
        T coeff1 = (i <= order) ? coefficients[i] : T();
        T coeff2 = (i <= other.order) ? other.coefficients[i] : T();
        resultCoeffs[i] = coeff1 + coeff2;
    }
    
    PolynomialTemplate<T> result(maxOrder, resultCoeffs);
    delete[] resultCoeffs;
    return result;
}

// Оператор вычитания
template<typename T>
PolynomialTemplate<T> PolynomialTemplate<T>::operator-(const PolynomialTemplate<T>& other) const {
    int maxOrder = std::max(order, other.order);
    T* resultCoeffs = new T[maxOrder + 1];
    
    for (int i = 0; i <= maxOrder; i++) {
        T coeff1 = (i <= order) ? coefficients[i] : T();
        T coeff2 = (i <= other.order) ? other.coefficients[i] : T();
        resultCoeffs[i] = coeff1 - coeff2;
    }
    
    PolynomialTemplate<T> result(maxOrder, resultCoeffs);
    delete[] resultCoeffs;
    return result;
}

// Оператор вызова функции
template<typename T>
T PolynomialTemplate<T>::operator()(T x) const {
    return evaluate(x);
}

// Оператор присваивания
template<typename T>
PolynomialTemplate<T>& PolynomialTemplate<T>::operator=(const PolynomialTemplate<T>& other) {
    if (this != &other) {
        delete[] coefficients;
        order = other.order;
        coefficients = new T[order + 1];
        for (int i = 0; i <= order; i++) {
            coefficients[i] = other.coefficients[i];
        }
    }
    return *this;
}

// Явная инстанциация для часто используемых типов
template class PolynomialTemplate<int>;
template class PolynomialTemplate<double>;
template class PolynomialTemplate<float>;