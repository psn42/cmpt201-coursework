#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char *buff = NULL;
  size_t size = 0;

  printf("Please enter some text: ");

  ssize_t num_char = getline(&buff, &size, stdin);

  if (num_char == -1) {
    perror("getline failed");
    exit(EXIT_FAILURE);
  }

  if (num_char > 0 && buff[num_char - 1] == '\n') {
    buff[num_char - 1] = '\0';
  }

  printf("\nTokens:\n");

  char *token;
  char *saveptr;
  const char *delimiter = " ";

  token = strtok_r(buff, delimiter, &saveptr);

  while (token != NULL) {
    printf("  %s\n", token);
    token = strtok_r(NULL, delimiter, &saveptr);
  }

  free(buff);

  return 0;
}
