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
        list.addTail(item);
    }

    // Deletion
    T dequeue() override { // remove head
        if(list.getHead() == nullptr) {
            throw std::runtime_error ("e or");
        }
        
        T d = (list.getHead())->data;
        list.removeHead();
        return d;
    }

    // Access
    T peek() const override { //return head
        if(list.getHead()  == nullptr) {
            throw std::runtime_error ("e or");
        }

        return (list.getHead())->data;
    }

    // Getter
    std::size_t getSize() const noexcept override {
        return list.getCount();
    }

};