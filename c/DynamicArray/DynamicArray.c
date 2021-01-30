#include <stdlib.h>
#include <stdio.h>

#include "DynamicArray.h"

dynamic_array da_create(void)
{
  dynamic_array array;
  array.capacity = 1;
  array.size = 0;
  array.values = (unsigned int *) calloc(array.capacity, sizeof(unsigned int));

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
  return position < 0 || position > array->size;
}

int da_is_empty(dynamic_array *array)
{
  return array->size == 0;
}

void da_increase_capacity(dynamic_array *array)
{
  unsigned int *temp;

  array->capacity *= 2;

  temp = (unsigned int *) realloc(array->values, array->capacity * sizeof(unsigned int));
  if (!temp) exit(1);
  else array->values = temp;

  for (int i = array->size; i < array->capacity; i++) {
    array->values[i] = NO_VALUE;
  }
}

void da_decrease_capacity(dynamic_array *array)
{
  unsigned int *temp;

  array->capacity /= 2;

  temp = (unsigned int *) realloc(array->values, array->capacity * sizeof(unsigned int));
  if (!temp) exit(1);
  else array->values = temp;
}

int da_can_decrease_capacity(dynamic_array *array)
{
  return array->size == (array->capacity / 2) &&
          array->size > 1;
}

void da_shift_left(unsigned int position, dynamic_array *array)
{
  for(int i = array->size; i > position; i--) {
    array->values[i] = array->values[i - 1];
  }
}

void da_shift_right(unsigned int position, dynamic_array *array)
{
  for(int i = position; i < (array->size - 1); i++) {
    array->values[i] = array->values[i + 1];
  }
}

void da_insert_into(unsigned int value, unsigned int position, dynamic_array *array)
{
  if (da_invalid_position(position, array)) return;
  if (da_is_full(array)) da_increase_capacity(array);
  
  da_shift_left(position, array);
  array->values[position] = value;
  array->size++;
}

void da_append(unsigned int value, dynamic_array *array)
{
  da_insert_into(value, array->size, array);
}

void da_delete_from(unsigned int position, dynamic_array *array)
{
  if (da_is_empty(array) ||
      da_invalid_position(position, array)) return;

  da_shift_right(position, array);
  array->values[array->size - 1] = NO_VALUE;
  array->size--;

  if (da_can_decrease_capacity(array)) da_decrease_capacity(array);
}

void da_delete(dynamic_array *array)
{
  da_delete_from((array->size - 1), array);
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