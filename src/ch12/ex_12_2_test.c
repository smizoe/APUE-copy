#include "apue.h"
extern int putenv_r(char *str);
extern char **environ;

int main(int argc, char const* argv[])
{
  if(putenv_r("FOO=bar") < 0)
    err_sys("putenv_r error");

  printf("environment variables:\n");
  for (int i = 0; environ[i] != NULL; i++) {
    printf("%s\n", environ[i]);
  }
  return 0;
}
