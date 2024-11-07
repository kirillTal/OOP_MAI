#pragma once

#include <memory>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <initializer_list>
#include "bFigure.h"

namespace Shape {

template <typename T>
struct is_valid_array_type {
    static constexpr bool value = 
        std::is_base_of_v<bFigure, typename T::element_type> && 
        std::is_same_v<T, std::shared_ptr<typename T::element_type>>;
};

template <typename T, typename = std::enable_if_t<is_valid_array_type<T>::value>>
class Array {
private:
    std::shared_ptr<T[]> data;    
    size_t capacity;               
    size_t size_;                 


    void resize(size_t new_capacity) {

        std::shared_ptr<T[]> new_data = std::shared_ptr<T[]>(new T[new_capacity]);


        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = std::move(data[i]);
        }

        data = std::move(new_data);
        capacity = new_capacity;
    }

public:

    Array(size_t initial_capacity = 10) 
        : data(std::shared_ptr<T[]>(new T[initial_capacity])), capacity(initial_capacity), size_(0) {}


    Array(std::initializer_list<T> init_list) 
        : data(std::shared_ptr<T[]>(new T[init_list.size()])), capacity(init_list.size()), size_(init_list.size()) {
        size_t i = 0;
        for (const auto& item : init_list) {
            data[i++] = item;
        }
    }


    Array(const Array& other) 
        : data(std::shared_ptr<T[]>(new T[other.capacity])), capacity(other.capacity), size_(other.size_) {
        for (size_t i = 0; i < size_; ++i) {
            data[i] = other.data[i];
        }
    }


    Array(Array&& other) noexcept 
        : data(std::move(other.data)), capacity(other.capacity), size_(other.size_) {
        other.capacity = 0;
        other.size_ = 0;
    }


    Array& operator=(const Array& other) {
        if (this != &other) {
            data = std::shared_ptr<T[]>(new T[other.capacity]);
            capacity = other.capacity;
            size_ = other.size_;
            for (size_t i = 0; i < size_; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }


    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
            capacity = other.capacity;
            size_ = other.size_;
            other.capacity = 0;
            other.size_ = 0;
        }
        return *this;
    }


    void push_back(const T& item) {
        if (size_ >= capacity) {
            resize(capacity * 2);  
        }
        data[size_++] = item;
    }

    void remove_at(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        for (size_t i = index; i < size_ - 1; ++i) {
            data[i] = std::move(data[i + 1]);
        }
        --size_;
    }


    T& operator[](size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }


    size_t size() const {
        return size_;
    }


    size_t get_capacity() const {
        return capacity;
    }

    void PrintAll() const {
        for (size_t i = 0; i < size_; ++i) {
            data[i]->print(std::cout);
            std::cout << std::endl;
        }
    }


    double TotalArea() const {
        double total = 0.0;
        for (size_t i = 0; i < size_; ++i) {
            total += data[i]->area();
        }
        return total;
    }
};

} 