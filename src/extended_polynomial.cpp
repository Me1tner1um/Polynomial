#include "../include/extended_polynomial.h"
#include <sstream>

// PowerArrayPolynomial implementation
PowerArrayPolynomial::PowerArrayPolynomial() : Polynomial(), powerIndices(nullptr), powerCount(0) {}

PowerArrayPolynomial::PowerArrayPolynomial(int ord, const double* coeffs, const int* powers, int powerCnt) 
    : Polynomial(ord, coeffs), powerCount(powerCnt) {
    powerIndices = new int[powerCount];
    for (int i = 0; i < powerCount; i++) {
        powerIndices[i] = powers[i];
    }
}

PowerArrayPolynomial::PowerArrayPolynomial(const PowerArrayPolynomial& other)
    : Polynomial(other), powerCount(other.powerCount) {
    powerIndices = new int[powerCount];
    for (int i = 0; i < powerCount; i++) {
        powerIndices[i] = other.powerIndices[i];
    }
}

PowerArrayPolynomial::~PowerArrayPolynomial() {
    delete[] powerIndices;
}

int* PowerArrayPolynomial::getPowerIndices() const {
    int* copy = new int[powerCount];
    for (int i = 0; i < powerCount; i++) {
        copy[i] = powerIndices[i];
    }
    return copy;
}

int PowerArrayPolynomial::getPowerCount() const {
    return powerCount;
}

void PowerArrayPolynomial::setPowerIndices(const int* powers, int count) {
    delete[] powerIndices;
    powerCount = count;
    powerIndices = new int[powerCount];
    for (int i = 0; i < powerCount; i++) {
        powerIndices[i] = powers[i];
    }
}

std::string PowerArrayPolynomial::toString() const {
    std::ostringstream oss;
    oss << "Polynomial with power indices: ";
    for (int i = 0; i < powerCount; i++) {
        oss << powerIndices[i];
        if (i < powerCount - 1) oss << ", ";
    }
    oss << " | " << Polynomial::toString();
    return oss.str();
}

// StringFormPolynomial implementation
StringFormPolynomial::StringFormPolynomial() : Polynomial() {
    updateFormattedString();
}

StringFormPolynomial::StringFormPolynomial(int ord, const double* coeffs)
    : Polynomial(ord, coeffs) {
    updateFormattedString();
}

StringFormPolynomial::StringFormPolynomial(const StringFormPolynomial& other)
    : Polynomial(other) {
    updateFormattedString();
}

void StringFormPolynomial::updateFormattedString() {
    formattedString = "Formatted: " + Polynomial::toString();
}

std::string StringFormPolynomial::toString() const {
    return formattedString;
}
