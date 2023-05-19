#ifndef SRC_LIBRARY_HEADERS_PART_1_S21_QUEUE_H_
#define SRC_LIBRARY_HEADERS_PART_1_S21_QUEUE_H_

#include "s21_list.h"

namespace s21 {

template <typename T, typename Container = S21List<T>> class S21Queue {
public:
  using container_type = Container;
  using value_type = typename Container::value_type;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;
  using size_type = typename Container::size_type;

  S21Queue() : container_() {}
  S21Queue(std::initializer_list<value_type> const &items)
      : container_(items) {}
  S21Queue(const S21Queue &q) : container_(q.container_) {}
  S21Queue(S21Queue &&q) noexcept : container_(std::move(q.container_)) {}
  ~S21Queue() = default;

  S21Queue &operator=(S21Queue<T> &&q) {
    this->container_ = std::move(q.container_);
    return *this;
  }
  S21Queue &operator=(const S21Queue<T> &q) {
    this->container_ = q.container_;
    return *this;
  }
  const_reference front();
  const_reference back();
  bool empty();
  size_type size();
  void push(const_reference value);
  void pop();
  void swap(S21Queue &other);
  template <typename... Args> void emplace_back(Args &&...args);

private:
  container_type container_{};
};

template <typename T, typename Container>
typename S21Queue<T, Container>::const_reference
S21Queue<T, Container>::front() {

  return this->container_.front();
}

template <typename T, typename Container>
typename S21Queue<T, Container>::const_reference
S21Queue<T, Container>::back() {
  return this->container_.back();
}

template <typename T, typename Container>
inline bool S21Queue<T, Container>::empty() {
  return this->container_.empty();
}

template <typename T, typename Container>
typename S21Queue<T, Container>::size_type S21Queue<T, Container>::size() {
  return this->container_.size();
}

template <typename T, typename Container>
inline void S21Queue<T, Container>::push(const_reference value) {
  this->container_.push_back(value);
}

template <typename T, typename Container>
inline void S21Queue<T, Container>::pop() {
  this->container_.pop_front();
}

template <typename T, typename Container>
inline void S21Queue<T, Container>::swap(S21Queue &other) {
  this->container_.swap(other.container_);
}

template <typename T, typename Container>
template <typename... Args>
inline void S21Queue<T, Container>::emplace_back(Args &&...args) {
  container_.emplace_back(args...);
}

} // namespace s21

#endif //  SRC_LIBRARY_HEADERS_PART_1_S21_QUEUE_H_