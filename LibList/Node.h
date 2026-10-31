// Copyright 2026 Igor
#pragma once

template <typename T>
class Node {
  T data_;
  Node* next_;

  Node(const T& data, Node* next = nullptr) : data_(data), next_(next) {}
  Node(const Node& other) = default;
  Node(Node&& other) = default;
};
