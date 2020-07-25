#include <stdbool.h>
#include <stdlib.h>

#ifndef VECTOR_H
#define VECTOR_H

/* All vectors are created with a default initial capacity. */
#define DEFAULT_INITIAL_CAPACITY ((size_t)10)

#define vector_name(name, T)     vector_##name##_##T
#define vector_t(T)              vector_name(t, T)

#define vector_create(T)         vector_name(create, T)
#define vector_create_default(T) vector_name(create_default, T)
#define vector_destroy(T)        vector_name(destroy, T)

#define vector_reserve(T)        vector_name(reserve, T)

#define vector_push_back(T)      vector_name(push_back, T)
#define vector_pop_back(T)       vector_name(pop_back, T)
#define vector_front(T)          vector_name(front, T)
#define vector_back(T)           vector_name(back, T)
#define vector_at(T)             vector_name(at, T)

/* Indicates whether the vector is empty. */
#define vector_empty(T)          vector_name(empty, T)

/* Clears all entries held by the vector. */
#define vector_clear(T)          vector_name(clear, T)
#define vector_size(T)           vector_name(size, T)
#define vector_capacity(T)       vector_name(capacity, T)

#define vector_declare(T)                                                      \
  typedef struct {                                                             \
    T *data;                                                                   \
    size_t size;                                                               \
    size_t capacity;                                                           \
  } vector_t(T);                                                               \
                                                                               \
  vector_t(T) * vector_create(T)() {                                           \
    vector_t(T) *created = (vector_t(T) *)malloc(sizeof(vector_t(T)));         \
    created->capacity = DEFAULT_INITIAL_CAPACITY;                              \
    created->data = (T *)malloc(sizeof(T) * created->capacity);                \
    created->size = 0;                                                         \
    return created;                                                            \
  }                                                                            \
                                                                               \
  vector_t(T) *                                                                \
      vector_create_default(T)(size_t initial_capacity, T default_val) {       \
    vector_t(T) *created = (vector_t(T) *)malloc(sizeof(vector_t(T)));         \
    created->capacity = initial_capacity;                                      \
    created->data = (T *)malloc(sizeof(T) * created->capacity);                \
    for (size_t i = 0; i < initial_capacity;)                                  \
      created->data[i++] = default_val;                                        \
    created->size = initial_capacity;                                          \
    return created;                                                            \
  }                                                                            \
                                                                               \
  void vector_reserve(T)(vector_t(T) * v, size_t new_capacity) {               \
    if (new_capacity <= v->capacity)                                           \
      return;                                                                  \
    T *move = (T *)malloc(sizeof(T) * new_capacity);                           \
    for (size_t i = 0; i < v->size; i++)                                       \
      move[i] = v->data[i];                                                    \
    free(v->data);                                                             \
    v->data = move;                                                            \
  }                                                                            \
                                                                               \
  bool vector_empty(T)(vector_t(T) * v) { return v->size == 0; }               \
                                                                               \
  void vector_push_back(T)(vector_t(T) * v, T new_val) {                       \
    if (v->size == v->capacity) {                                              \
      v->capacity = v->capacity << ((size_t)1);                                \
      T *replacement = (T *)malloc(sizeof(T) * v->capacity);                   \
      for (size_t i = 0; i < v->size; i++) {                                   \
        replacement[i] = v->data[i];                                           \
      };                                                                       \
      free(v->data);                                                           \
      v->data = replacement;                                                   \
    }                                                                          \
    v->data[v->size++] = new_val;                                              \
  }                                                                            \
                                                                               \
  void vector_pop_back(T)(vector_t(T) * v) { --(v->size); }                    \
                                                                               \
  T vector_at(T)(vector_t(T) * v, size_t idx) { return v->data[idx]; }         \
                                                                               \
  void vector_destroy(T)(vector_t(T) * v) {                                    \
    free(v->data);                                                             \
    free(v);                                                                   \
  }                                                                            \
                                                                               \
  size_t vector_size(T)(vector_t(T) * v) { return v->size; }                   \
                                                                               \
  size_t vector_capacity(T)(vector_t(T) * v) { return v->capacity; }           \
                                                                               \
  void vector_clear(T)(vector_t(T) * v) {                                      \
    free(v->data);                                                             \
    v->capacity = DEFAULT_INITIAL_CAPACITY;                                    \
    v->data = (T *)malloc(sizeof(T) * v->capacity);                            \
    v->size = 0;                                                               \
  }                                                                            \
                                                                               \
  T vector_back(T)(vector_t(T) * v) { return vector_at(T)(v, v->size - 1); }   \
                                                                               \
  T vector_front(T)(vector_t(T) * v) { return vector_at(T)(v, 0); }

#endif // VECTOR_H
