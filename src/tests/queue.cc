#include <gtest/gtest.h>

#include <queue>

#include "../library/headers/s21_containers.h"
#include "headers/PresidentTest.h"
#include "headers/UniversityTest.h"

using namespace s21;

class S21Queue_test : public ::testing::Test {
protected:
  void SetUp() override {}
  S21Queue<int> mylib;
  std::queue<int> orig;
};

TEST_F(S21Queue_test, constuctors_tests) {
  // default
  EXPECT_EQ(mylib.size(), orig.size());
  mylib.push(1);
  orig.push(1);
  EXPECT_EQ(mylib.front(), orig.front());
  mylib.push(2);
  orig.push(2);
  EXPECT_EQ(mylib.front(), orig.front());
  EXPECT_EQ(mylib.back(), orig.back());
  S21Queue<int> mylib_copy(mylib);
  std::queue<int> orig_copy(orig);
  EXPECT_EQ(mylib_copy.size(), orig_copy.size());
  EXPECT_EQ(mylib_copy.front(), orig_copy.front());
  EXPECT_EQ(mylib_copy.back(), orig_copy.back());
  //   // initializer_list
  S21Queue<int> mylib_initializer = {1, 2};
  EXPECT_EQ(mylib_initializer.size(), orig_copy.size());
  EXPECT_EQ(mylib_initializer.front(), orig_copy.front());
  EXPECT_EQ(mylib_initializer.back(), orig_copy.back());
  //   // move
  S21Queue<int> mylib_move(std::move(mylib));
  std::queue<int> orig_move(std::move(orig));
  EXPECT_EQ(mylib_copy.size(), orig_copy.size());
  EXPECT_EQ(mylib_copy.front(), orig_copy.front());
  EXPECT_EQ(mylib_copy.back(), orig_copy.back());
  EXPECT_EQ(mylib.size(), orig.size()); // empty after move
}

TEST_F(S21Queue_test, assignment_tests) {
  mylib.push(1);
  orig.push(1);
  mylib.push(2);
  orig.push(2);
  S21Queue<int> mylib_assign;
  std::queue<int> orig_assign;
  // copy
  mylib_assign = mylib;
  orig_assign = orig;
  EXPECT_EQ(mylib_assign.size(), orig_assign.size());
  EXPECT_EQ(mylib_assign.front(), orig_assign.front());
  EXPECT_EQ(mylib_assign.back(), orig_assign.back());
  EXPECT_EQ(mylib.size(), orig.size());
  // move
  S21Queue<int> mylib_assign_move;
  std::queue<int> orig_assign_move;
  mylib_assign_move = std::move(mylib);
  orig_assign_move = std::move(orig);
  EXPECT_EQ(mylib_assign_move.size(), orig_assign_move.size());
  EXPECT_EQ(mylib_assign_move.front(), orig_assign_move.front());
  EXPECT_EQ(mylib_assign_move.back(), orig_assign_move.back());
  EXPECT_EQ(mylib.size(), orig.size());
}

TEST_F(S21Queue_test, access_and_capacity_tests) {
  EXPECT_EQ(mylib.empty(), orig.empty());
  EXPECT_EQ(mylib.size(), orig.size());
  mylib.push(1);
  orig.push(1);
  EXPECT_EQ(mylib.front(), orig.front());
  mylib.push(2);
  orig.push(2);
  EXPECT_EQ(mylib.front(), orig.front());
  EXPECT_EQ(mylib.back(), orig.back());
}

TEST_F(S21Queue_test, modifiers_tests) {
  EXPECT_EQ(mylib.empty(), orig.empty());
  EXPECT_EQ(mylib.size(), orig.size());
  mylib.push(1);
  orig.push(1);
  EXPECT_EQ(mylib.front(), orig.front());
  mylib.push(2);
  orig.push(2);
  EXPECT_EQ(mylib.front(), orig.front());
  EXPECT_EQ(mylib.back(), orig.back());
  mylib.push(3);
  orig.push(3);
  mylib.push(4);
  orig.push(4);
  mylib.push(5);
  orig.push(5);
  // swap
  S21Queue<int> mylib_swap;
  std::queue<int> orig_swap;
  mylib_swap.swap(mylib);
  orig_swap.swap(orig);
  EXPECT_EQ(mylib.size(), orig.size());
  EXPECT_EQ(mylib_swap.size(), orig_swap.size());
  // pop
  while (1) {
    mylib_swap.pop();
    orig_swap.pop();
    if (mylib_swap.empty() || orig_swap.empty())
      break;
    EXPECT_EQ(mylib_swap.front(), orig_swap.front());
    EXPECT_EQ(mylib_swap.back(), orig_swap.back());
  }
}

TEST_F(S21Queue_test, bonus_emplace_back) {
  S21Queue<std::string> queue_string;
  std::queue<std::string> orig_string;
  queue_string.emplace_back("1");
  orig_string.emplace("1");
  queue_string.emplace_back("2");
  orig_string.emplace("2");
  queue_string.emplace_back("3");
  orig_string.emplace("3");
  queue_string.emplace_back("4");
  orig_string.emplace("4");
  queue_string.emplace_back("5");
  orig_string.emplace("5");
  // pop
  while (1) {
    queue_string.pop();
    orig_string.pop();
    if (queue_string.empty() || orig_string.empty())
      break;
    EXPECT_EQ(queue_string.front(), orig_string.front());
    EXPECT_EQ(queue_string.back(), orig_string.back());
  }
}