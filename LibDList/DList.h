// Copyright 2026 Igor
#pragma once
#include <stdexcept>

#include "DNode.h"

template <typename T>
class DList {
  DNode<T>* head_;
  DNode<T>* tail_;
  size_t size_;

 public:
  DList() : size_(0), head_(nullptr), tail_(nullptr) {}
  ~DList();
  DList(const DList& other);
  DList(DList&& other) noexcept;

  DNode<T>* push_front(const T& val) noexcept;
  DNode<T>* push_back(const T& val) noexcept;
  DNode<T>* insert(const T& val, size_t index);
  DNode<T>* insert(DNode<T>* DNode, const T& val);

  T pop_front();
  T pop_back();
  T erase(size_t index);

  bool isEmpty() const noexcept { return size_ == 0; }
  DNode<T>* find(const T& val) const noexcept;
  size_t size() const noexcept { return size_; }

  template <typename ValueType, typename DNodeType>
  class Iterator {
    DNodeType* current_;

   public:
    explicit Iterator(DNodeType* DNode) : current_(DNode) {}
    ValueType& operator*() { return current_->data_; }
    ValueType* operator->() { return &(current_->data_); }
    Iterator<ValueType, DNodeType>& operator++() noexcept {
      current_ = current_->next_;
      return *this;
    }
    Iterator<ValueType, DNodeType> operator++(int) noexcept {
      Iterator<ValueType, DNodeType> temp = *this;
      ++(*this);
      return temp;
    }
    Iterator<ValueType, DNodeType>& operator--() noexcept {
      current_ = current_->prev_;
      return *this;
    }
    Iterator<ValueType, DNodeType> operator--(int) noexcept {
      Iterator<ValueType, DNodeType> temp = *this;
      --(*this);
      return temp;
    }
    Iterator<ValueType, DNodeType> operator-(size_t step) noexcept {
      Iterator<ValueType, DNodeType> temp = *this;
      return temp -= step;
    }
    Iterator<ValueType, DNodeType>& operator-=(size_t step) {
      for (size_t i = step; i > 0; --i) {
        current_ = current_->prev_;
      }
      return *this;
    }
    Iterator<ValueType, DNodeType> operator+(size_t step) noexcept {
      Iterator<ValueType, DNodeType> temp = *this;
      return temp += step;
    }
    Iterator<ValueType, DNodeType>& operator+=(size_t step) {
      for (size_t i = step; i > 0; --i) {
        current_ = current_->next_;
      }
      return *this;
    }
    DNodeType* get_DNode() noexcept { return current_; }
    bool operator!=(
        const Iterator<ValueType, DNodeType>& other) const noexcept {
      return current_ != other.current_;
    }
    bool operator==(
        const Iterator<ValueType, DNodeType>& other) const noexcept {
      return current_ == other.current_;
    }
  };

  typedef Iterator<T, DNode<T>> iterator;
  typedef Iterator<const T, const DNode<T>> const_iterator;

  iterator begin() noexcept { return iterator(head_); }
  iterator end() noexcept { return iterator(nullptr); }
  const_iterator begin() const noexcept {
    return const_iterator(head_);
  }
  const_iterator end() const noexcept {
    return const_iterator(nullptr);
  }
  const_iterator cbegin() const noexcept {
    return const_iterator(head_);
  }
  const_iterator cend() const noexcept {
    return const_iterator(nullptr);
  }
};

template <typename T>
DList<T>::~DList() {
  if (!isEmpty()) {
    DNode<T>* next = nullptr;
    while (head_) {
      next = head_->next_;
      delete head_;
      head_ = next;
    }
  }
}

template <typename T>
DList<T>::DList(const DList& other) : size_(0), head_(nullptr), tail_(nullptr) {
  DNode<T>* cur = other.head_;
  while (cur) {
    push_back(cur->data_);
    cur = cur->next_;
  }
}

template <typename T>
inline DList<T>::DList(DList&& other) noexcept
    : size_(other.size_), head_(other.head_), tail_(other.tail_) {
  other.head_ = nullptr;
  other.tail_ = nullptr;
  other.size_ = 0;
}

template <typename T>
DNode<T>* DList<T>::push_front(const T& val) noexcept {
  DNode<T>* new_DNode = new DNode<T>(val, nullptr, head_);
  if (isEmpty()) {
    tail_ = new_DNode;
  } else {
    head_->prev_ = new_DNode;
  }
  head_ = new_DNode;
  ++size_;
  return new_DNode;
}

template <typename T>
DNode<T>* DList<T>::push_back(const T& val) noexcept {
  DNode<T>* new_DNode = new DNode<T>(val, tail_);
  if (isEmpty()) {
    head_ = new_DNode;
  } else {
    tail_->next_ = new_DNode;
  }
  tail_ = new_DNode;
  ++size_;
  return new_DNode;
}

template <typename T>
DNode<T>* DList<T>::insert(const T& val, size_t index) {
  if (index > size_) {
    throw std::out_of_range("Index is out of range!");
  } else if (index == 0) {
    return push_front(val);
  } else if (index == size_) {
    return push_back(val);
  }
  DNode<T>* cur = head_;
  for (size_t i = 0; i < index - 1; ++i) {
    cur = cur->next_;
  }
  DNode<T>* new_DNode = new DNode<T>(val, cur, cur->next_);
  cur->next_->prev_ = new_DNode;
  cur->next_ = new_DNode;
  ++size_;
  return new_DNode;
}

template <typename T>
DNode<T>* DList<T>::insert(DNode<T>* node, const T& val) {
  if (!node) {
    throw std::invalid_argument("DNode is nullptr!");
  }
  DNode<T>* new_node = new DNode<T>(val, node, node->next_);
  node->next_->prev_ = new_node;
  node->next_ = new_node;
  ++size_;
  return new_node;
}

template <typename T>
T DList<T>::pop_front() {
  if (isEmpty()) {
    throw std::out_of_range("DList is empty!");
  }
  T res = head_->data_;
  DNode<T>* temp = head_;
  head_ = head_->next_;
  if (head_) {
    head_->prev_ = nullptr;
  }
  delete temp;
  --size_;
  return res;
}

template <typename T>
T DList<T>::pop_back() {
  if (isEmpty()) {
    throw std::out_of_range("DList is empty!");
  }
  if (size_ == 1) {
    return pop_front();
  }
  DNode<T>* temp = tail_;
  T res = tail_->data_;
  tail_ = tail_->prev_;
  delete temp;
  tail_->next_ = nullptr;
  --size_;
  return res;
}

template <typename T>
T DList<T>::erase(size_t index) {
  if (isEmpty()) {
    throw std::out_of_range("DList is empty!");
  } else if (index >= size_) {
    throw std::out_of_range("Index is out of range!");
  } else if (index == 0) {
    return pop_front();
  } else if (index == size_ - 1) {
    return pop_back();
  }
  DNode<T>* cur = head_;
  for (size_t i = 0; i < index - 1; ++i) {
    cur = cur->next_;
  }
  DNode<T>* to_del = cur->next_;
  cur->next_ = to_del->next_;
  T res = to_del->data_;
  delete to_del;
  --size_;
  cur->next_->prev_ = cur;
  return res;
}

template <typename T>
DNode<T>* DList<T>::find(const T& val) const noexcept {
  DNode<T>* cur = head_;
  while (cur) {
    if (cur->data_ == val) {
      return cur;
    }
    cur = cur->next_;
  }
  return nullptr;
}
