#include <assert.h>

#include "../includes/stack.h"

typedef struct {
  int a;
} custom_obj;

stack_declare(custom_obj);

int main()
{
  stack_t(custom_obj)* s = stack_create(custom_obj)(10);
  stack_destroy(custom_obj)(s);
  return EXIT_SUCCESS;
}