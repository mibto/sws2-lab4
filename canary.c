#include <string.h>
#include <stdlib.h>
#include <stdio.h>
void vuln(char* input) {
char buf[16];
strcpy(buf, input);
}
int main(int argc, char** argv) {
if(argc == 2)
vuln(argv[1]);
else
printf("Need more arguments!\n");
return 0;
}
