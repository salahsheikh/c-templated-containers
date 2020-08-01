# c-templated-containers

A header-only library of templated data-structures in C. Using the preprocessor, template meta-programming can be used to wrap containers around arbitrary types.
The implemented containers are inspired by the C++ STL library and serve the same functionality. The implemented containers are:
* Stack
* Queue
* Vector

## Getting Started

To use any or all of the containers, simply integrate the relevant header files from the `includes` folder into your project.

### Prerequisites (to test)

CMake and Google Test are used to test the containers.


### Example Usage

A thorough treatment of the usage of the supported containers can be found in the `tests` and `examples` folders.
Before using the containers, they must be declared with the type that they will be used with. It is important to place this declaration outside of functions and ensure that it called only once.
In its place is where the preprocessor will spawn the generated functions for the requested type.

```c
// Arbitrary custom structs
typedef struct {
  int a;
} custom_obj;
queue_declare(custom_obj);

// Primitive types
queue_declare(int);
```

Each of the containers supports a slightly different API.
T is any arbitrary type.

#### stack.h
```c
stack_t(T) * stack_create(T)(size_t initial_capacity);
void stack_destroy(T)(stack_t(T) * created);

enum STACK_RESULT stack_push(T)(stack_t(T) * q, T new_val);
enum STACK_RESULT stack_top(T)(stack_t(T) * q, T * ref);
enum STACK_RESULT stack_pop(T)(stack_t(T) * q);

/* Indicates whether the stack is empty. */
bool stack_empty(T)(stack_t(T) * s);

// Be sure to verify successful operations using the included results enum.
enum STACK_RESULT { FULL_STACK_ERROR, EMPTY_STACK_ERROR, STACK_OP_SUCCESS };
```

#### queue.h
```c
queue_t(T) * queue_create(T)(size_t capacity);
enum QUEUE_RESULT queue_push(T)(queue_t(T) * q, T new_val);
enum QUEUE_RESULT queue_front(T)(queue_t(T) * q, T * ref);
enum QUEUE_RESULT queue_back(T)(queue_t(T) * q, T * ref);
void queue_destroy(T)(queue_t(T) * created);
enum QUEUE_RESULT queue_pop(T)(queue_t(T) * q);
bool queue_empty(T)(queue_t(T) * q);

enum QUEUE_RESULT { FULL_QUEUE_ERROR, EMPTY_QUEUE_ERROR, QUEUE_OP_SUCCESS };
```

#### vector.h
```c
vector_t(T) * vector_create(T)();
vector_t(T) * vector_create_default(T)(size_t initial_capacity, T default_val);
void vector_reserve(T)(vector_t(T) * v, size_t new_capacity);
bool vector_empty(T)(vector_t(T) * v);
void vector_push_back(T)(vector_t(T) * v, T new_val);
void vector_pop_back(T)(vector_t(T) * v);
// Analogous to the .at(idx) and the [] operator overload in the C++ STL
T vector_at(T)(vector_t(T) * v, size_t idx);
void vector_destroy(T)(vector_t(T) * v);
size_t vector_size(T)(vector_t(T) * v);
size_t vector_capacity(T)(vector_t(T) * v);
void vector_clear(T)(vector_t(T) * v);
T vector_back(T)(vector_t(T) * v);
T vector_front(T)(vector_t(T) * v);
```
