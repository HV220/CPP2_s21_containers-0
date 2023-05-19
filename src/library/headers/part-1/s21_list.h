#ifndef S21_CONTAINERS_SRC_SEQUENCE_S21_LIST_H_
#define S21_CONTAINERS_SRC_SEQUENCE_S21_LIST_H_

#include <initializer_list>
#include <iostream>
#include <memory>
#include <utility>
#include <valarray>

namespace s21 {

template <typename T> struct Node {
  T value{};
  Node *next{};
  Node *back{};

  Node() : value(), next(nullptr), back(nullptr) {}
  explicit Node(const T &value) : value(value), next(nullptr), back(nullptr) {}
  explicit Node(const T &&value)
      : value(std::move(value)), next(nullptr), back(nullptr) {}
};

template <typename T> class S21List {
public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  S21List();
  explicit S21List(size_type n);
  S21List(std::initializer_list<value_type> const &l);
  S21List(const S21List &l);
  S21List(S21List &&l) noexcept;
  S21List &operator=(const S21List &l) noexcept;
  S21List &operator=(S21List &&l) noexcept;
  ~S21List();

  class ListConstIterator {
  public:
    friend S21List;
    ListConstIterator() : node_(nullptr) {}
    explicit ListConstIterator(Node<value_type> *p) : node_(p) {}
    ListConstIterator(const ListConstIterator &other) : node_(other.node_) {}
    const_reference operator*() const;
    ListConstIterator &operator++();
    ListConstIterator operator++(int);
    ListConstIterator &operator--();
    ListConstIterator operator--(int);
    bool operator!=(const ListConstIterator &other);
    bool operator==(const ListConstIterator &other);

  protected:
    Node<value_type> *node_{};
  };

  class ListIterator : public ListConstIterator {
  public:
    ListIterator() { this->node_ = nullptr; }
    explicit ListIterator(Node<value_type> *p) { this->node_ = p; }
    ListIterator(const ListIterator &other) : ListConstIterator(other) {}
    reference operator*() { return this->node_->value; }
    ListIterator &operator=(const ListIterator &other);
  };

  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

  iterator insert(iterator pos, const_reference value);
  void push_back(const_reference value);
  void create_node();
  iterator begin() const;
  iterator end() const;
  bool empty();
  size_type size();
  const_reference front();
  const_reference back();
  size_type max_size();
  void remove_node(Node<value_type> *p);
  void push_front(const_reference value);
  void pop_back();
  void pop_front();
  void clear();
  void swap(S21List<T> &other);
  void merge(S21List<T> &other);
  void reverse();
  void unique();
  void sort();
  void erase(iterator pos);
  template <typename... Args>
  iterator emplace(const_iterator pos, Args &&...args);
  template <typename... Args> void emplace_back(Args &&...args);
  template <typename... Args> void emplace_front(Args &&...args);
  void splice(const_iterator pos, S21List &other);

private:
  Node<T> *fake{};
  size_type calc{};
};

template <typename T> S21List<T>::S21List() { this->fake = new Node<T>(); }

template <typename T> S21List<T>::S21List(size_type n) {

  for (size_t i = 0; i < n; i++) {
    S21List::create_node();
    this->calc++;
  }
}

template <typename T>
S21List<T>::S21List(std::initializer_list<value_type> const &l) {

  for (auto it = l.begin(); it != l.end(); ++it) {
    this->push_back(*it);
  }
}

template <typename T> S21List<T>::S21List(const S21List &l) {
  this->fake = new Node<T>();
  *this = l;
}

template <typename T> S21List<T>::S21List(S21List &&l) noexcept {

  this->fake = new Node<T>();

  *this = std::move(l);
}

template <typename T>
S21List<T> &S21List<T>::operator=(const S21List &l) noexcept {
  if (this == &l)
    return *this;

  this->clear();

  for (auto i = l.begin(); i != l.end(); ++i) {
    push_back(*i);
  }

  return *this;
}

template <typename T> S21List<T> &S21List<T>::operator=(S21List &&l) noexcept {
  if (this != &l) {
    this->clear();
    std::swap(this->calc, l.calc);
    std::swap(this->fake, l.fake);
  }

  return *this;
}

template <typename T> S21List<T>::~S21List() {
  while (this->calc) {
    this->pop_back();
  }
  delete (this->fake);
}

template <typename T>
typename S21List<T>::iterator S21List<T>::insert(iterator pos,
                                                 const_reference value) {
  if (!pos.node_ || this->fake == pos.node_) {
    this->push_back(value);
    return iterator(this->fake->back);
  }

  Node<value_type> *shift_node = pos.node_;
  Node<value_type> *prev_node = shift_node->back;
  Node<value_type> *new_node = new Node<T>(value);

  new_node->next = shift_node;
  new_node->back = prev_node;

  if (prev_node) {
    prev_node->next = new_node;
  } else {
    this->fake->back = new_node;
  }

  shift_node->back = new_node;

  ++this->calc;

  std::unique_ptr<Node<value_type>> node_ptr(new_node);
  return iterator(node_ptr.release());
}

template <typename T> void S21List<T>::push_back(const_reference value) {
  S21List::create_node();
  this->fake->back->value = value;
  this->calc++;
}

template <typename T> typename S21List<T>::iterator S21List<T>::begin() const {
  return fake->next ? iterator(this->fake->next) : iterator(this->fake);
}

template <typename T> typename S21List<T>::iterator S21List<T>::end() const {
  return iterator(this->fake);
}

template <typename T> bool S21List<T>::empty() { return !this->calc; }

template <typename T> typename S21List<T>::size_type S21List<T>::size() {
  return this->calc;
}

template <typename T> typename S21List<T>::const_reference S21List<T>::front() {
  return !this->fake->next ? this->fake->value : this->fake->next->value;
}

template <typename T> typename S21List<T>::const_reference S21List<T>::back() {

  return !this->fake->back ? this->fake->value : this->fake->back->value;
}

template <typename T> typename S21List<T>::size_type S21List<T>::max_size() {
  return (std::numeric_limits<size_type>::max() /
          sizeof(s21::Node<value_type>) / 2);
}

template <typename T> void S21List<T>::remove_node(Node<value_type> *p) {
  delete (p);
}

template <typename T>
inline void S21List<T>::push_front(const_reference value) {

  if (this->empty()) {
    this->push_back(value);
  } else {
    Node<value_type> *tmp = new Node(value);

    this->fake->next->back = tmp;
    tmp->next = this->fake->next;
    tmp->back = this->fake;
    this->fake->next = tmp;

    this->calc++;
  }
}

template <typename T> void S21List<T>::clear() {
  while (this->calc) {
    this->pop_back();
  }
}

template <typename T> inline void S21List<T>::swap(S21List<T> &other) {
  std::swap(this->fake, other.fake);
  std::swap(this->calc, other.calc);
}

template <typename T> inline void S21List<T>::merge(S21List<T> &other) {
  if (this == &other) {
    return;
  }
  auto it = this->begin();
  auto it_other = other.begin();

  while (!other.empty()) {
    if (it == this->end()) {
      this->insert(it, *it_other);
      auto temp = it_other;
      ++it_other;
      other.erase(temp);
    } else if (*it > *it_other) {
      this->insert(it, *it_other);
      auto temp = it_other;
      ++it_other;
      other.erase(temp);
    } else {
      ++it;
    }
  }
}

template <typename T> void S21List<T>::reverse() {

  for (auto it = this->begin(); it != this->end(); ++it) {
    for (auto it1 = it; it1 != this->end();) {
      ++it1;
      if (it1.node_ == this->fake) {
        break;
      }

      auto val = it.node_->value;
      it.node_->value = it1.node_->value;
      it1.node_->value = val;
    }
  }
}

template <typename T> inline void S21List<T>::unique() {

  if (this->empty()) {
    return;
  }

  auto begin = this->begin();
  while (begin != this->end()) {
    auto del_node = begin;
    auto next = ++begin;
    if (next == this->end()) {
      break;
    }
    if (*del_node == *(next)) {
      this->erase(del_node);
    }
  }
}

template <typename T> inline void S21List<T>::sort() {
  for (auto it = this->begin(); it != this->end(); ++it) {
    for (auto it1 = it; it1 != this->end();) {
      ++it1;
      if (it1.node_ == this->fake) {
        break;
      }
      if (it.node_->value >= it1.node_->value) {
        auto val = it.node_->value;
        it.node_->value = it1.node_->value;
        it1.node_->value = val;
      }
    }
  }
}

template <typename T> inline void S21List<T>::erase(iterator pos) {
  if (this->empty()) {
    return;
  }

  if (this->fake != pos.node_) {
    pos.node_->back->next = pos.node_->next;
    pos.node_->next->back = pos.node_->back;
    this->remove_node(pos.node_);
    this->calc--;
  }
}

template <typename T>
inline void S21List<T>::splice(const_iterator pos, S21List &other) {
  Node<T> *prev = pos.node_->back;

  prev->next = other.fake->next;
  other.fake->next->back = prev;
  pos.node_->back = other.fake->back;
  other.fake->back->next = pos.node_;
  this->calc += other.calc;

  other.fake->next = other.fake;
  other.fake->back = other.fake;

  other.calc = 0;
}

template <typename T>
template <typename... Args>
typename S21List<T>::iterator S21List<T>::emplace(const_iterator pos,
                                                  Args &&...args) {
  iterator tmp(pos.node_);
  return insert(tmp, value_type(std::forward<Args>(args)...));
}

template <typename T>
template <typename... Args>
inline void S21List<T>::emplace_back(Args &&...args) {
  this->push_back(value_type(std::forward<Args>(args)...));
}

template <typename T>
template <typename... Args>
inline void S21List<T>::emplace_front(Args &&...args) {
  this->push_front(value_type(std::forward<Args>(args)...));
}

template <typename T> void S21List<T>::pop_back() {

  if (this->empty()) {
    return;
  }

  if (this->fake->back && this->fake->back->back &&
      (this->fake->back->back != this->fake)) {
    auto tmp = this->fake->back;

    this->fake->back->back->next = this->fake;
    this->fake->back = this->fake->back->back;
    this->remove_node(tmp);

  } else if ((this->fake->back && this->fake->next) &&
             (this->fake->back == this->fake->next)) {

    this->remove_node(this->fake->back);

    this->fake->next = nullptr;
    this->fake->back = nullptr;
  }
  this->calc--;
}

template <typename T> inline void S21List<T>::pop_front() {

  if (this->fake->next && this->fake->next->next &&
      (this->fake->next->next != this->fake)) {
    auto tmp = this->fake->next->next;
    this->remove_node(this->fake->next);
    this->fake->next = tmp;
    this->fake->next->back = this->fake;
    this->calc--;
  } else {
    this->pop_back();
  }
}

template <typename T> void S21List<T>::create_node() {

  if (this->fake == nullptr) {
    this->fake = new Node<T>();
  }

  Node<T> *tmp = new Node<T>();

  if (this->fake->next == nullptr) {
    this->fake->next = tmp;
    this->fake->back = tmp;
    tmp->next = this->fake;
    tmp->back = this->fake;
  } else {
    tmp->next = this->fake;
    tmp->back = this->fake->back;
    this->fake->back->next = tmp;
    this->fake->back = tmp;
  }
}

template <typename value_type>
typename S21List<value_type>::const_reference
S21List<value_type>::ListConstIterator::operator*() const {
  return node_->value;
}

template <typename value_type>
typename S21List<value_type>::ListConstIterator &
S21List<value_type>::ListConstIterator::operator++() {
  this->node_ = this->node_->next;

  return *this;
}

template <typename value_type>
typename S21List<value_type>::ListConstIterator
S21List<value_type>::ListConstIterator::operator++(int) {
  ListConstIterator tmp(*this);
  this->node_ = this->node_->next;

  return tmp;
}

template <typename value_type>
typename S21List<value_type>::ListConstIterator &
S21List<value_type>::ListConstIterator::operator--() {
  this->node_ = this->node_->back;
  return *this;
}

template <typename value_type>
typename S21List<value_type>::ListConstIterator
S21List<value_type>::ListConstIterator::operator--(int) {

  ListConstIterator tmp(*this);

  this->node_ = this->node_->back;

  return tmp;
}

template <typename value_type>
typename S21List<value_type>::ListIterator &
S21List<value_type>::ListIterator::operator=(const ListIterator &other) {
  this->node_ = other.node_;
  return *this;
}

template <typename value_type>
inline bool S21List<value_type>::ListConstIterator::operator!=(
    const ListConstIterator &other) {

  return this->node_ != other.node_;
}

template <typename T>
inline bool
S21List<T>::ListConstIterator::operator==(const ListConstIterator &other) {
  return this->node_ == other.node_;
}

} // namespace s21

#endif //  SRC_LIBRARY_HEADERS_PART_1_S21_LIST_H_
