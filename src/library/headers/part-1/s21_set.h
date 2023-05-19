#ifndef SRC_LIBRARY_HEADERS_PART_1_S21_SET_H_
#define SRC_LIBRARY_HEADERS_PART_1_S21_SET_H_

#include "s21_avltree.h"
#include "s21_vector.h"

namespace s21 {

template <typename Key, typename Compare = std::less<Key>>
class S21Set : public AvlTree<Key> {
public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename AvlTree<Key>::iterator;
  using const_iterator = typename AvlTree<Key>::const_iterator;
  using size_type = size_t;

  S21Set() = default;
  S21Set(std::initializer_list<value_type> const &items);
  S21Set(const S21Set &other);
  S21Set(S21Set &&other) noexcept;
  ~S21Set() = default;

  S21Set &operator=(const S21Set &other);
  S21Set &operator=(S21Set &&other) noexcept;

  std::pair<iterator, bool> insert(const value_type &value);
  void merge(S21Set &other);

  template <typename... Args>
  S21Vector<std::pair<iterator, bool>> emplace(Args &&...args);
};

template <typename key_type, typename Compare>
S21Set<key_type, Compare>::S21Set(
    const std::initializer_list<value_type> &items) {
  for (const auto &it : items) {
    insert(it);
  }
}

template <typename key_type, typename Compare>
S21Set<key_type, Compare>::S21Set(const S21Set &other) : AvlTree<key_type>() {
  auto it = other.begin();
  for (size_type i{}; i < other.size(); ++i, ++it) {
    insert((*it).first);
  }
}

template <typename key_type, typename Compare>
S21Set<key_type, Compare>::S21Set(S21Set &&other) noexcept {
  this->swap(other);
}

template <typename key_type, typename Compare>
S21Set<key_type, Compare> &
S21Set<key_type, Compare>::operator=(const S21Set &other) {
  if (this != &other) {
    this->ClearForDestruct();
    auto it = other.begin();
    for (size_type i{}; i < other.size(); ++i, ++it) {
      insert((*it).first);
    }
  }
  return *this;
}

template <typename key_type, typename Compare>
S21Set<key_type, Compare> &
S21Set<key_type, Compare>::operator=(S21Set &&other) noexcept {
  if (this != &other) {
    this->ClearForDestruct();
    this->swap(other);
  }
  return *this;
}

template <typename key_type, typename Compare>
std::pair<typename S21Set<key_type, Compare>::iterator, bool>
S21Set<key_type, Compare>::insert(const S21Set::value_type &value) {
  return AvlTree<key_type>::InsertNode(value);
}

template <typename key_type, typename Compare>
void S21Set<key_type, Compare>::merge(S21Set &other) {
  iterator it = other.begin();
  iterator tmp;
  size_t size = other.size();
  for (size_t i{}; i < size; ++i) {
    auto result = insert((*it).first);
    tmp = it;
    ++tmp;
    if (result.second) {
      other.erase(it);
    }
    if (it != other.begin() || !result.second) {
      tmp = AvlTree<key_type>::set_iter_root(tmp, other);
      it = tmp;
    }
  }
}

template <typename Key, typename Compare>
template <typename... Args>
S21Vector<std::pair<typename AvlTree<Key>::iterator, bool>>
S21Set<Key, Compare>::emplace(Args &&...args) {
  S21Vector<std::pair<iterator, bool>> data;
  data.push_back(insert(std::forward<Args>(args)...));
  return data;
}

} // namespace s21

#endif //  SRC_LIBRARY_HEADERS_PART_1_S21_SET_H_