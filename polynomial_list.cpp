#include "polynomial_list.h"
#include <iostream>

PolynomialList::PolynomialList() : head(nullptr), tail(nullptr), size(0) {}

PolynomialList::~PolynomialList() {
    PolynomialNode* current = head;
    for (int i = 0; i < size; i++) {
        PolynomialNode* next = current->next;
        delete current;
        current = next;
    }
}

void PolynomialList::add(Polynomial* poly) {
    PolynomialNode* newNode = new PolynomialNode(poly);
    
    if (size == 0) {
        head = tail = newNode;
        head->next = head;
        head->prev = head;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        newNode->next = head;
        head->prev = newNode;
        tail = newNode;
    }
    size++;
}

void PolynomialList::remove(int index) {
    if (index < 0 || index >= size) return;
    
    PolynomialNode* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    
    if (size == 1) {
        head = tail = nullptr;
    } else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
        
        if (current == head) head = current->next;
        if (current == tail) tail = current->prev;
    }
    
    delete current;
    size--;
}

void PolynomialList::insert(int index, Polynomial* poly) {
    if (index < 0 || index > size) return;
    
    if (index == size) {
        add(poly);
        return;
    }
    
    PolynomialNode* newNode = new PolynomialNode(poly);
    PolynomialNode* current = head;
    
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    
    newNode->prev = current->prev;
    newNode->next = current;
    current->prev->next = newNode;
    current->prev = newNode;
    
    if (index == 0) head = newNode;
    size++;
}

Polynomial* PolynomialList::get(int index) const {
    if (index < 0 || index >= size) return nullptr;
    
    PolynomialNode* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    
    return current->data;
}

int PolynomialList::find(const Polynomial& poly) const {
    PolynomialNode* current = head;
    for (int i = 0; i < size; i++) {
        if (current->data->toString() == poly.toString()) {
            return i;
        }
        current = current->next;
    }
    return -1;
}

void PolynomialList::displayAll() const {
    PolynomialNode* current = head;
    std::cout << "List contents (" << size << " elements):" << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << i << ": " << current->data->toString() << std::endl;
        current = current->next;
    }
}

int PolynomialList::getSize() const {
    return size;
}

void PolynomialList::demonstratePolymorphism() const {
    std::cout << "=== Polymorphism Demonstration ===" << std::endl;
    PolynomialNode* current = head;
    for (int i = 0; i < size; i++) {
        std::cout << "Element " << i << " (type: " << typeid(*current->data).name() 
                  << "): " << current->data->toString() << std::endl;
        current = current->next;
    }
}