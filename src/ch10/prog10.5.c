#include "apue.h"
#include <pwd.h>

static void
my_alarm(int signo)
{
  struct passwd *rootptr;
  signal(SIGALRM,my_alarm);
  printf("in signal handler\n");
  if ((rootptr = getpwnam("jenkins")) == NULL)
    err_sys("getpwnam(jenkins) error");
  printf("foo\n");
  alarm(1);
}

int main(int argc, char *argv[])
{
  struct passwd *ptr;
  signal(SIGALRM,my_alarm);
  alarm(1);
  printf("alarm set (in main)\n");
  for (;;){
    if((ptr = getpwnam("smizoe")) == NULL)
      err_sys("getpwnam error");
    if(strcmp(ptr->pw_name, "smizoe") != 0)
      printf("return value corrupted!, pw_name = %s\n", ptr->pw_name);
  }
}
