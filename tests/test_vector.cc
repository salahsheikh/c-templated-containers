#include <gtest/gtest.h>

#include "../includes/vector.h"
#include <stdlib.h>

vector_declare(int, malloc, free);

static constexpr int TESTING_SIZE = 8192;

TEST(VectorTest, VectorElasticCapacity) {
  vector_t(int) *v = vector_create(int)();
  for (int i = 0; i < TESTING_SIZE; i++) {
    vector_push_back(int)(v, i);
  }
  for (int i = 0; i < TESTING_SIZE; i++) {
    ASSERT_EQ(vector_at(int)(v, i), i);
  }

  vector_destroy(int)(v);
}

TEST(VectorTest, EmptyVector) {
  vector_t(int) *v = vector_create(int)();
  ASSERT_TRUE(vector_empty(int)(v));
  vector_destroy(int)(v);
}

TEST(VectorTest, ClearVector) {
  vector_t(int) *v = vector_create(int)();
  for (int i = 0; i < TESTING_SIZE; i++) {
    vector_push_back(int)(v, i);
  }
  vector_clear(int)(v);
  ASSERT_TRUE(vector_empty(int)(v));
  vector_destroy(int)(v);
}

TEST(VectorTest, FrontAndBackVector) {
  vector_t(int) *v = vector_create(int)();
  vector_push_back(int)(v, 0);
  vector_push_back(int)(v, 1);
  vector_push_back(int)(v, 2);
  vector_push_back(int)(v, 3);
  vector_push_back(int)(v, 4);
  ASSERT_EQ(vector_front(int)(v), 0);
  ASSERT_EQ(vector_back(int)(v), 4);
  vector_destroy(int)(v);
}

TEST(VectorTest, PopBack) {
  vector_t(int) *v = vector_create(int)();
  vector_push_back(int)(v, 0);
  vector_push_back(int)(v, 1);
  vector_push_back(int)(v, 2);
  vector_push_back(int)(v, 3);
  vector_push_back(int)(v, 4);
  ASSERT_EQ(vector_back(int)(v), 4);
  vector_pop_back(int)(v);
  ASSERT_EQ(vector_back(int)(v), 3);
  vector_pop_back(int)(v);
  ASSERT_EQ(vector_back(int)(v), 2);
  vector_pop_back(int)(v);
  ASSERT_EQ(vector_back(int)(v), 1);
  vector_pop_back(int)(v);
  ASSERT_EQ(vector_back(int)(v), 0);
  vector_destroy(int)(v);
}

TEST(VectorTest, DefaultInitialValues) {
  vector_t(int) *v = vector_create_default(int)(TESTING_SIZE, 4);
  ASSERT_EQ(vector_capacity(int)(v), TESTING_SIZE);
  for (size_t i = 0; i < TESTING_SIZE; i++) {
    ASSERT_EQ(vector_at(int)(v, i), 4);
  }
  vector_destroy(int)(v);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}