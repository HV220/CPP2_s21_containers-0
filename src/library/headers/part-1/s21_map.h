#ifndef SRC_LIBRARY_HEADERS_PART_1_S21_MAP_H_
#define SRC_LIBRARY_HEADERS_PART_1_S21_MAP_H_

#include "s21_avltree.h"
#include "s21_vector.h"

namespace s21 {

template <typename Key, typename Value, typename Compare = std::less<Key>>
class S21Map : public AvlTree<Key, Value> {
public:
  using key_type = Key;
  using mapped_type = Value;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename AvlTree<Key, Value>::iterator;
  using const_iterator = typename AvlTree<Key, Value>::const_iterator;
  using size_type = size_t;

  S21Map() {}
  S21Map(std::initializer_list<value_type> const &items);
  S21Map(const S21Map &other);
  S21Map(S21Map &&other) noexcept;
  ~S21Map() = default;

  S21Map &operator=(const S21Map &other);
  S21Map &operator=(S21Map &&other) noexcept;

  mapped_type &at(const key_type &key);
  const mapped_type &at(const key_type &key) const;
  mapped_type &operator[](const key_type &key);

  std::pair<iterator, bool> insert(const value_type &value);
  std::pair<iterator, bool> insert(const key_type &key, const Value &obj);
  std::pair<iterator, bool> insert_or_assign(const key_type &key,
                                             const Value &obj);

  void merge(S21Map &other);

  template <typename... Args>
  S21Vector<std::pair<iterator, bool>> emplace(Args &&...args);
};

template <typename Key, typename Value, typename Compare>
S21Map<Key, Value, Compare>::S21Map(
    const std::initializer_list<value_type> &items) {
  for (const auto &it : items) {
    AvlTree<Key, Value>::InsertNode(it.first, it.second);
  }
}

template <typename Key, typename Value, typename Compare>
S21Map<Key, Value, Compare>::S21Map(const S21Map &other)
    : AvlTree<Key, Value>() {
  auto it = other.begin();
  for (size_type i{}; i < other.size(); ++i, ++it) {
    AvlTree<Key, Value>::InsertNode((*it).first, (*it).second);
  }
}

template <typename Key, typename Value, typename Compare>
S21Map<Key, Value, Compare>::S21Map(S21Map &&other) noexcept {
  this->swap(other);
}

template <typename Key, typename Value, typename Compare>
S21Map<Key, Value, Compare> &
S21Map<Key, Value, Compare>::operator=(const S21Map &other) {
  if (this != &other) {
    this->clear();
    auto it = other.begin();
    for (size_type i{}; i < other.size(); ++i, ++it) {
      AvlTree<Key, Value>::InsertNode((*it).first, (*it).second);
    }
  }
  return *this;
}

template <typename Key, typename Value, typename Compare>
S21Map<Key, Value, Compare> &
S21Map<Key, Value, Compare>::operator=(S21Map &&other) noexcept {
  if (this != &other) {
    this->clear();
    this->swap(other);
  }
  return *this;
}

template <typename Key, typename Value, typename Compare>
Value &S21Map<Key, Value, Compare>::at(const key_type &key) {
  bool find = false;
  auto ptr = AvlTree<Key, Value>::SearchNode(key, &find);
  if (!find) {
    throw std::out_of_range("key not found");
  }
  return (*ptr).second;
}

template <typename key_type, typename Value, typename Compare>
const Value &S21Map<key_type, Value, Compare>::at(const key_type &key) const {
  bool find = false;
  auto ptr = AvlTree<key_type, Value>::SearchNode(key, &find);
  if (!find) {
    throw std::out_of_range("key not found");
  }
  return (*ptr).second;
}

template <typename key_type, typename Value, typename Compare>
Value &S21Map<key_type, Value, Compare>::operator[](const key_type &key) {
  bool find = false;
  auto ptr = AvlTree<key_type, Value>::SearchNode(key, &find);
  if (!find) {
    ptr = this->end();
  }
  return (*ptr).second;
}

template <typename key_type, typename Value, typename Compare>
std::pair<typename S21Map<key_type, Value, Compare>::iterator, bool>
S21Map<key_type, Value, Compare>::insert(const S21Map::value_type &value) {
  return AvlTree<key_type, Value>::InsertNode(value.first, value.second);
}

template <typename key_type, typename Value, typename Compare>
std::pair<typename S21Map<key_type, Value, Compare>::iterator, bool>
S21Map<key_type, Value, Compare>::insert(const key_type &key,
                                         const Value &obj) {
  return AvlTree<key_type, Value>::InsertNode(key, obj);
}

template <typename key_type, typename Value, typename Compare>
std::pair<typename S21Map<key_type, Value, Compare>::iterator, bool>
S21Map<key_type, Value, Compare>::insert_or_assign(const key_type &key,
                                                   const Value &obj) {
  std::pair<typename S21Map<key_type, Value, Compare>::iterator, bool> result;
  auto it = this->find(key);
  if (it != this->end()) {
    this->change_value(it, obj);
    result.first = it;
    result.second = false;
  } else {
    result = this->InsertNode(key, obj);
  }
  return result;
}

template <typename key_type, typename Value, typename Compare>
void S21Map<key_type, Value, Compare>::merge(S21Map &other) {
  iterator it = other.begin();
  iterator tmp;
  size_t size = other.size();
  for (size_t i{}; i < size; ++i) {
    auto result = insert((*it).first, (*it).second);
    tmp = it;
    ++tmp;
    if (result.second) {
      other.erase(it);
    }
    if (it != other.begin() || !result.second) {
      it = tmp;
    }
  }
}

template <typename Key, typename Value, typename Compare>
template <typename... Args>
S21Vector<std::pair<typename AvlTree<Key, Value>::iterator, bool>>
S21Map<Key, Value, Compare>::emplace(Args &&...args) {
  S21Vector<std::pair<iterator, bool>> data;
  data.push_back(insert(std::forward<Args>(args)...));
  return data;
}

} // namespace s21

#endif //  SRC_LIBRARY_HEADERS_PART_1_S21_MAP_H_