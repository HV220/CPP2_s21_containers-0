#include <gtest/gtest.h>

#include <list>

#include "../library/headers/s21_containers.h"
#include "headers/PresidentTest.h"
#include "headers/UniversityTest.h"

using namespace s21;

class S21List_test : public ::testing::Test {
protected:
  void SetUp() override {}
  S21List<int> list_empty;
  S21List<int> list_1_ = S21List<int>(5);
  S21List<int> list_2_ = {1, 2, 3, 4, 5};
  S21List<int> list_3_ = {6, 7, 8, 9, 10};
  S21List<int> list_4_ = {1, 2, 3, 8, 9};
  S21List<int> list_5_ = {1, 1, 2, 3, 2, 4, 5, 5, 6};
  S21List<std::string> list_string = {"a", "b", "c", "d"};
  S21List<int> list_sort = {9, 8, 7, 6, 6, 6,    5,  8, 8,
                            9, 4, 3, 2, 1, -153, -1, 0};
  S21List<std::string> list_sort_string = {"ad", "bc", "bd", "ac"};
  S21List<UniversityTest> list_obj;

  std::list<int> test_empty;
  std::list<int> test1 = std::list<int>(5);
  std::list<int> test2 = {1, 2, 3, 4, 5};
  std::list<int> test3 = {6, 7, 8, 9, 10};
  std::list<int> test4 = {1, 2, 3, 8, 9};
  std::list<int> test5 = {1, 1, 2, 3, 2, 4, 5, 5, 6};
  std::list<std::string> test_string = {"a", "b", "c", "d"};
  std::list<int> test_sort = {9, 8, 7, 6, 6, 6,    5,  8, 8,
                              9, 4, 3, 2, 1, -153, -1, 0};
  std::list<std::string> test_sort_string = {"ad", "bc", "bd", "ac"};
  std::list<UniversityTest> test_obj;
};

TEST_F(S21List_test, constructors) {
  EXPECT_EQ(list_empty.size(), test_empty.size());
  EXPECT_EQ(list_1_.size(), test1.size());
  EXPECT_EQ(list_2_.size(), test2.size());
  EXPECT_EQ(list_2_.front(), test2.front());

  S21List<int> list_3_(list_2_);
  std::list<int> test3(test2);
  auto it = list_3_.begin();
  auto it_or = test3.begin();
  EXPECT_EQ(*it, *it_or);
  ++it, ++it_or;
  EXPECT_EQ(*it, *it_or);
  --it, --it_or;
  EXPECT_EQ(*it, *it_or);
  ++it, ++it_or;
  EXPECT_EQ(*it, *it_or);
  ++it, ++it_or;
  EXPECT_EQ(*it, *it_or);

  S21List<int> list_4_ = std::move(list_3_);
  std::list<int> test4 = std::move(test3);
  EXPECT_EQ(list_4_.size(), test4.size());
  EXPECT_EQ(list_3_.size(), test3.size());
  it = list_4_.begin();
  it_or = test4.begin();
  EXPECT_EQ(*it, *it_or);
  ++it, ++it_or;
  EXPECT_EQ(*it, *it_or);
  --it, --it_or;
  EXPECT_EQ(*it, *it_or);
  ++it, ++it_or;
  EXPECT_EQ(*it, *it_or);
  ++it, ++it_or;
  EXPECT_EQ(*it, *it_or);
}

TEST_F(S21List_test, BonusEmplace) {
  auto it = list_2_.begin();
  auto it_or = test2.begin();
  list_2_.emplace(it, 2);
  test2.emplace(it_or, 2);
  auto it_test = list_2_.begin();
  auto it_test_or = test2.begin();
  while (it_test != list_2_.end() || it_test_or != test2.end()) {
    EXPECT_EQ(*it_test, *it_test_or);
    ++it_test, ++it_test_or;
  }
}

TEST_F(S21List_test, BonusEmplaceBack) {
  list_2_.emplace_back(2);
  test2.emplace_back(2);
  auto it_test = list_2_.begin();
  auto it_test_or = test2.begin();
  while (it_test != list_2_.end() || it_test_or != test2.end()) {
    EXPECT_EQ(*it_test, *it_test_or);
    ++it_test, ++it_test_or;
  }
}

TEST_F(S21List_test, BonusEmplaceFront) {
  list_2_.emplace_front(2);
  test2.emplace_front(2);
  auto it_test = list_2_.begin();
  auto it_test_or = test2.begin();
  while (it_test != list_2_.end() || it_test_or != test2.end()) {
    EXPECT_EQ(*it_test, *it_test_or);
    ++it_test, ++it_test_or;
  }
  EXPECT_EQ(list_2_.size(), test2.size());
}