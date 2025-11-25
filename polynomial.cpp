#include "polynomial.h"
#include <sstream>
#include <iomanip>

int Polynomial::objectCount = 0;

// CON/DEstructors
Polynomial::Polynomial() : order(0) {
    coefficients = new double[1];
    coefficients[0] = 0.0;
    objectCount++;
}

Polynomial::Polynomial(int ord, const double* coeffs) : order(ord) {
    coefficients = new double[order + 1];
    for (int i = 0; i <= order; i++) {
        coefficients[i] = coeffs[i];
    }
    objectCount++;
}

Polynomial::Polynomial(const Polynomial& other) : order(other.order) {
    coefficients = new double[order + 1];
    for (int i = 0; i <= order; i++) {
        coefficients[i] = other.coefficients[i];
    }
    objectCount++;
}

Polynomial::~Polynomial() {
    delete[] coefficients;
    objectCount--;
}

// Basic methods
int Polynomial::getOrder() const {
    return order;
}

double* Polynomial::getCoefficients() const {
    double* copy = new double[order + 1];
    for (int i = 0; i <= order; i++) {
        copy[i] = coefficients[i];
    }
    return copy;
}

void Polynomial::setCoefficients(int ord, const double* coeffs) {
    delete[] coefficients;
    order = ord;
    coefficients = new double[order + 1];
    for (int i = 0; i <= order; i++) {
        coefficients[i] = coeffs[i];
    }
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
    double* newCoeffs = new double[order + 2];
    newCoeffs[0] = 0.0;
    for (int i = 0; i <= order; i++) {
        newCoeffs[i + 1] = coefficients[i];
    }
    delete[] coefficients;
    coefficients = newCoeffs;
    order++;
}

void Polynomial::decreaseDegree() {
    if (order > 0) {
        double* newCoeffs = new double[order];
        for (int i = 0; i < order; i++) {
            newCoeffs[i] = coefficients[i + 1];
        }
        delete[] coefficients;
        coefficients = newCoeffs;
        order--;
    }
}

int Polynomial::getObjectCount() {
    return objectCount;
}

// Operations
Polynomial Polynomial::operator+(const Polynomial& other) const {
    int maxOrder = std::max(order, other.order);
    double* resultCoeffs = new double[maxOrder + 1];
    
    for (int i = 0; i <= maxOrder; i++) {
        double coeff1 = (i <= order) ? coefficients[i] : 0.0;
        double coeff2 = (i <= other.order) ? other.coefficients[i] : 0.0;
        resultCoeffs[i] = coeff1 + coeff2;
    }
    
    Polynomial result(maxOrder, resultCoeffs);
    delete[] resultCoeffs;
    return result;
}

Polynomial Polynomial::operator-(const Polynomial& other) const {
    int maxOrder = std::max(order, other.order);
    double* resultCoeffs = new double[maxOrder + 1];
    
    for (int i = 0; i <= maxOrder; i++) {
        double coeff1 = (i <= order) ? coefficients[i] : 0.0;
        double coeff2 = (i <= other.order) ? other.coefficients[i] : 0.0;
        resultCoeffs[i] = coeff1 - coeff2;
    }
    
    Polynomial result(maxOrder, resultCoeffs);
    delete[] resultCoeffs;
    return result;
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

Polynomial operator+(double num, const Polynomial& other) {
    int order = other.order;
    double* resultCoeffs = new double[order + 1];

    resultCoeffs[0] = other.coefficients[0] + num;

    for (int i = 1; i < order; i++) {
        resultCoeffs[i] = other.coefficients[i];
    }

    Polynomial result(order, resultCoeffs);
    return result;
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
        delete[] coefficients;
        order = other.order;
        coefficients = new double[order + 1];
        for (int i = 0; i <= order; i++) {
            coefficients[i] = other.coefficients[i];
        }
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
    std::cout << "Enter the order (degree) of the polynomial: ";
    is >> poly.order;
    
    delete[] poly.coefficients;
    poly.coefficients = new double[poly.order + 1];
    
    std::cout << "Enter " << (poly.order + 1) << " coefficients: ";
    for (int i = 0; i <= poly.order; i++) {
        is >> poly.coefficients[i];
    }
    
    return is;
}

std::ofstream& operator<<(std::ofstream& ofs, const Polynomial& poly) {
    if (ofs.is_open()) {
        ofs << poly.order << std::endl;
        for (int i = 0; i <= poly.order; i++) {
            ofs << poly.coefficients[i] << " ";
        }
        ofs << std::endl;
    }
    return ofs;
}

std::ifstream& operator>>(std::ifstream& ifs, Polynomial& poly) {
    if (ifs.is_open()) {
        ifs >> poly.order;
        delete[] poly.coefficients;
        poly.coefficients = new double[poly.order + 1];
        for (int i = 0; i <= poly.order; i++) {
            ifs >> poly.coefficients[i];
        }
    }
    return ifs;
}

void Polynomial::saveToTextFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << order << std::endl;
        for (int i = 0; i <= order; i++) {
            file << coefficients[i] << " ";
        }
        file << std::endl;
        file.close();
    }
}

void Polynomial::loadFromTextFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        file >> order;
        delete[] coefficients;
        coefficients = new double[order + 1];
        for (int i = 0; i <= order; i++) {
            file >> coefficients[i];
        }
        file.close();
    }
}

void Polynomial::saveToBinaryFile(const std::string& filename) const {
    std::ofstream file(filename, std::ios::binary);
    if (file.is_open()) {
        file.write(reinterpret_cast<const char*>(&order), sizeof(order));
        for (int i = 0; i <= order; i++) {
            file.write(reinterpret_cast<const char*>(&coefficients[i]), sizeof(coefficients[i]));
        }
        file.close();
    }
}

void Polynomial::loadFromBinaryFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (file.is_open()) {
        file.read(reinterpret_cast<char*>(&order), sizeof(order));
        delete[] coefficients;
        coefficients = new double[order + 1];
        for (int i = 0; i <= order; i++) {
            file.read(reinterpret_cast<char*>(&coefficients[i]), sizeof(coefficients[i]));
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