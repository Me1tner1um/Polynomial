#include "polynomial.h"
#include <sstream>
#include <iomanip>
#include <fstream>

int Polynomial::objectCount = 0;

// CON/DEstructors
Polynomial::Polynomial() : order(0) {
    coefficients.push_back(0.0);
    objectCount++;
}

Polynomial::Polynomial(int ord, const std::vector<double>& coeffs) : order(ord), coefficients(coeffs) {
    objectCount++;
}

Polynomial::Polynomial(const Polynomial& other) : order(other.order), coefficients(other.coefficients) {
    objectCount++;
}

Polynomial::~Polynomial() {
    objectCount--;
}




// Basic methods
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

double Polynomial::evaluate(double x) const {
    double result = 0.0;
    double power = 1.0;
    
    for (int i = 0; i <= order; i++) {
        result += coefficients[i] * power;
        power *= x;
    }
    
    return result;
}

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

void Polynomial::increaseDegree() {
    coefficients.insert(coefficients.begin(), 0.0);
    order++;
}

void Polynomial::decreaseDegree() {
    if (order > 0) {
        coefficients.erase(coefficients.begin());
        order--;
    }
}

int Polynomial::getObjectCount() {
    return objectCount;
}




// Operations
Polynomial Polynomial::operator+(const Polynomial& other) const {
    int maxOrder = std::max(order, other.order);
    std::vector<double> resultCoeffs(maxOrder + 1, 0.0);
    
    for (int i = 0; i <= maxOrder; i++) {
        double coeff1 = (i <= order) ? coefficients[i] : 0.0;
        double coeff2 = (i <= other.order) ? other.coefficients[i] : 0.0;
        resultCoeffs[i] = coeff1 + coeff2;
    }
    
    return Polynomial(maxOrder, resultCoeffs);
}

Polynomial Polynomial::operator-(const Polynomial& other) const {
    int maxOrder = std::max(order, other.order);
    std::vector<double> resultCoeffs(maxOrder + 1, 0.0);
    
    for (int i = 0; i <= maxOrder; i++) {
        double coeff1 = (i <= order) ? coefficients[i] : 0.0;
        double coeff2 = (i <= other.order) ? other.coefficients[i] : 0.0;
        resultCoeffs[i] = coeff1 - coeff2;
    }
    
    return Polynomial(maxOrder, resultCoeffs);
}

Polynomial& Polynomial::operator++() {
    increaseDegree();
    return *this;
}

Polynomial Polynomial::operator++(int) {
    Polynomial temp = *this;
    increaseDegree();
    return temp;
}

Polynomial& Polynomial::operator--() {
    decreaseDegree();
    return *this;
}

Polynomial Polynomial::operator--(int) {
    Polynomial temp = *this;
    decreaseDegree();
    return temp;
}

double Polynomial::operator()(double x) const {
    return evaluate(x);
}

double Polynomial::operator[](int index) const {
    if (index < 0 || index > order) {
        return 0.0;
    }
    return coefficients[index];
}

Polynomial& Polynomial::operator=(const Polynomial& other) {
    if (this != &other) {
        order = other.order;
        coefficients = other.coefficients;
    }
    return *this;
}

bool Polynomial::operator==(const Polynomial& other) const {
    if (order != other.order) {
        return false;
    }
    
    for (int i = 0; i <= order; i++) {
        if (std::abs(coefficients[i] - other.coefficients[i]) > 1e-10) {
            return false;
        }
    }
    
    return true;
}

bool Polynomial::operator!=(const Polynomial& other) const {
    return !(*this == other);
}




// IN/OUTput
std::ostream& operator<<(std::ostream& os, const Polynomial& poly) {
    os << poly.toString();
    return os;
}

std::istream& operator>>(std::istream& is, Polynomial& poly) {
    std::cout << "Введите порядок многочлена: ";
    is >> poly.order;
    
    poly.coefficients.clear();
    std::cout << "Введите " << (poly.order + 1) << " коэффициентов: ";
    for (int i = 0; i <= poly.order; i++) {
        double coeff;
        is >> coeff;
        poly.coefficients.push_back(coeff);
    }
    
    return is;
}

void Polynomial::saveToTextFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << order << std::endl;
        for (double coeff : coefficients) {
            file << coeff << " ";
        }
        file << std::endl;
        file.close();
    }
}

void Polynomial::loadFromTextFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        file >> order;
        coefficients.clear();
        for (int i = 0; i <= order; i++) {
            double coeff;
            file >> coeff;
            coefficients.push_back(coeff);
        }
        file.close();
    }
}

void Polynomial::saveToBinaryFile(const std::string& filename) const {
    std::ofstream file(filename, std::ios::binary);
    if (file.is_open()) {
        file.write(reinterpret_cast<const char*>(&order), sizeof(order));
        for (double coeff : coefficients) {
            file.write(reinterpret_cast<const char*>(&coeff), sizeof(coeff));
        }
        file.close();
    }
}

void Polynomial::loadFromBinaryFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (file.is_open()) {
        file.read(reinterpret_cast<char*>(&order), sizeof(order));
        coefficients.clear();
        for (int i = 0; i <= order; i++) {
            double coeff;
            file.read(reinterpret_cast<char*>(&coeff), sizeof(coeff));
            coefficients.push_back(coeff);
        }
        file.close();
    }
}




// Exceptions
double Polynomial::safeEvaluate(double x) const {
    try {
        if (std::isnan(x) || std::isinf(x)) {
            throw PolynomialException("Invalid x value for evaluation");
        }
        return evaluate(x);
    }
    catch (const PolynomialException& e) {
        std::cerr << "Evaluation error: " << e.what() << std::endl;
        return 0.0;
    }
}

double Polynomial::safeGetCoefficient(int index) const {
    try {
        if (index < 0 || index > order) {
            throw PolynomialException("Index out of bounds");
        }
        return coefficients[index];
    }
    catch (const PolynomialException& e) {
        std::cerr << "Coefficient access error: " << e.what() << std::endl;
        return 0.0;
    }
}

void Polynomial::safeSetCoefficient(int index, double value) {
    try {
        if (index < 0 || index > order) {
            throw PolynomialException("Index out of bounds");
        }
        if (std::isnan(value) || std::isinf(value)) {
            throw PolynomialException("Invalid coefficient value");
        }
        coefficients[index] = value;
    }
    catch (const PolynomialException& e) {
        std::cerr << "Coefficient setting error: " << e.what() << std::endl;
    }
}