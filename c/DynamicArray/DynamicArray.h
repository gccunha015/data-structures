#define NO_VALUE 0
#define MAX_VALUES_PER_LINE 14

typedef struct dynamic_array {
  int capacity;
  int size;
  unsigned int *values;
} dynamic_array;

dynamic_array da_create(void);
void da_destroy(dynamic_array *array);
void da_insert_into(unsigned int value, int position, dynamic_array *array);
void da_append(unsigned int value, dynamic_array *array);
void da_delete_from(int position, dynamic_array *array);
void da_delete(dynamic_array *array);
int da_search(unsigned int value, dynamic_array *array);
void da_values(dynamic_array *array);
void da_info(int include_values, dynamic_array *array);