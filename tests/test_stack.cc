#include <gtest/gtest.h>

#include "../includes/stack.h"

stack_declare(int);

TEST(QueueTest, Creation) {
  stack_t(int) *q = stack_create(int)(3);
  ASSERT_EQ(q->capacity, 3);
  stack_destroy(int)(q);
}

TEST(QueueTest, PushAccessPatterns) {
  stack_t(int) *q = stack_create(int)(3);
  stack_push(int)(q, 1);
  stack_push(int)(q, 2);

  int read;
  ASSERT_TRUE((stack_top(int)(q, &read) == STACK_OP_SUCCESS));
  ASSERT_EQ(2, read);
  stack_pop(int)(q);

  ASSERT_EQ(stack_top(int)(q, &read), STACK_OP_SUCCESS);
  ASSERT_EQ(read, 1);
  stack_pop(int)(q);

  /* After being popped twice, the stack is now empty */
  ASSERT_EQ(stack_top(int)(q, &read), EMPTY_STACK_ERROR);

  stack_destroy(int)(q);
}

TEST(QueueTest, EmptyQueue) {
  stack_t(int) *q = stack_create(int)(3);
  stack_pop(int)(q);
  ASSERT_EQ(stack_pop(int)(q), EMPTY_STACK_ERROR);
  ASSERT_TRUE(stack_empty(int)(q));
  stack_destroy(int)(q);
}

TEST(QueueTest, FullQueue) {
  stack_t(int) *q = stack_create(int)(3);
  ASSERT_EQ(stack_push(int)(q, 1), STACK_OP_SUCCESS);
  ASSERT_EQ(STACK_OP_SUCCESS, stack_push(int)(q, 1));
  ASSERT_EQ(STACK_OP_SUCCESS, stack_push(int)(q, 1));
  ASSERT_EQ(FULL_STACK_ERROR, stack_push(int)(q, 1));
  stack_destroy(int)(q);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}