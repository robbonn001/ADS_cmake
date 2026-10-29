// Copyright 2026 Igor
#pragma once
#include <stdexcept>
#include <string>

template <class T>
class MultiStack {
  T* data_;
  size_t totalSize_;
  size_t size_;
  size_t sectors_;
  size_t* lefts_;
  size_t* rights_;
  size_t* tops_;

  void repack();

 public:
  MultiStack(size_t totalSize, size_t sectors = 1)
      : totalSize_(totalSize),
        sectors_(sectors),
        size_(0),
        data_(new T[totalSize]()),
        lefts_(new size_t[sectors]()),
        rights_(new size_t[sectors]()),
        tops_(new size_t[sectors]()) {
    size_t countPerStack = totalSize_ / sectors_;
    for (size_t i = 0; i < sectors_; ++i) {
      lefts_[i] = countPerStack * i;
      rights_[i] = countPerStack * (i + 1) - 1;
      tops_[i] = lefts_[i] - 1;
    }
    rights_[sectors_ - 1] = totalSize_ - 1;
  }

  /*MultiStack(const MultiStack<T>& other);
  MultiStack(MultiStack<T>&& other);*/

  ~MultiStack() {
    delete[] data_;
    delete[] lefts_;
    delete[] rights_;
    delete[] tops_;
  }

  void push(size_t sector, const T& elem) {
    if (sector >= sectors_) throw std::out_of_range("Sector is wrong");
    if (isFullSector(sector)) throw std::out_of_range("Stack is full!");
    tops_[sector]++;
    data_[tops_[sector]] = elem;
    ++size_;
  }
  T pop(size_t sector) {
    if (isEmptySector(sector)) throw std::out_of_range("Stack is empty!");
    tops_[sector]--;
    --size_;
  }
  T& top(size_t sector) {
    if (isEmptySector(sector)) throw std::out_of_range("Stack is empty!");
    return data_[tops_[sector]];
  }

  bool isEmptySector(size_t sector) const {
    if (sector >= sectors_) throw std::out_of_range("Sector is wrong");
    return lefts_[sector] - 1 == tops_[sector];
  }
  bool isFullSector(size_t sector) const {
    if (sector >= sectors_) throw std::out_of_range("Sector is wrong");
    return rights_[sector] == tops_[sector];
  }
  bool isEmpty() const noexcept { return size_ == 0; }
  bool isFull() const noexcept { return size_ == totalSize_; }
};