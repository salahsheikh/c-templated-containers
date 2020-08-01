#include <assert.h>

#include "../includes/queue.h"
#include <stdlib.h>

typedef struct {
  int a;
} custom_obj;

queue_declare(custom_obj, malloc, free);

int main()
{
  queue_t(custom_obj)* q = queue_create(custom_obj)(10);
  queue_destroy(custom_obj)(q);
  return EXIT_SUCCESS;
}