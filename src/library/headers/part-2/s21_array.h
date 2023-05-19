#ifndef SRC_LIBRARY_HEADERS_PART_2_S21_ARRAY_H_
#define SRC_LIBRARY_HEADERS_PART_2_S21_ARRAY_H_

#include "../part-1/s21_vector.h"

namespace s21 {
template <typename T, size_t N> class S21Array : protected S21Vector<T> {
public:
  using value_type = typename S21Vector<T>::value_type;
  using reference = typename S21Vector<T>::reference;
  using const_reference = typename S21Vector<T>::const_reference;
  using size_type = typename S21Vector<T>::size_type;
  using iterator = value_type *;
  using const_iterator = const value_type *;

  S21Array();
  S21Array(std::initializer_list<value_type> const &items);
  S21Array(const S21Array &a);
  S21Array(S21Array &&a);
  ~S21Array() = default;
  S21Array &operator=(S21Array &&other) noexcept;

  using S21Vector<T>::at;
  using S21Vector<T>::empty;
  using S21Vector<T>::size;
  using S21Vector<T>::front;
  using S21Vector<T>::back;
  using S21Vector<T>::data;
  using S21Vector<T>::operator[];
  iterator data();
  iterator begin() const;
  iterator end() const;
  size_type max_size();
  void swap(S21Array &other);
  void fill(const_reference value);

private:
  value_type arr[N]{};
};

template <typename T, size_t N> S21Array<T, N>::S21Array() {
  this->size_ = N;
  if (this->size_) {
    this->arr_ = this->arr;
  }
}

template <typename T, size_t N>
inline S21Array<T, N>::S21Array(std::initializer_list<value_type> const &items)
    : S21Array() {
  if (this->size_ < items.size()) {
    throw std::out_of_range("error many elements");
  } else {
    std::copy(items.begin(), items.end(), this->arr_);
  }
}

template <typename T, size_t N>
S21Array<T, N>::S21Array(const S21Array &a) : S21Array() {
  std::copy(a.begin(), a.end(), this->arr_);
}

template <typename T, size_t N>
S21Array<T, N>::S21Array(S21Array &&a) : S21Array() {
  std::move(a.begin(), a.end(), this->arr_);
}

template <typename T, size_t N>
S21Array<T, N> &S21Array<T, N>::operator=(S21Array &&other) noexcept {
  std::move(other.begin(), other.end(), this->arr_);
  return *this;
}

template <typename T, size_t N>
inline void S21Array<T, N>::swap(S21Array &other) {
  std::swap(*this, other);
}

template <typename T, size_t N>
void S21Array<T, N>::fill(const_reference value) {
  if (this->size_) {
    for (size_t i = 0; i < this->size_; ++i)
      this->arr_[i] = value;
  }
}

template <typename T, size_t N>
typename S21Array<T, N>::iterator S21Array<T, N>::data() {
  return this->arr_;
}

template <typename T, size_t N>
typename S21Array<T, N>::iterator S21Array<T, N>::begin() const {
  return this->arr_;
}

template <typename T, size_t N>
typename S21Array<T, N>::iterator S21Array<T, N>::end() const {
  return this->arr_ + this->size_;
}

template <typename T, size_t N>
typename S21Array<T, N>::size_type S21Array<T, N>::max_size() {
  return this->size_;
}

} // namespace s21

#endif //  SRC_LIBRARY_HEADERS_PART_2_S21_ARRAY_H_