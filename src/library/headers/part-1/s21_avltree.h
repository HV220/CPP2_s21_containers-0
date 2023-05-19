#ifndef SRC_LIBRARY_HEADERS_PART_1_AvlTree_H_
#define SRC_LIBRARY_HEADERS_PART_1_AvlTree_H_

#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <limits>
#include <utility>

namespace s21 {

template <typename Key, typename T> struct AvlNode {
  AvlNode<const Key, T> *parent_{};
  AvlNode<const Key, T> *left_{};
  AvlNode<const Key, T> *right_{};
  int height_{};
  std::pair<const Key, T> *data_{};
};

struct Height {
  int left{};
  int right{};
};

template <typename Key, typename T> struct TwoPointer {
  AvlNode<const Key, T> *current_node{};
  AvlNode<const Key, T> *new_node{};
};

template <typename Key, typename T = int, typename Compare = std::less<Key>>
class AvlTree {
public:
  using key_type = Key;
  using value_type = std::pair<const Key, T>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

protected:
  AvlNode<const key_type, T> *root_{};
  AvlNode<const key_type, T> *begin_{};
  AvlNode<const key_type, T> *end_{};
  Compare compare_{};
  size_type size_{};

public:
  // Constructors
  AvlTree() {
    begin_ = new AvlNode<const key_type, T>;
    end_ = new AvlNode<const key_type, T>;
    end_->data_ = new value_type();
  };
  ~AvlTree() {
    ClearForDestruct();
    delete end_->data_;
    delete end_;
    end_ = nullptr;
    size_ = 0;
  }

  // Iterators
  class ConstIterator {
  protected:
    AvlNode<const key_type, T> *node_{};
    AvlNode<const key_type, T> *iter_root_{};
    AvlNode<const key_type, T> *iter_begin_{};
    AvlNode<const key_type, T> *iter_end_{};

  public:
    friend AvlTree;
    ConstIterator() = default;
    ConstIterator(const ConstIterator &other)
        : node_(other.node_), iter_root_(other.iter_root_),
          iter_begin_(other.iter_begin_), iter_end_(other.iter_end_) {}

    ConstIterator &operator++();
    ConstIterator operator++(int);
    ConstIterator &operator--();
    ConstIterator operator--(int);
    std::pair<const key_type, T> &operator*() const {
      return *this->node_->data_;
    }
    std::pair<const key_type, T> *operator->() const {
      return this->node_->data_;
    }
    bool operator!=(const ConstIterator &other) const {
      return node_ != other.node_;
    }
    bool operator==(const ConstIterator &other) const {
      return node_ == other.node_;
    }

    // helper iterator functions
  private:
    void IterPlusPlus();
    void IterMinusMinus();
    explicit ConstIterator(AvlNode<const key_type, T> *node,
                           AvlNode<const key_type, T> *begin,
                           AvlNode<const key_type, T> *end)
        : node_(node), iter_root_(begin), iter_begin_(begin), iter_end_(end) {}
  };

  class Iterator : public ConstIterator {
  public:
    friend AvlTree;
    Iterator() = default;
    Iterator(const Iterator &other) : ConstIterator(other) {}
    Iterator &operator=(const Iterator &other);

  private:
    explicit Iterator(AvlNode<const key_type, T> *node,
                      AvlNode<const key_type, T> *begin,
                      AvlNode<const key_type, T> *end) {
      this->node_ = node;
      this->iter_root_ = begin;
      this->iter_begin_ = begin;
      this->iter_end_ = end;
    }
  };

  using iterator = Iterator;
  using const_iterator = ConstIterator;

  iterator begin() const;
  iterator end() const;

  // AvlTree Capacity
  bool empty() const noexcept { return !size_; }
  size_type size() const noexcept { return size_; }
  size_type max_size() const noexcept {
    return (std::numeric_limits<size_type>::max() /
            sizeof(AvlNode<const Key, T>) / 2);
  }

  // AvlTree Modifiers
  void clear();
  void erase(iterator pos);
  void swap(AvlTree &other) noexcept;

  // AvlTree Lookup
  iterator find(const key_type &key);
  bool contains(const Key &key);

  // Helper functions
protected:
  std::pair<iterator, bool> InsertNode(const key_type &key, T value = 0,
                                       bool dublicate = false);
  void ClearForDestruct();
  iterator set_iter_root(iterator it, AvlTree &other);
  iterator SearchNode(const Key &key, bool *find);
  void change_value(iterator it, T value);

private:
  AvlNode<const key_type, T> *AddNode(AvlNode<const key_type, T> *node,
                                      const key_type &key, T &value,
                                      bool *node_create, bool dublicate);
  TwoPointer<const key_type, T> CreateNodeLeft(AvlNode<const key_type, T> *node,
                                               const key_type &key, T &value);
  AvlNode<const key_type, T> *CreateNodeRight(AvlNode<const key_type, T> *node,
                                              const key_type &key, T &value);

  // Rotate functions
  void Balancing(AvlNode<const key_type, T> *node);
  void LittleRotateLeft(AvlNode<const key_type, T> *node);
  void LittleRotateRight(AvlNode<const key_type, T> *node);
  void BigRotateLeft(AvlNode<const key_type, T> *node);
  void BigRotateRight(AvlNode<const key_type, T> *node);

  // Helper function
  void Copy(AvlNode<const key_type, T> *node, AvlNode<const key_type, T> *tmp);
  Height get_left_right_height(AvlNode<const key_type, T> *node);
  int Traverse(AvlNode<const key_type, T> *node);
  void DeleteNode(AvlNode<const key_type, T> *node);
  void change_child(AvlNode<const key_type, T> *node,
                    AvlNode<const key_type, T> *child);
  void SwapNode(AvlNode<const key_type, T> *first,
                AvlNode<const key_type, T> *second);

  // Возвращает ноду, начиная с которой необходимо произвести балансировку
  AvlNode<const key_type, T> *
  DelNodeWithNullOrOneChild(AvlNode<const key_type, T> *pos);
};

// Iterators
template <typename key_type, typename T, typename Compare>
typename AvlTree<key_type, T, Compare>::ConstIterator &
AvlTree<key_type, T, Compare>::ConstIterator::operator++() {
  IterPlusPlus();
  return *this;
}

template <typename key_type, typename T, typename Compare>
typename AvlTree<key_type, T, Compare>::ConstIterator
AvlTree<key_type, T, Compare>::ConstIterator::operator++(int) {
  ConstIterator tmp(*this);
  IterPlusPlus();
  return tmp;
}

template <typename key_type, typename T, typename Compare>
typename AvlTree<key_type, T, Compare>::ConstIterator &
AvlTree<key_type, T, Compare>::ConstIterator::operator--() {
  IterMinusMinus();
  return *this;
}

template <typename key_type, typename T, typename Compare>
typename AvlTree<key_type, T, Compare>::ConstIterator
AvlTree<key_type, T, Compare>::ConstIterator::operator--(int) {
  ConstIterator tmp(*this);
  IterMinusMinus();
  return tmp;
}

template <typename Key, typename T, typename Compare>
typename AvlTree<Key, T, Compare>::Iterator &
AvlTree<Key, T, Compare>::Iterator::operator=(const AvlTree::Iterator &other) {
  this->node_ = other.node_;
  this->iter_root_ = other.iter_root_;
  this->iter_begin_ = other.iter_begin_;
  this->iter_end_ = other.iter_end_;
  return *this;
}

template <typename key_type, typename T, typename Compare>
typename AvlTree<key_type, T, Compare>::iterator
AvlTree<key_type, T, Compare>::begin() const {
  if (!root_) {
    begin_->data_ = new value_type();
  }
  iterator it(begin_, begin_, end_);
  return it;
}

template <typename key_type, typename T, typename Compare>
typename AvlTree<key_type, T, Compare>::iterator
AvlTree<key_type, T, Compare>::end() const {
  iterator it(end_, begin_, end_);
  return it;
}

// Helper iterator functions
template <typename key_type, typename T, typename Compare>
void AvlTree<key_type, T, Compare>::ConstIterator::IterPlusPlus() {
  while (iter_root_->parent_) {
    iter_root_ = iter_root_->parent_;
  }
  AvlNode<const key_type, T> *end = iter_root_;
  while (end->right_) {
    end = end->right_;
  }
  if (node_->right_) {
    node_ = node_->right_;
    while (node_->left_) {
      node_ = node_->left_;
    }
  } else if (node_->parent_) {
    if (node_->parent_->left_ == node_) {
      node_ = node_->parent_;
    } else if (node_->parent_->right_ == node_ && node_ != end) {
      while (node_->parent_->left_ != node_ && node_->parent_) {
        node_ = node_->parent_;
      }
      if (node_->parent_) {
        node_ = node_->parent_;
      }
    } else if (node_ == end) {
      node_ = iter_end_;
    }
  } else if (node_ == iter_end_ && iter_root_->height_) {
    node_ = iter_root_;
  } else if (node_ == end) {
    node_ = iter_end_;
  }
}

template <typename key_type, typename T, typename Compare>
void AvlTree<key_type, T, Compare>::ConstIterator::IterMinusMinus() {
  while (iter_root_->parent_) {
    iter_root_ = iter_root_->parent_;
  }
  while (iter_begin_->left_) {
    iter_begin_ = iter_begin_->left_;
  }
  if (node_ == iter_end_ && iter_root_->height_) {
    node_ = iter_root_;
    while (node_->right_) {
      node_ = node_->right_;
    }
  } else if (node_->left_) {
    node_ = node_->left_;
    while (node_->right_) {
      node_ = node_->right_;
    }
  } else if (node_->parent_) {
    if (node_->parent_->right_ == node_) {
      node_ = node_->parent_;
    } else if (node_->parent_->left_ == node_ && node_ != iter_begin_) {
      while (node_->parent_->right_ != node_) {
        node_ = node_->parent_;
      }
      node_ = node_->parent_;
    }
  }
}

// Insert node
template <typename key_type, typename T, typename Compare>
std::pair<typename AvlTree<key_type, T, Compare>::iterator, bool>
AvlTree<key_type, T, Compare>::InsertNode(const key_type &key, T value,
                                          bool dublicate) {
  bool node_create = true;
  AvlNode<const key_type, T> *node{};
  iterator it;
  if (!root_) {
    if (!begin_) {
      begin_ = new AvlNode<const key_type, T>;
    }
    root_ = node = begin_;
    root_->height_ = 1;
    root_->data_ = new value_type(key, value);
    size_++;
  } else {
    node = AddNode(root_, key, value, &node_create, dublicate);
    while (root_->parent_) {
      root_ = root_->parent_;
    }
  }
  it.node_ = node;
  if (node_create) {
    it.iter_root_ = root_;
    it.iter_begin_ = begin_;
    it.iter_end_ = end_;
  }
  std::pair<typename AvlTree<key_type, T, Compare>::iterator, bool> my_pair(
      it, node_create);
  return my_pair;
}

template <typename key_type, typename T, typename Compare>
AvlNode<const key_type, T> *
AvlTree<key_type, T, Compare>::AddNode(AvlNode<const key_type, T> *node,
                                       const key_type &key, T &value,
                                       bool *create, bool dublicate) {
  AvlNode<const key_type, T> *create_node{};
  if (node->data_->first == key && !dublicate) {
    create_node = node;
    *create = false;
  } else if (compare_(key, node->data_->first)) {
    if (node->left_) {
      create_node = AddNode(node->left_, key, value, create, dublicate);
    } else {
      TwoPointer<const key_type, T> TwoPointer;
      TwoPointer = CreateNodeLeft(node, key, value);
      create_node = TwoPointer.new_node;
      node = TwoPointer.current_node;
    }
  } else {
    if (node->right_) {
      create_node = AddNode(node->right_, key, value, create, dublicate);
    } else {
      create_node = CreateNodeRight(node, key, value);
    }
  }
  Balancing(node);
  return create_node;
}

template <typename key_type, typename T, typename Compare>
AvlNode<const key_type, T> *
AvlTree<key_type, T, Compare>::CreateNodeRight(AvlNode<const key_type, T> *node,
                                               const key_type &key, T &value) {
  node->right_ = new AvlNode<const key_type, T>;
  node->right_->parent_ = node;
  node->right_->height_ = 1;
  node->right_->data_ = new value_type(key, value);
  size_++;
  return node->right_;
}

template <typename key_type, typename T, typename Compare>
TwoPointer<const key_type, T>
AvlTree<key_type, T, Compare>::CreateNodeLeft(AvlNode<const key_type, T> *node,
                                              const key_type &key, T &value) {
  TwoPointer<const key_type, T> TwoPointer;
  if (compare_(key, begin_->data_->first)) {
    AvlNode<const key_type, T> *ptr = new AvlNode<const key_type, T>;
    Copy(node, ptr);
    if (node->parent_) {
      node->parent_->left_ = ptr;
    }
    if (node->right_) {
      node->right_->parent_ = ptr;
    }
    node = ptr;
    node->left_ = begin_;
    TwoPointer.current_node = ptr;
  } else {
    node->left_ = new AvlNode<const key_type, T>;
    TwoPointer.current_node = node;
  }
  TwoPointer.new_node = node->left_;
  node->left_->parent_ = node;
  node->left_->right_ = nullptr;
  node->left_->height_ = 1;
  value_type *tmp = new value_type(key, value);
  node->left_->data_ = tmp;
  size_++;
  return TwoPointer;
}

// Rotate functions
template <typename key_type, typename T, typename Compare>
void AvlTree<key_type, T, Compare>::Balancing(
    AvlNode<const key_type, T> *node) {
  Height height = get_left_right_height(node);
  node->height_ = std::max(height.left, height.right) + 1;
  if ((height.right - height.left) == 2) {
    Height height_right = get_left_right_height(node->right_);
    if (height_right.left <= height_right.right) {
      LittleRotateLeft(node);
    } else {
      BigRotateLeft(node);
    }
  } else if ((height.left - height.right) == 2) {
    Height height_left = get_left_right_height(node->left_);
    if (height_left.left >= height_left.right) {
      LittleRotateRight(node);
    } else {
      BigRotateRight(node);
    }
  }
}

template <typename key_type, typename T, typename Compare>
void AvlTree<key_type, T, Compare>::LittleRotateLeft(
    AvlNode<const key_type, T> *node) {
  AvlNode<const key_type, T> *tmp = new AvlNode<const key_type, T>;
  Copy(node, tmp);
  int height_left = 0;
  if (node->left_) {
    height_left = node->left_->height_;
  }
  node->height_ = height_left + 1;
  node->right_ = tmp->right_->left_;
  node->parent_ = tmp->right_;
  if (!tmp->parent_) {
    root_ = tmp->right_;
  } else {
    if (tmp->parent_->left_ == node) {
      tmp->parent_->left_ = tmp->right_;
    } else {
      tmp->parent_->right_ = tmp->right_;
    }
  }
  if (tmp->right_->left_) {
    tmp->right_->left_->parent_ = node;
  }
  tmp->right_->left_ = node;
  tmp->right_->parent_ = tmp->parent_;
  node = tmp->right_;
  delete tmp;
  Height height = get_left_right_height(node);
  node->height_ = std::max(height.left, height.right) + 1;
}

template <typename key_type, typename T, typename Compare>
void AvlTree<key_type, T, Compare>::LittleRotateRight(
    AvlNode<const key_type, T> *node) {
  AvlNode<const key_type, T> *tmp = new AvlNode<const key_type, T>;
  Copy(node, tmp);
  int height_right = 0;
  if (node->right_) {
    height_right = node->right_->height_;
  }
  node->height_ = height_right + 1;
  node->left_ = tmp->left_->right_;
  node->parent_ = tmp->left_;
  if (!tmp->parent_) {
    root_ = tmp->left_;
  } else {
    if (tmp->parent_->left_ == node) {
      tmp->parent_->left_ = tmp->left_;
    } else {
      tmp->parent_->right_ = tmp->left_;
    }
  }
  if (tmp->left_->right_) {
    tmp->left_->right_->parent_ = node;
  }
  tmp->left_->right_ = node;
  tmp->left_->parent_ = tmp->parent_;
  node = tmp->left_;
  delete tmp;
  Height height = get_left_right_height(node);
  node->height_ = std::max(height.left, height.right) + 1;
}

template <typename key_type, typename T, typename Compare>
void AvlTree<key_type, T, Compare>::BigRotateLeft(
    AvlNode<const key_type, T> *node) {
  LittleRotateRight(node->right_);
  LittleRotateLeft(node);
}

template <typename key_type, typename T, typename Compare>
void AvlTree<key_type, T, Compare>::BigRotateRight(
    AvlNode<const key_type, T> *node) {
  LittleRotateLeft(node->left_);
  LittleRotateRight(node);
}

// AvlTree Modifiers
template <typename key_type, typename T, typename Compare>
void AvlTree<key_type, T, Compare>::clear() {
  if (!empty()) {
    if (root_) {
      Traverse(root_);
      root_ = nullptr;
      size_ = 0;
    }
    begin_ = new AvlNode<const key_type, T>;
  }
}

template <typename key_type, typename T, typename Compare>
void AvlTree<key_type, T, Compare>::ClearForDestruct() {
  Traverse(root_);
  if (!root_) {
    delete begin_->data_;
    delete begin_;
    begin_ = nullptr;
  }
  root_ = nullptr;
  size_ = 0;
}

template <typename key_type, typename T, typename Compare>
void AvlTree<key_type, T, Compare>::erase(iterator pos) {
  if (pos.node_) {
    AvlNode<const key_type, T> *node{};
    if (pos.node_->right_ && pos.node_->left_) {
      node = pos.node_->right_;
      while (node->left_) {
        node = node->left_;
      }
      SwapNode(pos.node_, node);
      node = DelNodeWithNullOrOneChild(pos.node_);
    } else {
      node = DelNodeWithNullOrOneChild(pos.node_);
    }
    while (node->parent_) {
      Balancing(node);
      node = node->parent_;
    }
    Balancing(node);
    --size_;
    if (!node->parent_ && root_) {
      root_ = node;
    }
  }
}

template <typename key_type, typename T, typename Compare>
void AvlTree<key_type, T, Compare>::swap(AvlTree &other) noexcept {
  using std::swap;
  swap(root_, other.root_);
  if (!begin_) {
    begin_ = new AvlNode<const key_type, T>;
  }
  swap(begin_, other.begin_);
  swap(end_, other.end_);
  swap(size_, other.size_);
}

// AvlTree Lookup
template <typename key_type, typename T, typename Compare>
typename AvlTree<key_type, T, Compare>::iterator
AvlTree<key_type, T, Compare>::find(const key_type &key) {
  iterator it;
  it = SearchNode(key, nullptr);
  return it;
}

template <typename key_type, typename T, typename Compare>
bool AvlTree<key_type, T, Compare>::contains(const key_type &key) {
  bool result = false;
  SearchNode(key, &result);
  return result;
}

// Helper function
template <typename key_type, typename T, typename Compare>
void AvlTree<key_type, T, Compare>::Copy(AvlNode<const key_type, T> *node,
                                         AvlNode<const key_type, T> *tmp) {
  tmp->parent_ = node->parent_;
  tmp->left_ = node->left_;
  tmp->right_ = node->right_;
  tmp->height_ = node->height_;
  tmp->data_ = node->data_;
}

template <typename key_type, typename T, typename Compare>
Height AvlTree<key_type, T, Compare>::get_left_right_height(
    AvlNode<const key_type, T> *node) {
  Height height;
  if (node->left_) {
    height.left = node->left_->height_;
  }
  if (node->right_) {
    height.right = node->right_->height_;
  }
  return height;
}

template <typename key_type, typename T, typename Compare>
int AvlTree<key_type, T, Compare>::Traverse(AvlNode<const key_type, T> *node) {
  if (!node) {
    return 0;
  }
  Traverse(node->left_);
  node->left_ = nullptr;
  Traverse(node->right_);
  node->right_ = nullptr;
  delete (node->data_);
  delete (node);
  return 0;
}

template <typename key_type, typename T, typename Compare>
void AvlTree<key_type, T, Compare>::DeleteNode(
    AvlNode<const key_type, T> *node) {
  node->height_ = 0;
  node->parent_ = node->left_ = node->right_ = nullptr;
  delete node->data_;
  node->data_ = nullptr;
}

template <typename key_type, typename T, typename Compare>
AvlNode<const key_type, T> *
AvlTree<key_type, T, Compare>::DelNodeWithNullOrOneChild(
    AvlNode<const key_type, T> *pos) {
  AvlNode<const key_type, T> *node = pos->parent_;
  if (pos == begin_) {
    if (begin_ != root_) {
      if (begin_->right_) {
        begin_->height_ = begin_->right_->height_;
        delete begin_->data_;
        begin_->data_ = begin_->right_->data_;
        delete begin_->right_;
        begin_->right_ = nullptr;
      } else {
        begin_->right_ = begin_->parent_->right_;
        begin_->height_ = begin_->parent_->height_;
        delete begin_->data_;
        begin_->data_ = begin_->parent_->data_;
        begin_->left_ = begin_->parent_;
        begin_->parent_ = begin_->parent_->parent_;
        delete begin_->left_;
        begin_->left_ = nullptr;
        if (begin_->parent_) {
          begin_->parent_->left_ = begin_;
        }
        if (begin_->right_) {
          begin_->right_->parent_ = begin_;
        }
      }
    } else {
      if (begin_->right_) {
        delete begin_->data_;
        begin_->data_ = begin_->right_->data_;
        begin_->height_ = begin_->right_->height_;
        delete begin_->right_;
        begin_->right_ = nullptr;
      } else {
        DeleteNode(begin_);
        root_ = nullptr;
      }
    }
    node = begin_;
  } else if (!pos->left_ && !pos->right_) {
    change_child(pos, nullptr);
  } else if ((!pos->left_ && pos->right_) || (pos->left_ && !pos->right_)) {
    if (pos->left_) {
      pos->left_->parent_ = node;
      change_child(pos, pos->left_);
    } else if (pos->right_) {
      pos->right_->parent_ = node;
      change_child(pos, pos->right_);
    }
  }
  return node;
}

template <typename key_type, typename T, typename Compare>
void AvlTree<key_type, T, Compare>::change_child(
    AvlNode<const key_type, T> *node, AvlNode<const key_type, T> *child) {
  if (node->parent_) {
    if (node->parent_->left_ == node) {
      node->parent_->left_ = child;
    } else if (node->parent_->right_ == node) {
      node->parent_->right_ = child;
    }
    DeleteNode(node);
    delete node;
  }
}

template <typename key_type, typename T, typename Compare>
typename AvlTree<key_type, T, Compare>::iterator
AvlTree<key_type, T, Compare>::SearchNode(const key_type &key, bool *find) {
  AvlNode<const key_type, T> *node = root_;
  iterator it(end_, begin_, end_);
  if (node) {
    while (node->data_->first != key && (node->left_ || node->right_)) {
      if (compare_(key, node->data_->first)) {
        if (!node->left_) {
          break;
        }
        node = node->left_;
      } else {
        if (!node->right_) {
          break;
        }
        node = node->right_;
      }
    }
    if (node->data_->first == key) {
      it.node_ = node;
      if (find) {
        *find = true;
      }
    } else {
      it.node_ = end_;
    }
  }
  return it;
}

template <typename key_type, typename T, typename Compare>
void AvlTree<key_type, T, Compare>::change_value(iterator it, T value) {
  it.node_->data_->second = value;
}

template <typename key_type, typename T, typename Compare>
void AvlTree<key_type, T, Compare>::SwapNode(
    AvlNode<const key_type, T> *first, AvlNode<const key_type, T> *second) {
  AvlNode<const key_type, T> *tmp = new AvlNode<const key_type, T>;
  Copy(first, tmp);
  if (first->right_ != second) {
    first->parent_ = second->parent_;
    first->parent_->left_ = first;
    first->right_ = second->right_;
    second->left_ = tmp->left_;
    if (second->left_) {
      second->left_->parent_ = second;
    }
    second->right_ = tmp->right_;
    if (second->right_) {
      second->right_->parent_ = second;
    }
  } else {
    first->parent_ = second;
    first->right_ = second->right_;
    second->right_ = first;
    second->left_ = tmp->left_;
  }
  if (first->right_) {
    first->right_->parent_ = first;
  }
  first->left_ = nullptr;
  second->parent_ = tmp->parent_;
  if (second->parent_) {
    if (second->parent_->left_ == first) {
      second->parent_->left_ = second;
    }
    if (second->parent_->right_ == first) {
      second->parent_->right_ = second;
    }
  }
  first->height_ = second->height_;
  second->height_ = tmp->height_;
  delete tmp;
  tmp = nullptr;
}

template <typename key_type, typename T, typename Compare>
typename AvlTree<key_type, T, Compare>::iterator
AvlTree<key_type, T, Compare>::set_iter_root(iterator it, AvlTree &other) {
  if (it.iter_root_ != other.root_) {
    it.iter_root_ = other.root_;
  }
  return it;
}

} // namespace s21

#endif //  SRC_LIBRARY_HEADERS_PART_1_AvlTree_H_