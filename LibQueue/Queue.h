// Copyright 2026 Igor
#pragma once
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

template <class T>
class Queue {
  size_t size_;
  size_t count_;
  size_t front_;
  size_t back_;
  T* data_;

 public:
  Queue(size_t size = 0);
  Queue(const Queue<T>& other);
  Queue(Queue<T>&& other) noexcept;
  ~Queue();

  size_t size() const noexcept { return size_; }
  size_t count() const noexcept { return count_; }
  bool isFull() const noexcept { return count_ == size_; }
  bool isEmpty() const noexcept { return count_ == 0; }

  T& front();
  T& back();
  T pop();
  void push(const T& elem);

  template <class U>
  friend void swap(Queue<U>& first, Queue<U>& second);

  Queue<T>& operator=(const Queue<T>& other);
  Queue<T>& operator=(Queue<T>&& other) noexcept;
};

template <class T>
inline Queue<T>::Queue(size_t size)
    : size_(size), front_(0), back_(0), count_(0), data_(new T[size]()) {}

template <class T>
Queue<T>::Queue(const Queue<T>& other)
    : size_(other.size_),
      front_(other.front_),
      back_(other.back_),
      count_(other.count_),
      data_(new T[size_]()) {
  for (size_t i = 0; i < size_; ++i) {
    data_[i] = other.data_[i];
  }
}

template <class T>
Queue<T>::Queue(Queue<T>&& other) noexcept
    : size_(0), front_(0), back_(0), count_(0), data_(nullptr) {
  swap(*this, other);
}

template <class T>
inline Queue<T>::~Queue() {
  if (data_) delete[] data_;
}

template <class T>
inline T& Queue<T>::front() {
  if (isEmpty()) throw std::out_of_range("Queue is empty!");
  return data_[front_];
}

template <class T>
inline T& Queue<T>::back() {
  if (isEmpty()) throw std::out_of_range("Queue is empty!");
  return data_[back_ - 1];
}

template <class T>
T Queue<T>::pop() {
  if (isEmpty()) throw std::out_of_range("Queue is empty!");
  T result = data_[front_];
  front_ = (front_ + 1) % size_;
  --count_;
  return result;
}

template <class T>
inline void Queue<T>::push(const T& elem) {
  if (isFull()) throw std::overflow_error("Queue is full!");
  back_ = (back_ % size_) + 1;
  data_[back_ - 1] = elem;
  ++count_;
}

template <class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other) {
  if (this != &other) {
    Queue temp(*this);
    swap(*this, temp);
  }
  return (*this);
}

template <class T>
Queue<T>& Queue<T>::operator=(Queue<T>&& other) noexcept {
  if (this != &other) {
    Queue temp(std::move(other));
    swap(*this, temp);
  }
  return (*this);
}

template <class U>
inline void swap(Queue<U>& first, Queue<U>& second) {
  using std::swap;
  swap(first.size_, second.size_);
  swap(first.front_, second.front_);
  swap(first.back_, second.back_);
  swap(first.count_, second.count_);
  swap(first.data_, second.data_);
}
