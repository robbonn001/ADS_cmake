// Copyright 2026 Igor
#pragma once

template <typename T>
struct Node {
    T data_;
    Node* next_;

    explicit Node(const T& data, Node* next = nullptr) :
        data_(data), next_(next) {}
};
