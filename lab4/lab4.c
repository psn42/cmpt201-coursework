#define _DEFAULT_SOURCE
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 128

struct header {
  uint64_t size;
  struct header *next;
};

void print_out(char *format, void *data, size_t data_size) {
  char buf[BUF_SIZE];
  ssize_t len = snprintf(buf, BUF_SIZE, format,
                         data_size == sizeof(uint64_t) ? *(uint64_t *)data
                                                       : *(void **)data);
  if (len < 0) {
    perror("snprintf");
    exit(EXIT_FAILURE);
  }
  write(STDOUT_FILENO, buf, len);
}

int main(void) {
  const int TOTAL = 256;
  const int BLOCK = TOTAL / 2;

  void *mem = sbrk(TOTAL);
  if (mem == (void *)-1) {
    perror("srbk");
    return 1;
  }

  struct header *first = (struct header *)mem;
  struct header *second = (struct header *)((char *)mem + BLOCK);

  first->size = BLOCK;
  first->next = NULL;

  second->size = BLOCK;
  second->next = first;

  size_t header_sz = sizeof(struct header);
  size_t data_len = BLOCK - header_sz;

  unsigned char *data1 = (unsigned char *)first + header_sz;
  unsigned char *data2 = (unsigned char *)second + header_sz;

  memset(data1, 0, data_len);
  memset(data2, 1, data_len);
  printf("first block:      %p\n", (void *)first);
  printf("second block:     %p\n", (void *)second);

  print_out("first block size:  %" PRIu64 "\n", &first->size, sizeof(uint64_t));
  print_out("first block next:  %p\n", &first->next, sizeof(void *));
  print_out("second block size: %" PRIu64 "\n", &second->size,
            sizeof(uint64_t));
  print_out("secong block next: %p\n", &second->next, sizeof(void *));

  for (size_t i = 0; i < data_len; i++) {
    printf("%u\n", (unsigned)data1[i]);
  }
  for (size_t i = 0; i < data_len; i++) {
    printf("%u\n", (unsigned)data2[i]);
  }

  return 0;
}
