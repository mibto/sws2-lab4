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

char buf[] = "deadbeef";
char fub[] = "cafebabe";

void magic(int a) {
  if(a == 16 && strcmp(buf, fub) == 0)
    printf("SUCCESS\n");
  else
    printf("%x %s %s\n", a, buf, fub);
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
