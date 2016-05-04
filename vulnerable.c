#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 128

struct record {
  int version;
  int length;
  char data[MAX_LENGTH];
};

void print_hex_memory(void *mem, int size) {
  int i;
  unsigned char *p = (unsigned char *)mem;
  for (i=0;i<size;i++) {
    if (i%16==0)
      printf("\n");
    printf("0x%02x ", p[i]);
  }
  printf("\n");
}
int print_next_record(FILE* fp) {
  struct record my_record;
  int OK = 0;
  int chars = fread(&my_record.version, 1, sizeof(int), fp);
  chars += fread(&my_record.length, 1, sizeof(int), fp);
  if((ferror(fp)) ) {
    printf("Error.\n");
    return 1;
  } else if( feof(fp) ) {
    if(chars == 0) {
      printf("EOF.\n");
    } else {
      printf("Incomplete records.\n");
    }
    return 1;
  }
  if (my_record.version < 2) {
    /* Should be an error, but we can cope with it */
    printf("Warning: Deprecated record version - parsing anyway.\n");
  } else if (my_record.length > MAX_LENGTH || my_record.length <= 0) {
    printf("Incorrect record length.\n");
    return 1;
  }
  fread(my_record.data, 1, my_record.length, fp);
  if( (ferror(fp)) || feof(fp) ) {
    printf("Incomplete record.\n");
    return 1;
  }
  print_hex_memory(my_record.data, my_record.length);
  return OK;
}
int main(int argc, char** argv) {
  if(argc == 2) {
    FILE* pf = fopen(argv[1], "r");
    if (!pf) {
      printf("Unable to open file!\n");
      return 1;
    }
    while( print_next_record(pf) == 0);
    return 0;
  }
  printf("Need more arguments!\n");
  return 1;
}
