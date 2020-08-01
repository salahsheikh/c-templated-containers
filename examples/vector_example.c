#include <assert.h>

#include "../includes/vector.h"
#include <stdlib.h>

typedef struct {
  int a;
} custom_obj;

vector_declare(custom_obj, malloc, free);

int main()
{
  vector_t(custom_obj)* v_instance = vector_create(custom_obj)();

  for (int i = 0; i < 20; i++) {
    vector_push_back(custom_obj)(v_instance, (custom_obj){ 1 });
  }

  int sum = 0;
  while (!vector_empty(custom_obj)(v_instance)) {
    custom_obj returned = vector_back(custom_obj)(v_instance);
    sum += returned.a;

    vector_pop_back(custom_obj)(v_instance);
  }

  assert(sum == 20);

  vector_destroy(custom_obj)(v_instance);
  return EXIT_SUCCESS;
}