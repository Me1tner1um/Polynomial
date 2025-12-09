#ifndef POLYNOMIAL_STL_H
#define POLYNOMIAL_STL_H

#include "polynomial.h"
#include <list>
#include <set>
#include <map>
#include <algorithm>
#include <chrono>
#include <random>
#include <functional>

class PolynomialSTLAnalysis {
private:
    Polynomial** polynomialArray;
    int arraySize;
    std::list<Polynomial> polynomialList;
    std::set<std::string> polynomialSet;
    std::multiset<std::string> polynomialMultiSet;
    std::map<int, Polynomial> polynomialMap;
    std::multimap<int, Polynomial> polynomialMultiMap;

public:
    PolynomialSTLAnalysis();
    ~PolynomialSTLAnalysis();
    
    void generateTestData(int count);
    void analyzeArrayOperations();
    void analyzeSetOperations();
    void runAllAnalysis();
    
private:
    template<typename Container>
    void measureTime(const std::string& operationName, 
                    std::function<void()> operation);
};

#endif