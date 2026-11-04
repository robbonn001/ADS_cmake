// Copyright 2026 Igor
#pragma once
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

template <class T>
class MultiStack {
  T* data_;
  size_t totalSize_;
  size_t size_;
  size_t sectors_;
  size_t* lefts_;
  size_t* rights_;
  size_t* tops_;

  bool shiftLeft(size_t sector, size_t old_left);
  bool shiftRight(size_t sector, size_t step);
  void repack(size_t sector);

 public:
  explicit MultiStack(size_t totalSize, size_t sectors = 1)
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

  MultiStack(const MultiStack<T>& other);
  MultiStack(MultiStack<T>&& other) noexcept;
  MultiStack<T>& operator=(const MultiStack<T>& other);
  MultiStack<T>& operator=(MultiStack<T>&& other) noexcept;

  ~MultiStack() {
    delete[] data_;
    delete[] lefts_;
    delete[] rights_;
    delete[] tops_;
  }

  void push(size_t sector, const T& elem) {
    if (isFullSector(sector)) repack(sector);
    tops_[sector]++;
    data_[tops_[sector]] = elem;
    ++size_;
  }
  T pop(size_t sector) {
    if (isEmptySector(sector)) throw std::out_of_range("Stack is empty!");
    T elem = data_[tops_[sector]];
    tops_[sector]--;
    --size_;
    return elem;
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
    if (!data_) return false;
    return rights_[sector] == tops_[sector];
  }
  bool isEmpty() const noexcept { return size_ == 0; }
  bool isFull() const noexcept { return size_ == totalSize_; }

  template <class U>
  friend std::ostream& operator<<(std::ostream& os, const MultiStack<U>& stack);

  template <class U>
  friend void swap(MultiStack<U>& first, MultiStack<U>& second) noexcept;
};

template <class T>
inline MultiStack<T>::MultiStack(const MultiStack<T>& other)
    : size_(other.size_),
      totalSize_(other.totalSize_),
      sectors_(other.sectors_) {
  data_ = new T[totalSize_];
  lefts_ = new size_t[sectors_];
  rights_ = new size_t[sectors_];
  tops_ = new size_t[sectors_];

  for (size_t i = 0; i < sectors_; ++i) {
    lefts_[i] = other.lefts_[i];
    rights_[i] = other.rights_[i];
    tops_[i] = other.tops_[i];
  }
  for (size_t i = 0; i < totalSize_; ++i) {
    data_[i] = other.data_[i];
  }
}

template <class T>
inline MultiStack<T>::MultiStack(MultiStack<T>&& other) noexcept
    : size_(other.size_),
      totalSize_(other.totalSize_),
      sectors_(other.sectors_),
      data_(other.data_),
      lefts_(other.lefts_),
      rights_(other.rights_),
      tops_(other.tops_) {
  other.data_ = nullptr;
  other.lefts_ = nullptr;
  other.rights_ = nullptr;
  other.tops_ = nullptr;
  other.size_ = 0;
  other.totalSize_ = 0;
  other.sectors_ = 0;
}

template <class T>
inline MultiStack<T>& MultiStack<T>::operator=(const MultiStack<T>& other) {
  if (this == &other) return *this;
  MultiStack<T> temp(other);
  swap(*this, temp);

  return *this;
}

template <class T>
inline MultiStack<T>& MultiStack<T>::operator=(MultiStack<T>&& other) noexcept {
  if (this == &other) return *this;
  MultiStack<T> temp(std::move(other));
  swap(*this, temp);
  return *this;
}

template <class T>
inline bool MultiStack<T>::shiftLeft(size_t sector, size_t step) {
  if (!isEmptySector(sector) && step != 0) {
    for (size_t i = lefts_[sector]; i <= tops_[sector] - step; ++i) {
      data_[i] = std::move(data_[step + i]);
    }
    tops_[sector] -= step;
    return true;
  }
  return false;
}

template <class T>
inline bool MultiStack<T>::shiftRight(size_t sector, size_t step) {
  if (!isFullSector(sector) && step != 0) {
    for (size_t i = tops_[sector]; i >= lefts_[sector] - step; --i) {
      data_[i + step] = std::move(data_[i]);
    }
    tops_[sector] += step;
    return true;
  }
  return false;
}

template <class T>
inline void MultiStack<T>::repack(size_t sector) {
  if (isFull()) throw std::overflow_error("Stack is full!");
  size_t extraSpace = totalSize_ - size_ - 1;
  size_t extraSpacePerStack = extraSpace / sectors_;
  size_t* oldLefts = new size_t[sectors_];
  for (size_t i = 0; i < sectors_; ++i) {
    oldLefts[i] = lefts_[i];
    rights_[i] = tops_[i] +
                 ((i == sector) ? ((extraSpace % sectors_) + 1) : 0) +
                 extraSpacePerStack;
    lefts_[i] = (i == 0) ? 0 : rights_[i - 1] + 1;
    rights_[i] -= oldLefts[i] - lefts_[i];
  }
  rights_[sectors_ - 1] = totalSize_ - 1;

  if (sector == 0) {
    for (size_t i = sectors_ - 1; i < sectors_; --i) {
      shiftRight(i, lefts_[i] - oldLefts[i]);
    }
  } else {
    for (size_t i = 1; i < sectors_; ++i) {
      size_t step = (long long)oldLefts[i] - lefts_[i];
      if (i == sector) {
        if (step > 0) {
          shiftLeft(i, step);
        } else if (step < 0) {
          shiftRight(i, -step);
        }
      } else if (i > sector) {
        shiftRight(i, -step);
      } else if (i < sector) {
        shiftLeft(i, step);
      }
    }
  }

  delete[] oldLefts;
}

template <class U>
std::ostream& operator<<(std::ostream& os, const MultiStack<U>& stack) {
  for (size_t i = 0; i < stack.sectors_; ++i) {
    for (size_t j = stack.lefts_[i]; j <= stack.tops_[i]; ++j) {
      os << stack.data_[j] << " ";
    }
    os << '\n';
  }
  return os;
}

template <class U>
inline void swap(MultiStack<U>& first, MultiStack<U>& second) noexcept {
  using std::swap;
  swap(first.data_, second.data_);
  swap(first.totalSize_, second.totalSize_);
  swap(first.size_, second.size_);
  swap(first.sectors_, second.sectors_);
  swap(first.lefts_, second.lefts_);
  swap(first.rights_, second.rights_);
  swap(first.tops_, second.tops_);
}
