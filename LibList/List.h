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
  Node<T>* insert(Node<T>* node, const T& val);

  T pop_front();
  T pop_back();
  T erase(size_t index);

  bool isEmpty() const noexcept { return size_ == 0; }
  Node<T>* find(const T& val) const noexcept;
  size_t size() const noexcept { return size_; }

  template <typename ValueType, typename NodeType>
  class Iterator {
    NodeType* current_;

   public:
    explicit Iterator(NodeType* node) : current_(node) {}
    ValueType& operator*() { return current_->data_; }
    ValueType* operator->() { return &(current_->data_); }
    Iterator<ValueType, NodeType>& operator++() noexcept {
      if (current_) {
        current_ = current_->next_;
      }
      return *this;
    }
    Iterator<ValueType, NodeType> operator++(int) noexcept {
      Iterator<ValueType, NodeType> temp = *this;
      ++(*this);
      return temp;
    }
    NodeType* get_node() noexcept { return current_; }
    const Node<T>* get_node() const noexcept { return current_; }
    bool operator!=(const Iterator<ValueType, NodeType>& other)
        const noexcept {
      return current_ != other.current_;
    }
    bool operator==(const Iterator<ValueType, NodeType>& other)
        const noexcept {
      return current_ == other.current_;
    }
  };

  typedef Iterator<T, Node<T>> list_iterator;
  typedef Iterator<const T, const Node<T>> const_list_iterator;

  list_iterator begin() noexcept { return list_iterator(head_); }
  list_iterator end() noexcept { return list_iterator(nullptr); }
  const_list_iterator begin() const noexcept {
    return const_list_iterator(head_);
  }
  const_list_iterator end() const noexcept {
    return const_list_iterator(nullptr);
  }
  const_list_iterator cbegin() const noexcept {
    return const_list_iterator(head_);
  }
  const_list_iterator cend() const noexcept {
    return const_list_iterator(nullptr);
  }
};

template <typename T>
List<T>::~List() {
  if (!isEmpty()) {
    Node<T>* next = nullptr;
    while (head_) {
      next = head_->next_;
      delete head_;
      head_ = next;
    }
  }
}

template <typename T>
List<T>::List(const List& other) : size_(0), head_(nullptr), tail_(nullptr) {
  Node<T>* cur = other.head_;
  while (cur) {
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
    tail_ = new_node;
  }
  head_ = new_node;
  ++size_;
  return new_node;
}

template <typename T>
Node<T>* List<T>::push_back(const T& val) noexcept {
  Node<T>* new_node = new Node<T>(val);
  if (isEmpty()) {
    head_ = new_node;
  } else {
    tail_->next_ = new_node;
  }
  tail_ = new_node;
  ++size_;
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
  ++size_;
  return new_node;
}

template <typename T>
Node<T>* List<T>::insert(Node<T>* node, const T& val) {
  if (!node) {
    throw std::invalid_argument("Node is nullptr!");
  }
  Node<T>* new_node = new Node<T>(val, node->next_);
  node->next_ = new_node;
  ++size_;
  return new_node;
}

template <typename T>
T List<T>::pop_front() {
  if (isEmpty()) {
    throw std::out_of_range("List is empty!");
  }
  T res = head_->data_;
  Node<T>* temp = head_;
  head_ = head_->next_;
  delete temp;
  --size_;
  return res;
}

template <typename T>
T List<T>::pop_back() {
  if (isEmpty()) {
    throw std::out_of_range("List is empty!");
  }
  if (size_ == 1) {
    return pop_front();
  }
  Node<T>* temp = head_;
  while (temp->next_ != tail_) {
    temp = temp->next_;
  }
  T res = tail_->data_;
  delete tail_;
  --size_;
  tail_ = temp;
  return res;
}

template <typename T>
T List<T>::erase(size_t index) {
  if (isEmpty()) {
    throw std::out_of_range("List is empty!");
  } else if (index >= size_) {
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
  --size_;
  return res;
}

template <typename T>
Node<T>* List<T>::find(const T& val) const noexcept {
  Node<T>* cur = head_;
  while (cur) {
    if (cur->data_ == val) {
      return cur;
    }
    cur = cur->next_;
  }
  return nullptr;
}
