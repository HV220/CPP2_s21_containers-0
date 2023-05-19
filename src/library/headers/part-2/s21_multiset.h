#ifndef SRC_LIBRARY_HEADERS_PART_2_S21_MULTISET_H_
#define SRC_LIBRARY_HEADERS_PART_2_S21_MULTISET_H_

#include "../part-1/s21_avltree.h"

namespace s21 {

template <typename Key, typename Compare = std::less<Key>>
class S21Multiset : public AvlTree<Key> {
public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename AvlTree<Key>::iterator;
  using const_iterator = typename AvlTree<Key>::const_iterator;
  using size_type = size_t;

  S21Multiset() = default;
  S21Multiset(std::initializer_list<value_type> const &items);
  S21Multiset(const S21Multiset &other);
  S21Multiset(S21Multiset &&other) noexcept;
  ~S21Multiset() = default;

  S21Multiset &operator=(const S21Multiset &other);
  S21Multiset &operator=(S21Multiset &&other) noexcept;

  iterator insert(const value_type &value);
  void merge(S21Multiset &other);
  size_type count(const key_type &key);

  iterator lower_bound(const key_type &key);
  iterator upper_bound(const key_type &key);
  std::pair<iterator, iterator> equal_range(const Key &key);

  template <typename... Args>
  S21Vector<std::pair<iterator, bool>> emplace(Args &&...args);
};

template <typename key_type, typename Compare>
S21Multiset<key_type, Compare>::S21Multiset(
    std::initializer_list<value_type> const &items) {
  for (const auto &value : items) {
    insert(value);
  }
}

template <typename key_type, typename Compare>
S21Multiset<key_type, Compare>::S21Multiset(const S21Multiset &other)
    : AvlTree<key_type>() {
  auto it = other.begin();
  for (size_type i{}; i < other.size(); ++i, ++it) {
    insert((*it).first);
  }
}

template <typename key_type, typename Compare>
S21Multiset<key_type, Compare>::S21Multiset(S21Multiset &&other) noexcept {
  this->swap(other);
}

template <typename key_type, typename Compare>
S21Multiset<key_type, Compare> &
S21Multiset<key_type, Compare>::operator=(const S21Multiset &other) {
  if (this != &other) {
    this->clear();
    auto it = other.begin();
    for (size_type i{}; i < other.size(); ++i, ++it) {
      insert((*it).first);
    }
  }
  return *this;
}

template <typename key_type, typename Compare>
S21Multiset<key_type, Compare> &
S21Multiset<key_type, Compare>::operator=(S21Multiset &&other) noexcept {
  if (this != &other) {
    this->clear();
    this->swap(other);
  }
  return *this;
}

template <typename key_type, typename Compare>
typename S21Multiset<key_type, Compare>::iterator
S21Multiset<key_type, Compare>::insert(const value_type &value) {
  auto pair = AvlTree<key_type>::InsertNode(value, {}, true);
  return pair.first;
}

template <typename key_type, typename Compare>
void S21Multiset<key_type, Compare>::merge(S21Multiset &other) {
  iterator it = other.begin();
  iterator tmp;
  size_t size = other.size();
  for (size_t i{}; i < size; ++i) {
    insert((*it).first);
    tmp = it;
    ++tmp;
    other.erase(it);
    if (it != other.begin()) {
      tmp = AvlTree<key_type>::set_iter_root(tmp, other);
      it = tmp;
    }
  }
}

template <typename key_type, typename Compare>
typename S21Multiset<key_type, Compare>::size_type
S21Multiset<key_type, Compare>::count(const key_type &key) {
  size_type number = 0;
  auto it = AvlTree<key_type>::find(key);
  while ((*it).first == key && it != this->begin()) {
    --it;
  }
  if ((*it).first != key) {
    ++it;
  }
  while ((*it).first == key && it != this->end()) {
    ++number;
    ++it;
  }
  return number;
}

template <typename key_type, typename Compare>
typename S21Multiset<key_type, Compare>::iterator
S21Multiset<key_type, Compare>::lower_bound(const key_type &key) {
  auto it = AvlTree<key_type>::find(key);
  while ((*it).first == key && it != this->begin()) {
    --it;
  }
  if ((*it).first != key) {
    ++it;
  }
  return it;
}

template <typename key_type, typename Compare>
typename S21Multiset<key_type, Compare>::iterator
S21Multiset<key_type, Compare>::upper_bound(const key_type &key) {
  auto it = lower_bound(key);
  while ((*it).first == key) {
    ++it;
  }
  return it;
}

template <typename key_type, typename Compare>
std::pair<typename S21Multiset<key_type, Compare>::iterator,
          typename S21Multiset<key_type, Compare>::iterator>
S21Multiset<key_type, Compare>::equal_range(const key_type &key) {
  return std::make_pair(lower_bound(key), upper_bound(key));
}

template <typename Key, typename Compare>
template <typename... Args>
S21Vector<std::pair<typename AvlTree<Key>::iterator, bool>>
S21Multiset<Key, Compare>::emplace(Args &&...args) {
  S21Vector<std::pair<iterator, bool>> data;
  data.push_back(
      AvlTree<Key>::InsertNode(std::forward<Args>(args)..., {}, true));
  return data;
}

} // namespace s21

#endif //  SRC_LIBRARY_HEADERS_PART_2_S21_MULTISET_H_