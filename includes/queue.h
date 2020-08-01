#include <stdbool.h>

#ifndef QUEUE_H
#define QUEUE_H

/*
 * `queue.h` implements a ring buffer backed a fixed-size array.
 * To use, `queue_declare(type)` must be called outside of a function.
 * All queue methods are suffixed with the type name enclosed with
 * parenthesis. For example:
 *    queue_create(int)(args);
 * The specialized name corresponds to the name given in `queue_declare`.
 */

#define queue_name(name, T)   queue_##name##_##T
#define queue_t(T)            queue_name(t, T)

/* Creates and initializes the queue. */
#define queue_create(T)       queue_name(create, T)

/* Disposes of resources held by the queue. */
#define queue_destroy(T)      queue_name(destroy, T)

#define queue_push(T)         queue_name(push, T)
#define queue_front(T)        queue_name(front, T)
#define queue_back(T)         queue_name(back, T)
#define queue_pop(T)          queue_name(pop, T)

/* Indicates whether the queue is empty. */
#define queue_empty(T)        queue_name(empty, T)

#define queue_declare(T, M_ALLOC, M_FREE)                                      \
  typedef struct {                                                             \
    T *data;                                                                   \
    size_t write, read;                                                        \
    size_t capacity, size;                                                     \
    void *(*M_ALLOC)(unsigned);                                                \
    void (*M_FREE)(void *);                                                    \
  } queue_t(T);                                                                \
                                                                               \
  queue_t(T) * queue_create(T)(size_t capacity) {                              \
    queue_t(T) *created = (queue_t(T) *)M_ALLOC(sizeof(queue_t(T)));           \
    created->capacity = capacity;                                              \
    created->data = (T *)M_ALLOC(sizeof(T) * capacity);                        \
    created->size = 0;                                                         \
    created->read = created->write = 0;                                        \
    return created;                                                            \
  }                                                                            \
                                                                               \
  bool queue_empty(T)(queue_t(T) * q) { return q->size == 0; }                 \
                                                                               \
  enum QUEUE_RESULT queue_push(T)(queue_t(T) * q, T new_val) {                 \
    if (q->size == q->capacity)                                                \
      return FULL_QUEUE_ERROR;                                                 \
    q->data[q->write] = new_val;                                               \
    q->write = (q->write + 1) % q->capacity;                                   \
    ++(q->size);                                                               \
    return QUEUE_OP_SUCCESS;                                                   \
  }                                                                            \
                                                                               \
  enum QUEUE_RESULT queue_front(T)(queue_t(T) * q, T * ref) {                  \
    if (queue_empty(T)(q))                                                     \
      return EMPTY_QUEUE_ERROR;                                                \
    *ref = q->data[q->read];                                                   \
    return QUEUE_OP_SUCCESS;                                                   \
  }                                                                            \
                                                                               \
  enum QUEUE_RESULT queue_back(T)(queue_t(T) * q, T * ref) {                   \
    if (queue_empty(T)(q))                                                     \
      return EMPTY_QUEUE_ERROR;                                                \
    *ref = q->data[q->write - 1];                                              \
    return QUEUE_OP_SUCCESS;                                                   \
  }                                                                            \
                                                                               \
  void queue_destroy(T)(queue_t(T) * created) {                                \
    M_FREE(created->data);                                                     \
    M_FREE(created);                                                           \
  }                                                                            \
                                                                               \
  enum QUEUE_RESULT queue_pop(T)(queue_t(T) * q) {                             \
    if (q->read == q->write)                                                   \
      return EMPTY_QUEUE_ERROR;                                                \
    q->read = (q->read + 1) % q->capacity;                                     \
    --(q->size);                                                               \
    return QUEUE_OP_SUCCESS;                                                   \
  }

enum QUEUE_RESULT { FULL_QUEUE_ERROR, EMPTY_QUEUE_ERROR, QUEUE_OP_SUCCESS };

#endif // QUEUE_H
