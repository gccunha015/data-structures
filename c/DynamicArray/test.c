#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "DynamicArray.h"

void populate(dynamic_array *);

int main(void)
{
  dynamic_array array = da_create(14);

  da_values(&array);
  populate(&array);
  da_values(&array);

  da_destroy(&array);

  return 0;
}

void populate(dynamic_array *array)
{
  int max = array->capacity * 10;

  srand(time(NULL));

  for (int i = 0; i < array->capacity; i++) {
    da_insert(rand() % max, array);
  }
}
