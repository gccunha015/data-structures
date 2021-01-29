#include <stdlib.h>
#include <stdio.h>

#include "DynamicArray.h"

dynamic_array da_create(unsigned int capacity)
{
  dynamic_array array;
  array.capacity = capacity;
  array.size = 0;
  array.values = (unsigned int *) calloc(capacity, sizeof(unsigned int));

  return array;
}

void da_destroy(dynamic_array *array)
{
  free(array->values);
}

int da_is_full(dynamic_array *array)
{
  return array->size == array->capacity;
}

int da_invalid_position(unsigned int position, dynamic_array *array)
{
  return position >= array->capacity;
}

int da_is_empty(dynamic_array *array)
{
  return array->size == 0;
}

void da_insert_into(unsigned int value, unsigned int position, dynamic_array *array)
{
  if (da_is_full(array) ||
      da_invalid_position(position, array)) return;
  
  array->values[position] = value;
  array->size++;
}

void da_insert(unsigned int value, dynamic_array *array)
{
  if (da_is_full(array)) return;

  da_insert_into(value, array->size, array);
}

int da_delete_from(unsigned int position, dynamic_array *array)
{
  if (da_is_empty(array) ||
      da_invalid_position(position, array)) return 0;

  array->values[position] = NO_VALUE;
  array->size--;

  return 1;
}

int da_delete(unsigned int value, dynamic_array *array)
{
  if (da_is_empty(array)) return 0;

  for (unsigned int i = 0; i < array->size; i++) {
    if (array->values[i] == value) return da_delete_from(i, array);
  }

  return 0;
}

void da_values(dynamic_array *array)
{
  printf("  Values:\n");
  printf("    [\n      ");
  for (unsigned int i = 0; i < array->capacity; i++) {
    printf("%03i ", array->values[i]);
    if ((i+1) % MAX_VALUES_PER_LINE == 0 &&
        (i+1) < array->capacity) printf("\n      ");
  }
  printf("\n    ]\n");
}

void da_info(int include_values, dynamic_array *array)
{
  printf("------------------------------ INFO ------------------------------\n");
  printf("  Capacity: %u\n", array->capacity);
  printf("  Size: %u\n", array->size);
  if (include_values) da_values(array);
  printf("------------------------------------------------------------------\n");
}