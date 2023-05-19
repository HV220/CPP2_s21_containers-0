#ifndef SRC_LIBRARY_HEADERS_PART_1_S21_VECTOR_H_
#define SRC_LIBRARY_HEADERS_PART_1_S21_VECTOR_H_

#include <cmath>
#include <cstring>
#include <iostream>
#include <stdexcept>

namespace s21 {

template <typename T> class S21Vector {
public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using pointer = T *;

protected:
  size_type size_{};
  size_type capacity_{};
  value_type *arr_{};

public:
  // constructs
  S21Vector() = default;
  explicit S21Vector(size_type size);
  S21Vector(std::initializer_list<value_type> const &items);
  S21Vector(const S21Vector &other);
  S21Vector(S21Vector &&other);

  // Destructor
  ~S21Vector();

  // Vector Element access
  reference at(size_type pos);
  const_reference front();
  const_reference back();
  value_type *data() noexcept;

  // Reload operator
  reference operator[](size_type pos) noexcept;
  S21Vector &operator=(S21Vector &&other) noexcept;
  S21Vector &operator=(const S21Vector &other);

  // ConstIterator class
  class ConstIterator {
  public:
    friend class S21Vector;
    ConstIterator() { this->ptr_ = nullptr; }
    ConstIterator(pointer p) { this->ptr_ = p; }
    ConstIterator(const ConstIterator &other) : ptr_(other.ptr_) {}
    ~ConstIterator() {}

    ConstIterator &operator=(const ConstIterator &other) {
      this->ptr_ = other.ptr_;
      return *this;
    }

    ConstIterator &operator++() {
      this->ptr_++;
      return *this;
    };

    const_reference operator*() { return *this->ptr_; };

    ConstIterator operator+(const size_t value) {
      ConstIterator it_const(this->ptr_ + value);
      return it_const;
    };

    bool operator!=(const ConstIterator &other) const {
      return this->ptr_ != other.ptr_;
    };

    bool operator==(const ConstIterator &other) const {
      return this->ptr_ == other.ptr_;
    };

    ConstIterator operator++(int) {
      ConstIterator temp(*this);
      this->ptr_++;
      return temp;
    };

    ConstIterator &operator--() {
      this->ptr_--;
      return *this;
    };

    ConstIterator operator--(int) {
      ConstIterator temp(*this);
      this->ptr_--;
      return temp;
    };

  protected:
    S21Vector::pointer ptr_;
  };

  // Iterator class
  class Iterator : public ConstIterator {
  public:
    Iterator() : ConstIterator() {}
    Iterator(pointer p) : ConstIterator(p) {}
    Iterator(const Iterator &other) : ConstIterator(other) {}
    Iterator(const ConstIterator &other) : ConstIterator(other) {}
    ~Iterator() {}

    reference operator*() { return *this->ptr_; };

    Iterator &operator=(const Iterator &other) {
      this->ptr_ = other.ptr_;
      return *this;
    }

    Iterator operator+(const size_t value) {
      Iterator it(this->ptr_ + value);
      return it;
    };

    Iterator &operator=(const value_type &val) {
      Iterator it(this->ptr_ + val);
      return it;
    };

    Iterator operator-(const Iterator &value) { return this->ptr_ - value; };

    Iterator operator-(const size_t value) {
      Iterator it(this->ptr_ - value);
      return it;
    };
  };

  using iterator = Iterator;
  using const_iterator = ConstIterator;

  // Vector Iterator
  iterator begin() const { return iterator(arr_); }
  iterator end() const { return iterator(arr_ + size_); }

  // Vector Capacity
  bool empty() const noexcept { return size_ == 0; }

  size_type size() const noexcept { return this->size_; }

  size_type max_size() const noexcept {
    return (std::numeric_limits<size_type>::max() / sizeof(value_type) / 2);
  }

  size_type capacity() const noexcept { return this->capacity_; }

  void reserve(size_type size);
  void shrink_to_fit();

  // Vector Modifiers
  void clear() noexcept { size_ = 0; }
  void push_back(const_reference value);
  void pop_back() noexcept {
    if (this->size_)
      --size_;
  }
  void swap(S21Vector &other);
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  template <typename... Args> void emplace_back(Args &&...args);
  template <typename... Args>
  iterator emplace(const_iterator pos, Args &&...args);

  // Helper function
private:
  void initialization(size_type size);
  void copy_vector(const S21Vector &other);
  void move_vector(S21Vector &other) noexcept;
  void overwriting_arr(size_type size);
  void clear_arr();
};

// Сonstructs
template <typename value_type>
S21Vector<value_type>::S21Vector(size_type size) {
  initialization(size);
}

template <typename value_type>
S21Vector<value_type>::S21Vector(
    std::initializer_list<value_type> const &items) {
  initialization(items.size());
  std::copy(items.begin(), items.end(), arr_);
}

template <typename value_type>
S21Vector<value_type>::S21Vector(const S21Vector &other) {
  copy_vector(other);
}

template <typename value_type>
S21Vector<value_type>::S21Vector(S21Vector &&other) {
  move_vector(other);
}

// Destructor
template <typename value_type> S21Vector<value_type>::~S21Vector() {
  if (this->capacity_) {
    delete[] arr_;
  }
}

// Vector Element access
template <typename value_type>
typename S21Vector<value_type>::reference
S21Vector<value_type>::at(size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("out_of_range");
  }
  return arr_[pos];
}

template <typename value_type>
typename S21Vector<value_type>::const_reference S21Vector<value_type>::front() {
  if (!size_) {
    throw std::out_of_range("vector_array_is_nullptr");
  }
  return *arr_;
}

template <typename value_type>
typename S21Vector<value_type>::const_reference S21Vector<value_type>::back() {
  return *(arr_ + size_ - 1);
}

template <typename value_type>
typename S21Vector<value_type>::value_type *
S21Vector<value_type>::data() noexcept {
  return arr_;
}

// Reload operator
template <typename value_type>
typename S21Vector<value_type>::reference
S21Vector<value_type>::operator[](size_type pos) noexcept {
  return arr_[pos];
}

template <typename value_type>
S21Vector<value_type> &
S21Vector<value_type>::operator=(S21Vector &&other) noexcept {
  if (this != &other) {
    delete[] arr_;
    move_vector(other);
  }
  return *this;
}

template <typename value_type>
S21Vector<value_type> &
S21Vector<value_type>::operator=(const S21Vector &other) {
  if (this != &other) {
    delete[] arr_;
    copy_vector(other);
  }
  return *this;
}

// Vector Capacity
template <typename value_type>
void S21Vector<value_type>::reserve(size_type size) {
  if (size >= capacity_ && size <= this->max_size()) {
    overwriting_arr(size);
  }
}

template <typename value_type> void S21Vector<value_type>::shrink_to_fit() {
  if (capacity_ > size_) {
    overwriting_arr(size_);
  }
}

// Vector Modifiers
template <typename value_type>
void S21Vector<value_type>::push_back(const_reference value) {
  if (capacity_ == 0) {
    reserve(1);
  } else if (capacity_ == size_) {
    reserve(2 * capacity_);
  }
  arr_[size_] = value;
  ++size_;
}

template <typename value_type>
void S21Vector<value_type>::swap(S21Vector &other) {
  if (this->arr_ != other.arr_) {
    std::swap(this->size_, other.size_);
    std::swap(this->capacity_, other.capacity_);
    std::swap(this->arr_, other.arr_);
  }
}

template <typename value_type>
typename S21Vector<value_type>::iterator
S21Vector<value_type>::insert(iterator pos, const_reference value) {

  auto position = &(*pos) - this->arr_;

  if (position == (&(*(this->end())) - this->arr_)) {
    this->push_back(value);
    auto it_res = this->end();
    return --it_res;
  }

  S21Vector<value_type> tmp;

  for (auto it = this->begin(); it != this->end(); it++) {
    if (position == (&(*it) - this->arr_)) {
      tmp.push_back(value);
    }
    tmp.push_back(*it);
  }

  for (auto it = tmp.begin(), it_origin = this->begin(); it != tmp.end();
       ++it) {
    if (it_origin == this->end()) {
      this->push_back(*it);
    } else {
      *it_origin = *it;
      it_origin++;
    }
  }

  auto it_res = this->begin();

  for (it_res = this->begin(); it_res != this->end(); it_res++) {
    if (&(*it_res) - this->arr_ == position) {
      break;
    }
  }

  return it_res;
}

template <typename value_type> void S21Vector<value_type>::erase(iterator pos) {
  if (capacity_) {
    iterator tmp = begin();
    iterator iter_begin = tmp;
    iterator iter_end = end() - 1;
    size_t n{};
    for (; tmp != pos; ++n, ++tmp) {
      if (tmp == (iter_begin - 1) || tmp == iter_end) {
        throw std::out_of_range("incorrect pos");
      }
    }
    for (; tmp != iter_end; ++tmp) {
      *tmp = *(tmp + 1);
    }
  }
  --size_;
}

// Helper function
template <typename value_type>
void S21Vector<value_type>::initialization(size_type size) {
  capacity_ = size_ = size;
  arr_ = new value_type[size]{};
}

template <typename value_type>
void S21Vector<value_type>::copy_vector(const S21Vector &other) {
  if (other.capacity_) {
    size_ = other.size_;
    capacity_ = other.capacity_;
    arr_ = new value_type[other.capacity_]{};
    for (size_type i{}; i < other.size_; ++i) {
      arr_[i] = other.arr_[i];
    }
  }
}

template <typename value_type>
void S21Vector<value_type>::move_vector(S21Vector &other) noexcept {
  std::swap(this->size_, other.size_);
  std::swap(this->capacity_, other.capacity_);
  std::swap(this->arr_, other.arr_);
  other.size_ = 0;
  other.capacity_ = 0;
  other.arr_ = nullptr;
}

template <typename value_type>
void S21Vector<value_type>::overwriting_arr(size_type size) {
  capacity_ = size;
  value_type *tmp = new value_type[capacity_]{};
  for (size_type i{}; i < size_; ++i) {
    tmp[i] = arr_[i];
  }
  delete[] arr_;
  arr_ = tmp;
}

template <typename T> inline void S21Vector<T>::clear_arr() {
  delete[] this->arr_;
}

template <typename T>
template <typename... Args>
void S21Vector<T>::emplace_back(Args &&...args) {
  push_back(value_type(std::forward<Args>(args)...));
}

template <typename value_type>
template <typename... Args>
typename S21Vector<value_type>::iterator
S21Vector<value_type>::emplace(const_iterator pos, Args &&...args) {
  iterator tmp(pos.ptr_);
  return insert(tmp, value_type(std::forward<Args>(args)...));
}

} // namespace s21

#endif //  SRC_LIBRARY_HEADERS_PART_1_S21_VECTOR_H_