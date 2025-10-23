#include "polynomial_stl.h"
#include <iostream>

void PolynomialSTLAnalysis::generateTestData(int count) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-10.0, 10.0);
    
    polynomialVector.clear();
    polynomialList.clear();
    polynomialSet.clear();
    polynomialMultiSet.clear();
    polynomialMap.clear();
    polynomialMultiMap.clear();
    
    for (int i = 0; i < count; i++) {
        std::vector<double> coeffs = {dis(gen), dis(gen), dis(gen)}; // 2nd degree
        Polynomial poly(2, coeffs);
        
        polynomialVector.push_back(poly);
        polynomialList.push_back(poly);
        polynomialSet.insert(poly.toString());
        polynomialMultiSet.insert(poly.toString());
        polynomialMap[i] = poly;
        polynomialMultiMap.insert({i % 5, poly});
    }
}

void PolynomialSTLAnalysis::analyzeVectorOperations() {
    std::cout << "=== Vector Operations Analysis ===" << std::endl;
    
    // Добавление
    measureTime<std::vector<Polynomial>>("Vector Push Back", [this]() {
        std::vector<Polynomial> temp;
        for (const auto& poly : polynomialVector) {
            temp.push_back(poly);
        }
    });
    
    // Удаление
    measureTime<std::vector<Polynomial>>("Vector Erase", [this]() {
        auto temp = polynomialVector;
        if (!temp.empty()) {
            temp.erase(temp.begin());
        }
    });
    
    // Поиск
    measureTime<std::vector<Polynomial>>("Vector Find", [this]() {
        if (!polynomialVector.empty()) {
            auto it = std::find(polynomialVector.begin(), polynomialVector.end(), 
                               polynomialVector[0]);
        }
    });
    
    // Сортировка
    measureTime<std::vector<Polynomial>>("Vector Sort", [this]() {
        auto temp = polynomialVector;
        std::sort(temp.begin(), temp.end(), 
                 [](const Polynomial& a, const Polynomial& b) {
                     return a.toString() < b.toString();
                 });
    });
}

void PolynomialSTLAnalysis::analyzeSetOperations() {
    std::cout << "=== Set Operations Analysis ===" << std::endl;
    
    // Вставка
    measureTime<std::set<std::string>>("Set Insert", [this]() {
        std::set<std::string> temp;
        for (const auto& poly : polynomialVector) {
            temp.insert(poly.toString());
        }
    });
    
    // Поиск
    measureTime<std::set<std::string>>("Set Find", [this]() {
        if (!polynomialSet.empty()) {
            auto it = polynomialSet.find(polynomialVector[0].toString());
        }
    });
    
    // Удаление
    measureTime<std::set<std::string>>("Set Erase", [this]() {
        auto temp = polynomialSet;
        if (!temp.empty()) {
            temp.erase(temp.begin());
        }
    });
}

void PolynomialSTLAnalysis::runAllAnalysis() {
    generateTestData(1000);
    analyzeVectorOperations();
    analyzeSetOperations();
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