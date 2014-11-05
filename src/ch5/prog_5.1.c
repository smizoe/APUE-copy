#include "ourhdr.h"

int main(int argc, char *argv[])
{
  int c;
  while ( (c = getc(stdin)) != EOF)
    if (putc(c, stdout) == EOF)
      err_sys("output errror");

  if (ferror(stdin))
    err_sys("input error");
  
  return 0;
}
