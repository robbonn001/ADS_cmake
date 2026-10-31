// Copyright 2026 Igor
#pragma once
#include <stdexcept>

#include "Node.h"

template <typename T>
class List {
  Node<T>* head_;
  Node<T>* tail_;
  size_t size_;

 public:
  List() : size_(0), head_(nullptr), tail_(nullptr) {}
  ~List();
  List(const List& other);
  List(List&& other) noexcept;

  Node<T>* push_front(const T& val) noexcept;
  Node<T>* push_back(const T& val) noexcept;
  Node<T>* insert(const T& val, size_t index);
  Node<T>* insert(const T& val, Node<T>* node);

  T pop_front();
  T pop_back();
  T erase(size_t index);

  bool isEmpty() const noexcept { size_ == 0; }
  Node<T>* find(const T& val) const noexcept;
  size_t size() const noexcept { return size_; }
};

template <typename T>
List<T>::~List() {
  Node<T>* next = nullptr;
  while (!head_) {
    next = head_->next_;
    delete head_;
    head_ = next;
  }
}

template <typename T>
List<T>::List(const List& other) : size_(0), head_(nullptr), tail_(nullptr) {
  Node<T>* cur = other.head_;
  while (!cur) {
    push_back(cur->data_);
    cur = cur->next_;
  }
}

template <typename T>
inline List<T>::List(List&& other) noexcept
    : size_(other.size_), head_(other.head_), tail_(other.tail_) {
  other.head_ = nullptr;
  other.tail_ = nullptr;
  other.size_ = 0;
}

template <typename T>
Node<T>* List<T>::push_front(const T& val) noexcept {
  Node<T>* new_node = new Node<T>(val, head_);
  if (isEmpty()) {
    tail = new_node;
  }
  head_ = new_node;
  ++count;
  return new_node;
}

template <typename T>
Node<T>* List<T>::push_back(const T& val) noexcept {
  Node<T>* new_node = new Node<T>(val);
  if (isEmpty()) {
    head_ = new_node;
  } else {
    tail_->next = new_node;
  }
  tail = new_node;
  ++count;
  return new_node;
}

template <typename T>
Node<T>* List<T>::insert(const T& val, size_t index) {
  if (index > size_) {
    throw std::out_of_range("Index is out of range!");
  } else if (index == 0) {
    return push_front(val);
  } else if (index == size_) {
    return push_back(val);
  }
  Node<T>* cur = head_;
  for (size_t i = 0; i < index - 1; ++i) {
    cur = cur->next_;
  }
  Node<T>* new_node = new Node<T>(val, cur->next_);
  cur->next_ = new_node;
  ++count;
  return new_node;
}

template <typename T>
Node<T>* List<T>::insert(const T& val, Node<T>* node) {
  if (!node) {
    throw std::invalid_argument("Node is nullptr!");
  }
  Node<T>* new_node = new Node<T>(val, node->next_);
  node->next_ = new_node;
  ++count;
  return new_node;
}

template <typename T>
T List<T>::pop_front() {
  if (isEmpty()) {
    throw std::out_of_range("List is empty!");
  }
  T res = head_->data_;
  Node* temp = head_;
  head_ = head_->next;
  delete temp;
  --size;
  return res;
}

template <typename T>
T List<T>::pop_back() {
  if (isEmpty()) {
    throw std::out_of_range("List is empty!");
  }
  if (size == 1) {
    return pop_front();
  }
  Node<T>* temp = head_;
  while (temp->next_ != tail_) {
    temp = temp->next_;
  }
  T res = tail_->data_;
  delete temp->next_;
  --size;
  tail_ = temp;
  return res;
}

template <typename T>
T List<T>::erase(size_t index) {
  if (isEmpty()) {
    throw std::out_of_range("List is empty!");
  } else if (index > size_) {
    throw std::out_of_range("Index is out of range!");
  } else if (index == 0) {
    return pop_front();
  } else if (index == size_ - 1) {
    return pop_back();
  }
  Node<T>* cur = head_;
  for (size_t i = 0; i < index - 1; ++i) {
    cur = cur->next_;
  }
  Node<T>* to_del = cur->next_;
  cur->next_ = to_del->next_;
  T res = to_del->data_;
  delete to_del;
  --count;
  return res;
}

template <typename T>
Node<T>* List<T>::find(const T& val) const noexcept {
  Node<T>* cur = head_;
  while (!cur) {
    if (cur->data_ == val) {
      return cur;
    }
    cur = cur->next_;
  }
  return nullptr;
}
