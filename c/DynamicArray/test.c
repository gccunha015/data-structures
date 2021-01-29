#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "DynamicArray.h"

void populate(dynamic_array *);
int show_menu(void);
void execute_option(int, dynamic_array *);

int main(void)
{
  int opt;
  dynamic_array array = da_create();

  do {
    opt = show_menu();
    execute_option(opt, &array);
  } while (opt != 0);

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

int is_invalid(int opt)
{
  return opt < 0 || opt > 9;
}

int show_menu(void)
{
  int opt = -1, invalid_opt;

  printf("------------------------------ MENU ------------------------------\n");
  printf(" [0] exit\n");
  printf(" [1] append\n");
  printf(" [2] insert into\n");
  printf(" [3] delete\n");
  printf(" [4] delete from\n");
  printf(" [5] search\n");
  printf(" [6] info\n");
  printf(" [7] info without values\n");
  printf(" [8] just values\n");
  printf(" [9] populate\n");
  printf("------------------------------------------------------------------\n");
  do {
    printf("What is your option? ");
    scanf("%i", &opt);
    if (invalid_opt = is_invalid(opt)) printf("Invalid option!\n");
  } while (invalid_opt);

  return opt;
}

int ask_question(char *question)
{
  int answer = 0, invalid_answer;

  do {
    printf("%s ", question);
    scanf("%i", &answer);
    if (invalid_answer = answer < 0) printf("Invalid answer!\n");
  } while (invalid_answer);

  return answer;
}

void execute_option(int opt, dynamic_array *array)
{
  int value, position;

  switch (opt) {
    case 1:
      value = ask_question("What value do you want to append?");
      da_append(value, array);
      da_values(array);
      break;
    case 2:
      value = ask_question("What value do you want to insert?");
      position = ask_question("What position do you want to insert into?");
      da_insert_into(value, position, array);
      da_values(array);
      break;
    case 3:
      da_delete(array);
      da_values(array);
      break;
    case 4:
      position = ask_question("What position do you want to delete from?");
      da_delete_from(position, array);
      da_values(array);
      break;
    case 5:
      break;
    case 6:
      da_info(1, array);
      break;
    case 7:
      da_info(0, array);
      break;
    case 8:
      da_values(array);
      break;
    case 9:
      populate(array);
      break;
    default:
      exit(0);
  }
}