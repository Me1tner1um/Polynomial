#include <iostream>
#include <vector>
#include <limits>
#include "polynomial.h"

using namespace std;

// Прототипы функций
void lab1_demo();
void lab2_demo();
void lab3_demo();
void lab4_demo();
void lab5_demo();
void lab6_demo();
void lab7_demo();
void lab8_demo();
Polynomial inputPolynomial();
vector<double> inputCoefficients(int order);
void displayPolynomialInfo(const Polynomial& poly);

int main() {
    int choice;
    
    do {
        cout << "\n=== Polynomial Laboratory Works ===" << endl;
        cout << "1. Lab 1 - Basic Polynomial Class" << endl;
        cout << "2. Lab 2 - Operator Overloading" << endl;
        cout << "3. Lab 3 - Input/Output Operations" << endl;
        cout << "4. Lab 4 - Inheritance" << endl;
        cout << "5. Lab 5 - Dynamic Lists and Polymorphism" << endl;
        cout << "6. Lab 6 - Exception Handling" << endl;
        cout << "7. Lab 7 - Templates" << endl;
        cout << "8. Lab 8 - STL Analysis" << endl;
        cout << "0. Exit" << endl;
        cout << "Choose laboratory work: ";
        cin >> choice;
        
        // Очистка буфера ввода
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch (choice) {
            case 1: lab1_demo(); break;
            case 2: lab2_demo(); break;
            case 3: lab3_demo(); break;
            case 4: lab4_demo(); break;
            case 5: lab5_demo(); break;
            case 6: lab6_demo(); break;
            case 7: lab7_demo(); break;
            case 8: lab8_demo(); break;
            case 0: cout << "Goodbye!" << endl; break;
            default: cout << "Invalid choice!" << endl;
        }
    } while (choice != 0);
    
    return 0;
}

// Функция для ввода коэффициентов
vector<double> inputCoefficients(int order) {
    vector<double> coefficients;
    cout << "Enter " << (order + 1) << " coefficients (from constant term to highest degree):" << endl;
    
    for (int i = 0; i <= order; i++) {
        double coeff;
        cout << "Coefficient for x^" << i << ": ";
        cin >> coeff;
        coefficients.push_back(coeff);
    }
    
    return coefficients;
}

// Функция для ввода многочлена
Polynomial inputPolynomial() {
    int order;
    cout << "Enter the order (degree) of the polynomial: ";
    cin >> order;
    
    if (order < 0) {
        cout << "Order cannot be negative. Using order = 0." << endl;
        order = 0;
    }
    
    vector<double> coefficients = inputCoefficients(order);
    return Polynomial(order, coefficients);
}

// Функция для отображения информации о многочлене
void displayPolynomialInfo(const Polynomial& poly) {
    cout << "Polynomial: " << poly.toString() << endl;
    cout << "Degree: " << poly.getOrder() << endl;
    
    // Вывод коэффициентов
    vector<double> coeffs = poly.getCoefficients();
    cout << "Coefficients: ";
    for (size_t i = 0; i < coeffs.size(); i++) {
        cout << coeffs[i];
        if (i < coeffs.size() - 1) cout << ", ";
    }
    cout << endl;
}

void lab1_demo() {
    cout << "\n=== Lab 1: Basic Polynomial Class ===" << endl;
    
    cout << "\n--- Creating First Polynomial ---" << endl;
    Polynomial p1 = inputPolynomial();
    displayPolynomialInfo(p1);
    
    // Вычисление значения
    double x;
    cout << "\nEnter x value to evaluate polynomial: ";
    cin >> x;
    cout << "p(" << x << ") = " << p1.evaluate(x) << endl;
    
    // Операции с многочленом
    cout << "\n--- Polynomial Operations ---" << endl;
    cout << "Original: " << p1.toString() << endl;
    
    p1.increaseDegree();
    cout << "After increasing degree: " << p1.toString() << endl;
    
    p1.decreaseDegree();
    cout << "After decreasing degree: " << p1.toString() << endl;
    
    // Создание второго многочлена для демонстрации
    cout << "\n--- Creating Second Polynomial ---" << endl;
    Polynomial p2 = inputPolynomial();
    displayPolynomialInfo(p2);
    
    // Статический член
    cout << "\nNumber of Polynomial objects created: " << Polynomial::getObjectCount() << endl;
}

void lab2_demo() {}
void lab3_demo() {}
void lab4_demo() {}
void lab5_demo() {}
void lab6_demo() {}
void lab7_demo() {}
void lab8_demo() {}