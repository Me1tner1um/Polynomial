#include "polynomial_stl.h"
#include <iostream>
#include <cstring>

PolynomialSTLAnalysis::PolynomialSTLAnalysis() : polynomialArray(nullptr), arraySize(0) {}

PolynomialSTLAnalysis::~PolynomialSTLAnalysis() {
    if (polynomialArray != nullptr) {
        for (int i = 0; i < arraySize; i++) {
            delete polynomialArray[i];
        }
        delete[] polynomialArray;
    }
}

void PolynomialSTLAnalysis::generateTestData(int count) {
    // Очистка предыдущих данных
    if (polynomialArray != nullptr) {
        for (int i = 0; i < arraySize; i++) {
            delete polynomialArray[i];
        }
        delete[] polynomialArray;
    }
    
    polynomialArray = new Polynomial*[count];
    arraySize = count;
    
    polynomialList.clear();
    polynomialSet.clear();
    polynomialMultiSet.clear();
    polynomialMap.clear();
    polynomialMultiMap.clear();
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-10.0, 10.0);
    
    for (int i = 0; i < count; i++) {
        double* coeffs = new double[3];
        coeffs[0] = dis(gen);
        coeffs[1] = dis(gen);
        coeffs[2] = dis(gen);
        
        Polynomial* poly = new Polynomial(2, coeffs);
        
        polynomialArray[i] = poly;
        polynomialList.push_back(*poly);
        polynomialSet.insert(poly->toString());
        polynomialMultiSet.insert(poly->toString());
        polynomialMap[i] = *poly;
        polynomialMultiMap.insert({i % 5, *poly});
        
        delete[] coeffs;
    }
}

void PolynomialSTLAnalysis::analyzeArrayOperations() {
    std::cout << "=== Array Operations Analysis ===" << std::endl;
    
    // Копирование массива
    measureTime<Polynomial**>("Array Copy", [this]() {
        Polynomial** temp = new Polynomial*[arraySize];
        for (int i = 0; i < arraySize; i++) {
            double* coeffs = polynomialArray[i]->getCoefficients();
            temp[i] = new Polynomial(polynomialArray[i]->getOrder(), coeffs);
            delete[] coeffs;
        }
        
        // Очистка временного массива
        for (int i = 0; i < arraySize; i++) {
            delete temp[i];
        }
        delete[] temp;
    });
    
    // Поиск в массиве
    measureTime<Polynomial**>("Array Find", [this]() {
        if (arraySize > 0) {
            Polynomial* target = polynomialArray[0];
            for (int i = 0; i < arraySize; i++) {
                if (*polynomialArray[i] == *target) {
                    break;
                }
            }
        }
    });
    
    // Сортировка массива (пузырьковая сортировка)
    measureTime<Polynomial**>("Array Sort", [this]() {
        if (arraySize > 1) {
            Polynomial** temp = new Polynomial*[arraySize];
            for (int i = 0; i < arraySize; i++) {
                double* coeffs = polynomialArray[i]->getCoefficients();
                temp[i] = new Polynomial(polynomialArray[i]->getOrder(), coeffs);
                delete[] coeffs;
            }
            
            // Пузырьковая сортировка по строковому представлению
            for (int i = 0; i < arraySize - 1; i++) {
                for (int j = 0; j < arraySize - i - 1; j++) {
                    if (temp[j]->toString() > temp[j + 1]->toString()) {
                        Polynomial* swap = temp[j];
                        temp[j] = temp[j + 1];
                        temp[j + 1] = swap;
                    }
                }
            }
            
            // Очистка временного массива
            for (int i = 0; i < arraySize; i++) {
                delete temp[i];
            }
            delete[] temp;
        }
    });
    
    // Линейный обход массива
    measureTime<Polynomial**>("Array Traversal", [this]() {
        for (int i = 0; i < arraySize; i++) {
            polynomialArray[i]->toString();
        }
    });
}

void PolynomialSTLAnalysis::analyzeSetOperations() {
    std::cout << "=== Set Operations Analysis ===" << std::endl;
    
    // Вставка в set
    measureTime<std::set<std::string>>("Set Insert", [this]() {
        std::set<std::string> temp;
        for (int i = 0; i < arraySize; i++) {
            temp.insert(polynomialArray[i]->toString());
        }
    });
    
    // Поиск в set
    measureTime<std::set<std::string>>("Set Find", [this]() {
        if (!polynomialSet.empty() && arraySize > 0) {
            auto it = polynomialSet.find(polynomialArray[0]->toString());
        }
    });
    
    // Удаление из set
    measureTime<std::set<std::string>>("Set Erase", [this]() {
        auto temp = polynomialSet;
        if (!temp.empty()) {
            temp.erase(temp.begin());
        }
    });
    
    // Обход set
    measureTime<std::set<std::string>>("Set Traversal", [this]() {
        for (const auto& str : polynomialSet) {
            std::string temp = str;
        }
    });
}

void PolynomialSTLAnalysis::runAllAnalysis() {
    std::cout << "Generating test data..." << std::endl;
    generateTestData(1000);
    
    std::cout << "\nPerforming STL analysis..." << std::endl;
    analyzeArrayOperations();
    analyzeSetOperations();
    
    std::cout << "\nAnalysis completed!" << std::endl;
    std::cout << "Array size: " << arraySize << std::endl;
    std::cout << "List size: " << polynomialList.size() << std::endl;
    std::cout << "Set size: " << polynomialSet.size() << std::endl;
    std::cout << "Multiset size: " << polynomialMultiSet.size() << std::endl;
    std::cout << "Map size: " << polynomialMap.size() << std::endl;
    std::cout << "Multimap size: " << polynomialMultiMap.size() << std::endl;
}

template<typename Container>
void PolynomialSTLAnalysis::measureTime(const std::string& operationName, 
                                      std::function<void()> operation) {
    auto start = std::chrono::high_resolution_clock::now();
    operation();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << operationName << ": " << duration.count() << " microseconds" << std::endl;
}