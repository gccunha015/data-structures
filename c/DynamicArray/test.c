#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "DynamicArray.h"

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

  return 0;
}

void populate(unsigned int elements, dynamic_array *array)
{
  int max = 1000;

  srand(time(NULL));

  for (int i = 0; i < elements; i++) {
    da_append(rand() % max, array);
  }
}

int is_invalid(int opt)
{
  return opt < 0 || opt > 10;
}

int show_menu(void)
{
  int opt = -1, invalid_opt;

  printf("------------------------------ MENU ------------------------------\n");
  printf(" [00] exit\n");
  printf(" [01] append\n");
  printf(" [02] insert into\n");
  printf(" [03] delete\n");
  printf(" [04] delete from\n");
  printf(" [05] search\n");
  printf(" [06] info\n");
  printf(" [07] info without values\n");
  printf(" [08] just values\n");
  printf(" [09] populate\n");
  printf(" [10] deplete\n");
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
      value = ask_question("How many random numbers do you want to append to the array?");
      populate(value, array);
      da_values(array);
      break;
    case 10:
      da_destroy(array);
      *array = da_create(); 
      break;
    default:
      da_destroy(array);
      exit(0);
  }
}