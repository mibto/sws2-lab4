#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void dummy() {
  void* p_memset = &memset;
  void* p_strcpy = &strcpy;
  void* p_memcpy = &memcpy;
  void* p_exit = &exit;
}

void vuln(char* str) {
  char buf[128];
  FILE* pf = fopen(str, "r");
  fread(buf, 1, 256, pf);
}

unsigned int q = 0x12345678;
unsigned int x = 0x12345678;

void magic() {
  if(q == 0x11111111 && x == 0x22222222)
    printf("SUCCESS\n");
  else
    printf("%x %x\n", q, x);
}

int main(int argc, char** argv) {
  if(argc != 2) {
    printf("Need more arguments!\n");
    return 1;
  }
  printf("OK\n");
  vuln(argv[1]);
  return 0;
}
