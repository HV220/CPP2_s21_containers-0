#ifndef SRC_LIBRARY_HEADERS_PART_1_S21_STACK_H_
#define SRC_LIBRARY_HEADERS_PART_1_S21_STACK_H_
#include "s21_list.h"

namespace s21 {

template <typename T, typename Container = S21List<T>> class S21Stack {
public:
  using container_type = Container;
  using value_type = typename Container::value_type;
  using size_type = typename Container::size_type;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;
  S21Stack() : container_() {}
  S21Stack(std::initializer_list<value_type> const &items)
      : container_(items) {}
  S21Stack(const S21Stack &q) : container_(q.container_) {}
  S21Stack(S21Stack &&q) noexcept : container_(std::move(q.container_)) {}
  ~S21Stack() = default;
  S21Stack &operator=(S21Stack<T> &&q) {
    this->container_ = std::move(q.container_);
    return *this;
  }
  S21Stack &operator=(const S21Stack<T> &q) {
    this->container_ = q.container_;
    return *this;
  }
  void push(T &&value) { container_.push_front(value); }
  void pop() { container_.pop_front(); }
  const_reference top() { return container_.front(); }
  bool empty() { return container_.empty(); }
  void swap(S21Stack<T> &other) { this->container_.swap(other.container_); }
  size_type size() { return container_.size(); }
  void push(const_reference value) { container_.push_front(value); }

  template <typename... Args> void emplace_front(Args &&...args) {
    container_.emplace_front(args...);
  }

private:
  container_type container_{};
};

} // namespace s21

#endif //  SRC_LIBRARY_HEADERS_PART_1_S21_STACK_H_