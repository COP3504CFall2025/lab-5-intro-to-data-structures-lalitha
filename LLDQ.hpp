#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <utility>



template <typename T>
class LLDQ : public DequeInterface<T> {
private:
    LinkedList<T> list;

public:
    // Constructor
    LLDQ() {
        list = LinkedList<T>();
    }

    // Core Insertion Operations
    void pushFront(const T& item) override {
        list.addHead(item);
    }
    void pushBack(const T& item) override {
        list.addTail(item);
    }

    // Core Removal Operations
    T popFront() override {
        if(list.getHead() == nullptr) {
            throw std::runtime_error ("e or");
        }
        
        T d = (list.getHead())->data;
        list.removeHead();
        return d;
    }

    T popBack() override {
        if(list.getTail() == nullptr) {
            throw std::runtime_error ("e or");
        }
        
        T d = (list.getTail())->data;
        list.removeTail();
        return d;
    }

    // Element Accessors
    const T& front() const override {
        if(list.getHead() == nullptr) {
            throw std::runtime_error ("e or");
        }
        
        return (list.getHead())->data;
    }
    const T& back() const override {
        if(list.getTail() == nullptr) {
            throw std::runtime_error ("e or");
        }
        
        return (list.getTail())->data;
    }

    // Getter
    std::size_t getSize() const noexcept override {
        return list.getCount();
    }
};






