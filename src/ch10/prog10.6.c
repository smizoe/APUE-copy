#include "apue.h"
#include <sys/wait.h>

int main(int argc, char *argv[])
{
  pid_t pid;

  if(signal(SIGCLD, sig_cld) == SIG_ERR)
  return 0;
}
