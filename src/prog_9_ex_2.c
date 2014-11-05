#include "apue.h"

int main(int argc, char *argv[])
{
  int pid;
  pid_t sid;
  if((pid = fork()) < 0)
    err_sys("fork error");
  else if (pid == 0) {
    sid = setsid();
    printf("child is now a session leader with pgid %d\n", sid);
    sleep(10);
    exit(0);
  }

  if(waitpid(pid, NULL, 0) != pid)
    err_sys("waitpid() error");
  exit(0);
}
