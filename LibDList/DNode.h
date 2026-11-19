// Copyright 2026 Igor
#pragma once

template <typename T>
struct DNode {
  T data_;
  DNode<T>* next_;
  DNode<T>* prev_;

  explicit DNode(const T& data, DNode<T>* prev = nullptr,
                 DNode<T>* next = nullptr)
      : data_(data), prev_(prev), next_(next) {}
};
