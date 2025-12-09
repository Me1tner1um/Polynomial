#include <iostream>
#include <limits>
#include "../include/polynomial.h"
#include "../include/extended_polynomial.h"
#include "../include/polynomial_list.h"
#include "../include/polynomial_template.h"
#include "../include/polynomial_stl.h"

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
double* inputCoefficients(int order, int& count);
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
double* inputCoefficients(int order, int& count) {
    count = order + 1;
    double* coefficients = new double[count];
    cout << "Enter " << count << " coefficients (from constant term to highest degree):" << endl;
    
    for (int i = 0; i < count; i++) {
        double coeff;
        cout << "Coefficient for x^" << i << ": ";
        cin >> coeff;
        coefficients[i] = coeff;
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
    
    int count;
    double* coefficients = inputCoefficients(order, count);
    Polynomial poly(order, coefficients);
    delete[] coefficients;
    return poly;
}

// Функция для отображения информации о многочлене
void displayPolynomialInfo(const Polynomial& poly) {
    cout << "Polynomial: " << poly.toString() << endl;
    cout << "Degree: " << poly.getOrder() << endl;
    
    // Вывод коэффициентов
    double* coeffs = poly.getCoefficients();
    cout << "Coefficients: ";
    for (int i = 0; i <= poly.getOrder(); i++) {
        cout << coeffs[i];
        if (i < poly.getOrder()) cout << ", ";
    }
    cout << endl;
    delete[] coeffs;
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
    
    // Работа с файлами через операторы
    cout << "\n--- File Operations with Operators ---" << endl;
    string filename;
    
    cout << "Enter filename for text file (without extension): ";
    cin >> filename;
    string textFile = filename + ".txt";
    string binaryFile = filename + ".bin";
    
    // Сохранение в текстовый файл через оператор <<
    std::ofstream outFile(textFile);
    if (outFile.is_open()) {
        outFile << p1;
        outFile.close();
        cout << "Polynomial saved to " << textFile << " using operator<<" << endl;
    }
    
    // Сохранение в бинарный файл (старый метод)
    p1.saveToBinaryFile(binaryFile);
    cout << "Polynomial saved to " << binaryFile << " using saveToBinaryFile" << endl;
    
    // Загрузка из текстового файла через оператор >>
    Polynomial p3, p4;
    std::ifstream inFile(textFile);
    if (inFile.is_open()) {
        inFile >> p3;
        inFile.close();
        cout << "Loaded from text file using operator>>: " << p3 << endl;
    }
    
    // Загрузка из бинарного файла (старый метод)
    p4.loadFromBinaryFile(binaryFile);
    cout << "Loaded from binary file using loadFromBinaryFile: " << p4 << endl;
    
    // Проверка корректности
    if (p1.toString() == p3.toString() && p1.toString() == p4.toString()) {
        cout << "All file operations completed successfully!" << endl;
    } else {
        cout << "Error in file operations!" << endl;
    }
}

void lab4_demo() {
    std::cout << "\n=== Lab 4: Inheritance ===" << std::endl;
    
    double coeffs[] = {1.0, 2.0, 3.0};
    int powers[] = {0, 1, 2};
    
    Polynomial basePoly(2, coeffs);
    std::cout << "Base polynomial: " << basePoly.toString() << std::endl;
    
    PowerArrayPolynomial powerPoly(2, coeffs, powers, 3);
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

    double coeffs1[] = {1.0, 2.0, 3.0};
    double coeffs2[] = {4.0, 5.0, 6.0};
    int powers[] = {0, 1, 2};
    
    list.add(new Polynomial(2, coeffs1));
    list.add(new PowerArrayPolynomial(2, coeffs2, powers, 3));
    list.add(new StringFormPolynomial(1, new double[2]{7.0, 8.0}));
    
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

void lab6_demo() {
    std::cout << "\n=== Lab 6: Exception Handling ===" << std::endl;
    try {
        // Test constructor
        double coeffs1[] = {1.0, 2.0, 3.0};
        Polynomial p1(2, coeffs1);
        std::cout << "P1: " << p1 << std::endl;

        // Test evaluation
        double result = p1.evaluate(2.0);
        std::cout << "P1(2) = " << result << std::endl;

        // Test operator[]
        double coeff = p1[1];
        std::cout << "Coefficient at index 1: " << coeff << std::endl;

        // Test arithmetic operations
        double coeffs2[] = {2.0, 1.0};
        Polynomial p2(1, coeffs2);
        Polynomial p3 = p1 + p2;
        std::cout << "P1 + P2: " << p3 << std::endl;

        // Test file operations
        p1.saveToTextFile("polynomial.txt");
        Polynomial p4;
        p4.loadFromTextFile("polynomial.txt");
        std::cout << "Loaded from file: " << p4 << std::endl;

        // Test edge cases
        // double invalid_coeffs[] = {1.0, std::numeric_limits<double>::infinity()};

        // Polynomial p5(1, invalid_coeffs);

    } catch (const PolynomialException& e) {
        std::cerr << "Polynomial exception: " << e.what() << std::endl;
        return;
    } catch (...) {
        std::cerr << "Unknown exception occurred" << std::endl;
        return;
    }

    std::cout << "Program completed successfully" << std::endl;
}

void lab7_demo() {
    cout << "\n=== Lab 7: Templates ===" << endl;
    
    cout << "--- Integer Polynomial ---" << endl;
    cout << "Enter order for integer polynomial: ";
    int order;
    cin >> order;
    
    int* intCoeffs = new int[order + 1];
    cout << "Enter " << (order + 1) << " integer coefficients:" << endl;
    for (int i = 0; i <= order; i++) {
        int coeff;
        cout << "Coefficient for x^" << i << ": ";
        cin >> coeff;
        intCoeffs[i] = coeff;
    }
    
    PolynomialTemplate<int> intPoly(order, intCoeffs);
    cout << "Integer polynomial: " << intPoly.toString() << endl;
    
    int xInt;
    cout << "Enter integer x value: ";
    cin >> xInt;
    cout << "Value at x=" << xInt << ": " << intPoly.evaluate(xInt) << endl;
    cout << "Using operator(): " << intPoly(xInt) << endl;
    
    delete[] intCoeffs;
    
    cout << "\n--- Double Polynomial ---" << endl;
    cout << "Enter order for double polynomial: ";
    cin >> order;
    
    double* doubleCoeffs = new double[order + 1];
    cout << "Enter " << (order + 1) << " double coefficients:" << endl;
    for (int i = 0; i <= order; i++) {
        double coeff;
        cout << "Coefficient for x^" << i << ": ";
        cin >> coeff;
        doubleCoeffs[i] = coeff;
    }
    
    PolynomialTemplate<double> doublePoly(order, doubleCoeffs);
    cout << "Double polynomial: " << doublePoly.toString() << endl;
    
    double xDouble;
    cout << "Enter double x value: ";
    cin >> xDouble;
    cout << "Value at x=" << xDouble << ": " << doublePoly.evaluate(xDouble) << endl;
    
    delete[] doubleCoeffs;
    
    // Демонстрация операторов
    cout << "\n--- Operator Demonstrations ---" << endl;
    cout << "Creating another polynomial for operations..." << endl;
    
    double coeffs2[] = {1.5, 2.5};
    PolynomialTemplate<double> poly2(1, coeffs2);
    cout << "Second polynomial: " << poly2.toString() << endl;
    
    PolynomialTemplate<double> sum = doublePoly + poly2;
    cout << "Sum: " << sum.toString() << endl;
    
    PolynomialTemplate<double> diff = doublePoly - poly2;
    cout << "Difference: " << diff.toString() << endl;
    
    cout << "\n--- Float Polynomial ---" << endl;
    cout << "Enter order for float polynomial: ";
    cin >> order;
    
    float* floatCoeffs = new float[order + 1];
    cout << "Enter " << (order + 1) << " float coefficients:" << endl;
    for (int i = 0; i <= order; i++) {
        float coeff;
        cout << "Coefficient for x^" << i << ": ";
        cin >> coeff;
        floatCoeffs[i] = coeff;
    }
    
    PolynomialTemplate<float> floatPoly(order, floatCoeffs);
    cout << "Float polynomial: " << floatPoly.toString() << endl;
    
    float xFloat;
    cout << "Enter float x value: ";
    cin >> xFloat;
    cout << "Value at x=" << xFloat << ": " << floatPoly.evaluate(xFloat) << endl;
    
    delete[] floatCoeffs;
    
    cout << "\n--- Template Comparison ---" << endl;
    cout << "All polynomials use the same template class but with different data types!" << endl;
    cout << "intPoly type: " << typeid(intPoly).name() << endl;
    cout << "doublePoly type: " << typeid(doublePoly).name() << endl;
    cout << "floatPoly type: " << typeid(floatPoly).name() << endl;
}

void lab8_demo() {
    cout << "\n=== Lab 8: STL Analysis ===" << endl;
    
    int dataSize;
    cout << "Enter number of test polynomials to generate: ";
    cin >> dataSize;
    
    PolynomialSTLAnalysis analysis;
    analysis.generateTestData(dataSize);
    analysis.runAllAnalysis();
    
    cout << "\nSTL analysis completed!" << endl;
}