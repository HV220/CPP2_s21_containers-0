#include <gtest/gtest.h>

#include <iostream>
#include <iterator>
#include <map>

#include "../library/headers/s21_containers.h"
#include "../library/headers/s21_containersplus.h"
#include "headers/PresidentTest.h"
#include "headers/UniversityTest.h"

using namespace s21;

using std::cout;
using std::endl;

class S21Map_test : public ::testing::Test {
protected:
  void SetUp() override {}
  S21Map<int, int> map_empty;
  S21Map<int, int> map{{1, 25}, {0, 43}, {4, 4}, {7, 11}, {-5, 28}};
  S21Map<int, int> map3{{10, 50}, {8, 60}, {6, 70}};
  S21Map<int, std::string> map_s;
  std::map<int, int> std_map_empty;
  std::map<int, int> std_map{{1, 25}, {0, 43}, {4, 4}, {7, 11}, {-5, 28}};
  std::map<int, int> std_map3{{10, 50}, {8, 60}, {6, 70}};
  std::map<int, std::string> std_map_s;
};

TEST_F(S21Map_test, construct_il) {
  for (const auto &pair : std_map3) {
    EXPECT_EQ(map3.at(pair.first), std_map3.at(pair.first));
  }
}

TEST_F(S21Map_test, construct_copy) {
  S21Map<int, int> map4(map3);
  std::map<int, int> std_map4(std_map3);
  for (auto &pair : std_map4) {
    EXPECT_EQ(map4.at(pair.first), std_map4.at(pair.first));
  }
}

TEST_F(S21Map_test, construct_move) {
  S21Map<int, int> map4(std::move(map3));
  std::map<int, int> std_map4(std::move(std_map3));
  for (const auto &pair : std_map4) {
    EXPECT_EQ(map4.at(pair.first), std_map4.at(pair.first));
  }
}

TEST_F(S21Map_test, operator_copy) {
  map_empty = map3;
  std_map_empty = std_map3;
  for (auto &pair : std_map_empty) {
    EXPECT_EQ(map_empty.at(pair.first), std_map_empty.at(pair.first));
  }
}

TEST_F(S21Map_test, operator_move) {
  map_empty = std::move(map3);
  std_map_empty = std::move(std_map3);
  for (const auto &pair : std_map_empty) {
    EXPECT_EQ(map_empty.at(pair.first), std_map_empty.at(pair.first));
  }
}

TEST_F(S21Map_test, swap) {
  S21Map<int, int> map5{{15, 25}, {12, 30}, {20, 50}};
  std::map<int, int> std_map5{{15, 25}, {12, 30}, {20, 50}};
  map3.swap(map5);
  std_map3.swap(std_map5);
  for (const auto &pair : std_map3) {
    EXPECT_EQ(map3.at(pair.first), std_map3.at(pair.first));
  }

  for (const auto &pair : std_map5) {
    EXPECT_EQ(map5.at(pair.first), std_map5.at(pair.first));
  }

  map_empty.swap(map5);
  std_map_empty.swap(std_map5);
  for (const auto &pair : std_map_empty) {
    EXPECT_EQ(map_empty.at(pair.first), std_map_empty.at(pair.first));
  }

  for (const auto &pair : std_map5) {
    EXPECT_EQ(map5.at(pair.first), std_map5.at(pair.first));
  }
}

TEST_F(S21Map_test, size) {
  EXPECT_EQ(map_empty.size(), std_map_empty.size());
  EXPECT_EQ(map.size(), std_map.size());
}

TEST_F(S21Map_test, max_size) { EXPECT_EQ(map.max_size(), std_map.max_size()); }

TEST_F(S21Map_test, it_begin) {
  auto it = map.begin();
  auto std_it = std_map.begin();
  EXPECT_EQ(it->first, std_it->first);
}

TEST_F(S21Map_test, it_end) {
  auto it = map.end();
  auto std_it = std_map.end();
  --it;
  --std_it;
  EXPECT_EQ(it->first, std_it->first);
}

TEST_F(S21Map_test, at) {
  for (const auto &pair : std_map) {
    EXPECT_EQ(map.at(pair.first), std_map.at(pair.first));
  }
  EXPECT_ANY_THROW(map.at(9));
  EXPECT_ANY_THROW(map.at(9));
}

TEST_F(S21Map_test, operator_brkt) {
  map[0];
  map = std::move(map);
  map[1] = 35;
  map[9];
  std_map[0];
  std_map[1] = 35;
  std_map[9];
  EXPECT_EQ(map[1], 35);
  EXPECT_EQ(map[0], std_map[0]);
  EXPECT_EQ(map[1], std_map[1]);
  EXPECT_EQ(map[9], std_map[9]);

  map_s.insert(std::pair(1, "25"));
  map_s.insert(std::pair(3, "50"));
  std_map_s.insert(std::pair{1, "25"});
  std_map_s.insert(std::pair{3, "50"});
  map_s[1] = "43";
  map_s[3];
  map_s[9];
  std_map_s[1] = "43";
  std_map_s[3];
  std_map_s[9];
  EXPECT_EQ(map_s[1], std_map_s[1]);
  EXPECT_EQ(map_s[3], std_map_s[3]);
  EXPECT_EQ(map_s[9], std_map_s[9]);
}

TEST_F(S21Map_test, empty) {
  EXPECT_TRUE(map_empty.empty());
  EXPECT_TRUE(std_map_empty.empty());
}

TEST_F(S21Map_test, insert_value_type) {
  auto pr1 = map_s.insert(std::pair(1, "25"));
  auto pr2 = map_s.insert(std::pair(2, "55"));
  auto std_pr1 = std_map_s.insert(std::pair(1, "25"));
  auto std_pr2 = std_map_s.insert(std::pair(2, "55"));
  EXPECT_EQ((*pr1.first).first, (*std_pr1.first).first);
  EXPECT_EQ((*pr2.first).first, (*std_pr2.first).first);
  EXPECT_EQ((*pr1.first).second, (*std_pr1.first).second);
  EXPECT_EQ((*pr2.first).second, (*std_pr2.first).second);
}

TEST_F(S21Map_test, insert_key_value) {
  auto pr1 = map_s.insert(1, "25");
  auto pr2 = map_s.insert(2, "55");
  auto std_pr1 = std_map_s.insert(std::pair(1, "25"));
  auto std_pr2 = std_map_s.insert(std::pair(2, "55"));
  EXPECT_EQ((*pr1.first).first, (*std_pr1.first).first);
  EXPECT_EQ((*pr2.first).first, (*std_pr2.first).first);
  EXPECT_EQ((*pr1.first).second, (*std_pr1.first).second);
  EXPECT_EQ((*pr2.first).second, (*std_pr2.first).second);
}

TEST_F(S21Map_test, contains) {
  S21Map<int, char> example = {{1, 'a'}, {2, 'b'}};
  std::map<int, char> std_example = {{1, 'a'}, {2, 'b'}};
  EXPECT_TRUE(example.contains(2));
  EXPECT_FALSE(example.contains(5));
}

TEST_F(S21Map_test, insert_or_assign) {
  auto pr1 = map.insert_or_assign(9, 35);
  auto pr2 = std_map.insert_or_assign(9, 35);

  EXPECT_EQ(pr1.second, pr2.second);
  EXPECT_EQ((*(pr1.first)).second, (*(pr2.first)).second);
  auto pr3 = map.insert_or_assign(9, 48);
  auto pr4 = std_map.insert_or_assign(9, 48);
  EXPECT_EQ(pr3.second, pr4.second);
  EXPECT_EQ((*(pr1.first)).second, (*(pr2.first)).second);

  map_s.insert(std::pair(1, "25"));
  auto pr_s1 = map_s.insert_or_assign(9, "35");
  std_map_s.insert(std::pair{1, "25"});
  auto pr_s2 = std_map_s.insert_or_assign(9, "35");

  EXPECT_EQ(pr_s1.second, pr_s2.second);
  EXPECT_EQ((*(pr_s1.first)).second, (*(pr_s2.first)).second);
  auto pr_s3 = map_s.insert_or_assign(9, "48");
  auto pr_s4 = std_map_s.insert_or_assign(9, "48");
  EXPECT_EQ(pr_s3.second, pr_s4.second);
  EXPECT_EQ((*(pr_s3.first)).second, (*(pr_s4.first)).second);
}

TEST_F(S21Map_test, emplace) {
  auto pr3 = map_s.emplace(1, "a");
  auto std_pr3 = std_map_s.emplace(1, "a");
  EXPECT_EQ((*pr3[0].first).first, (*std_pr3.first).first);
  EXPECT_EQ((*pr3[0].first).second, (*std_pr3.first).second);
}

TEST_F(S21Map_test, clear) {
  EXPECT_EQ(map.size(), std_map.size());
  EXPECT_EQ(map_empty.size(), std_map_empty.size());
  map.clear();
  std_map.clear();
  map_empty.clear();
  std_map_empty.clear();
  EXPECT_EQ(map_empty.size(), std_map_empty.size());
  EXPECT_EQ(map.size(), std_map.size());
  EXPECT_ANY_THROW(map.at(1));
  EXPECT_ANY_THROW(std_map.at(1));
}

TEST_F(S21Map_test, erase) {
  map_s.insert(1, "25");
  map_s.insert(2, "55");
  std_map_s.insert(std::pair(1, "25"));
  std_map_s.insert(std::pair(2, "55"));
  map3.erase((map3.begin()));
  std_map3.erase((std_map3.begin()));
  map_s.erase((map_s.begin()));
  std_map_s.erase((std_map_s.begin()));

  for (auto const &it : map3) {
    EXPECT_EQ(map3.at(it.first), std_map3.at(it.first));
  }

  for (auto const &it : map_s) {
    EXPECT_EQ(map_s.at(it.first), std_map_s.at(it.first));
  }
}

TEST_F(S21Map_test, erase2) {
  for (auto i = 0; i < 100; ++i) {
    map_empty.insert({i, i});
    std_map_empty.insert({i, i});
  }
  for (auto i = 10000; i > 0; --i) {
    map_empty.insert({i, i});
    std_map_empty.insert({i, i});
  }

  for (auto i = -10000; i < 0; ++i) {
    map_empty.insert({i, i});
    std_map_empty.insert({i, i});
  }

  for (auto i = 0;; ++i) {
    if (std_map_empty.empty())
      break;
    map_empty.erase(map_empty.begin());
    std_map_empty.erase(std_map_empty.begin());
  }
}

TEST_F(S21Map_test, merge) {
  S21Map<int, std::string> ma_{{1, "apple"}, {5, "pear"}, {10, "banana"}};
  S21Map<int, std::string> mb_{
      {2, "zorro"}, {4, "batman"}, {5, "X"}, {8, "alpaca"}};
  S21Map<int, std::string> u_;
  std::map<int, std::string> ma{{1, "apple"}, {5, "pear"}, {10, "banana"}};
  std::map<int, std::string> mb{
      {2, "zorro"}, {4, "batman"}, {5, "X"}, {8, "alpaca"}};
  std::map<int, std::string> std_u;
  u_.merge(ma_);
  std_u.merge(ma);
  EXPECT_EQ(ma_.size(), ma.size());
  u_.merge(mb_);
  std_u.merge(mb);
  EXPECT_EQ(mb_.size(), mb.size());
  EXPECT_EQ(mb_.at(5), mb.at(5));

  for (auto const &kv : u_)
    EXPECT_EQ(u_.at(kv.first), std_u.at(kv.first));
}
