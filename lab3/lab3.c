#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HISTORY_SIZE 5

void add_to_history(char *line, char *history[], int *next, int *count) {
  if (*count == HISTORY_SIZE && history[*next] != NULL) {
    free(history[*next]);
  }

  history[*next] = line;
  *next = (*next + 1) % HISTORY_SIZE;

  if (*count < HISTORY_SIZE) {
    (*count)++;
  }
}

void print_history(char *history[], int count, int next) {
  int start = (count == HISTORY_SIZE) ? next : 0;

  for (int i = 0; i < count; i++) {
    int idx = (start + i) % HISTORY_SIZE;
    printf("%s", history[idx]);
  }
}

int main(void) {
  char *history[HISTORY_SIZE] = {NULL};
  int count = 0;
  int next = 0;
  char *line = NULL;
  size_t len = 0;

  while (1) {
    printf("Enter Input: ");
    ssize_t read = getline(&line, &len, stdin);
    if (read == -1) {
      break;
    }

    char *copy = strdup(line);
    if (!copy) {
      fprintf(stderr, "Memory allocation failed\n");
      break;
    }

    add_to_history(copy, history, &next, &count);

    if (strcmp(copy, "print\n") == 0) {
      print_history(history, count, next);
    }
  }

  for (int i = 0; i < HISTORY_SIZE; i++) {
    free(history[i]);
  }
  free(line);

  return 0;
}
