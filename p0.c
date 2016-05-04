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

unsigned int q = 0;

void magic(int a, int b) {
  if(a == 0xDEADBEEF && b == 0xCAFEBABE && q == 0x55555555)
    printf("SUCCESS\n");
  else
    printf("%x %x %x\n", a, b, q);
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
