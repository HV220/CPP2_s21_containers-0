#include <gtest/gtest.h>

#include <iostream>
#include <set>

#include "../library/headers/s21_containers.h"
#include "../library/headers/s21_containersplus.h"
#include "headers/PresidentTest.h"
#include "headers/UniversityTest.h"

using namespace s21;

class S21Set_test : public ::testing::Test {
protected:
  void SetUp() override {}
  S21Set<int> set_empty;
  S21Set<int> set{1, 0, 4, 7, -5};
  S21Set<int> set3{10, 8, 6};
  S21Set<int> std_set_test{7, -5, 1, 0, 4};
  S21Set<std::string> set_s;
  std::set<int> std_set_empty;
  std::set<int> std_set{1, 0, 4, 7, -5};
  std::set<int> std_set3{10, 8, 6};
  std::set<std::string> std_set_s;
  S21Set<int> S21_set_ten{1, 2, 56, 76, 123, 53, 78, 43, 21, 100};
  std::set<int> std_set_ten{1, 2, 56, 76, 123, 53, 78, 43, 21, 100};
};

TEST_F(S21Set_test, construct_il) {
  EXPECT_EQ(set.size(), std_set.size());
  auto it = set.begin();
  for (const auto &std_data : std_set) {
    EXPECT_EQ(it->first, std_data);
    ++it;
  }
}

TEST_F(S21Set_test, construct_copy) {
  S21Set<int> set4(set3);
  std::set<int> std_set4(std_set3);
  EXPECT_EQ(set4.size(), std_set4.size());
  auto it = set4.begin();
  for (const auto &std_data : std_set4) {
    EXPECT_EQ(it->first, std_data);
    ++it;
  }
}

TEST_F(S21Set_test, construct_move) {
  S21Set<int> set4(std::move(set3));
  std::set<int> std_set4(std::move(std_set3));
  auto it = set4.begin();
  for (const auto &std_data : std_set4) {
    EXPECT_EQ(it->first, std_data);
    ++it;
  }
}

TEST_F(S21Set_test, operator_copy) {
  set_empty = set3;
  std_set_empty = std_set3;
  auto it = set_empty.begin();
  for (const auto &std_data : std_set_empty) {
    EXPECT_EQ(it->first, std_data);
    ++it;
  }
}

TEST_F(S21Set_test, operator_move) {
  set_empty = std::move(set3);
  std_set_empty = std::move(std_set3);
  auto it = set_empty.begin();
  for (const auto &std_data : std_set_empty) {
    EXPECT_EQ(it->first, std_data);
    ++it;
  }
}

TEST_F(S21Set_test, swap) {
  S21Set<int> set5{15, 12, 20};
  std::set<int> std_set5{15, 12, 20};
  set3.swap(set5);
  std_set3.swap(std_set5);
  auto it = set3.begin();
  for (const auto &std_data : std_set3) {
    EXPECT_EQ(it->first, std_data);
    ++it;
  }

  auto it2 = set5.begin();
  for (const auto &std_data : std_set5) {
    EXPECT_EQ(it2->first, std_data);
    ++it2;
  }

  set_empty.swap(set5);
  std_set_empty.swap(std_set5);
  auto it3 = set5.begin();
  for (const auto &std_data : std_set5) {
    EXPECT_EQ(it3->first, std_data);
    ++it3;
  }

  auto it4 = set_empty.begin();
  for (const auto &std_data : std_set_empty) {
    EXPECT_EQ(it4->first, std_data);
    ++it4;
  }
}

TEST_F(S21Set_test, size) {
  EXPECT_EQ(set_empty.size(), std_set_empty.size());
  EXPECT_EQ(set.size(), std_set.size());
}

TEST_F(S21Set_test, max_size) {
  EXPECT_EQ(set.max_size(), std_set_test.max_size());
}

TEST_F(S21Set_test, clear) {
  EXPECT_EQ(set.size(), std_set.size());
  EXPECT_EQ(set_empty.size(), std_set_empty.size());
  set.clear();
  std_set.clear();
  set_empty.clear();
  std_set_empty.clear();
  EXPECT_EQ(set_empty.size(), std_set_empty.size());
  EXPECT_EQ(set.size(), std_set.size());
}

TEST_F(S21Set_test, it_begin) {
  auto it = set.begin();
  auto std_it = std_set.begin();
  EXPECT_EQ(it->first, *std_it);
}

TEST_F(S21Set_test, it_end) {
  auto it = set.end();
  auto std_it = std_set.end();
  --it;
  --std_it;
  EXPECT_EQ(it->first, *std_it);
}

TEST_F(S21Set_test, empty) {
  EXPECT_TRUE(set_empty.empty());
  EXPECT_TRUE(std_set_empty.empty());
}

TEST_F(S21Set_test, insert) {
  auto pr1 = set_s.insert("25");
  auto pr2 = set_s.insert("55");
  auto pr3 = set_s.insert("55");
  auto std_pr1 = std_set_s.insert("25");
  auto std_pr2 = std_set_s.insert("55");
  auto std_pr3 = std_set_s.insert("55");

  auto it2 = set_s.begin();
  for (const auto &std_data : std_set_s) {
    EXPECT_EQ(it2->first, std_data);
    ++it2;
  }

  EXPECT_EQ(set_s.size(), std_set_s.size());
  EXPECT_EQ(pr1.second, std_pr1.second);
  EXPECT_EQ(pr2.second, std_pr2.second);
  EXPECT_EQ(pr3.second, std_pr3.second);
}

TEST_F(S21Set_test, contains) {
  S21Set<char> example = {'a', 'b'};
  EXPECT_TRUE(example.contains('a'));
  EXPECT_FALSE(example.contains('t'));
}

TEST_F(S21Set_test, erase) {
  set_s.insert("1");
  set_s.insert("2");
  std_set_s.insert("1");
  std_set_s.insert("2");
  set3.erase((set3.begin()));
  std_set3.erase((std_set3.begin()));
  set_s.erase((set_s.begin()));
  std_set_s.erase((std_set_s.begin()));

  auto it = set3.begin();
  for (const auto &std_data : std_set3) {
    EXPECT_EQ(it->first, std_data);
    ++it;
  }

  auto it2 = set_s.begin();
  for (const auto &std_data : std_set_s) {
    EXPECT_EQ(it2->first, std_data);
    ++it2;
  }
}

TEST_F(S21Set_test, emplace) {
  auto pr2 = set_empty.emplace(10);
  auto std_pr2 = std_set_empty.emplace(10);
  auto pr3 = set_s.emplace("a");
  auto std_pr3 = std_set_s.emplace("a");

  EXPECT_EQ((*pr2[0].first).first, (*std_pr2.first));
  EXPECT_EQ(pr2[0].second, std_pr2.second);

  EXPECT_EQ((*pr3[0].first).first, (*std_pr3.first));
  EXPECT_EQ(pr3[0].second, std_pr3.second);

  auto pr4 = set_s.emplace("a");
  auto std_pr4 = std_set_s.emplace("a");
  EXPECT_EQ(pr4[0].second, std_pr4.second);
}

TEST_F(S21Set_test, merge) {
  S21Set<std::string> ma_{"apple", "x", "banana"};
  S21Set<std::string> mb_{"zorro", "batman", "x", "alpaca"};
  S21Set<std::string> u_;
  std::set<std::string> ma{"apple", "x", "banana"};
  std::set<std::string> mb{"zorro", "batman", "x", "alpaca"};
  std::set<std::string> std_u;
  u_.merge(ma_);
  std_u.merge(ma);
  EXPECT_EQ(ma_.size(), ma.size());
  u_.merge(mb_);
  std_u.merge(mb);
  EXPECT_EQ(mb_.size(), mb.size());
  EXPECT_EQ(mb_.begin()->first, *mb.begin());

  auto it2 = u_.begin();
  for (const auto &std_data : std_u) {
    EXPECT_EQ(it2->first, std_data);
    ++it2;
  }
}

TEST_F(S21Set_test, find) {
  set_s = {"apple", "x", "banana"};
  std_set_s = {"apple", "x", "banana"};
  for (const auto &data : std_set_s) {
    auto iter = set_s.find(data);
    auto iter2 = std_set_s.find(data);
    EXPECT_EQ(iter->first, *iter2);
  }

  for (const auto &data : std_set) {
    auto iter = set.find(data);
    auto iter2 = std_set.find(data);
    EXPECT_EQ(iter->first, *iter2);
  }

  auto iter = set_s.find("data");
  auto iter2 = std_set_s.find("data");
  EXPECT_EQ(iter, set_s.end());
  EXPECT_EQ(iter2, std_set_s.end());
}

TEST_F(S21Set_test, functions_erase_alot) {

  S21Set<int>::iterator it1 = S21_set_ten.find(76);
  std::set<int>::iterator it2 = std_set_ten.find(76);
  S21_set_ten.erase(it1);
  std_set_ten.erase(it2);
  it1 = S21_set_ten.find(123);
  it2 = std_set_ten.find(123);
  S21_set_ten.erase(it1);
  std_set_ten.erase(it2);
  it1 = S21_set_ten.find(43);
  it2 = std_set_ten.find(43);
  S21_set_ten.erase(it1);
  std_set_ten.erase(it2);
  ASSERT_EQ(S21_set_ten.size(), std_set_ten.size());
}