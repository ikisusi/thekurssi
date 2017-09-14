#include <stdio.h>
#include <string.h>

char buffer[16] = "foobar";
char secret[16] = "CSE-Oulu";

/* char *secret = "CSE-Oulu"; */

int testfun(void) {
  printf("\nEnter security code to print secret>");
  fread(buffer, 1, 16, stdin);
  if (strcmp(buffer, secret)) {
    printf("\nWrong code! You entered: %s\n", buffer);
    return(0);
  } else {
    return(1);
  }
}

int main(void) {

  if(testfun()) {
    printf("\nMy secret: I love Assembly language\n");
  }
  return(0);
}
