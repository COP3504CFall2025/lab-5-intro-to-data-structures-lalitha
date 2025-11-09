#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
public:
    // Big 5 + Parameterized Constructor
    ABS() {
        capacity_ = 0;
        curr_size_ = 0;
        array_ = new T[capacity_];
    }

    explicit ABS(const size_t capacity) {
        capacity_ = capacity;
        curr_size_ = 0;
        array_ = new T[capacity_];
    }

    ABS(const ABS& other) : capacity_(other.capacity_), curr_size_(other.curr_size_), array_(new T[other.capacity_]) {
        //fill data
        for(size_t i = 0; i < curr_size_; i++) {
            array_[i] = other.array_[i];
        }
    }   

    ABS& operator=(const ABS& rhs) {
        //check if same
        if(this == &rhs) return *this;

        //delete og data
         delete[] array_;

        //copy variables
        array_ = new T[rhs.capacity_];
        curr_size_ = rhs.curr_size_;
        capacity_ = rhs.capacity_;

        //fill data
        for(size_t i = 0; i < curr_size_; i++) {
            array_[i] = rhs.array_[i];
        }

    return *this;
    }

    ABS(ABS&& other) noexcept : curr_size_(other.curr_size_), capacity_(other.capacity_), array_(other.array_){
        other.curr_size_ = 0;
        other.capacity_ = 0;
        other.array_ = nullptr;
    }

    ABS& operator=(ABS&& rhs) noexcept {
        //check if same
        if(this == &rhs) return *this;

        //delete og
        delete[] array_;

        // variables
        array_ = rhs.array_;
        curr_size_ = rhs.curr_size_;
        capacity_ = rhs.capacity_;

        rhs.array_ = nullptr;
        rhs.curr_size_ = 0;
        rhs.capacity_ = 0;

        return *this;
    }
    ~ABS() noexcept override {
        delete[] array_;

        array_ = nullptr;
        curr_size_ = 0;
        capacity_ = 0;      
    }

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override {
        return curr_size_;
    }

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept {
        return capacity_;
    }

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept {
        return array_;
    }

    // Push item onto the stack
    void push(const T& data) override {
        if(curr_size_ < capacity_) {
            array_[curr_size_] = data;
            curr_size_++;
        } else { //too big :(
            //relocate
            (capacity_ == 0) ? (capacity_ = 1) : (capacity_ *= 2);

            T* array = new T[capacity_];
            for(size_t i = 0; i < curr_size_; i++) {
                array[i] = array_[i];
            }
            delete[] array_;
            array_ = array;

            array_[curr_size_] = data;
            curr_size_++;
        }
    }

    T peek() const override {
        if(curr_size_ == 0) {
            throw std::out_of_range ("Out of Range");
            return 0;
        }
        return array_[curr_size_ - 1];
    }

    T pop() override {
        if(curr_size_ == 0) {
            throw std::out_of_range ("Out of Range");
            return 0;
        }
        return array_[curr_size_ - 1];
        curr_size_--;
    }

private:
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;
};
