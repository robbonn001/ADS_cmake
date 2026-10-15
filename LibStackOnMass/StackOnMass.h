// Copyright 2026 Igor
#pragma once
#include <stdexcept>

template<class T>
class StackOnMass {
    T* data_;
    size_t size_;
    int top_;

    public:
        StackOnMass(size_t size);
        StackOnMass(const StackOnMass& other);
        StackOnMass(StackOnMass&& other);
        ~StackOnMass();

        void push(const T& elem);
        T pop();
        T& top();
        bool isEmpty() const noexcept;
        bool isFull() const noexcept;
};

template<class T>
inline StackOnMass<T>::StackOnMass(size_t size): size_(size), top_(-1), data_(new T[size]()) {}

template<class T>
inline StackOnMass<T>::StackOnMass(const StackOnMass& other): size_(other.size), top_(other.top_), data_(new T[other.size])
{
    for (size_t i=0;i<size_;++i) data_[i] = other.data_[i];
}

template<class T>
inline StackOnMass<T>::StackOnMass(StackOnMass&& other): size_(other.size), top_(other.top_), data_(other.data_)
{
    other.data_ = nullptr;
}

template<class T>
inline StackOnMass<T>::~StackOnMass()
{
    if (data_) {
        delete[] data_;
    }
    data_ = nullptr;
}

template<class T>
inline void StackOnMass<T>::push(const T& elem)
{
    if (isFull()) throw std::logic_error("Stack is full!");
    data_[++top_] = elem;
}

template<class T>
inline T StackOnMass<T>::pop()
{
    if (isEmpty()) throw std::logic_error("Stack is empty!");
    return data_[top_--];
}

template<class T>
inline T& StackOnMass<T>::top()
{
    if (isEmpty()) throw std::logic_error("Stack is empty!");
    return data_[top_];
}

template<class T>
inline bool StackOnMass<T>::isEmpty() const noexcept
{
    return top_ == -1;
}

template<class T>
inline bool StackOnMass<T>::isFull() const noexcept
{
    return top_ == size_ - 1;
}
