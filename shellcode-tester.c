#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  if(argc == 2) {
    char buf[128];
    FILE* pf = fopen(argv[1], "r");
    fread(buf, 1, 256, pf);
    void (*code)(void);
    code = (void (*)(void))&buf;
    code();
  }
  else {
    printf("Need more arguments!\n");
  }
}
