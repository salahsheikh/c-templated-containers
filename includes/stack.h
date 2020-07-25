#include <stdlib.h>
#include <stdbool.h>

#ifndef STACK_H
#define STACK_H

#define stack_name(name, T)   stack_##name##_##T
#define stack_t(T)            stack_name(t, T)

#define stack_create(T)       stack_name(create, T)
#define stack_destroy(T)      stack_name(destroy, T)

#define stack_push(T)         stack_name(push, T)
#define stack_top(T)          stack_name(top, T)
#define stack_pop(T)          stack_name(pop, T)

/* Indicates whether the stack is empty. */
#define stack_empty(T)        stack_name(empty, T)

#define stack_declare(T)                                                       \
  typedef struct {                                                             \
    T *data;                                                                   \
    size_t current;                                                            \
    size_t capacity;                                                           \
  } stack_t(T);                                                                \
                                                                               \
  stack_t(T) * stack_create(T)(size_t capacity) {                              \
    stack_t(T) *created = (stack_t(T) *)malloc(sizeof(stack_t(T)));            \
    created->capacity = capacity;                                              \
    created->data = (T *)malloc(sizeof(T) * capacity);                         \
    created->current = 0;                                                      \
    return created;                                                            \
  }                                                                            \
                                                                               \
  bool stack_empty(T)(stack_t(T) * s) { return s->current == 0; }              \
                                                                               \
  enum STACK_RESULT stack_push(T)(stack_t(T) * q, T new_val) {                 \
    if (q->current == q->capacity)                                             \
      return FULL_STACK_ERROR;                                                 \
    q->data[q->current++] = new_val;                                           \
    return STACK_OP_SUCCESS;                                                   \
  }                                                                            \
                                                                               \
  enum STACK_RESULT stack_top(T)(stack_t(T) * q, T * ref) {                    \
    if (0 == q->current)                                                       \
      return EMPTY_STACK_ERROR;                                                \
    *ref = q->data[q->current - 1];                                            \
    return STACK_OP_SUCCESS;                                                   \
  }                                                                            \
                                                                               \
  void stack_destroy(T)(stack_t(T) * created) {                                \
    free(created->data);                                                       \
    free(created);                                                             \
  }                                                                            \
                                                                               \
  enum STACK_RESULT stack_pop(T)(stack_t(T) * q) {                             \
    if (q->current == 0)                                                       \
      return EMPTY_STACK_ERROR;                                                \
    q->current--;                                                              \
    return STACK_OP_SUCCESS;                                                   \
  }

enum STACK_RESULT { FULL_STACK_ERROR, EMPTY_STACK_ERROR, STACK_OP_SUCCESS };

#endif // STACK_H
