#include <ctype.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_BUF 15
#define MAX_USERS 20
#define DEF_WAIT 750000

typedef enum group {
  GROUP_1,
  GROUP_2,
} Group;

typedef struct user {
  Group group;
  uint64_t age;
} User;

/* Function Prototypes */
int trim(char *input);
int wait_us(uint32_t time);
int clear_screen(void);
int convert_to_uint64(const char *input, uint64_t *output);
int insert_data(User *u);
int calc_mean_group1(const User *users, size_t len, double *out);
int calc_mean_group2(const User *users, size_t len, double *out);
int calc_mean_total(const User *users, size_t len, double *out);

int main(void) {
  User users[MAX_USERS];
  double mean_total = 0.0, mean_g1 = 0.0, mean_g2 = 0.0;
  size_t count = 0;

  while (1) {

    if (wait_us(DEF_WAIT)) {
      fprintf(stderr, "Error: wait_us() failed.\n");
      return EXIT_FAILURE;
    }

    if (clear_screen()) {
      fprintf(stderr, "Error: clear_screen() failed.\n");
      return EXIT_FAILURE;
    }

    printf("This program receives group and age data for %d individuals.\n",
           MAX_USERS);

    for (size_t i = 0; i < MAX_USERS; i++) {
      if (insert_data(&users[i])) {
        fprintf(stderr, "Error: failed to insert data for user %zu.\n", i);
        return EXIT_FAILURE;
      }
      count++;
    }

    if (calc_mean_group1(users, count, &mean_g1)) {
      fprintf(stderr, "Error: failed to calculate mean for group 1.\n");
      return EXIT_FAILURE;
    }

    if (calc_mean_group2(users, count, &mean_g2)) {
      fprintf(stderr, "Error: failed to calculate mean for group 2.\n");
      return EXIT_FAILURE;
    }

    if (calc_mean_total(users, count, &mean_total)) {
      fprintf(stderr, "Error: failed to calculate total mean.\n");
      return EXIT_FAILURE;
    }

    printf("Mean age (Group 1): %.1lf\n"
           "Mean age (Group 2): %.1lf\n"
           "Mean age (All groups): %.1lf\n",
           mean_g1, mean_g2, mean_total);
  }

  return EXIT_SUCCESS;
}

/* --- Utility Functions --- */

int trim(char *input) {
  size_t len = strlen(input);
  if (len == 0)
    return 1;

  size_t start = 0;
  while (start < len && isspace((unsigned char)input[start]))
    start++;

  size_t end = len;
  while (end > start && isspace((unsigned char)input[end - 1]))
    end--;

  memmove(input, input + start, end - start);
  input[end - start] = '\0';
  return 0;
}

int wait_us(uint32_t time) { return usleep(time) ? 1 : 0; }

int clear_screen(void) { return system("clear") ? 1 : 0; }

int convert_to_uint64(const char *input, uint64_t *output) {
  if (!input || !output)
    return 1;
  char *endptr = NULL;
  *output = strtoull(input, &endptr, 10);
  if (*endptr != '\0')
    return 1;
  return 0;
}

int insert_data(User *u) {
  if (!u)
    return 1;

  char buf[MAX_BUF];
  printf("Enter group (1 or 2): ");
  if (!fgets(buf, sizeof(buf), stdin))
    return 1;
  trim(buf);
  if (strcmp(buf, "1") == 0)
    u->group = GROUP_1;
  else if (strcmp(buf, "2") == 0)
    u->group = GROUP_2;
  else
    return 1;

  printf("Enter age: ");
  if (!fgets(buf, sizeof(buf), stdin))
    return 1;
  trim(buf);
  if (convert_to_uint64(buf, &u->age))
    return 1;

  return 0;
}

int calc_mean_group1(const User *users, size_t len, double *out) {
  if (!users || !out || len == 0)
    return 1;
  double sum = 0.0;
  size_t count = 0;
  for (size_t i = 0; i < len; i++) {
    if (users[i].group == GROUP_1) {
      sum += users[i].age;
      count++;
    }
  }
  if (count == 0)
    return 1;
  *out = sum / count;
  return 0;
}

int calc_mean_group2(const User *users, size_t len, double *out) {
  if (!users || !out || len == 0)
    return 1;
  double sum = 0.0;
  size_t count = 0;
  for (size_t i = 0; i < len; i++) {
    if (users[i].group == GROUP_2) {
      sum += users[i].age;
      count++;
    }
  }
  if (count == 0)
    return 1;
  *out = sum / count;
  return 0;
}

int calc_mean_total(const User *users, size_t len, double *out) {
  if (!users || !out || len == 0)
    return 1;
  double sum = 0.0;
  for (size_t i = 0; i < len; i++) {
    sum += users[i].age;
  }
  *out = sum / len;
  return 0;
}
