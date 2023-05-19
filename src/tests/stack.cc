#include <gtest/gtest.h>

#include <stack>

#include "../library/headers/s21_containers.h"

#include "headers/PresidentTest.h"
#include "headers/UniversityTest.h"

using namespace s21;

class S21Stack_test : public ::testing::Test {
protected:
  void SetUp() override {}
  S21Stack<int> stack;
  std::stack<int> orig;
};

TEST_F(S21Stack_test, constuctors_tests) {
  // default
  EXPECT_EQ(stack.size(), orig.size());
  stack.push(1);
  orig.push(1);
  EXPECT_EQ(stack.top(), orig.top());
  stack.push(2);
  orig.push(2);
  EXPECT_EQ(stack.size(), orig.size());
  //   // copy
  S21Stack<int> stack_copy(stack);
  std::stack<int> orig_copy(orig);
  EXPECT_EQ(stack_copy.size(), orig_copy.size());
  EXPECT_EQ(stack_copy.top(), orig_copy.top());
  //   // initializer_list
  S21Stack<int> queue_initializer = {1, 2};
  EXPECT_EQ(queue_initializer.size(), orig_copy.size());
  EXPECT_EQ(queue_initializer.top(), 1);
  //   // move
  S21Stack<int> stack_move(std::move(stack));
  std::stack<int> orig_move(std::move(orig));
  EXPECT_EQ(stack_move.size(), orig_move.size());
  EXPECT_EQ(stack_move.top(), orig_move.top());
  EXPECT_EQ(stack.size(), orig.size()); // empty after move
}

TEST_F(S21Stack_test, assignment_tests) {
  stack.push(1);
  orig.push(1);
  stack.push(2);
  orig.push(2);
  S21Stack<int> stack_assign;
  std::stack<int> orig_assign;
  // copy
  stack_assign = stack;
  orig_assign = orig;
  EXPECT_EQ(stack_assign.size(), orig_assign.size());
  EXPECT_EQ(stack_assign.top(), orig_assign.top());
  EXPECT_EQ(stack.size(), orig.size());
  // move
  S21Stack<int> stack_assign_move;
  std::stack<int> orig_assign_move;
  stack_assign_move = std::move(stack);
  orig_assign_move = std::move(orig);
  EXPECT_EQ(stack_assign_move.size(), orig_assign_move.size());
  EXPECT_EQ(stack_assign_move.top(), orig_assign_move.top());
  EXPECT_EQ(stack.size(), orig.size());
}

TEST_F(S21Stack_test, access_and_capacity_tests) {
  EXPECT_EQ(stack.empty(), orig.empty());
  EXPECT_EQ(stack.size(), orig.size());
  stack.push(1);
  orig.push(1);
  EXPECT_EQ(stack.top(), orig.top());
  stack.push(2);
  orig.push(2);
  EXPECT_EQ(stack.top(), orig.top());
}

TEST_F(S21Stack_test, modifiers_tests) {
  EXPECT_EQ(stack.empty(), orig.empty());
  EXPECT_EQ(stack.size(), orig.size());
  stack.push(1);
  orig.push(1);
  EXPECT_EQ(stack.top(), orig.top());
  stack.push(2);
  orig.push(2);
  EXPECT_EQ(stack.top(), orig.top());
  stack.push(3);
  orig.push(3);
  stack.push(4);
  orig.push(4);
  stack.push(5);
  orig.push(5);
  // swap
  S21Stack<int> stack_swap;
  std::stack<int> orig_swap;
  stack_swap.swap(stack);
  orig_swap.swap(orig);
  EXPECT_EQ(stack.size(), orig.size());
  EXPECT_EQ(stack_swap.size(), orig_swap.size());
  // pop
  while (1) {
    stack_swap.pop();
    orig_swap.pop();
    if (stack_swap.empty() || orig_swap.empty())
      break;
    EXPECT_EQ(stack_swap.top(), orig_swap.top());
  }
}

TEST_F(S21Stack_test, bonus_emplace_back) {
  S21Stack<std::string> stack_string;
  std::stack<std::string> orig_string;
  stack_string.emplace_front("1");
  orig_string.emplace("1");
  stack_string.emplace_front("2");
  orig_string.emplace("2");
  stack_string.emplace_front("3");
  orig_string.emplace("3");
  stack_string.emplace_front("4");
  orig_string.emplace("4");
  stack_string.emplace_front("5");
  orig_string.emplace("5");
  // pop
  while (1) {
    stack_string.pop();
    orig_string.pop();
    if (stack_string.empty() || orig_string.empty())
      break;
    EXPECT_EQ(stack_string.top(), orig_string.top());
  }
}