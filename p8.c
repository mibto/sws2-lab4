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
  char buf[64];
  FILE* pf = fopen(str, "r");
  fread(buf, 1, 256, pf);
}

int a, b, c;

int foo(int x) {
  a = x;
  b = x;
  c = x;
}

int magic(int q, int x) {
  if(a == 0xCAFEDEAD && a == b && a == c && (q - x) == 3)
    printf("SUCCESS\n");
  else
    printf("%x %x %x", q, x, a);
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
