#include <stdio.h>
#include <string.h>

char *secret = "deadabba";

int main(int argc, char *argv[]) {

  int i;

  /* amplify */
  for (i = 0; i < 1000000; i++) {
    if (!strcmp(argv[1], secret)) {
      printf("\nMy secret: I love Assembly language\n");
      return 0;
    }
  }

  return 1;
}
