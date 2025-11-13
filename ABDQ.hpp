#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;                 // underlying dynamic array    circular array buffer
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

public:
    // Big 5
    ABDQ() {
       // Default Constructor. Default capacity_ to 4, size_ to 0, front_ and back_ to 0, and create buffer array data_.
       capacity_ = 4;
       size_ = 0;
       front_ = 0;
       back_ = 0;

       data_ = new T[capacity_];
    }

    explicit ABDQ(std::size_t capacity) : capacity_(capacity) {
        size_ = 0;
        front_ = 0;
        back_ = 0;

        data_ = new T[capacity_];
    }

    ABDQ(const ABDQ& other) : size_(other.size_), front_(other.front_), back_(other.back_), data_(new T(capacity_)) {
        for(size_t i = 0; i < other.size_; i++) {
            data_[i] = other.data_[i];
        }
    }

    ABDQ(ABDQ&& other) noexcept : size_(other.size_), front_(other.front_), back_(other.back_), data_(other.data_) {
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
        other.data_ = nullptr;
    }

    ABDQ& operator=(const ABDQ& other) {
        //check if same
        if(this == &other) {return *this;}

        //clear old
        delete[] data_;

        //copy over
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;

        data_ = new T[capacity_];
        for(size_t i = 0; i < other.size_; i++) {
            data_[i] = other.data_[i];
        }

        return *this;
    }
    ABDQ& operator=(ABDQ&& other) noexcept {
        //check if same
        if(this == &other) {return *this;}

        //clear old
        delete[] data_;

        //new data
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        data_ = other.data_;

        //delet4e old
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
        other.data_ = nullptr;

        return *this;
    }
    ~ABDQ() override {
        size_ = 0;
        front_ = 0;
        back_ = 0;

        delete[] data_;
    }

    // Insertion
    void pushFront(const T& item) override {
        if(size_ >= capacity_) {
            ensureCapacity();
        }

        size_++;
        for(int i = front_; i < size_ - 1; i++) {
                data_[i + 1] = data_[i];
            }
        T el = data_[front_];
    }

    void pushBack(const T& item) override {
        if(size_ >= capacity_) {
            ensureCapacity();
        }

        size_++;
        for(int i = back_; i < size_ - 1; i++) {
                data_[i + 1] = data_[i];
            }
        T el = data_[back_];
    }

    void ensureCapacity() {
        (capacity_ == 0) ? (capacity_ = 1) : (capacity_ *= 2);
        T* data = new T[capacity_];
         for(size_t i = 0; i < size_; i++) {
             data[i] = data_[i];
        }
        delete[] data_;
        data_ = data;
    }

    void shrinkIfNeeded() {
        capacity_ /= 2;
        T* data = new T[capacity_];
         for(size_t i = 0; i < size_; i++) {
             data[i] = data_[i];
        }
        delete[] data_;
        data_ = data;
    }

    // Deletion
    T popFront() override {
        if((front_ - back_) == 0) {
            throw std::runtime_error("e or");
        }


        T el = data_[front_];
        for(int i = front_ + 1; i < size_; i++) {
            data_[i - 1] = data_[i];
        }
        size_--;

        //resize
        if(size_ <= capacity_ / 4 && capacity_ > 1) {
            shrinkIfNeeded();
        }

        return el;
    }

    T popBack() override {
        if((front_ - back_) == 0) {
            throw std::runtime_error("e or");
        }

        T el = data_[back_];
        for(int i = back + 1; i < size_; i++) {
            data_[i - 1] = data_[i];
        }
        size_--;

        //resize
        if(size_ <= capacity_ / 4 && capacity_ > 1) {
            shrinkIfNeeded();
        }

        return el;
    }

    // Access
    const T& front() const override {
        return data_[front_];
    }

    const T& back() const override {
        return data_[back_];
    }

    // Getters
    std::size_t getSize() const noexcept override {
        return size_;
    }

};
