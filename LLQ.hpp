#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLQ : public QueueInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLQ() {
        list = LinkedList<T>();
    }

    // Insertion
    void enqueue(const T& item) override { // add new tail
        
    }

    // Deletion
    T dequeue() override { // remove head

    }

    // Access
    T peek() const override { //return head

    }

    // Getter
    std::size_t getSize() const noexcept override {
        return list.getCount();
    }

};