#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLS : public StackInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLS() {
        list =  LinkedList<T>();
    }

    // Insertion
    void push(const T& item) override { //add node at head
        list.addHead(item);
    }

    // Deletion
    T pop() override { //remove and return head

        if(list.getHead() == nullptr) {
            throw std::runtime_error ("e or");
        }
    ]
        
        T d = (list.getHead())->data;
        list.removeHead();
        return d;
    }

    // Access
    T peek() const override {

        if(list.getHead()  == nullptr) {
            throw std::runtime_error ("e or");
        }

        return (list.getHead())->data;
    }

    //Getters
    std::size_t getSize() const noexcept override {
        return list.getCount();
    }
};