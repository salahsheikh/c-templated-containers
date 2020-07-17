#include <gtest/gtest.h>

#include "../includes/queue.h"

queue_declare(int);

TEST(QueueTest, QueueCreation) {
  queue_t(int) *q = queue_create(int)(3);
  ASSERT_EQ(q->capacity, 3);
  queue_destroy(int)(q);
}

TEST(QueueTest, QueuePushAccessPatterns) {
  queue_t(int) *q = queue_create(int)(3);
  queue_push(int)(q, 1);
  queue_push(int)(q, 2);

  int read;
  ASSERT_EQ(queue_front(int)(q, &read), QUEUE_OP_SUCCESS);
  ASSERT_EQ(read, 1);

  queue_pop(int)(q);
  ASSERT_EQ(queue_front(int)(q, &read), QUEUE_OP_SUCCESS);
  ASSERT_EQ(read, 2);

  queue_destroy(int)(q);
}

TEST(QueueTest, EmptyQueue) {
  queue_t(int) *q = queue_create(int)(3);
  ASSERT_EQ(queue_pop(int)(q), EMPTY_QUEUE_ERROR);
  ASSERT_TRUE(queue_empty(int)(q));
  queue_destroy(int)(q);
}

TEST(QueueTest, FullQueue) {
  queue_t(int) *q = queue_create(int)(3);
  ASSERT_EQ(queue_push(int)(q, 1), QUEUE_OP_SUCCESS);
  ASSERT_EQ(queue_push(int)(q, 1), QUEUE_OP_SUCCESS);
  ASSERT_EQ(queue_push(int)(q, 1), QUEUE_OP_SUCCESS);
  ASSERT_EQ(queue_push(int)(q, 1), FULL_QUEUE_ERROR);
  queue_destroy(int)(q);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}