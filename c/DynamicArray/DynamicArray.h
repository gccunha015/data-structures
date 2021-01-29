#define NO_VALUE 0
#define MAX_VALUES_PER_LINE 14

typedef struct dynamic_array {
  unsigned int capacity;
  unsigned int size;
  unsigned int *values;
} dynamic_array;

dynamic_array da_create(void);
void da_destroy(dynamic_array *array);
void da_insert_into(unsigned int value, unsigned int position, dynamic_array *array);
void da_append(unsigned int value, dynamic_array *array);
int da_delete_from(unsigned int position, dynamic_array *array);
int da_delete(dynamic_array *array);
void da_values(dynamic_array *array);
void da_info(int include_values, dynamic_array *array);