#include <stdio.h>
#include <string.h>
#include <errno.h>


int main(int argc, char *argv[]) {

  FILE *inputfile;
  int inputint;
  int valid = 1; /* assume not valid until proved otherwise */


  /* REQ: Write a C program accepting such a file  ... */

  if (argc != 2) {
    fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
    return -1;
  }

  if (!(inputfile = fopen(argv[1], "rb"))) {
    fprintf(stderr, "Coudln't open file '%s', error %d (%s)\n",
            argv[1], errno, strerror(errno));
    return -1;
  }

  /*  REQ: ... which checks:
    First Token is an Integer  */

  if (fscanf(inputfile, "%i", &inputint) == 1) {
    /* First token was an integer */
    printf("Got int: %i\n", inputint);

    /* REQ: Second Token is a String
       NOTE: since no Token separator is specified, anything goes
       so it is enough to check there are characters left and
       since nothing have to be done with the string we don't
       even have to read it
      */

    if (!feof(inputfile)) {
      /* REQ: Only two Tokens present
        NOTE: since nothing is excluded from allowed characters in string
        and no token separator is speciefied then there can't be more than
       two tokens ever with these requirements
        */
      printf("Not yet at EOF so there was a string as well\n");
      valid = 0;
    }
  }

  /* clean-up */

  fclose(inputfile);

  /* If the content is as above - return code 0, otherwise 1 */

  return valid;
}
