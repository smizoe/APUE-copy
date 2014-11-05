#include "apue.h"
#include <sys/wait.h>

int main(void)
{
  pid_t pid;
  if((pid = fork()) < 0)
    err_sys("fork error");
  else if (pid == 0) {
    if ((pid = fork()) < 0 )
      err_sys("fork error");
    else if(pid > 0)
      exit(0);
    sleep(2);
    printf("second child (I am id %ld), parent pid = %ld\n", (long) getpid(), (long) getppid());
    exit(0);
  }
  printf("grand parent is waiting for %ld\n", (long) pid);
  if( waitpid(pid, NULL, 0) != pid)
    err_sys("waitpid error");

  exit(0);
}
