#include "extended_polynomial.h"
#include <sstream>

PowerArrayPolynomial::PowerArrayPolynomial() : Polynomial() {}

PowerArrayPolynomial::PowerArrayPolynomial(int ord, const std::vector<double>& coeffs, 
                                         const std::vector<int>& powers) 
    : Polynomial(ord, coeffs), powerIndices(powers) {}

PowerArrayPolynomial::PowerArrayPolynomial(const PowerArrayPolynomial& other)
    : Polynomial(other), powerIndices(other.powerIndices) {}

std::vector<int> PowerArrayPolynomial::getPowerIndices() const {
    return powerIndices;
}

void PowerArrayPolynomial::setPowerIndices(const std::vector<int>& powers) {
    powerIndices = powers;
}

std::string PowerArrayPolynomial::toString() const {
    std::ostringstream oss;
    oss << "Polynomial with power indices: ";
    for (size_t i = 0; i < powerIndices.size(); i++) {
        oss << powerIndices[i];
        if (i < powerIndices.size() - 1) oss << ", ";
    }
    oss << " | " << Polynomial::toString();
    return oss.str();
}

StringFormPolynomial::StringFormPolynomial() : Polynomial() {
    updateFormattedString();
}

StringFormPolynomial::StringFormPolynomial(int ord, const std::vector<double>& coeffs)
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