// Copyright 2026 Igor
#pragma once
#include <stdexcept>
#include <utility>

template <class T>
class StackOnMass {
    T* data_;
    size_t size_;
    int top_;

     public:
        StackOnMass();
        explicit StackOnMass(size_t size);
        StackOnMass(const StackOnMass<T>& other);
        StackOnMass(StackOnMass<T>&& other) noexcept;
        ~StackOnMass();

        void push(const T& elem);
        T pop();
        T& top();
        bool isEmpty() const noexcept;
        bool isFull() const noexcept;

        StackOnMass<T>& operator=(const StackOnMass<T>& other);
        StackOnMass<T>& operator=(StackOnMass<T>&& other) noexcept;

        template <class U>
    friend void swap(StackOnMass<U>& first, StackOnMass<U>& second) noexcept;
};

template <class T>
inline StackOnMass<T>::StackOnMass(): size_(0), top_(-1), data_(nullptr) {}

template <class T>
inline StackOnMass<T>::StackOnMass(size_t size):
    size_(size), top_(-1), data_(new T[size]()) {}

template <class T>
inline StackOnMass<T>::StackOnMass(const StackOnMass<T>& other):
    size_(other.size_), top_(other.top_), data_(new T[other.size_]()) {
    for (size_t i = 0;i < size_;++i) data_[i] = other.data_[i];
}

template <class T>
inline StackOnMass<T>::StackOnMass(StackOnMass<T>&& other) noexcept:
    size_(0), top_(-1), data_(nullptr) {
    swap(*this, other);
}

template <class T>
inline StackOnMass<T>::~StackOnMass() {
    if (data_) {
        delete[] data_;
    }
}

template <class T>
inline void StackOnMass<T>::push(const T& elem) {
    if (isFull()) throw std::logic_error("Stack is full!");
    data_[++top_] = elem;
}

template <class T>
inline T StackOnMass<T>::pop() {
    if (isEmpty()) throw std::logic_error("Stack is empty!");
    return data_[top_--];
}

template <class T>
inline T& StackOnMass<T>::top() {
    if (isEmpty()) throw std::logic_error("Stack is empty!");
    return data_[top_];
}

template <class T>
inline bool StackOnMass<T>::isEmpty() const noexcept {
    return top_ == -1;
}

template <class T>
inline bool StackOnMass<T>::isFull() const noexcept {
    return top_ == size_ - 1;
}

template <class T>
inline StackOnMass<T>& StackOnMass<T>::operator=(const StackOnMass<T>& other) {
    if (this != &other) {
        StackOnMass temp(other);
        swap(*this, temp);
    }
    return (*this);
}

template <class T>
StackOnMass<T>& StackOnMass<T>::operator=(StackOnMass<T>&& other)
noexcept {
    if (this != &other) {
        if (data_) delete[] data_;
        top_ = -1;
        size_ = 0;
        data_ = nullptr;
        swap(*this, other);
    }
    return (*this);
}

template <class U>
inline void swap(StackOnMass<U>& first, StackOnMass<U>& second) noexcept {
    using std::swap;
    swap(first.data_, second.data_);
    swap(first.size_, second.size_);
    swap(first.top_, second.top_);
}
