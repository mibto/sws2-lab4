#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef void(*callback)(int i);
typedef struct {
char buf[128];
callback cb;
} foo_t;
void cbfun(int i) {
printf("Got %d\n", i);
}
void unused(int i) {
printf("Got %d (unused)\n", i);
}
void vuln(char* input, foo_t foo) {
strcpy(foo.buf, input);
foo.cb(strlen(input));
}
void bar(char* a) {
foo_t foo;
foo.cb = cbfun;
vuln(a, foo);
}
int main(int argc, char** argv) {
bar(argv[1]);
exit(0);
}
