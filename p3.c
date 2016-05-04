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

int i = 0;

void vuln(char* str) {
  char buf[128];
  FILE* pf = fopen(str, "r");
  i = fread(buf, 1, 256, pf);
}


int magic(int q, int x) {
  if(q != x && q > 3 && q < 20 && i == 200)
    printf("SUCCESS\n");
  else
    printf("%x %x %x", q, x, i);
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
