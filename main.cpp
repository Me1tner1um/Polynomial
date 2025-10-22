#include <iostream>
#include <vector>
#include <limits>
#include "polynomial.h"
#include "extended_polynomial.h"
#include "polynomial_list.h"

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
    cout << p1.getOrder() << endl;
    cout << "After increasing degree: " << p1.toString() << endl;
    
    p1.decreaseDegree();
    cout << p1.getOrder() << endl;
    cout << "After decreasing degree: " << p1.toString() << endl;
    
    // Создание второго многочлена для демонстрации
    cout << "\n--- Creating Second Polynomial ---" << endl;
    Polynomial p2 = inputPolynomial();
    displayPolynomialInfo(p2);
    
    // Статический член
    cout << "\nNumber of Polynomial objects created: " << Polynomial::getObjectCount() << endl;
}

void lab2_demo() {
    cout << "\n=== Lab 2: Operator Overloading ===" << endl;
    
    cout << "--- First Polynomial ---" << endl;
    Polynomial p1 = inputPolynomial();
    displayPolynomialInfo(p1);
    
    cout << "\n--- Second Polynomial ---" << endl;
    Polynomial p2 = inputPolynomial();
    displayPolynomialInfo(p2);
    
    cout << "\n--- Operator Demonstrations ---" << endl;
    
    // Сложение
    Polynomial sum = p1 + p2;
    cout << "p1 + p2 = " << sum.toString() << endl;
    
    // Вычитание
    Polynomial diff = p1 - p2;
    cout << "p1 - p2 = " << diff.toString() << endl;
    
    // Инкремент/декремент
    cout << "\n--- Increment/Decrement Operations ---" << endl;
    cout << "Original p1: " << p1.toString() << endl;
    
    ++p1;
    cout << "After ++p1: " << p1.toString() << endl;
    
    --p1;
    cout << "After --p1: " << p1.toString() << endl;
    
    // Оператор вызова функции
    double x;
    cout << "\nEnter x value to evaluate p1: ";
    cin >> x;
    cout << "p1(" << x << ") = " << p1(x) << endl;
    
    // Оператор индексирования
    cout << "\n--- Indexing Operation ---" << endl;
    int index;
    cout << "Enter coefficient index to display (0 to " << p1.getOrder() << "): ";
    cin >> index;
    if (index >= 0 && index <= p1.getOrder()) {
        cout << "p1[" << index << "] = " << p1[index] << endl;
    } else {
        cout << "Invalid index!" << endl;
    }
}

void lab3_demo() {
    cout << "\n=== Lab 3: Input/Output Operations ===" << endl;
    
    cout << "--- Create Polynomial ---" << endl;
    Polynomial p1 = inputPolynomial();
    displayPolynomialInfo(p1);
    
    // Вывод в поток
    cout << "\n--- Stream Output ---" << endl;
    cout << "Using operator<<: " << p1 << endl;
    
    // Ввод из потока
    cout << "\n--- Stream Input ---" << endl;
    Polynomial p2;
    cout << "Now let's input another polynomial using operator>>:" << endl;
    cin >> p2;
    cout << "You entered: " << p2 << endl;
    
    // Работа с файлами
    cout << "\n--- File Operations ---" << endl;
    string filename;
    
    cout << "Enter filename for text file (without extension): ";
    cin >> filename;
    string textFile = filename + ".txt";
    string binaryFile = filename + ".bin";
    
    p1.saveToTextFile(textFile);
    p1.saveToBinaryFile(binaryFile);
    cout << "Polynomial saved to " << textFile << " and " << binaryFile << endl;
    
    // Загрузка из файлов
    Polynomial p3, p4;
    p3.loadFromTextFile(textFile);
    p4.loadFromBinaryFile(binaryFile);
    
    cout << "Loaded from text file: " << p3 << endl;
    cout << "Loaded from binary file: " << p4 << endl;
    
    // Проверка корректности
    if (p1.toString() == p3.toString() && p1.toString() == p4.toString()) {
        cout << "File operations completed successfully!" << endl;
    } else {
        cout << "Error in file operations!" << endl;
    }
}

void lab4_demo() {
    std::cout << "\n=== Lab 4: Inheritance ===" << std::endl;
    
    std::vector<double> coeffs = {1.0, 2.0, 3.0};
    std::vector<int> powers = {0, 1, 2};
    
    Polynomial basePoly(2, coeffs);
    std::cout << "Base polynomial: " << basePoly.toString() << std::endl;
    
    PowerArrayPolynomial powerPoly(2, coeffs, powers);
    std::cout << "Power array polynomial: " << powerPoly.toString() << std::endl;
    
    StringFormPolynomial stringPoly(2, coeffs);
    std::cout << "String form polynomial: " << stringPoly.toString() << std::endl;
    
    Polynomial* polyPtr = &basePoly;
    std::cout << "Base pointer to base: " << polyPtr->toString() << std::endl;
    
    polyPtr = &powerPoly;
    std::cout << "Base pointer to derived (PowerArray): " << polyPtr->toString() << std::endl;
    
    polyPtr = &stringPoly;
    std::cout << "Base pointer to derived (StringForm): " << polyPtr->toString() << std::endl;
}

void lab5_demo() {
    std::cout << "\n=== Lab 5: Dynamic Lists and Polymorphism ===" << std::endl;
    
    PolynomialList list;

    std::vector<double> coeffs1 = {1.0, 2.0, 3.0};
    std::vector<double> coeffs2 = {4.0, 5.0, 6.0};
    std::vector<int> powers = {0, 1, 2};
    
    list.add(new Polynomial(2, coeffs1));
    list.add(new PowerArrayPolynomial(2, coeffs2, powers));
    list.add(new StringFormPolynomial(1, {7.0, 8.0}));
    
    list.displayAll();
    
    list.demonstratePolymorphism();
    
    Polynomial searchPoly(2, coeffs1);
    int foundIndex = list.find(searchPoly);
    std::cout << "Found polynomial at index: " << foundIndex << std::endl;
    
    if (foundIndex != -1) {
        list.remove(foundIndex);
        std::cout << "After removal:" << std::endl;
        list.displayAll();
    }
}

void lab6_demo() {}
void lab7_demo() {}
void lab8_demo() {}